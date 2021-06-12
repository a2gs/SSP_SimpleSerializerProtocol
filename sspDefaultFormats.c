/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 * https://sites.google.com/view/a2gs
 *
 * SSP - SimpleSerializerProtocol
 *
 * MIT License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
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
		return(SSP_THEREISNOSPACE);

	*proc = 1;

	*dataOut = *((unsigned char *)dataIn);

	return(SSP_OK);
}

sspRet_t charByeFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	unsigned char aux = 0;
	unsigned char *dest = NULL;

	if(dataOutSz != 1)
		return(SSP_DATAINSIZEERROR);

	if(dataInSz < 1)
		return(SSP_THEREISNOSPACE);

	*proc = 1;

	aux = *((unsigned char *)dataIn);
	dest = (unsigned char *)dataOut;

	*dest = aux;

	return(SSP_OK);
}

sspRet_t float32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	float aux = 0.0;
	float *orig = NULL;

	orig = dataIn;
	aux = *orig;

	snprintf((char *)dataOut, dataOutSz, "%f", aux);

	*proc = strnlen((char *)dataOut, dataOutSz);

	return(SSP_OK);
}

sspRet_t float32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	float *dest = NULL;

	dest = dataOut;

	*dest = strtof((char *)dataIn, NULL);

	*proc = sizeof(float);

	return(SSP_OK);
}

sspRet_t integer32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	snprintf((char *)dataOut, dataOutSz, "%d", *((int32_t *) dataIn));

	*proc = strnlen((char *)dataOut, dataOutSz);

	return(SSP_OK);
}

sspRet_t integer32FromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	float *dest = NULL;

	dest = dataOut;

	*dest = strtod((char *)dataIn, NULL);

	*proc = sizeof(int32_t);

	return(SSP_OK);
}
