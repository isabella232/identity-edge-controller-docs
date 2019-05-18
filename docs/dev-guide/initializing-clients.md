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

### Initializing Clients With the IEC SDK

The IEC SDK requires access to a configuration to provide keys, URLs, and so on. After you 
have installed and registered the IEC Service, you can initialise this configuration in two 
ways:

* Manually, using a JSON configuration file and the `iecutil` utility.
 
  `iecutil` creates a configuration database (named `iec-sdk.db`) based on the properties 
  in this configuration JSON file.

  A sample configuration file follows:
  ```{
       "zmq_client": {
         "endpoint": "tcp://127.0.0.1:5556",
         "secret_key":"zZZfS7BthsFLMv$]Zq{tNNOtd69hfoBsuc-lg1cM",
         "public_key":"uH&^{aIzDw5<>TRbHcu0q#(zo]uLl6Wyv/1{/^C+",
         "server_public_key":"9m27tKf3aoNWQ(G-f[>W]gP%f&+QxPD:?mX*)hdJ",
         "msg_timeout_sec": 5
       },
       "logging": {
         "enabled": true,
         "debug": true,
         "max_file_size_mb": 5,
         "max_backup_files": 5,
         "max_file_age_days": 0,
         "compress_file_backups": true
       },
       "client_configuration": {
         "id": "iec-client"
       }
     }
  ```
  The configuration database *must* exist for the ZMQ communication to be established. Once 
  the database exists, you can update it from AM through the IEC Service. For security 
  reasons, you should delete or protect the JSON configuration file once the client has been 
  initialized. 
  
* Dynamically, using the `iec_set_attribute` function to set individual attribute values.

  Dynamic configuration takes precedence over a database configuration, if one exists. You 
  can use the `iec_set_attribute` utility to set a number of configuration attribute values, such 
  as the `IEC_ENDPOINT` and `IEC_SECRETKEY`. For a list of all the attributes, see 
  [libiectypes.h](https://stash.forgerock.org/projects/IOT/repos/identity-edge-controller-core/browse/cmd/iecsdk/libiectypes.h).
  
#### Initializing a Client Manually

To initialize the client manually:

1. Your C application must include the `libiecclient.h` library and a call to `iec_initialise()`.

   See the example client application [init_sdk_static.c](../training/sdk/examples/init_sdk_static/init_sdk_static.c).
   
2. Create a new directory in the `~/forgerock/examples` directory, with the same name as your client 
application and place the C application in that directory.

   For example, to build the `init_sdk_static.c` application, copy 
   [init_sdk_static.c](../training/sdk/examples/init_sdk_static/init_sdk_static.c) into a new directory 
   named `init_sdk_static`:
   
   ```
   mkdir ~/forgerock/examples/init_sdk_static
   cp init_sdk_static.c ~/forgerock/examples/init_sdk_static
   ```
   
3. Run the build script to set the build variables and build the application:

   ```~/forgerock/build-examples.sh```
   
   The build script creates the application `init_sdk_static` in the `~/forgerock/examples/init_sdk_static` 
   directory:
   
   ```
   ls examples/init_sdk_static/
   init_sdk_static  init_sdk_static.c
   ```
   
4. Copy the database configuration file (`sdk-config.json`) to the directory containing your 
application. For example:

   ```
   cp ~/forgerock/sdk-config.json ~/forgerock/examples/init_sdk_static
   ```
   
5. Edit the database configuration file to specify the IP address on which the SDK runs. For example, 
if you are setting this up in the training environment, edit the file as follows:

   `zmq_client.endpoint: tcp://172.16.0.11:5556`
   
6. Change to the directory in which your client application is located, then use the IEC utility to 
initialize the client application, based on the database configuration file in that directory:

   ```
   cd ~/forgerock/examples/init_sdk_static
   ~/forgerock/iecutil -file sdk-config.json -initialise sdk
   iec util: Initialising sdk
   iec util: Finished sdk initialisation
   ```
   
   An SDK application looks in the directory from which it's run for a configuration database or for a 
   file that contains the database location.
   
   **Note** If you change the configuration and need to reinitialize the SDK, remove the 
  `iec-sdk.db` in the application directory, then run the initialization again.
  
7. Run the example application:

   ```
   cd ~/forgerock/examples/init_sdk_static
   ./init_sdk_static
   ```
   
   If the initialization was successful, you should see the `iec-client` identity in the AM Console.

#### Initializing a Client Dynamically

If you are running this example after the previous example, delete the configuration file and database 
(`sdk-config.json` and `iec-sdk.db`) from the `~/forgerock/examples/init_sdk_static` directory.

To initialize the client dynamically:

1. Your C application must include the `libiecclient.h` library, and provide the complete SDK 
configuration with the `iec_set_attribute()` function.

   See the example client application [init_sdk_dynamic.c](../training/sdk/examples/init_sdk_dynamic/init_sdk_dynamic.c).
   
2. Create a new directory in the `~/forgerock/examples` directory, with the same name as your client 
  application and place the C application in that directory.
  
   For example, to build the `init_sdk_dynamic.c` application, copy 
   [init_sdk_dynamic.c](../training/sdk/examples/init_sdk_static/init_sdk_dynamic.c) into a new 
   directory named `init_sdk_dynamic`:
   
   ```
   mkdir ~/forgerock/examples/init_sdk_dynamic
   cp init_sdk_dynamic.c ~/forgerock/examples/init_sdk_dynamic
   ```
  
3. Run the build script to set the build variables and build the application:

   `~/forgerock/build-examples.sh`
   
   The build script creates the application `init_sdk_dynamic` in the 
   `~/forgerock/examples/init_sdk_dynamic` directory:
   
   ```
   ls examples/init_sdk_dynamic/
   init_sdk_dynamic init_sdk_dynamic.c
   ```

4. Run the example application:

   ```
   cd ~/forgerock/examples/init_sdk_dynamic
   ./init_sdk_dynamic
   *** Initialising the SDK dynamically
   *** SDK function(s): iec_initialise
   
   Setting dynamic attributes... Done
   
   Initialising sdk... Done
   ```
   
   If the initialization was successful, you should see the `iec-dynamic-client` identity in the AM 
   Console.