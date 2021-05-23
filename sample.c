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

typedef struct _myType_t{
	int a;
	char b[10];
	double c;
}myType_t;

int myTypeToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t *dataOutSz)
{
	return(0);
}

int myTypeFromNet(void *dataIn, size_t *dataInSz, unsigned char *dataOut, size_t dataOutSz)
{
	return(0);
}

#define MYPROTO_MAX_SZ (10000)

int main(int argc, char *argv[])
{
	sspFmt_t myFmt[] = {
		{1, stringToNet,   stringFromNet},
		{2, charByteToNet, charByeFromNet},
		{2, myTypeToNet,   myTypeFromNet},
		{4, floatToNet,    floatFromNet},
		{5, integerToNet,  integerFromNet}
	};
	ssp_t myProto;
	unsigned char buffer[MYPROTO_MAX_SZ] = {0};

	sspCtx(&myProto, 1, myFmt, SSP_QTD_FMT(myFmt), buffer, MYPROTO_MAX_SZ);

	sspStartToNet(&myProto);

	return(0);
}
