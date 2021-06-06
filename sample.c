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

#define MYTYPE_ID_STRING (1)
#define MYTYPE_ID_CHAR   (2)
#define MYTYPE_ID_MYTYPE (3)
#define MYTYPE_ID_FLOAT  (4)
#define MYTYPE_ID_INT32  (5)

int main(int argc, char *argv[])
{
	sspFmt_t myFmt[] = {
		{MYTYPE_ID_STRING, stringToNet,    stringFromNet},
		{MYTYPE_ID_CHAR,   charByteToNet,  charByeFromNet},
		{MYTYPE_ID_MYTYPE, myTypeToNet,    myTypeFromNet},
		{MYTYPE_ID_FLOAT,  float32ToNet,   float32FromNet},
		{MYTYPE_ID_INT32,  integer32ToNet, integer32FromNet}
	};
	ssp_t myProto;
	sspRet_t ret;
	unsigned char buffer[MYPROTO_MAX_SZ] = {0};

	int32_t a = 123;
	float b = 13.08;
	char c[] = "sample string";
	char d = 'a';
	myType_t e = {13, "abcde", 1.41};

#define SAMPLE_SSP_COMMON_RETURNING_CHECK(__sample_ret_) { \
																				if(ret != SSP_OK){                                                                            \
																					printf("[%s:%d] SSP error: [%s].\n", __FILE__, __LINE__, sspReturnMessage(__sample_ret_)); \
																					return(-1);                                                                                \
																				}                                                                                             \
																			}

	ret = sspCtx(&myProto, 1, myFmt, SSP_QTD_FMT(myFmt), buffer, MYPROTO_MAX_SZ);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspStartToNet(&myProto);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspPack(&myProto, MYTYPE_ID_STRING, &c, strlen(c));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspPack(&myProto, MYTYPE_ID_CHAR, &d, 1);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspPack(&myProto, MYTYPE_ID_MYTYPE, &e, sizeof(myType_t));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspPack(&myProto, MYTYPE_ID_FLOAT, &b, sizeof(float));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspPack(&myProto, MYTYPE_ID_INT32, &a, sizeof(int32_t));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspCloseToNet(ssp);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

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
