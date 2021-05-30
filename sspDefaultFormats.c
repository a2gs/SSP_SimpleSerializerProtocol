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
#include "ssp.h"

/*
 * TO NET:
 * dataIn -> typed input (host origin -> net dest)
 * dataOut -> formatted to 'unsgiedn char *' output (dest)
 *
 * FROM NET:
 * dataIn -> formatted 'unsgiedn char *' input (net oringin -> host dest)
 * dataOut -> typed output (dest)
 */

sspRet_t stringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	*proc = (dataInSz < dataOutSz ? dataInSz : dataOutSz);

	memcpy(dataOut, dataIn, *proc);

	return(SSP_OK);
}

sspRet_t stringFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	*proc = (dataInSz < dataOutSz ? dataInSz : dataOutSz);

	memcpy(dataOut, dataIn, *proc);
	*((unsigned char *)dataOut + *proc) = '\0';

	return(SSP_OK);
}

sspRet_t charByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	if(dataInSz != 1)
		return(SSP_DATAINSIZEERROR);

	if(dataOutSz == 0)
		return(SSP_THEREISNOMORESPACE);

	*proc = 1;

	*dataOut = *((unsigned char *)dataIn);

	return(SSP_OK);
}

sspRet_t charByeFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

sspRet_t floatToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

sspRet_t floatFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

sspRet_t integer32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

sspRet_t integer32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}
