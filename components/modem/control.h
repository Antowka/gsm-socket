//
// Created by anton on 04.01.18.
//

#ifndef GSM_MODULE_CONTROL_H
#define GSM_MODULE_CONTROL_H

void send_configuration(void);
void enable_modem(void);
void enable_relay(void);
void disable_relay(void);
int is_enabled_relay(void);
int equals_dtmf_code(char *code);
void send_at_command(char *at_command);
int is_ring(char *message);
int contain(char *message, char *substring);


#endif //GSM_MODULE_CONTROL_H
