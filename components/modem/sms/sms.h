//
// Created by anton on 04.01.18.
//

#ifndef GSM_MODULE_SMS_H
#define GSM_MODULE_SMS_H

#define SMS_BUFFER_LENGTH 64

int is_sms(char *message);
char *get_sms_text(char *message);
void send_sms(char *phone, char *text);

#endif //GSM_MODULE_SMS_H
