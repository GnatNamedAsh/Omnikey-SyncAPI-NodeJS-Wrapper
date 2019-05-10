// #include <winscard.h>
// #include <iostream>
// #include <cstdlib> 
// #include <string>
// #include "SmartcardClass.h"
// #include <fstream>

// //#define S_WIN
// #pragma comment(lib, "Winscard.lib")
// #pragma comment(lib, "scardsynx64.lib")

// #include "Include/SCardI2C.h"

// using std::cout;
// using std::endl;
// using std::string;

#include <napi.h>
#include "SmartcardWrap.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	return Smartcard::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll);

// int main() {
// //	LONG rv;
// //	
// //	SCARDCONTEXT hContext;
// //	LPTSTR mszReaders;
// //	SCARDHANDLE hCard;
// //	DWORD dwReaders, dwActiveProtocol, dwRecvLength;
// //
// //	SCARD_IO_REQUEST pioSendPci;
// //	BYTE readBuffer[1024];
// //	BYTE writeBuffer[1024];
// //
// //	BYTE cmd1[] = { 0xff, 0xd6, 0x00, 0x00, 0x0b, 0x48, 0x65, 0x6c, 0x6c,
// //		0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64 };
// //
// //	unsigned int i;
// //
// //	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
// //	CHECK("SCardEstablishContext", rv);
// //#ifdef SCARD_AUTOALLOCATE
// //	dwReaders = SCARD_AUTOALLOCATE;
// //	rv = SCardListReaders(hContext, NULL, (LPTSTR) &mszReaders, &dwReaders);
// //	CHECK("SCardListReaders", rv);
// //#else
// //	rv = SCardListReaders(hContext, NULL, NULL, &dwReaders);
// //	CHECK("SCardListReaders", rv);
// //
// //	mszReaders = calloc(dwReaders, sizeof(char));
// //	rv = SCardListReaders(hContext, NULL, mszReaders, &dwReaders);
// //	CHECK("SCardListReaders", rv);
// //#endif
// //
// //
// //	rv = SCardConnect(hContext, mszReaders, SCARD_SHARE_SHARED,
// //		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
// //	
// //
// //	string thing;
// //	cout << "Please enter the string you'd like to store: ";
// //	std::getline(std::cin, thing);
// //	
// //
// //	for (auto i = 0; i < 1024; ++i) {
// //		writeBuffer[i] = (byte)255;
// //	}
// //
// //	for (auto i = 0; i < 1024; ++i) {
// //		readBuffer[i] = (byte)255;
// //	}
// //	
// //	for (auto i = 0; i < thing.size(); i++) {
// //		writeBuffer[i] = thing[i];
// //	}
// //
// //	
// //	
// //	/*for (auto i = 0; i < 1024; i++) {
// //		cout << std::hex << std::setfill('0') << std::setw(2) << (int)writeBuffer[i] << " ";
// //	}*/
// //
// //	SCardI2CInit(hCard, 0, AT24C512);
// //
// //	SCardI2CWriteData(hCard, writeBuffer, 1024, 0000, thing.size());
// //
// //	cout << "The information being written to the card: " << thing << endl;
// //
// //	SCardI2CReadData(hCard, readBuffer, 1024, 0000, 1024);
// //

// //	//dwRecvLength = sizeof(pbRecvBuffer);
// //	//rv = SCardTransmit(hCard, &pioSendPci, cmd1, sizeof(cmd1),
// //	//	NULL, pbRecvBuffer, &dwRecvLength);
// //	//CHECK("SCardTransmit", rv)
// //
// //	//	printf("response: ");
// //	//for (i = 0; i < dwRecvLength; i++)
// //	//	printf("%02X ", pbRecvBuffer[i]);
// //	//printf("\n");
// //
// //	/*dwRecvLength = sizeof(pbRecvBuffer);
// //	rv = SCardTransmit(hCard, &pioSendPci, cmd2, sizeof(cmd2),
// //		NULL, pbRecvBuffer, &dwRecvLength);
// //	CHECK("SCardTransmit", rv)
// //
// //		printf("response: ");
// //	for (i = 0; i < dwRecvLength; i++)
// //		printf("%02X ", pbRecvBuffer[i]);
// //	printf("\n");
// //*/
// //	rv = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
// //	CHECK("SCardDisconnect", rv)
// //
// //#ifdef SCARD_AUTOALLOCATE
// //		rv = SCardFreeMemory(hContext, mszReaders);
// //	CHECK("SCardFreeMemory", rv)
// //
// //#else
// //		free(mszReaders);
// //#endif
// //
// //	rv = SCardReleaseContext(hContext);
// //
// //	CHECK("SCardReleaseContext", rv)
// //
// //		return 0;
// //
// 	SmartcardClass card;
// 	BYTE* data;

// 	std::streampos fileSize;
// 	std::ifstream file("Labadie956_Jeff209_19.json.gz", std::ios::binary);

// 	file.seekg(0, std::ios::end);
// 	fileSize = file.tellg();
// 	file.seekg(0, std::ios::beg);

// 	data = new BYTE[fileSize];
// 	file.read((char*)data, fileSize);

// 	cout << fileSize << endl;
// 	cout << (ULONG)fileSize << endl;

// 	cout << "Resetting data..." << endl;
// 	card.reset();

// 	cout << "Writing new data of size " << fileSize << " to the card..." << endl;
	
// 	card.write(data, fileSize);

// 	cout << "Reading the information from the card..." << endl;
// 	BYTE* information = card.read();
	
// 	for (int i = 0; i < ((ULONG)fileSize + 200); i++) {
// 		std::cout << information[i] << " ";
// 	}

// 	delete(information);
// 	delete(data);

// 	information = nullptr;
// 	data = nullptr;

// 	return EXIT_SUCCESS;
// }