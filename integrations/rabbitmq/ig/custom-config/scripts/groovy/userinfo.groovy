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

String accessToken = null

// extract the accessToken from the incoming request
if (request.method == 'POST') {
    // if method == 'POST' -> token is in application/x-www-form-urlencoded body
	accessToken = request.form.password?.getAt(0)
} else if (request.method == 'GET' && request.uri.query) {
    // if method == 'GET' -> token is in query
	Form f = new Form().fromQueryString(request.uri.query)
	accessToken = f.password?.getAt(0)
}
logger.info(accessToken)

request.uri.rebase(new URI("${am_protocol}://${am_host}:${am_port}" as String))
// use the userinfo endpoint to check the access token
request.uri.setPath("/openam/oauth2/userinfo")
request.uri.setQuery("realm=${am_realm}")
request.headers.put("Authorization", "Bearer ${accessToken}" as String)
request.headers.put("Host", "${am_host}:${am_port}" as String)
logger.info(request.uri.toString())
logger.info(request.headers.toString())
return next.handle(context,request)
	.then({ response ->
		logger.info(response.status.toString())
		if (response.status.isSuccessful()) {
			response.headers.put('Content-Type', 'text/plain')
			response.setEntity("allow")
		}
		return response
})
