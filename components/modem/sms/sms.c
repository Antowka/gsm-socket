//
// Created by anton on 04.01.18.
//

#include <string.h>
#include <stdio.h>
#include "sms.h"
#include "../../system/mydefs.h"
#include "../control.h"
#include "../../system/initializer.h"

static char sms_buffer[SMS_BUFFER_LENGTH];
static char *sms_buffer_pointer = (char *) &sms_buffer;

int is_sms(char *message) {
    return strstr(message, SMS_CMD_PREFIX) != NULL;
}

char *get_sms_text(char *message) {
    memset(sms_buffer, 0, sizeof sms_buffer);
    memcpy(sms_buffer_pointer, &message[(strstr(message, SMS_CMD_PREFIX) - message + 4)], SMS_BUFFER_LENGTH - 1);
    return sms_buffer;
}

void send_sms(char *phone, char *text) {

    char phone_command[25];
    char sms_text[sizeof(text) + 1];

    send_at_command("AT+CSCS=\"GSM\"\r\n");
    delay_ms(800);

    send_at_command("AT+CMGF=1\r\n");
    delay_ms(800);

    sprintf(phone_command, "AT+CMGS=\"%s\"\r\n", phone);
    send_at_command(phone_command);
    delay_ms(800);

    sprintf(sms_text, "%s%c", text, '\032');
    send_at_command(sms_text);
    delay_ms(800);
}