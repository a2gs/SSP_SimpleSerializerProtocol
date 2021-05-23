#include <stddef.h>
#include <string.h>
#include "ssp.h"

/*
ID
0 - string
1 - int
2 - float
3 - date
 
2bytes4bytes|BITMAP|2bytes4bytes...|
VERSIONfull_sz|BITMAP|IdSszabcde|IdSzabcde|IdSzabcde


2bytes4bytes|4Bytes2bytes4bytes...|
VERSIONfull_sz|TagIdSszabcde|TagIdSzabcde|TagIdSzabcde


DumpMsg()
*/

int sspCtx(ssp_t *ssp, unsigned int version, sspFmt_t *format, unsigned int qtdFmt, unsigned char *msg, size_t msgMaxSz)
{
	ssp->version = version;
	ssp->format = format;
	ssp->qtdFmt = qtdFmt;
	ssp->msg = msg;
	ssp->msgMaxSz = msgMaxSz;

	ssp->msgSz = 0;

	return(SSP_OK);
}

int sspStartFetch(ssp_t *ssp)
{
	ssp->msgSz = 0;

	return(SSP_OK);
}

int sspStartToNet(ssp_t *ssp)
{
	memset(ssp->msg, 0, ssp->msgMaxSz);
	sspStartFetch(ssp);

	return(SSP_OK);
}

/* ================================== */

int stringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz)
{
	return(0);
}

int stringFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz)
{
	return(0);
}

int charByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz)
{
	return(0);
}

int charByeFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz)
{
	return(0);
}

int floatToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz)
{
	return(0);
}

int floatFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz)
{
	return(0);
}

int integerToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz)
{
	return(0);
}

int integerFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz)
{
	return(0);
}

/* ================================== */

int pack(unsigned int id, void *dataIn, size_t *dataInSz)
{
	return(0);
}

int unpack(unsigned int id, void *dataOut, size_t dataOutSz)
{
	return(0);
}
