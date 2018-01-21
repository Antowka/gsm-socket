//
// Created by anton on 04.01.18.
//

#include <string.h>
#include "../system/initializer.h"
#include "../uart/uart.h"
#include "../system/helperavr.h"
#include "dtmf/dtmf.h"

void send_at_command(char *at_command) {
    uputs0(at_command);
}

void enable_modem(void) {
    PIN_ON(PORTB, PWR_KEY_PIN);
    delay_ms(2500);
    PIN_OFF(PORTB, PWR_KEY_PIN);
}

void send_configuration(void) {

    enable_modem();

    delay_ms(5000);
    send_at_command("AT\r");

    delay_ms(800);
    send_at_command("ATE0\r");

    delay_ms(800);
    send_at_command("AT+CMGD=1,4\r");

    delay_ms(800);
    send_at_command("AT+CMGF=1\r");

    delay_ms(800);
    send_at_command("AT+CNMI=1,2,0,0,0\r");

    delay_ms(800);
    send_at_command("AT+DDET=1\r");

    delay_ms(800);
}

void enable_relay(void) {
    PIN_OFF(PORTD, RELAY_PIN);
}

void disable_relay(void) {
    PIN_ON(PORTD, RELAY_PIN);
}

int is_enabled_relay(void) {
    return !CHECK_PIN(PORTD, RELAY_PIN);
}

int equals_dtmf_code(char *code) {
    return strcmp(get_dtmf_symbols_from_array(), code) == 0;
}

int is_ring(char *message) {
    return strstr(message, "RING") != NULL;
}

int contain(char *message, char *substring) {
    return strstr(message, substring) != NULL;
}
