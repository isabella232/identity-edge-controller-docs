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

#ifndef __IEC_TYPES_H_
#define __IEC_TYPES_H_

/*
 * sdk_attribute enumerates the available attributes for the IEC SDK.
 * Each attribute is set from a supplied string value and converted to the 'expected' type using the following rules:
 * 		string - a null terminated string
 * 		bool   - 1, t, T, TRUE, true, True, 0, f, F, FALSE, false, False
 * 		int    - string representation of an integral number
 * Refer to each enum for the 'expected' type.
*/
typedef enum {
    IEC_ENDPOINT,                   // string
    IEC_SECRETKEY,                  // string
    IEC_PUBLICKEY,                  // string
    IEC_SERVERPUBLICKEY,            // string
    IEC_MSGTIMEOUTSEC,              // int
    IEC_CLIENT_ID,                  // string
    IEC_LOGGING_ENABLED,            // bool
    IEC_LOGGING_DEBUG,              // bool
    IEC_LOGGING_LOGFILE,            // string
    IEC_LOGGING_MAXSIZE,            // int
    IEC_LOGGING_MAXBACKUPS,         // int
    IEC_LOGGING_MAXAGE,             // int
    IEC_LOGGING_COMPRESSBACKUPS,    // bool
} iec_sdk_attribute;

#endif
