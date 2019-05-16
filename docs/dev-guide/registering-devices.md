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

### Registering a Device

A client application developed with the IEC SDK can register a device ID with AM and 
provide configuration from AM for the device with this ID. 
___
**Note** There is a wide range of device node types from many different manufacturers. 
Specific programming and configuration of these devices is outside the scope of the 
IEC project.
___

The client application initiates the registration flow with an `iec_device_register` library 
call. The procedure assumes that the device is made known (in some way) to the client.

Using the configured device ID and specific device registration data, such as keys, the client 
issues a ZMQ request of type `DeviceRegister` to the IEC Service. The IEC Service receives the 
request and does the following:

1. Registers with AM claiming to be node type `device`.
2. Checks that the IEC Service has been registered with AM.
3. Authenticates the device with AM, with the specified device ID and node type `client` 
   (the client attests for the device).
4. The client registers the device with AM using claims, with node type `device` and the 
   following data:

   * specified device ID
   * registration data
   * registration key
   
5. The client returns with an outcome
6. IEC Service responds with a success ZMQ message
7. The device is registered

