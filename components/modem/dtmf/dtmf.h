//
// Created by anton on 04.01.18.
//

#ifndef GSM_MODULE_DTMF_H
#define GSM_MODULE_DTMF_H

int is_dtmf_symbol(char *message);
int is_hash_dtmf_symbol(char *message);
int is_star_dtmf_symbol(char *message);
void add_dtmf_symbol_to_array(char symbol);
char * get_dtmf_symbols_from_array(void);
void clear_dtmf_symbols_array(void);
void get_dtmf_symbol(char *symbol, const char *message);

#endif //GSM_MODULE_DTMF_H
