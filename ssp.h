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

#define SSP_OK    (1)
#define SSP_ERROR (0)

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

int sspCtx(ssp_t *ssp, unsigned int version, sspFmt_t *format, unsigned qtdFmt, unsigned char *msg, size_t msgMaxSz);
int sspStartToNet(ssp_t *ssp);
int sspStartFetch(ssp_t *ssp);

int pack(ssp_t *ssp, unsigned int id, void *dataIn, size_t *dataInSz);
int unpack(ssp_t *ssp, unsigned int id, void *dataOut, size_t dataOutSz);

#endif
