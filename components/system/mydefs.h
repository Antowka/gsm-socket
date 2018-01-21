//
// Created by anton on 04.01.18.
//

#ifndef GSM_MODULE_MYDEFS_H

#define GSM_MODULE_MYDEFS_H

//OUR DEF
#define PING_AT_COUNTER 6
#define LED_PIN 0
#define PWR_KEY_PIN 2
#define RELAY_PIN 3
#define DTMF_COMMAND_LENGTH 2
static char *PHONE_NUMBER = "+79875359969"; //your phone number
static char *SMS_CMD_PREFIX = "CMD:";



//Easier type writing:
typedef unsigned char  u8;
typedef   signed char  s8;
typedef unsigned short u16;
typedef   signed short s16;
typedef unsigned long  u32;
typedef   signed long  s32;


//Access bits like variables:

struct bits {
    u8 b0:1;
    u8 b1:1;
    u8 b2:1;
    u8 b3:1;
    u8 b4:1;
    u8 b5:1;
    u8 b6:1;
    u8 b7:1;
} __attribute__((__packed__));

#define SBIT_(port,pin) ((*(volatile struct bits*)&port).b##pin)
#define	SBIT(x,y)	SBIT_(x,y)


//Optimization improvements

// always inline function x:

#define AIL(x)   static x __attribute__ ((always_inline)); static x


// never inline function x:

#define NIL(x)   x __attribute__ ((noinline)); x


// volatile access (reject unwanted removing access):

#define vu8(x)  (*(volatile u8*)&(x))
#define vs8(x)  (*(volatile s8*)&(x))
#define vu16(x) (*(volatile u16*)&(x))
#define vs16(x) (*(volatile s16*)&(x))
#define vu32(x) (*(volatile u32*)&(x))
#define vs32(x) (*(volatile s32*)&(x))

#endif //GSM_MODULE_MYDEFS_H