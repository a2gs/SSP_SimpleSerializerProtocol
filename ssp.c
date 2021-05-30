/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 * https://sites.google.com/view/a2gs
 *
 * SSP - SimpleSerializerProtocol
 *
 * MIT License
 */

#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "ssp.h"

/*
ID
0 - string
1 - int
2 - float
3 - date
 
2bytes4bytes|2bytes4bytes...|

VERSIONfull_sz|IdSszabcde|IdSzabcde|IdSzabcde
VERSION full_sz   Id Sz abcde    Id Sz abcde   Id Sz abcde
*/

sspRet_t sspCtx(ssp_t *ssp, uint16_t version, sspFmt_t *format, unsigned int qtdFmt, unsigned char *msg, size_t msgMaxSz)
{
	ssp->version = version;
	ssp->format = format;
	ssp->qtdFmt = qtdFmt;
	ssp->msg = msg;
	ssp->msgMaxSz = msgMaxSz;

	sspStartFetch(ssp); /* ssp->msgWalker */

	return(SSP_OK);
}

sspRet_t sspStartFetch(ssp_t *ssp)
{
	/* Jumping VERSION and FULLSIZE */
	ssp->msgWalker = ssp->msg + sizeof(uint16_t) + sizeof(uint32_t);

	return(SSP_OK);
}

sspRet_t sspStartToNet(ssp_t *ssp)
{
	memset(ssp->msg, 0, ssp->msgMaxSz);
	sspStartFetch(ssp);

	return(SSP_OK);
}

sspRet_t sspCloseToNet(ssp_t *ssp)
{
	/* write the size (ssp->msg[msgSz] - ssp->msg), if < smgMaxLen */
	return(SSP_OK);
}

/* ================================== */

/* #include <arpa/inet.h>
 *
 * uint32_t htonl(uint32_t hostlong);
 * uint16_t htons(uint16_t hostshort);
 * uint32_t ntohl(uint32_t netlong);
 * uint16_t ntohs(uint16_t netshort);
 */

sspRet_t writeFmtIdAndData(ssp_t *ssp, uint16_t fmtId, void *dataIn, size_t dataInSz)
{
	uint32_t szNetByteOrder = 0;
	uint16_t idNetByteOrder = 0;
	size_t sz = 0;
	size_t szLeft = 0;

#define SSP_SIZEOF_SZFMTID_SZFIELD (sizeof(uint16_t) + sizeof(uint32_t))

	szLeft = &ssp->msg[ssp->msgMaxSz] - ssp->msgWalker;

	/* Check size at least to fmt id and field size */
	if(szLeft < SSP_SIZEOF_SZFMTID_SZFIELD)
		return(SSP_THEREISNOMORESPACE);

	idNetByteOrder = htons(fmtId);
	memcpy(ssp->msgWalker, &idNetByteOrder, sizeof(uint16_t));


	ssp->format[fmtId].toNet(dataIn, dataInSz, ssp->msgWalker + SSP_SIZEOF_SZFMTID_SZFIELD, szLeft - SSP_SIZEOF_SZFMTID_SZFIELD, &sz);

	/* write field size to buffer */
	szNetByteOrder = ntohl((uint32_t)sz);
	memcpy(ssp->msgWalker + sizeof(uint16_t), &szNetByteOrder, sizeof(uint32_t));

	return(SSP_OK);
}

sspRet_t pack(ssp_t *ssp, uint16_t id, void *dataIn, size_t dataInSz)
{
	unsigned int i = 0;

	for(i = 0; i <= ssp->qtdFmt; i++){
		if(ssp->format[i].id == id){
			if(writeFmtIdAndData(ssp, i, dataIn, dataInSz) == SSP_ERROR){
				return(SSP_ERROR);
			}

			return(SSP_OK);
		}
	}

	return(SSP_ERROR);
}

sspRet_t unpack(ssp_t *ssp, uint16_t id, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}
