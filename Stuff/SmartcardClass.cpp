#include "SmartcardClass.h"
#include <cmath>
#include <iostream>

SmartcardClass::SmartcardClass()
{
	

	SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);

#ifdef SCARD_AUTOALLOCATE
	dwReaders = SCARD_AUTOALLOCATE;
	SCardListReaders(hContext, NULL, (LPTSTR)& mszReaders, &dwReaders);

#else
	SCardListReaders(hContext, NULL, NULL, &dwReaders);


	mszReaders = calloc(dwReaders, sizeof(char));
	SCardListReaders(hContext, NULL, mszReaders, &dwReaders);

#endif


	SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);

	SCardI2CInit(hCard, 0, AT24C512);

}


SmartcardClass::~SmartcardClass()
{
	SCardDisconnect(hCard, SCARD_LEAVE_CARD);
	SCardReleaseContext(hContext);
}

bool SmartcardClass::write(BYTE* data, ULONG length) {
	
	SCardI2CWriteData(hCard, data, length, 0000, length);
	return true;
}

BYTE* SmartcardClass::read() {
	BYTE* information = new BYTE[1024 * 64];
	SCardI2CReadData(hCard, information, 1024 * 64, 0000, 1024 * 64);
	
	return information;
}

bool SmartcardClass::reset() {
	BYTE* null_data = new BYTE[1024 * 64];

	for (int i = 0; i < (1024 * 64); i++) {
		null_data[i] = (byte)255;
	}

	SCardI2CWriteData(hCard, null_data, 1024 * 64, 0, 1024 * 64);
	delete(null_data);
	null_data = nullptr;

	return true;
}
//void SmartcardClass::resetReadBuffer() {
//	for (auto i = 0; i < 1024; i++) {
//		readBuffer[i] = (byte)255;
//	}
//}
//
//void SmartcardClass::resetWriteBuffer() {
//	for (auto i = 0; i < 1024; i++) {
//		writeBuffer[i] = (byte)255;
//	}
//}