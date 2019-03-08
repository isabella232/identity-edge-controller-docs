#!/usr/bin/env bash

#
# Copyright 2019 ForgeRock AS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# set the AWS account variables if we are not in the container
if [ -f ../../.env ]; then
    source ../../.env
fi

# Only change these variables if you have also change them in the source code
FUNCTION_NAME="iec-custom-authorize-handler"
ROLE_NAME="iec-custom-authorize-handler-execution-role"
AUTHORIZER_NAME="iec-custom-authorizer"
TOKEN_HEADER_NAME="X-Token-Header"

cd bin/lambda

# Create AWS Lambda authorize handler
aws lambda create-function \
    --function-name ${FUNCTION_NAME} \
    --memory 128 \
    --role arn:aws:iam::${AWS_ACCOUNT_ID}:role/${ROLE_NAME} \
    --runtime go1.x \
    --zip-file fileb://handler.zip \
    --handler authhandler

# If the function has already been created, then the previous call will fail, so we try an update as well
aws lambda update-function-code \
    --function-name ${FUNCTION_NAME} \
    --zip-file fileb://handler.zip

# Add the environment variables required by the Lambda
aws lambda update-function-configuration \
    --function-name ${FUNCTION_NAME} \
    --environment Variables={AWS_PUBLISH_RESOURCE="arn:aws:iot:${AWS_REGION}:${AWS_ACCOUNT_ID}:topic/customauthtesting"}

# Create custom authorizer and associate it with Lambda
device_public_key=$(cat ../../keys/device-public.pem)
aws iot create-authorizer \
    --authorizer-name ${AUTHORIZER_NAME} \
    --authorizer-function-arn arn:aws:lambda:${AWS_REGION}:${AWS_ACCOUNT_ID}:function:${FUNCTION_NAME} \
    --token-key-name ${TOKEN_HEADER_NAME} \
    --token-signing-public-keys FIRST_KEY="${device_public_key}" \
    --status ACTIVE

# If the authorizer has already been created, then the previous call will fail, so we try an update as well
aws iot update-authorizer \
    --authorizer-name ${AUTHORIZER_NAME} \
    --authorizer-function-arn arn:aws:lambda:${AWS_REGION}:${AWS_ACCOUNT_ID}:function:${FUNCTION_NAME} \
    --token-key-name ${TOKEN_HEADER_NAME} \
    --token-signing-public-keys FIRST_KEY="${device_public_key}" \
    --status ACTIVE

# View the new authorizer properties
aws iot describe-authorizer --authorizer-name ${AUTHORIZER_NAME}

# Add Lambda invocation permissions
aws lambda add-permission \
    --function-name ${FUNCTION_NAME} \
    --principal iot.amazonaws.com \
    --source-arn arn:aws:iot:${AWS_REGION}:${AWS_ACCOUNT_ID}:authorizer/${AUTHORIZER_NAME} \
    --statement-id autherizer-statement \
    --action "lambda:InvokeFunction"

# View the Lambda function's policy that contains the invocation permissions
aws lambda get-policy --function-name ${FUNCTION_NAME}

cd - &>/dev/null
