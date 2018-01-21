#include <string.h>
#include "../../system/mydefs.h"

//
// Created by anton on 04.01.18.
//

static char dtmf_symbols[DTMF_COMMAND_LENGTH];
int index_of_last_symbol = 0;

int is_dtmf_symbol(char *message) {
    return strstr(message, "+DTMF:") != NULL;
}

int is_hash_dtmf_symbol(char *message) {
  return strstr(message, "+DTMF: #") != NULL;
}

int is_star_dtmf_symbol(char *message) {
    return strstr(message, "+DTMF: *") != NULL;
}

void get_dtmf_symbol(char *symbol, const char *message) {
    *symbol = message[9];
}

void add_dtmf_symbol_to_array(char symbol) {

    if (index_of_last_symbol >= DTMF_COMMAND_LENGTH) {
        index_of_last_symbol = 0;
    }

    dtmf_symbols[index_of_last_symbol++] = symbol;
}

char * get_dtmf_symbols_from_array(void) {
    return dtmf_symbols;
}

void clear_dtmf_symbols_array(void) {
    index_of_last_symbol = 0;
    memset(dtmf_symbols, 0, sizeof dtmf_symbols);
}


