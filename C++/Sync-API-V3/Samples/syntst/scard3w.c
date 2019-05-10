/** •
•@file scard3w.c
•@brief <Brief description> *


•$Id$ *
•@date Oct 31, 2011
•@version $Revision$
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/




/*****************************************************************************/
/** GLOBAL INCLUDES                                                         **/
/*****************************************************************************/


#include <okos.h>
#if defined S_WIN || defined S_WNT
   #include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include <ok.h>

#include "scrn.h"
#include "scrni.h"
//#include <str.h>
//#include <mem.h>

#include <winscard.h>
#include "syntst.h"

/*****************************************************************************/
/**  EXTERN DECLARATIONS                                                    **/
/*****************************************************************************/

/*****************************************************************************/
/**  GLOBAL DECLARATIONS                                                    **/
/*****************************************************************************/

static  CHAR    szText[160] = "\0";           /* Common string for text I/O */


#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF

//#define _CRT_SECURE_NO_WARNINGS


/*****************************************************************************/
/** LOCAL FUNCTION PROTOTYPES                                               **/
/*****************************************************************************/



/*****************************************************************************/
/**  IMPLEMENTATION                                                         **/
/*****************************************************************************/


/*****************************************************************************/
/** SUBROUTINES                                                             **/
/*****************************************************************************/




/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPReadData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1024];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "TEST SCard3WBPRead");
   SCRNPutTextAt( 2, 29, "-------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength         :");
   ulDataLen=SCRNGetULongAt(usLine++,23,1,1024);
   SCRNPutTextAt(usLine, 2,"Address            :");
   ulAddress=SCRNGetULongAt(usLine++,23,0,1023);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/
   eErr = SCard3WBPReadData(ulHandleSmartCard,
                          ulDataLen,
                          abData,
                          ulAddress);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   //StrPrintf(szText," (%dms)",ulTime2);
   sprintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      WriteBuffer(abData, ulDataLen, &usLine, 0);
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


VOID TestSCard3WBPVerifyProtectBitEx(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1024];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "TEST SCard3WBPVerifyProtectBitEx");
   SCRNPutTextAt( 2, 29, "--------------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength         :");
   ulDataLen=SCRNGetULongAt(usLine++,23,1,1024);
   SCRNPutTextAt(usLine, 2,"Address            :");
   ulAddress=SCRNGetULongAt(usLine++,23,0,1023);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/
   eErr = SCard3WBPVerifyProtectBitEx(ulHandleSmartCard,
                          ulDataLen,
                          abData,
                          ulAddress);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   //StrPrintf(szText," (%dms)",ulTime2);
   sprintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      WriteBuffer(abData, ulDataLen, &usLine, 0);
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPPresentPIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abPIN[4];

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPPresentPin");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"PIN (2 Byte)    :");
   SCRNGetTextAt(usLine++, 20, 2, abPIN, sizeof(abPIN));

   /*---- Call function to test ----*/

   eErr = SCard3WBPPresentPIN(ulHandleSmartCard,
                            2,
                            abPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPVerifyProtectBit(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   ULONG  ulAddress;
   BOOL   fProtected;

   SCRNClear();
   SCRNPutTextAt( 1, 24, "TEST SCard3WBPVerifyProtectBit");
   SCRNPutTextAt( 2, 24, "-------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Address         :");
   ulAddress=SCRNGetULongAt(usLine++,20,0,1023);

   /*---- Call function to test ----*/
   eErr = SCard3WBPVerifyProtectBit (ulHandleSmartCard,
                                   ulAddress,
                                   &fProtected);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      if (fProtected)
         SCRNPutTextAt(usLine, 2,"This byte is PROTECTED");
      else
         SCRNPutTextAt(usLine, 2,"This byte is unprotected");
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}



/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPWriteData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1025];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;
   BOOL  fProtect;

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPWriteData");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength  :");
   ulDataLen=SCRNGetULongAt(usLine++,16,1,1024);
   SCRNPutTextAt(usLine, 2,"Data        :");
   SCRNGetTextAt(usLine++, 16,(USHORT)ulDataLen, abData, sizeof(abData));
   SCRNPutTextAt(usLine, 2,"Address     :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,1023);
   SCRNPutTextAt(usLine, 2,"Protect (0=FALSE/1=TRUE) :");
   fProtect=SCRNGetULongAt(usLine++,30,0,1);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/

   eErr = SCard3WBPWriteData(ulHandleSmartCard,
                           ulDataLen,
                           abData,
                           ulAddress,
                           fProtect);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   //StrPrintf(szText," (%dms)",ulTime2);
   sprintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}

/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPCompareAndProtect(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   bData[2];
   ULONG  ulAddress;

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPCompareAndProtect");
   SCRNPutTextAt( 2, 27, "--------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datenbyte   :");
   SCRNGetTextAt(usLine++, 16,1,bData,sizeof(bData));
   SCRNPutTextAt(usLine, 2,"Addresse    :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,1023);

   /*---- Call function to test ----*/
   eErr = SCard3WBPCompareAndProtect(ulHandleSmartCard,
                                   bData[0],
                                   ulAddress);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPChangePIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abOldPIN[4];
   BYTE   abNewPIN[4];

   SCRNClear();
   SCRNPutTextAt( 1, 30, "TEST SCard3WBPChangePIN");
   SCRNPutTextAt( 2, 30, "------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Old PIN (2 Byte):");
   SCRNGetTextAt(usLine++, 20, 2, abOldPIN, sizeof(abOldPIN));
   SCRNPutTextAt(usLine, 2,"New PIN (2 Byte):");
   SCRNGetTextAt(usLine++, 20, 2, abNewPIN, sizeof(abNewPIN));

   /*---- Call function to test ----*/
   eErr = SCard3WBPChangePIN(ulHandleSmartCard,
                           2, abOldPIN,
                           2, abNewPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPIsPinPresented(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BOOL   fPinPresented = FALSE;

   SCRNClear();
   SCRNPutTextAt( 1, 25, "TEST SCard3WBPIsPinPresented");
   SCRNPutTextAt( 2, 25, "-----------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);

   /*---- Call function to test ----*/
   eErr = SCard3WBPIsPinPresented(ulHandleSmartCard,
                                &fPinPresented);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr == NO_ERROR)
      {
      if (fPinPresented)
         SCRNPutTextAt(13, 2, "PIN is presented!");
      else
         SCRNPutTextAt(13, 2, "PIN is not presented!");
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}








