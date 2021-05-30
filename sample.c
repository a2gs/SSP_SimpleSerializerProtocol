/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 * https://sites.google.com/view/a2gs
 *
 * SSP - SimpleSerializerProtocol
 *
 * MIT License
 */

#include <stdio.h>
#include <stddef.h>
#include "ssp.h"
#include "sspDeafultFormats.h"

typedef struct _myType_t{
	int a;
	char b[10];
	double c;
}myType_t;

sspRet_t myTypeToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz, size_t *proc)
{
	return(SSP_OK);
}

sspRet_t myTypeFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(SSP_OK);
}

#define MYPROTO_MAX_SZ (10000)

int main(int argc, char *argv[])
{
	sspFmt_t myFmt[] = {
		{1, stringToNet,    stringFromNet},
		{2, charByteToNet,  charByeFromNet},
		{2, myTypeToNet,    myTypeFromNet},
		{4, float32ToNet,   float32FromNet},
		{5, integer32ToNet, integer32FromNet}
	};
	ssp_t myProto;
	unsigned char buffer[MYPROTO_MAX_SZ] = {0};

	sspCtx(&myProto, 1, myFmt, SSP_QTD_FMT(myFmt), buffer, MYPROTO_MAX_SZ);

	sspStartToNet(&myProto);

	sspStartFetch(ssp);

	/*
	sspPack(....);
	sspPack(....);
	sspPack(....);
	sspPack(....);
	sspPack(....);
	sspPack(....);
	sspPack(....);
	sspPack(....);
	*/

	sspCloseToNet(ssp);

	/*
	send(ssp->msg);

	reset ssp to receive (empty ssp->msg)

	sspStartFetch(ssp_t *ssp)

	sspUnpack(....);
	sspUnpack(....);
	sspUnpack(....);
	sspUnpack(....);
	sspUnpack(....);
	*/

	return(SSP_OK);
}

int sspStartToNet(ssp_t *ssp)
	return(0);
}
