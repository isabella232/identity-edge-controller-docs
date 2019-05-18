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

### Understanding the IEC

Before you start developing clients, it is helpful to have an overview of the IEC and its 
components. Read the official [IEC Documentation](http://backstage.forgerock.com/docs/iec/6.5/) 
as a starting point.

The code examples in this guide assume that you are using the 
[IEC training environment](https://github.com/ForgeRock/identity-edge-controller-docs/tree/master/training). 
If you are not using the training environment, make sure that you have installed all the 
required components, including the IEC SDK, and that everything is up and running, as 
described in the [IEC Installation Guide](http://backstage.forgerock.com/docs/iec/6.5/install-guide). 
Also make sure that you have set the `LIBRARY_PATH` variables, as described in 
[To Install the SDK](http://backstage.forgerock.com/docs/iec/6.5/install-guide/index.html#install-sdk).  
Adjust the examples for your environment.

The IEC Service attests for both clients (SDK) and devices. Onboarding either of these node 
types will fail if the IEC Service has not registered successfully with AM. In general, the 
functional flow is from the SDK Client library (`libiecclient.so`) API, via ZMQ and the IEC 
Service to the AM IEC Plugin and back.

For details of the IEC components and how they interact, see the 
[IEC Getting Started Guide](http://backstage.forgerock.com/docs/iec/6.5/getting-started).

Log in to the AM Admin Console. The default credentials for the AM admin user in the training 
environment are `amadmin` and `password`. The training environment already has a configured realm 
named `edge`. If you are not using the training environment, configure this realm, as described in 
[Configuring AM for IoT](http://backstage.forgerock.com/docs/iec/6.5/install-guide/index.html#am-iot-config). 
