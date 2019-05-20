<!--
 ! Copyright 2019 ForgeRock AS
 !
 ! Licensed under the Apache License, Version 2.0 (the "License");
 ! you may not use this file except in compliance with the License.
 ! You may obtain a copy of the License at
 !
 ! http://www.apache.org/licenses/LICENSE-2.0
 !
 ! Unless required by applicable law or agreed to in writing, software
 ! distributed under the License is distributed on an "AS IS" BASIS,
 ! WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ! See the License for the specific language governing permissions and
 ! limitations under the License.
-->

## ForgeRock Identity Edge Application Developers Guide

This guide shows you how to use the ForgeRock® Identity Edge Controller (IEC) SDK to 
develop client applications and to register them with the IEC Service. The IEC SDK client 
library provides client APIs in C and [Go](https://golang.org/) for client applications to 
invoke ForgeRock Access Manager (AM) functionality through the IEC Service. The SDK library 
is small and uses a secure lightweight messaging protocol so that it can run on constrained 
devices.

The examples in this Guide use the C API. Adjust the examples if you are using Go.

### Before You Start
* [Understanding IEC](understanding-iec.md)
* [About the Build Script](build-script.md)

### Developing Clients With the IEC SDK
* [Initializing Clients](initializing-clients.md)
* [Registering a Device](registering-devices.md)

