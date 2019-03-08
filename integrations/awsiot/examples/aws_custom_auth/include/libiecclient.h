/* Created by "go tool cgo" - DO NOT EDIT. */

/* package forgerock.org/cmd/iecsdk */

/* Start of preamble from import "C" comments.  */


#line 16 "/root/workspace/elines_iec-1.0.0-postcommit-FFIF3MFUUMOW6H4HYCILARYR2ZNFYARU27NRXSSQ36FTQEUWKBPA/iec/go/src/forgerock.org/cmd/iecsdk/main.go"

#include <stdbool.h>
#include "libiectypes.h"

#line 1 "cgo-generated-wrapper"


/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

//#ifndef GO_CGO_PROLOGUE_H
//#define GO_CGO_PROLOGUE_H
//
//typedef signed char GoInt8;
//typedef unsigned char GoUint8;
//typedef short GoInt16;
//typedef unsigned short GoUint16;
//typedef int GoInt32;
//typedef unsigned int GoUint32;
//typedef long long GoInt64;
//typedef unsigned long long GoUint64;
//typedef GoInt64 GoInt;
//typedef GoUint64 GoUint;
//typedef __SIZE_TYPE__ GoUintptr;
//typedef float GoFloat32;
//typedef double GoFloat64;
//typedef float _Complex GoComplex64;
//typedef double _Complex GoComplex128;
//
///*
//  static assertion to make sure the file is being used on architecture
//  at least with matching size of GoInt.
//*/
//typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];
//
//typedef struct { const char *p; GoInt n; } GoString;
//typedef void *GoMap;
//typedef void *GoChan;
//typedef struct { void *t; void *v; } GoInterface;
//typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;
//
//#endif
//
///* End of boilerplate cgo prologue.  */
//
//#ifdef __cplusplus
//extern "C" {
//#endif


/*
 * 'iec_initialise' will prepare the SDK by checking that a running IEC exists and that it is ready to except requests.
 * It will also perform setup task like configuring the logging system. This function will block until the IEC
 * is ready. If any of the aforementioned tasks fail then -1 will be returned. A message describing the error can
 * be retrieved with 'iec_last_error'.
 */

extern int iec_initialise();

/*
 * 'iec_last_error' will return the last error that was reported in the SDK. The message returned is purely for debug
 * purposes and should not be used for programmatic recovery as the messages may change over time. Instead the API
 * function return codes should be interpreted to change program behaviour.
 */

extern char* iec_last_error();

/*
 * 'iec_device_register' will send a request to register a new device with the given unique ID. If
 * the request fails then -1 will be returned.
 * param p0 A unique ID for the device.
 * param p1 Registration data that may be used to attest the device during registration. A NULL indicates no data.
 */

extern int iec_device_register(char* p0, char* p1);

/*
 * 'iec_device_configuration' will send a request to retrieve the configuration for the device with the given ID.
 * The device must already be registered. If the request was successful then 'config' will point to where the
 * configuration was placed on the heap. If the request fails then -1 will be returned.
 * param p0 The unique ID for the device.
 * param p1 Pointer to where the configuration was placed on the heap.
 */

extern int iec_device_configuration(char* p0, char** p1);

/*
 * 'iec_device_tokens' will send a request to retrieve tokens for the device with the given ID.
 * The device must already have been registered.
 * If the request is successful then 'tokens' will point to where the tokens were placed on the heap.
 * If the request fails then -1 will be returned.
 * param p0 The unique ID for the device
 * param p1 Pointer to where the tokens were placed on the heap
 */

extern int iec_device_tokens(char* p0, char** p1);

/*
 * 'iec_user_code' will send a request to start the device pairing process. The device will receive a code to hand
 * to the user that it wants to pair with. The user will authorise the pairing and the device will receive tokens that
 * will allow it to act on behalf of the user. To retrieve the tokens and complete the pairing process, a call to
 * `iec_user_tokens` must be made after handing the code to the user.
 * The device must be registered prior to this call.
 * If the request is successful then 'code' will point to where the code was placed on the heap.
 * If the request fails then -1 will be returned.
 * param p0 The unique ID for the device.
 * param p1 Pointer to where the code was placed on the heap.
 */

extern int iec_user_code(char* p0, char** p1);

/*
 * 'iec_user_tokens' will send a request to retrieve tokens for the device with the given ID. This call must follow
 * `iec_user_code` and it completes the pairing process.
 * NOTE: this call will block until the user has authorised the pairing request or when the code expires.
 * The device must be registered prior to this call.
 * If the request is successful then 'tokens' will point to where the tokens were placed on the heap.
 * If the request fails then -1 will be returned.
 * param p0 The unique ID for the device.
 * param p1 Pointer to where the tokens were placed on the heap.
 */

extern int iec_user_tokens(char* p0, char** p1);

/*
 * 'iec_device_custom_command' will send a request to execute the custom command for the device with the given ID.
 * The device must already have been registered.
 * If the request is successful then 'response' will point to where the response from AM was placed on the heap.
 * If the request fails then -1 will be returned.
 * param p0 The unique ID for the device
 * param p1 The custom command to execute
 * param p2 Parameters for the command
 * param p3 Pointer to where the response was placed on the heap
 */

extern int iec_device_custom_command(char* p0, char* p1, char* p2, char** p3);

/*
 * 'iec_json_parse' will parse the json string and store the result in memory.
 * If the request fails then -1 will be returned.
 */

extern int iec_json_parse(char* p0);

/*
 * 'iec_json_get_string' will get the string value associated with the given key from the JSON string that was parsed in
 * a previous 'iec_json_parse' call.
 * If the key is missing then -1 will be returned.
 */

extern int iec_json_get_string(char* p0, char** p1);

/*
 * 'iec_json_get_int' will get the integer value associated with the given key from the JSON string that was parsed in
 * a previous 'iec_json_parse' call.
 * If the key is missing then -1 will be returned.
 */

extern int iec_json_get_int(char* p0, int* p1);

/*
 * 'iec_json_get_bool' will get the boolean value associated with the given key from the JSON string that was parsed in
 * a previous 'iec_json_parse' call.
 * If the key is missing then -1 will be returned.
 */

extern int iec_json_get_bool(char* p0, _Bool* p1);

/*
 * 'iec_set_attribute' will set a sdk attribute to the given value.
 * If an error occurs then -1 will be returned.
 * param p0 The sdk attribute
 * param p1 The new value for the attribute in a string representation. Refer to the definition of sdk_attribute for the
 * expected types and conversion rules
 */

extern int iec_set_attribute(iec_sdk_attribute p0, char* p1);

#ifdef __cplusplus
}
#endif
