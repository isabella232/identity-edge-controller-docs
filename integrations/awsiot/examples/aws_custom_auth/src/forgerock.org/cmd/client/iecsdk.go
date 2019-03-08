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

package main

/*
#include <stdlib.h>
#include <stdio.h>
#include <libiecclient.h>
#include <libiectypes.h>

char* tokens;

static char* device_tokens(char* deviceId) {
    int result = iec_device_tokens(deviceId, &tokens);
    if (result < 0) {
        return NULL;
    }
    return tokens;
}

*/
import "C"
import (
	"errors"
	"unsafe"
)

func initialiseSDK() error {
	result := C.iec_initialise()
	if int(result) < 0 {
		cError := C.iec_last_error()
		defer C.free(unsafe.Pointer(cError))
		return errors.New(C.GoString(cError))
	}
	return nil
}

func registerDevice(deviceID, regData string) error {
	cName := C.CString(deviceID)
	defer C.free(unsafe.Pointer(cName))
	cRegData := C.CString(regData)
	defer C.free(unsafe.Pointer(cRegData))

	result := C.iec_device_register(cName, cRegData)
	if result < 0 {
		cError := C.iec_last_error()
		defer C.free(unsafe.Pointer(cError))
		return errors.New(C.GoString(cError))
	}
	return nil
}

func deviceTokens(deviceID string) (string, error) {
	cName := C.CString(deviceID)
	defer C.free(unsafe.Pointer(cName))

	cTokens := C.device_tokens(cName)
	defer C.free(unsafe.Pointer(cTokens))
	if cTokens == nil {
		cError := C.iec_last_error()
		defer C.free(unsafe.Pointer(cError))
		return "", errors.New(C.GoString(cError))
	}

	return C.GoString(cTokens), nil
}