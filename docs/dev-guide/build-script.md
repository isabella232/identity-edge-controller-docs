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

### About the Build Script

The SDK includes a `build-examples.sh` script that sets the required environment variables and builds 
all applications that are in the following directories:
  
<pre>~/forgerock/examples/<i>app-name</i></pre>

The build script creates applications named *app-name* in the corresponding 
`~/forgerock/examples/app-name` directory.
   
Before you use the script, open it in a text editor and adjust the path to your local C compiler, 
for example:

`export CC=usr/bin/gcc`
  
The build script is not executable by default. Make sure that the script is executable before you 
try the examples:

`chmod +x build-examples.sh`