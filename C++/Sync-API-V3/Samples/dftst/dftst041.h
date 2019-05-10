/**
•
•@file	    dftst041.h
•@brief     :	  *
•<Long description> * ?

•$Id$ *
•@date      : Oct 31, 2011
•@version :2.0.0.0
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/

#ifndef _INC_DFTST041
   #define _INC_DFTST041

	
	#ifdef __cplusplus
	extern "C" {
	#endif
		

	//
	// Read
	//
	VOID TestAT45DB041_ContinuousArrayRead (
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_MainMemoryPageRead (
										SCARDHANDLE ulHandleSmartCard
										);

	VOID TestAT45DB041_BufferRead (
									SCARDHANDLE ulHandleSmartCard
									);
	
	VOID TestAT45DB041_StatusRegRead(
				 					SCARDHANDLE ulHandleSmartCard
				 					);


	//
	// Program and erase test functions
	//
	VOID TestAT45DB041_BufferWrite(
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_BufferToMainMemoryPageProgram (
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_PageErase (
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_BlockErase (
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_MainMemoryPageProgramThroughBuffer (
											SCARDHANDLE ulHandleSmartCard
											);


	//
	// Additional commands
	//
	VOID TestAT45DB041_MainMemoryPageToBufferTransfer(
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_MainMemoryPageToBufferCompare(
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_AutoPageRewriteThroughBuffer(
													SCARDHANDLE ulHandleSmartCard
													);

	#ifdef __cplusplus
	}
	#endif


#endif  /* _INC_DFTST041 */



