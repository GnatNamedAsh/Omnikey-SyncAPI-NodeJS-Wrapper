/**
@brief Function declaration supporting iClass synchronious credentials.

@file SCardCL.h

@copyright
Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef _INC_SCARD_CL
   #define _INC_SCARD_CL

#include <windows.h>
#ifndef S_WNT
	#define S_WNT
#endif

#include <ok.h>

   #ifdef __cplusplus
extern "C" {
   #endif

/**
	*The function <b>SCardCLiCLASSTransmit</b> does the communication between the reader and an iCLASS card.
	*\n This function is the only gateway to work with iCLASS card. The parameters must be in accordance to the APDU described in the <a href="https://www.hidglobal.com/sites/default/files/resource_files/5321-903_b.4_omnikey_contactless_developer_guide_en.pdf">OMNIKEY CL Developer Guide</a>.

	*@param ulHandleCard Handle to the iCLASS card, provided from the "smart card resource manager" after connecting the card (SCardConnect)
	*@param pucSendData	the APDU must be according to the specification
	*@param ulSendDataBufLen length of the APDU
	*@param pucReceivedData	a buffer provided to receive the response
	*@param pulReceivedDataBufLen length of the provided buffer is given, it returns the actual received bytes
	
	*@return OK Standard Error Codes (see header file ok.h)
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardCLICCTransmit(IN SCARDHANDLE		ulHandleCard,
								  IN PUCHAR     		pucSendData,				
                         		  IN ULONG       		ulSendDataBufLen,
                        		  IN OUT PUCHAR			pucReceivedData,
								  IN OUT PULONG			pulReceivedDataBufLen);

   #ifdef __cplusplus
}
   #endif

#endif  /* _INC_SCARD_CL */