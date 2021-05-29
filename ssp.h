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

/*
#define SSP_OK    (1)
#define SSP_ERROR (0)
*/
enum SSP_ret_t{
    SSP_OK = 1,
    SSP_ERROR,
    SSP_TRUNCATEDBUTTHEREISNOMORESPACE,
    SSP_THEREISNOMORESPACE
};

#define SSP_QTD_FMT(__ssp_qtdfmt__) (sizeof(__ssp_qtdfmt__) / sizeof(sspFmt_t))

typedef struct _sspFmt_t{
	uint16_t id;
	int (*toNet)(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);
	int (*fromNet)(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc);
}sspFmt_t;

typedef struct _ssp_t{
	uint16_t version;
	sspFmt_t *format;
	unsigned int qtdFmt;
	unsigned char *msg;
	unsigned char *msgWalker;
	size_t msgMaxSz;
}ssp_t;

int sspCtx(ssp_t *ssp, uint16_t version, sspFmt_t *format, unsigned qtdFmt, unsigned char *msg, size_t msgMaxSz);
int sspStartToNet(ssp_t *ssp);
int sspStartFetch(ssp_t *ssp);

int pack(ssp_t *ssp, uint16_t id, void *dataIn, size_t dataInSz);
int unpack(ssp_t *ssp, uint16_t id, void *dataOut, size_t dataOutSz, size_t *proc);

#endif
