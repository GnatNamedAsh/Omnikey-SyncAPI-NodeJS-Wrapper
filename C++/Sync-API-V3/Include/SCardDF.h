
/**
@brief Function declaration supporting ATMEL DataFlash credentials.

@file SCardDF.h

@copyright
Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef _INC_SCARD_SPI
   #define _INC_SCARD_SPI

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
	
#include <ok.h>


//
// All structures and unions are aligned with 1.
// The initial pack value is saved in old_value, it will be restored with pop below.
//

#pragma pack(push,old_value,1)




// DEFINE card types: the constants below are according the i2c card type used
typedef enum _SCARD_DATA_FLASH_TYPE
   {
   // DataFlash cards from Atmel:
   AT45DB041 = 0xc1,
   DATAFLASH_TYPE_ENUM_TAIL          // must always be the last entry in this enum!!
   }
SCARD_DATA_FLASH_TYPE, *PSCARD_DATA_FLASH_TYPE;

//
// AT45DB041B
//
#define AT45DB041_TOTAL_PAGES 						2048
#define AT45DB041_PAGE_SIZE	 						264
#define AT45DB041_BUFFER_SIZE 						264
#define AT45DB041_MAX_BLOCK_NUMBER 					255

#ifdef __cplusplus
extern "C" {
#endif

/**
	* Initializes the library for DataFlash card specified with <b>Type</b>. The function must be called once at the beginning before using any other command.

	* @param ulHandleCard Handle to the DataFlash card.
	* @param Type  Type of the DataFlash
	* @return NO_ERROR     The shared library is initialized
	* @return OKERR_INIT   The shared library is not initialized because DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfInit(
								IN SCARDHANDLE	 	   	ulHandleCard,	
								IN SCARD_DATA_FLASH_TYPE Type
								);

/**
	* Sequentially reads continuous number of bytes from the main memory. Depending on the start byte address <b>ulByteAdr</b> and <b>ulBytesToRead</b>, page boundaries can be crossed.
	* \n It is up to the application to provide a read buffer with the necessary length.
	
	* @param ulHandleCard  Handle to the DataFlash card.
	* @param pbReadBuffer  Pointer to the buffer where the data read are to be stored.
	* @param ulReadBufferSize Read buffer size
	* @param ulPageAdr Page number of the start address
	* @param ulByteAdr Page relative byte number of the start address
	* @param ulBytesToRead Number of bytes to read.
	* @param pulBytesReturned  Number of bytes actually read.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT   The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfContinuousArrayRead(
										IN SCARDHANDLE ulHandleCard,   	
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										OUT PULONG    	pulBytesReturned	
										);

/**
	* Main Memory Page Read allows the user to read data directly from one of the pages in the main memory bypassing both of the data buffers and leaving the contents of the buffers unchanged. 
	No page boundary is crossed. When the end of a page in the main memory is reached, the read will continue at the beginning of the same page. 
	It is up to the application to provide a read buffer with the necessary length.
	
	* @param ulHandleCard 	Handle to the DataFlash card.
	* @param pbReadBuffer 	Pointer to the buffer where the data read are to be stored.
	* @param ulReadBufferSize	Read buffer size
	* @param ulPageAdr	Page number of the start address
	* @param ulByteAdr 	Page relative byte number of the start address.
	* @param ulBytesToRead 	Number of bytes to read.
	* @param pulBytesReturned 	Number of bytes actually read.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	        The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfMainMemoryPageRead(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										OUT PULONG    	pulBytesReturned	
										);
/**
	* Data can be read from either one of the two buffers indicated through <b>ucBufferNumber</b>. For the dataflash cards supported there are two buffers numbered 1 and 2.
	* \n When the end of a buffer is reached, the read will continue back at the beginning of the buffer. It is up to the application to provide a read buffer with the necessary length.
	
	* @param ulHandleCard  Handle to the DataFlash card.
	* @param pbReadBuffer Pointer to the buffer where the data read are to be stored.
	* @param ulReadBufferSize Read buffer size.
	* @param ulByteAdr Byte number of the start address in the buffer.
	* @param ulBytesToRead  Number of bytes to read.
	* @param ucBufferNumber Number 1 or 2 of the buffer to read from.
	* @param pulBytesReturned Number of bytes actually read.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT   The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfBufferRead(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										IN UCHAR			ucBufferNumber,
										OUT PULONG    	pulBytesReturned	
										);

/**
	* The status register can be used to determine the device's Ready/Busy status, the result of a Main Memory Page to Buffer Compare operation or the device density.
	* \n Please, refer to the technical specification of the DataFlash card used to obtain the meaning of the different bits of the status byte.
	
	* @param ulHandleCard 	Handle to the DataFlash card.
	* @param pbReadBuffer 	Pointer to the buffer where the status byte is to be stored.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	  The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfStatusRegisterRead(
  										IN SCARDHANDLE ulHandleCard,
  										IN BYTE    		*pbReadBuffer
  										);

/**
	* Writes the data pointed by <b>pbWriteBuffer</b> into DataFlash buffer indicated through <b>ucBufferNumber.</b>
	* \n If the end of the buffer is reached, the write will wrap around back to the beginning of the buffer.
	
	* @param ulHandleCard Handle to the DataFlash card.
	* @param pbWriteBuffer  Pointer to the buffer holding data to be written
	* @param ulByteAdr Byte number of the start address in the buffer
	* @param ulBytesToWrite Number of bytes to write
	* @param ucBufferNumber Number 1 or 2 of the buffer to be written.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT   The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfBufferWrite(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE     	*pbWriteBuffer,
										IN ULONG    	ulByteAdr,
										IN ULONG    	ulBytesToWrite,
										IN UCHAR			ucBufferNumber
										);

/**
	* Data written into either buffer 1 or buffer 2 can be programmed into main memory with or without initial erasure of the destination page.
	* \n Erase parameter specifies if the destination page in the main memory is first to be erased.
	* \n <b>fErase</b> :
	* \n 1 program with erase
	* \n 0 program without erase
	* \n Successive page programming operations without doing page erase are not recomended.
	
	* @param ulHandleCard Handle to the DataFlash card.
	* @param ucBufferNumber Number 1 or 2 of the buffer to transfer.
	* @param ulPageAdr Destination page number to be programmed.
	* @param fErase Program with=1 / without=0 erase.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT   The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfBufferToMainMemoryPageProgram(
										IN SCARDHANDLE	ulHandleCard,   //  Handle (get from SCardConnect)
										IN UCHAR			ucBufferNumber,
										IN ULONG   		ulPageAdr,   	         //  page address to read from
										IN BOOL			fErase
										);

/**
	* Erases the specified page in the main memory

	* @param ulHandleCard 	Handle to the DataFlash card.
	* @param ulPageAdr 	Page number to be erased.

	* @return OK Standard Error Codes	(See header file ok.h)
	
	* @return OKERR_INIT	  The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY  SCardDfPageErase(
										IN SCARDHANDLE	ulHandleCard,
										IN ULONG   		ulPageAdr
										);

/**
	* A block of pages can be erased with this single operation. Erases the block specified with <b>ulBlockNr</b> number in the main memory.
	
	* @param ulHandleCard  Handle to the DataFlash card.
	* @param ulBlockNr Number of the block to be erased.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT    The shared library is not initialized or DataFalsh card type is not supported.
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY  SCardDfBlockErase(
										IN SCARDHANDLE	ulHandleCard,
										IN ULONG   		ulBlockNr
										);

/**
	* This operation is a combination of the "buffer write" and "buffer to main memory page program with build in erase" operations.
	* \n Data is first written in buffer 1 or buffer 2 and then programmed into the specified page in the main memory. 
	If the end of the buffer is reached, the write will wrap around back to the beginning of the buffer.
	
	* @param ulHandleCard  Handle to the DataFlash card.
	* @param pbWriteBuffer  Pointer to the buffer holding data to be written
	* @param ulPageAdr Page number of the start address
	* @param ulByteAdr Page relative byte number of the start address.
	* @param ulBytesToWrite Number of bytes to
	* @param ucBufferNumber Number 1 or 2 of the buffer to be programmed into the main memory page
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	  The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfMainMemoryPageProgramThroughBuffer (
										IN SCARDHANDLE ulHandleCard,
										IN BYTE     	*pbWriteBuffer,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToWrite,
										IN UCHAR			ucBufferNumber
										);

/**
	* A page of data can be transferred from main memory page to either buffer 1 or buffer 2. The old content of the selected buffer will be lost.
	
	* @param ulHandleCard 	Handle to the DataFlash card.
	* @param ucBufferNumber 	Number 1 or 2 of the buffer to receive the main memory page
	* @param ulPageAdr 	Number of the page in the main memory to be transferred.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	  The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfMainMemoryPageToBufferTransfer(
  										IN SCARDHANDLE	ulHandleCard,
  										IN UCHAR			ucBufferNumber,
  										IN ULONG   		ulPageAdr
  										);

/**
	* A page of data in main memory can be compared to the data in buffer 1 or buffer 2. The status register of the DataFlash card is updated. 
	For AT45DB041B this is bit-6. For the other DataFlash types, please refer to the technical specification.
	
	* @param ulHandleCard 	Handle to the DataFlash card.
	* @param ucBufferNumber 	Number 1 or 2 of the buffer to be compared.
	* @param ulPageAdr 	Number of the page in the main memory to be compared.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	  The shared library is not initialized or DataFalsh card type is not supported
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardDfMainMemoryPageToBufferCompare(
														IN SCARDHANDLE	ulHandleCard,
														IN UCHAR			ucBufferNumber,
														IN ULONG   		ulPageAdr
														);

/**
	* This mode is only needed if multiple bytes within a page or multiple pages of data are modified in a random fashion.
	* \n This mode is a combination of two operations: Main Memory Page to Buffer Transfer and Buffer to Main Memory Page Program with Build-In Erase.
	* \n A page of data is first transferred from the main memory to buffer-1 or -2, and then the same data is programmed back into its original page of main memory.
	
	* @param ulHandleCard  Handle to the DataFlash card.
	* @param ucBufferNumber  Buffer number 1 or 2 to rewrite.
	* @param ulPageAdr Number of the page in the main memory to be rewritten.
	
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT    The shared library is not initialized or DataFalsh card type is not supported.
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .

*/
OKERR ENTRY SCardDfAutoPageRewriteThroughBuffer(
														IN SCARDHANDLE	ulHandleCard,
														IN UCHAR			ucBufferNumber,
														IN ULONG   		ulPageAdr
														);

#ifdef __cplusplus
}
#endif

#pragma pack(pop,old_value)
// Restóre the old packing value.

#endif  /* _INC_SCARD_SPI */