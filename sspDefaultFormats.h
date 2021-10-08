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

sspRet_t sspStringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);        /* char [] */
sspRet_t sspStringFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);      /* char [] */
sspRet_t sspCharByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* char */
sspRet_t sspCharByteFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* char */
sspRet_t sspInteger32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);     /* int */
sspRet_t sspInteger32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);   /* int */
sspRet_t sspUInteger32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);    /* unsigned int */
sspRet_t sspUInteger32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);  /* unsigned int */
sspRet_t sspLong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);        /* long */
sspRet_t sspLong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);      /* long */
sspRet_t sspULong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);       /* unsigned long */
sspRet_t sspULong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* unsigned long */
sspRet_t sspLonglong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);    /* long long */
sspRet_t sspLonglong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);  /* long long */
sspRet_t sspULonglong64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);   /* unsigned long long */
sspRet_t sspULonglong64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc); /* unsigned long long */
sspRet_t sspFloat32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);       /* float */
sspRet_t sspFloat32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);     /* float */
sspRet_t sspUFloat32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* unsigned float */
sspRet_t sspUFloat32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);    /* unsigned float */
sspRet_t sspDouble64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);      /* double */
sspRet_t sspDouble64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);    /* double */
sspRet_t sspUDouble64ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);     /* unsigned double */
sspRet_t sspUDouble64FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);   /* unsigned double */

#endif
