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

export GOPATH=$(pwd)
export GOOS=linux

go get github.com/aws/aws-lambda-go/lambda

go build -o ${GOPATH}/bin/lambda/authhandler forgerock.org/cmd/lambda

cd bin/lambda
zip handler.zip ./authhandler
cd - &>/dev/null
