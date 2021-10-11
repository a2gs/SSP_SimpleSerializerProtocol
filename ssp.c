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
 
2bytes4bytes|2bytes4bytes...|2bytes4bytes...|2bytes4bytes...|
VERSIONfull_sz|IdSszabcde|IdSzabcde|IdSzabcde
VERSION full_sz   Id Sz abcde    Id Sz abcde   Id Sz abcde

*/

#define SSP_SIZEOF_VERSION_FULLSIZE (sizeof(SSP_VERSION_TYPE) + sizeof(SSP_FULLSIZE_TYPE))

sspRet_t sspSetToInitMsgWalker(ssp_t *ssp)
{
	ssp->msgWalker = ssp->msg + SSP_SIZEOF_VERSION_FULLSIZE;

	return(SSP_OK);
}

SSP_FULLSIZE_TYPE sspGetFullsizeFromNet(ssp_t *ssp)
{
	SSP_FULLSIZE_TYPE szFromNet = 0;

	memcpy(&szFromNet, ssp->msg + sizeof(SSP_VERSION_TYPE), sizeof(SSP_FULLSIZE_TYPE));

	return(ntohl(szFromNet));
}

sspRet_t sspCtx(ssp_t *ssp, SSP_VERSION_TYPE version, sspFmt_t *format, unsigned int qtdFmt, unsigned char *msg, size_t msgMaxSz)
{
	ssp->version = version;
	ssp->format = format;
	ssp->qtdFmt = qtdFmt;
	ssp->msg = msg;
	ssp->msgMaxSz = msgMaxSz;

	sspSetToInitMsgWalker(ssp);

	return(SSP_OK);
}

char * sspReturnMessage(sspRet_t err)
{
	char *ret = NULL;

	switch(err){
		case SSP_ERROR:
			ret = "Error";
			break;

		case SSP_TRUNCATEDBUTTHEREISNOMORESPACE:
			ret = "Data truncated. There is no more space.";
			break;

		case SSP_THEREISNOSPACE:
			ret = "There is no more space.";
			break;

		case SSP_DATAINSIZEERROR:
			ret = "Input data size is not correct.";
			break;

		default:
			ret = "Ok";
	}

	return(ret);
}

SSP_VERSION_TYPE sspGetVersion(ssp_t *ssp)
{
	return(ssp->version);
}

sspRet_t sspSetVersion(ssp_t *ssp, SSP_VERSION_TYPE version)
{
	ssp->version = version;

	return(SSP_OK);
}

sspRet_t sspFetch(ssp_t *ssp)
{

	return(SSP_OK);
}

sspRet_t sspGetRawDataField(ssp_t *ssp, SSP_FIELDSIZE_TYPE *szField, SSP_ID_TYPE *idField, unsigned char **rawData)
{

	return(SSP_OK);
}

sspRet_t sspGetDataField(ssp_t *ssp, SSP_FIELDSIZE_TYPE *szField, SSP_ID_TYPE *idField, void **rawData)
{

	return(SSP_OK);
}

sspRet_t sspStartFetch(ssp_t *ssp)
{
	ssp->fetch.szFromNet = sspGetFullsizeFromNet(ssp);
	ssp->fetch.fetchWalker = ssp->msg + SSP_SIZEOF_VERSION_FULLSIZE;

	return(SSP_OK);
}

int sspLoadVersion(ssp_t *ssp)
{
	SSP_VERSION_TYPE versionNetByteOrder = 0;

	memcpy(&versionNetByteOrder, ssp->msg, sizeof(SSP_VERSION_TYPE));
	ssp->version = ntohs(versionNetByteOrder);

	return(SSP_OK);
}

int sspWriteVersion(ssp_t *ssp)
{
	SSP_VERSION_TYPE versionNetByteOrder = 0;

	versionNetByteOrder = htons(ssp->version);
	memcpy(ssp->msg, &versionNetByteOrder, sizeof(SSP_VERSION_TYPE));

	return(SSP_OK);
}

sspRet_t sspStartToNet(ssp_t *ssp)
{
	memset(ssp->msg, 0, ssp->msgMaxSz);
	sspSetToInitMsgWalker(ssp);

	return(SSP_OK);
}

sspRet_t sspStartFromNet(ssp_t *ssp)
{
	sspLoadVersion(ssp);
	sspSetToInitMsgWalker(ssp);

	return(SSP_OK);
}

int sspWriteFullsize(ssp_t *ssp)
{
	SSP_FULLSIZE_TYPE szNetByteOrder = 0;

	szNetByteOrder = ntohl((uint32_t)(ssp->msgWalker - ssp->msg));
	memcpy(ssp->msg + sizeof(SSP_VERSION_TYPE), &szNetByteOrder, sizeof(SSP_FULLSIZE_TYPE));

	return(SSP_OK);
}

sspRet_t sspCloseToNet(ssp_t *ssp)
{
	sspWriteVersion(ssp);
	sspWriteFullsize(ssp);

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

sspRet_t sspWriteFmtIdSizeAndData(ssp_t *ssp, unsigned int fmtIndex, SSP_ID_TYPE fmtId, void *dataIn, size_t dataInSz)
{
	SSP_FIELDSIZE_TYPE szNetByteOrder = 0;
	SSP_ID_TYPE idNetByteOrder = 0;
	size_t sz = 0, szLeft = 0;
	sspRet_t retFmt = SSP_ERROR;

#define SSP_SIZEOF_SZFMTID_SZFIELD (sizeof(SSP_VERSION_TYPE) + sizeof(SSP_FIELDSIZE_TYPE)) /* id + size */

	szLeft = ssp->msgMaxSz - (ssp->msgWalker - ssp->msg);

	DEBUG("Size total: [%ld] Size left: [%ld]\n", ssp->msgMaxSz, szLeft);

	/* TODO */
	/* Check size at least to fmt id and field size */  // TODO: aqui podemos ver se ha espaco para data
	/* This code MUST (__MUST__) be alive, but today there is no way. We need format this field in another buffer
	 * and after check (and then copy) to ssp->msgWalker
	if(szLeft < SSP_SIZEOF_SZFMTID_SZFIELD + (sizeof(dataaaaaaaaaaaaaa) ?????? ) )
		return(SSP_THEREISNOSPACE);
	*/

	/* write field id to buffer */
	idNetByteOrder = htons(fmtId);
	memcpy(ssp->msgWalker, &idNetByteOrder, sizeof(SSP_ID_TYPE));

	/* write field size to buffer */
	szNetByteOrder = ntohl((uint32_t)sz);
	memcpy(ssp->msgWalker + sizeof(SSP_ID_TYPE), &szNetByteOrder, sizeof(SSP_FIELDSIZE_TYPE));

	/* write field data to buffer */
	retFmt = ssp->format[fmtIndex].toNet(dataIn, dataInSz, ssp->msgWalker + SSP_SIZEOF_SZFMTID_SZFIELD, szLeft - SSP_SIZEOF_SZFMTID_SZFIELD, &sz);

	if(retFmt != SSP_OK)
		return(SSP_ERROR);

	ssp->msgWalker += SSP_SIZEOF_SZFMTID_SZFIELD + sz;
	return(SSP_OK);
}

sspRet_t sspPack(ssp_t *ssp, SSP_ID_TYPE id, void *dataIn, size_t dataInSz)
{
	unsigned int i = 0;

	for(i = 0; i < ssp->qtdFmt; i++){
		if(ssp->format[i].id == id){

			DEBUG("format matches: %d\n", id);

			if(sspWriteFmtIdSizeAndData(ssp, i, id, dataIn, dataInSz) == SSP_ERROR){
				return(SSP_ERROR);
				DEBUG("format error\n");
			}

			return(SSP_OK);
		}
	}

	DEBUG("format not found\n");
	return(SSP_ERROR);
}

sspRet_t sspUnpack(ssp_t *ssp, SSP_ID_TYPE id, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

sspRet_t sspMessage(ssp_t *ssp, unsigned char **msg, size_t *msgSz)
{
	if((ssp->msg == NULL) || (ssp->msgWalker == NULL))
		return(SSP_ERROR);

	*msg   = ssp->msg;
	*msgSz = ssp->msgWalker - ssp->msg;

	return(SSP_OK);
}
