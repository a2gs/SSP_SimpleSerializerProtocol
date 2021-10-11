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
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "ssp.h"
#include "sspDefaultFormats.h"

typedef struct _myType_t{
	int a;
	char b[10];
	double c;
}myType_t;

sspRet_t myTypeToNet(void *dataIn, size_t dataInSz, unsigned char *dataOut, size_t dataOutSz, size_t *proc)
{
#define SSP_SAMPLE_MYTYPE_TONET_BUFFER_SZ (100)
	char buf[SSP_SAMPLE_MYTYPE_TONET_BUFFER_SZ] = {0};
	myType_t *myData = (myType_t *)dataIn;
	size_t fmtbuf = 0;

	snprintf(buf, SSP_SAMPLE_MYTYPE_TONET_BUFFER_SZ,
	         "<a fmt=int>%d</a><b fmt=str>%s</b><c fmt=double>%f</c>",
	         myData->a, myData->b, myData->c);

	fmtbuf = strnlen(buf, SSP_SAMPLE_MYTYPE_TONET_BUFFER_SZ);

	*proc = (fmtbuf < dataOutSz ? fmtbuf : dataOutSz);

	memcpy(dataOut, myData, *proc);

	return(SSP_OK);
}

sspRet_t myTypeFromNet(unsigned char *dataIn, size_t dataInSz, void *dataOut, size_t dataOutSz, size_t *proc)
{
	return(SSP_OK);
}

#define MYPROTO_MAX_SZ	(10000)
#define SAMPLE_SSP_OK	(0)
#define SAMPLE_SSP_ERROR	(1)

#define MYTYPE_ID_STRING (1)
#define MYTYPE_ID_CHAR   (2)
#define MYTYPE_ID_MYTYPE (3)
#define MYTYPE_ID_FLOAT  (4)
#define MYTYPE_ID_INT32  (5)

/* Used to write and read information: */
sspFmt_t myFmt[] = {
	{MYTYPE_ID_STRING, sspStringToNet,    sspStringFromNet},
	{MYTYPE_ID_CHAR,   sspCharByteToNet,  sspCharByteFromNet},
	{MYTYPE_ID_MYTYPE, myTypeToNet,        myTypeFromNet},
	{MYTYPE_ID_FLOAT,  sspFloat32ToNet,   sspFloat32FromNet},
	{MYTYPE_ID_INT32,  sspInteger32ToNet, sspInteger32FromNet}
};

#define SAMPLE_SSP_COMMON_RETURNING_CHECK(__sample_ret_) { \
																				if(ret != SSP_OK){                                                                            \
																					printf("[%s:%d] SSP error: [%s].\n", __FILE__, __LINE__, sspReturnMessage(__sample_ret_)); \
																					return(SAMPLE_SSP_ERROR);                                                                  \
																				}                                                                                             \
																			}

int sampleSSPWrite(void)
{
	ssp_t myProto;
	sspRet_t ret;
	unsigned char buffer[MYPROTO_MAX_SZ] = {0};

	unsigned char *msg = NULL;
	size_t msgSz = 0;

	int32_t a = 123;
	float b = 13.08;
	char c[] = "sample string";
	char d = 'a';
	myType_t e = {13, "abcde", 1.41};

	DEBUG("a=[%d] b=[%f] c=[%s] d=[%c] e=myType\n", a, b, c, d);

	ret = sspCtx(&myProto, 1, myFmt, SSP_QTD_FMT(myFmt), buffer, MYPROTO_MAX_SZ);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspStartToNet\n");

	/* sspSetVersion(&myProto, 2); */

	ret = sspStartToNet(&myProto);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspPack(c)\n");

	ret = sspPack(&myProto, MYTYPE_ID_STRING, &c, strlen(c));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspPack(d)\n");

	ret = sspPack(&myProto, MYTYPE_ID_CHAR, &d, 1);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspPack(e)\n");

	ret = sspPack(&myProto, MYTYPE_ID_MYTYPE, &e, sizeof(myType_t));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspPack(b)\n");

	ret = sspPack(&myProto, MYTYPE_ID_FLOAT, &b, sizeof(float));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspPack(a)\n");

	ret = sspPack(&myProto, MYTYPE_ID_INT32, &a, sizeof(int32_t));
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspCloseToNet\n");

	ret = sspCloseToNet(&myProto);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspMessage\n");

	ret = sspMessage(&myProto, &msg, &msgSz);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("write\n");

	if(write(STDERR_FILENO, msg, msgSz) != (ssize_t) msgSz){
		printf("[%s:%d] write error: [%s].\n", __FILE__, __LINE__, strerror(errno));
		return(SAMPLE_SSP_ERROR);
	}

	return(SAMPLE_SSP_OK);
}

int sampleSSPRead(void)
{
	ssp_t myProto;
	sspRet_t ret;
	unsigned char buffer[MYPROTO_MAX_SZ] = {0};
	unsigned int i = 0;
	ssize_t readRet = 0;

	readRet = read(STDIN_FILENO, buffer, MYPROTO_MAX_SZ);
	if(readRet == -1){
		printf("[%s:%d] read error: [%s].\n", __FILE__, __LINE__, strerror(errno));
		return(SAMPLE_SSP_ERROR);
	}

	printf("Size read: [%zd]\n", readRet);

	/* version = 0. Set version here is futile, we will read it from net */
	ret = sspCtx(&myProto, 0, myFmt, SSP_QTD_FMT(myFmt), buffer, MYPROTO_MAX_SZ);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	DEBUG("sspStartToNet\n");

	ret = sspStartFromNet(&myProto);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	ret = sspStartFetch(&myProto);
	SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	for(i = 0; ; i++){
		SSP_FIELDSIZE_TYPE szField;
		SSP_ID_TYPE idField;
		unsigned char *rawData = NULL;
		void *data = NULL;

		ret = sspFetch(&myProto);
		SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

		ret = sspGetRawDataField(&myProto, &szField, &idField, &rawData);
		SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

		ret = sspGetDataField(&myProto, &szField, &idField, &data);
		SAMPLE_SSP_COMMON_RETURNING_CHECK(ret);

	}

	return(SAMPLE_SSP_OK);
}

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("Sample usage:\n\t%s [write|read]\n\n\twrite - Write to ouput sample buffer\n\tread - Read from STDIN a message\n", argv[0]);
		return(1);
	}

	if(strncmp("write", argv[1], strlen(argv[1])) == 0){
		sampleSSPWrite();
	}else if(strncmp("read", argv[1], strlen(argv[1])) == 0){
		sampleSSPRead();
	}else{
		printf("Erro parameter [%s]. Allowed: 'write' or 'read'\n", argv[1]);
		return(1);
	}

	return(0);
}
