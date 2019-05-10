#pragma once

#include <winscard.h>

#pragma comment(lib, "Winscard.lib")
#pragma comment(lib, "scardsynx64.lib")

#include "Include/SCardI2C.h"

class SmartcardClass
{
private:
	SCARDCONTEXT hContext;
	LPTSTR mszReaders;
	SCARDHANDLE hCard;
	DWORD dwReaders, dwActiveProtocol, dwRecvLength;
	/*BYTE readBuffer[1024];
	BYTE writeBuffer[1024];
	void resetWriteBuffer();
	void resetReadBuffer();*/

public:
	SmartcardClass();
	~SmartcardClass();
	bool write(BYTE* data, ULONG length);
	BYTE* read();
	bool reset();
};

