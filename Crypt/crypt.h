#ifndef _CRYPT_H_
#define _CRYPT_H_

#include <stdio.h>

#define DES_MODE_ENC	1
#define DES_MODE_DEC	2

#define FARGOSCARDESTABLISHCONTEXT			42001;
#define FARGOCHECKSMARTCARD					42002;
#define FARGOGETSERIAL   					42008;

//function Prototypes..

extern "C" {

int AuthanticateDesfire(unsigned char *Data, int DataLen, unsigned char *commandToSend, int *commandLen);

};
#endif

