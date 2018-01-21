#include <stdio.h>
#include <avr/wdt.h>
#include <string.h>
#include "components/system/initializer.h"
#include "components/system/mydefs.h"
#include "components/uart/uart.h"
#include "components/system/helperavr.h"
#include "components/modem/control.h"
#include "components/modem/sms/sms.h"
#include "components/modem/dtmf/dtmf.h"

static int ping_counter = PING_AT_COUNTER;
static int timer_expiration_flag = 0;



void ping_modem(void) {

    if (ping_counter <= 0) {
        enable_modem();
        send_configuration();
        ping_counter = PING_AT_COUNTER;
    } else if (ping_counter < (PING_AT_COUNTER / 2)) {
        send_at_command("AT\r\n");
    }

    ping_counter--;
}

void sms_handler(char *message) {
    char *sms_command = get_sms_text(message);
    if (contain(sms_command, "ON")) {
        enable_relay();
        send_sms(PHONE_NUMBER, is_enabled_relay() ? "OK" : "FAIL");
    } else if (contain(sms_command, "OFF")) {
        disable_relay();
        send_sms(PHONE_NUMBER, is_enabled_relay() ? "FAIL" : "OK");
    } else if (contain(sms_command, "STATUS")) {
        send_sms(PHONE_NUMBER, is_enabled_relay() ? "ON" : "OFF");
    }
}

void dtmf_handler(char *message) {

    if (is_hash_dtmf_symbol(message)) {
        if (equals_dtmf_code("01")) {
            enable_relay();
            if (is_enabled_relay()) {
                send_at_command("AT+VTS=\"2,2,2\"\r\n");
            }
        } else if (equals_dtmf_code("02")) {
            disable_relay();
            if (!is_enabled_relay()) {
                send_at_command("AT+VTS=\"2,2,2\"\r\n");
            }
        } else if (equals_dtmf_code("03")) {
            char at[14];
            sprintf(at, "AT+VTS=\"%s\"\r\n", is_enabled_relay() ? "2" : "2,2");
            send_at_command(at);
        }

    } else if (is_star_dtmf_symbol(message)) {
        clear_dtmf_symbols_array();
    } else {
        char symbol;
        get_dtmf_symbol(&symbol, message);
        add_dtmf_symbol_to_array(symbol);
    }
}


int main() {

    static char buffer[RX0_SIZE] = "";
    static int buffer_index = 0;

    init_pins_status();
    init_timer();
    wdt_init();
    init_uart();
    send_configuration();

    while (1) {

        wdt_reset();
        buffer_index = 0;

        if (timer_expiration_flag) {
            STOP_TIMER1;
            timer_expiration_flag = 0;
            ping_modem();
            START_TIMER1;
        }

        if (!ukbhit0()) {
            continue;
        }
        delay_ms(200);
        memset(buffer, 0, sizeof buffer);

        do {
            buffer[buffer_index++] = ugetchar0();
        } while (ukbhit0());

        if (buffer_index) {

            if (is_sms(buffer)) {
                STOP_TIMER1;
                sms_handler(buffer);
                clean_buffer();
                START_TIMER1;
            } else if (is_dtmf_symbol(buffer)) {
                STOP_TIMER1;
                blink();
                dtmf_handler(buffer);
                clean_buffer();
                START_TIMER1;
            } else if (is_ring(buffer)) {
                STOP_TIMER1;
                send_at_command("ATA\r\n");
                clean_buffer();
                START_TIMER1;
            } else if (contain(buffer, "OK")) { //handle PONG
                STOP_TIMER1;
                blink();
                timer_expiration_flag = 0;
                ping_counter = PING_AT_COUNTER;
                clean_buffer();
                START_TIMER1;
            }
        }
    }
}

ISR(TIMER1_OVF_vect) {
    timer_expiration_flag = 1;
}