#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "helperavr.h"
#include "mydefs.h"

//
// Created by anton on 04.01.18.
//
void init_pins_status(void) {

    PIN_PULL_UP(DDRB, PORTB, PINB3);
    PIN_PULL_UP(DDRB, PORTB, PINB4);
    PIN_PULL_UP(DDRB, PORTB, PINB5);

    PIN_PULL_UP(DDRD, PORTD, PIND2);
    PIN_PULL_UP(DDRD, PORTD, PIND4);
    PIN_PULL_UP(DDRD, PORTD, PIND5);
    PIN_PULL_UP(DDRD, PORTD, PIND6);
    PIN_PULL_UP(DDRD, PORTD, PIND7);

    PIN_PULL_UP(DDRC, PORTC, PIND0);
    PIN_PULL_UP(DDRC, PORTC, PIND1);
    PIN_PULL_UP(DDRC, PORTC, PIND2);
    PIN_PULL_UP(DDRC, PORTC, PIND3);

    PIN_AS_OUTPUT(DDRB, LED_PIN);
    PIN_AS_OUTPUT(DDRD, RELAY_PIN);
    PIN_AS_OUTPUT(DDRB, PWR_KEY_PIN);

    PIN_ON(PORTD, RELAY_PIN);
    PIN_OFF(PORTB, PWR_KEY_PIN);
}

void delay_ms(int delay) {
    while (delay--) {
        _delay_ms(1);
        wdt_reset();
    }
}

void blink(void) {
    PIN_ON(PORTB, LED_PIN);
    delay_ms(100);
    PIN_OFF(PORTB, LED_PIN);
}

void wdt_init(void) {
    MCUSR = 0;
    wdt_enable(WDTO_8S);
}

void init_timer(void) {
    TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10); // CPU_SPEED / 1024
    TIMSK1 |= (1 << TOIE1);
    TCNT1 = 0;
}