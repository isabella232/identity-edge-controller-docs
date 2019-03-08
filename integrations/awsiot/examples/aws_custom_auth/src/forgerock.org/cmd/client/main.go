/*
 * Copyright 2019 ForgeRock AS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

package main

import (
	"fmt"
	"net/http"
	"crypto/tls"
	"io/ioutil"
	"strings"
	"crypto"
	"github.com/dgrijalva/jwt-go"
	"crypto/rsa"
	"net/http/httputil"
	"time"
	"encoding/json"
	"crypto/rand"
	"encoding/base64"
	"flag"
)

const (
	deviceID = "Anaconda"

	authorizerName = "iec-custom-authorizer"
	authorizationTokenHeaderName = "X-Token-Header"
	devicePrivateKeyLocation = "../../keys/device-private.pem"

	bearerTokenExp = time.Minute * 5
	bearerTokenIss = deviceID
	bearerTokenSub = deviceID
)

var amIntrospectURL string
var awsPublishURL string

type oauth2Tokens struct {
	AccessToken string `json:"access_token"`
	IDToken     string `json:"id_token"`
}

type authorizationToken struct {
	AccessToken      string `json:"access_token"`
	JWTBearerToken   string `json:"jwt_bearer_token"`
	AuthorizationURL string `json:"authorization_url"`
	ClientID         string `json:"client_id"`
}

func main() {
	amURL := flag.String("am-introspect-url", "", "Provide the AM introspect URL")
	awsIoTEndpoint := flag.String("aws-iot-endpoint", "", "Provide the AWS IoT endpoint")
	flag.Parse()

	if *amURL == "" {
		panic("AM introspect URL must be provided")
	}
	if *awsIoTEndpoint == "" {
		panic("AWS IoT endpoint must be provided")
	}

	amIntrospectURL = *amURL
	awsPublishURL = fmt.Sprintf("https://%s/topics/customauthtesting", *awsIoTEndpoint)

	var err error
	var tokensJson string

	fmt.Printf("Initialising SDK... ")
	if err = initialiseSDK(); err != nil {
		panic("Initialisation request failed: " + err.Error())
	}
	fmt.Println("Done")

	fmt.Printf("Registering device (id: %s)... ", deviceID)
	if err = registerDevice(deviceID, "{}"); err != nil {
		panic("Registration request failed: " + err.Error())
	}
	fmt.Println("Done")

	fmt.Printf("Requesting OAuth 2.0 tokens for device (id: %s)... ", deviceID)
	if tokensJson, err = deviceTokens(deviceID); err != nil {
		panic("Tokens request failed: " + err.Error())
	}
	fmt.Println("Done")

	var oauth2Tokens oauth2Tokens
	err = json.Unmarshal([]byte(tokensJson), &oauth2Tokens)
	if err != nil {
		fmt.Println("Tokens response: " + tokensJson)
		panic("Failed to unmarshal tokens response: " + err.Error())
	}

	fmt.Printf("Publish message for device (id: %s)... ", deviceID)
	if err = publishMessage(authorizationTokenJson(oauth2Tokens)); err != nil {
		panic("Failed to publish message to AWS: " + err.Error())
	}
	fmt.Println("Done")
}

func signedJWTBearerToken() string {
	claims := &jwt.StandardClaims{
		Issuer:    bearerTokenIss,
		Subject:   bearerTokenSub,
		ExpiresAt: time.Now().Add(bearerTokenExp).Unix(),
		Audience:  amIntrospectURL[:len(amIntrospectURL)-11], // remove the `/introspect` part
	}
	token := jwt.NewWithClaims(jwt.SigningMethodRS256, claims)
	signedJWT, err := token.SignedString(privateKey())
	if err != nil {
		panic("Failed to sign JWT bearer token: " + err.Error())
	}
	return signedJWT
}

func authorizationTokenJson(oauth2Tokens oauth2Tokens) string {
	token := authorizationToken{
		AccessToken:      oauth2Tokens.AccessToken,
		JWTBearerToken:   signedJWTBearerToken(),
		AuthorizationURL: amIntrospectURL,
		ClientID:         deviceID,
	}
	tokenJson, err := json.Marshal(token)
	if err != nil {
		panic("Failed to marshal authorization token: " + err.Error())
	}
	return string(tokenJson)
}

func publishMessage(authorizationToken string) error {

	messageBody := strings.NewReader("{\"msg\":\"Hello from client!\"}")

	client := &http.Client{
		Transport: &http.Transport{
			TLSClientConfig: &tls.Config{
				InsecureSkipVerify: true,
			},
		},
	}
	request, err := http.NewRequest(http.MethodPost, awsPublishURL, messageBody)
	request.Header.Set("X-Amz-CustomAuthorizer-Name", authorizerName)
	request.Header.Set("X-Amz-CustomAuthorizer-Signature", tokenSignature(authorizationToken))
	request.Header.Set(authorizationTokenHeaderName, authorizationToken)

	response, err := client.Do(request)
	if err != nil {
		return err
	}
	defer response.Body.Close()

	if response.StatusCode != 200 {
		reqDump, _ := httputil.DumpRequest(request, true)
		resDump, _ := httputil.DumpResponse(response, true)
		return fmt.Errorf("invalid publish status:  %s\n\nRequest:\n%s\n\nResponse:\n%s\n",
			response.Status, string(reqDump), string(resDump))
	}
	return nil
}

func tokenSignature(token string) string {
	h := crypto.SHA256.New()
	h.Write([]byte(token))
	digest := h.Sum(nil)

	signedBytes, err := rsa.SignPKCS1v15(rand.Reader, privateKey(), crypto.SHA256, digest)
	if err != nil {
		panic("Failed to create signature for token: " + err.Error())
	}
	return base64.StdEncoding.EncodeToString(signedBytes)
}

func privateKey() *rsa.PrivateKey {
	keyData, err := ioutil.ReadFile(devicePrivateKeyLocation)
	if err != nil {
		panic("Failed to read private key: " + err.Error())
	}
	pk, err := jwt.ParseRSAPrivateKeyFromPEM(keyData)
	if err != nil {
		panic("Failed to parse private key: " + err.Error())
	}
	return pk
}
