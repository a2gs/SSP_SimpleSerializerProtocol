/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 * https://sites.google.com/view/a2gs
 *
 * SSP - SimpleSerializerProtocol
 *
 * MIT License
 */

#ifndef __SSP_DEFAULT_FORMATS_H__
#define __SSP_DEFAULT_FORMATS_H__

#include <stddef.h>

sspRet_t stringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);        /* char [] */
sspRet_t stringFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);      /* char [] */
sspRet_t charByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* char */
sspRet_t charByeFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* char */
sspRet_t integer32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);     /* int */
sspRet_t integer32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);   /* int */
sspRet_t uinteger32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);    /* unsigned int */
sspRet_t uinteger32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);  /* unsigned int */
sspRet_t long64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);        /* long */
sspRet_t long64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);      /* long */
sspRet_t ulong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);       /* unsigned long */
sspRet_t ulong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* unsigned long */
sspRet_t longlong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);    /* long long */
sspRet_t longlong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);  /* long long */
sspRet_t ulonglong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);   /* unsigned long long */
sspRet_t ulonglong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc); /* unsigned long long */
sspRet_t float32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);       /* float */
sspRet_t float32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* float */
sspRet_t ufloat32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* unsigned float */
sspRet_t ufloat32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);    /* unsigned float */
sspRet_t double64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* double */
sspRet_t double64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);    /* double */
sspRet_t udouble64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);     /* unsigned double */
sspRet_t udouble64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);   /* unsigned double */

#endif
