/** •
•@file syntst.h
•@brief <Brief description> *
•$Id$ *
•@date Oct 31, 2011
•@version $Revision$
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/


#ifndef _INC_SYNTST
   #define _INC_SYNTST

   #include <winscard.h>
   #include <SCard2WBP.h>
   #include <SCard3WBP.h>

/*****************************************************************************/
/** usefull constants                                                       **/
/*****************************************************************************/


   #define SLESCard2WBP_MAX_DATA_LEN     256   //@cnst Maximum len of data send to the SLE SCard2WBP SC
   #define SLESCard2WBP_PIN_LEN          3     //@cnst Length of PIN


/*****************************************************************************/
/** S28I function interface                                                 **/
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif

   VOID main(VOID);

   VOID TestSCardConnect(VOID);
   VOID TestSCardReconnect(VOID);
   VOID TestSCardDisconnect(VOID);
   VOID HandleError(DWORD dwErrorFlags);

   VOID TestSCard3WBPReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPPresentPIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPVerifyProtectBit(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPWriteData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPCompareAndProtect(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPChangePIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPIsPinPresented(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPVerifyProtectBitEx(SCARDHANDLE ulHandleSmartcard);

   VOID TestSCard2WBPReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPPresentPIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadProtectionMemory(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPWriteData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPCompareAndProtect(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadErrorCounter(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPIsPinPresented(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPChangePIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadSecurityMemory(SCARDHANDLE ulHandleSmartcard);

   //MP010321+   I2C bus cards in test_i2c.c
   VOID TestSCard_I2C_Init(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard_I2C_ReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard_I2C_WriteData(SCARDHANDLE ulHandleSmartcard);
   //MP010321.

   VOID TestSCard4404ReadData(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404WriteData(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404VerifyUserCode(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseErrorCounter(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseUserMemory(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseScratchPadMemory(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404Status(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404ChangeUserCode(SCARDHANDLE ulHandleSmartCard);
   
   BOOL SelectReader(VOID);

   GPCHAR StrError(OKERR eErr);
   VOID ErrorMessage(OKERR eErr);

   VOID WriteBuffer(GPBYTE pbBuffer, ULONG ulLength, GPUSHORT pusLineNumb,
                    ULONG ulPos);


   #ifdef __cplusplus
}
   #endif


#endif  /* _INC_SYNTST */




