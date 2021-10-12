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

#ifdef DEBUG_ON
	#include <stdio.h>
	#define DEBUG(...) {                      \
	                     printf("DEBUG: ");   \
	                     printf(__VA_ARGS__); \
	                   }
#else
	#define DEBUG(x) NULL
#endif

typedef enum _sspRet_t{
	SSP_OK = 1,
	SSP_ERROR,
	SSP_TRUNCATEDBUTTHEREISNOMORESPACE,
	SSP_THEREISNOSPACE,
	SSP_DATAINSIZEERROR
}sspRet_t;

#define SSP_QTD_FMT(__ssp_qtdfmt__) (sizeof(__ssp_qtdfmt__) / sizeof(sspFmt_t))

#define SSP_VERSION_TYPE	uint16_t
#define SSP_FULLSIZE_TYPE	uint32_t

#define SSP_FIELDSIZE_TYPE	uint32_t
#define SSP_ID_TYPE			uint16_t

typedef struct _sspFmt_t{
	uint16_t id;
	sspRet_t (*toNet)(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);
	sspRet_t (*fromNet)(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc);
}sspFmt_t;

typedef struct _sspFetchCtx_t{
	uint32_t szFromNet;
	unsigned char *fetchWalker;
}sspFetchCtx_t;

typedef struct _ssp_t{
	SSP_VERSION_TYPE version;

	sspFmt_t *format;
	unsigned int qtdFmt;

	unsigned char *msg;
	unsigned char *msgWalker;
	size_t msgMaxSz;

	sspFetchCtx_t fetch;
}ssp_t;

sspRet_t sspCtx(ssp_t *ssp, uint16_t version, sspFmt_t *format, unsigned qtdFmt, unsigned char *msg, size_t msgMaxSz);

sspRet_t sspStartToNet(ssp_t *ssp);
sspRet_t sspStartFromNet(ssp_t *ssp);

sspRet_t sspStartFetch(ssp_t *ssp);
sspRet_t sspFetch(ssp_t *ssp);
sspRet_t sspGetRawDataField(ssp_t *ssp, SSP_FIELDSIZE_TYPE *szField, SSP_ID_TYPE *idField, unsigned char **rawData);
sspRet_t sspGetDataField(ssp_t *ssp, SSP_FIELDSIZE_TYPE *szField, SSP_ID_TYPE *idField, void **data, size_t szData);

sspRet_t sspSetVersion(ssp_t *ssp, uint16_t version);
uint16_t sspGetVersion(ssp_t *ssp);

char * sspReturnMessage(sspRet_t err);

sspRet_t sspPack(ssp_t *ssp, uint16_t id, void *dataIn, size_t dataInSz);
sspRet_t sspUnpack(ssp_t *ssp, uint16_t id, void *dataOut, size_t dataOutSz, size_t *proc);

sspRet_t sspCloseToNet(ssp_t *ssp);
sspRet_t sspMessage(ssp_t *ssp, unsigned char **msg, size_t *msgSz);

#endif
