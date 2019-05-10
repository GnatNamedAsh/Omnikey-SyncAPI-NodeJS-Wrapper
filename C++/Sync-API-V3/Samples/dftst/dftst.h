/**
•
•@file bdftst.h
•@brief     :	  *
•$Id$ *
•@date      : Oct 31, 2011
•@version :2.0.0.0
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/

#ifndef _INC_DFTST
   #define _INC_DFTST


	#ifdef __cplusplus
	extern "C" {
	#endif

   VOID TestSCardConnect(VOID);

   VOID TestSCardReconnect(VOID);

   VOID TestSCardDisconnect(VOID);

   VOID HandleError(
						DWORD dwErrorFlags
						);

	VOID WriteBuffer(
						GPBYTE pbBuffer,
						ULONG ulLength,
						GPUSHORT pusLineNumb,
						ULONG ulPos
						);

   VOID ErrorMessage(
							OKERR eErr
							);


	#ifdef __cplusplus
	}
	#endif

#endif  /* _INC_DFTST */





