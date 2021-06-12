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

typedef enum _sspRet_t{
	SSP_OK = 1,
	SSP_ERROR,
	SSP_TRUNCATEDBUTTHEREISNOMORESPACE,
	SSP_THEREISNOSPACE,
	SSP_DATAINSIZEERROR
}sspRet_t;

#define SSP_QTD_FMT(__ssp_qtdfmt__) (sizeof(__ssp_qtdfmt__) / sizeof(sspFmt_t))

typedef struct _sspFmt_t{
	uint16_t id;
	sspRet_t (*toNet)(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);
	sspRet_t (*fromNet)(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);
}sspFmt_t;

typedef struct _ssp_t{
	uint16_t version;

	sspFmt_t *format;
	unsigned int qtdFmt;

	unsigned char *msg;
	unsigned char *msgWalker;
	size_t msgMaxSz;
}ssp_t;

sspRet_t sspCtx(ssp_t *ssp, uint16_t version, sspFmt_t *format, unsigned qtdFmt, unsigned char *msg, size_t msgMaxSz);
sspRet_t sspStartToNet(ssp_t *ssp);
sspRet_t sspStartFetch(ssp_t *ssp);
char * sspReturnMessage(sspRet_t err);

sspRet_t sspPack(ssp_t *ssp, uint16_t id, void *dataIn, size_t dataInSz);
sspRet_t sspUnpack(ssp_t *ssp, uint16_t id, void *dataOut, size_t dataOutSz, size_t *proc);

sspRet_t sspCloseToNet(ssp_t *ssp);
sspRet_t sspMessage(ssp_t *ssp, unsigned char **msg, size_t *msgSz);

#endif
