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

int stringToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	*proc = (dataInSz < dataOutSz ? dataInSz : dataOutSz);

	memcpy(dataOut, dataIn, *proc);

	return(SSP_OK);
}

int stringFromNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	*proc = (dataInSz < dataOutSz ? dataInSz : dataOutSz);

	memcpy(dataOut, dataIn, *proc);
	dataOut[*proc] = '\0';

	return(SSP_OK);
}

int charByteToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

int charByeFromNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

int floatToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

int floatFromNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

int integer32ToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}

int integer32FromNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
	return(0);
}
