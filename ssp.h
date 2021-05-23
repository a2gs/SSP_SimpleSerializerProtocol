/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 * https://sites.google.com/view/a2gs
 *
 * SSP - SimpleSerializerProtocol
 *
 * MIT License
 */

#ifndef __SSP_H__
#define __SSP_H__

#include <stddef.h>

#define SSP_OK (1)
#define SSP_ERRO (0)

#define SSP_QTD_FMT(__ssp_qtdfmt__) (sizeof(__ssp_qtdfmt__) / sizeof(sspFmt_t))

typedef struct _sspFmt_t{
	unsigned int id;
	int (*toNet)(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);
	int (*fromNet)(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);
}sspFmt_t;

typedef struct _ssp_t{
	unsigned int version;
	sspFmt_t *format;
	unsigned int qtdFmt;
	unsigned char *msg;
	size_t msgMaxSz;
	size_t msgSz;
}ssp_t;

/* Common formats */
int stringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);      /* char [] */
int stringFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);    /* char [] */
int charByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);    /* char */
int charByeFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);   /* char */
int integerToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);     /* int */
int integerFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);   /* int */
int uintegerToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);    /* unsigned int */
int uintegerFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);  /* unsigned int */
int longToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);        /* long */
int longFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);      /* long */
int ulongToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);       /* unsigned long */
int ulongFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);     /* unsigned long */
int longlongToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);    /* long long */
int longlongFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);  /* long long */
int ulonglongToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);   /* unsigned long long */
int ulonglongFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz); /* unsigned long long */
int floatToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);       /* float */
int floatFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);     /* float */
int ufloatToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);      /* unsigned float */
int ufloatFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);    /* unsigned float */
int doubleToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);      /* double */
int doubleFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);    /* double */
int udoubleToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz);     /* unsigned double */
int udoubleFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz);   /* unsigned double */

int sspCtx(ssp_t *ssp, unsigned int version, sspFmt_t *format, unsigned qtdFmt, unsigned char *msg, size_t msgMaxSz);
int sspStartToNet(ssp_t *ssp);
int sspStartFetch(ssp_t *ssp);

int pack(unsigned int id, void *dataIn, size_t *dataInSz);
int unpack(unsigned int id, void *dataOut, size_t dataOutSz);

#endif
