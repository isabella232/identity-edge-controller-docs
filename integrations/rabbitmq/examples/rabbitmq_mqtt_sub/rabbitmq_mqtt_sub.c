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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <mosquitto.h>

#include <libiecclient.h>

/* Ideally the MQTT settings would be set dynamically e.g. using an iec_get_configuration call */
#define MQTT_HOSTNAME "172.16.0.1"
#define MQTT_TOPIC "chat"
#define MQTT_QOS 1
#define MQTT_PORT 1883

/**
 * mosq_message_cb is called when a message is received from the broker
 */
void mosq_message_cb(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    printf("Received the following message on topic %s: ", message->topic);
    (void)fwrite(message->payload, 1, message->payloadlen, stdout);
    printf("\n");
    fflush(stdout);
}

/**
 * mosq_connect_cb is a connection response callback for the mosquitto client
 */
void mosq_connect_cb(struct mosquitto *mosq, void *userdata, int result)
{
    printf("Connection %s\n\n",result==0?"ACCEPTED":"REFUSED");
    if (result != 0) {
        mosquitto_disconnect(mosq);
        return;
    }
    mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, MQTT_QOS);
}

int main() {
    printf("\n*** Using OAuth 2.0 tokens to connect to RabbitMQ server\n\n");
    char device_id[] = "Cribyn";
    int result;

    result = iec_initialise();
    if (result < 0) {
        char* error = iec_last_error();
        printf("Initialisation request failed: %s\n", error);
        free(error);
        return result;
    }

    /* Register device with IEC */
    printf("Registering device (id: %s)... ", device_id);
    result = iec_device_register(device_id, NULL);
    if (result < 0) {
        char* error = iec_last_error();
        printf("Registration request failed: %s\n", error);
        free(error);
        return result;
    }
    printf("Done\n");

    /* Request OAuth 2.0 tokens from IEC */
    printf("Requesting OAuth 2.0 access token for device (id: %s)... ", device_id);
    char* tokens;
    result = iec_device_tokens(device_id, &tokens);
    if (result < 0) {
        char* error = iec_last_error();
        printf("Access token request failed: %s\n", error);
        free(error);
        return result;
    }
    printf("Done\n");

    /* Extract access token */
    char* access_token;
    if (iec_json_parse(tokens) != 0 || iec_json_get_string("access_token", &access_token) != 0 ) {
        char* error = iec_last_error();
        printf("Failed to extract id token: %s\n", error);
        free(error);
        return -1;
    }
    printf("access token: %s\n", access_token);

    /* Initialize the Mosquitto library */
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(device_id, true, NULL);
    if (!mosq) {
        printf("Can't create Mosquitto instance\n");
        return -1;
    }

    /* Set callbacks */
    mosquitto_message_callback_set(mosq, mosq_message_cb);
    mosquitto_connect_callback_set(mosq, mosq_connect_cb);


    /* Use the device ID and access token as the username and password respectively */
    /* Remove this line to see what happens when the device connects without an access token */
    mosquitto_username_pw_set(mosq, device_id, access_token);

    /* Connect to server */
    result = mosquitto_connect(mosq, MQTT_HOSTNAME, MQTT_PORT, 86400);
    if (result != 0) {
        printf("Can't connect to MQTT server\n");
        mosquitto_destroy(mosq);
        return result;
    }

    mosquitto_loop_forever(mosq, -1, 1);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
