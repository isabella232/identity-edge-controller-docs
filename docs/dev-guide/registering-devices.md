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

To register a device:
 
1. Your client application must include the `libiecclient.h` library and a call to 
`iec_device_register()`.

   See the example client application 
[register_device.c](../training/sdk/examples/register_device/register_device.c). This sample 
application includes dynamic client initialization, shown in 
[Initializing a Client Dynamically](initializing-clients.md#initializing-a-client-dynamically).

2. If you are working in the training environment, the sample application (`register_device.c`) is 
   already present in `~/forgerock/examples/register_device`.
   
   If you are not working in the training environment, create a new directory in the  
   `~/forgerock/examples` directory, with the same name as your client application and place the 
   C application in that directory.
  
   For example, copy 
   [register_device.c](../training/sdk/examples/register_device/register_device.c) into a new 
   directory named `register_device`:
   
   ```
   mkdir ~/forgerock/examples/register_device
   cp register_device.c ~/forgerock/examples/register_device
   ```
  
3. Set the device ID and any custom registration data. In the example, the device ID is 
   `Narwhal`.
   
   Note that the registration data is discarded as soon as the device is registered. No registration 
   data is stored in AM. 

3. Make sure that the build script is executable, then run the script to set the build variables 
   and build the application:

   `~/forgerock/build-examples.sh`
   
   The build script creates the application `register_device` in the 
   `~/forgerock/examples/register_device` directory:
   
   ```
   ls examples/register_device/
   register_device register_device.c
   ```

4. Run the example application:

   ```
   cd ~/forgerock/examples/register_device
   ./register_device
   *** Registering a device
   *** SDK function(s): iec_initialise, iec_device_register

   Setting dynamic attributes... Done
   
   Initialising sdk... Done
   
   Registering device (id: Narwhal)... Done
   ```
   
   If the initialization was successful, you should see the `Narwhal` identity in the AM 
   Console. The `reg-dev-client` identity is the identity of your client application, set 
   with the `IEC_CLIENT_ID` dynamic attribute.
   
#### Understanding the Device Registration Process

1. The call to `iec_device_register` initiates the registration. 
   
   <hr>
   The procedure assumes that the device is made known (in some way) to the client.
   <hr>
   
2. Using the specified device ID and device registration data, such as keys, the client issues 
  a ZMQ request of type `DeviceRegister` to the IEC Service. The IEC Service receives the 
  request and does the following:
   
   * Registers with AM claiming to be node type `device`.
   * Checks that the IEC Service has been registered with AM.
   * Authenticates the device with AM, with the specified device ID and node type `client` 
   (the client attests for the device).
   
3. The client registers the device with AM using claims, with node type `device` and the 
   following data:

   * specified device ID
   * registration data
   * registration key
   
4. The client returns with an outcome
5. The IEC Service responds with a success ZMQ message
6. The device is registered   