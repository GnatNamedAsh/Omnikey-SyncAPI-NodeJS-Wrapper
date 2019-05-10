/**
@brief Function declaration supporting SLE4404 credentials.

@file SCard4404.h

@copyright
Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef _INC_SC4404
   #define _INC_SC4404

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
   #include <ok.h>
   #include <winscard.h>

#define  SCARD4404_MEMORY_SIZE_IN_BIT            416
#define  SCARD4404_MEMORY_COUNTER_SIZE_IN_BIT     64
#define  SCARD4404_ERROR_COUNTER_SIZE_IN_BIT       4

#define  SCARD4404_MEMORY_COUNTER_ADDRESS         112
#define  SCARD4404_ERROR_COUNTER_ADDRESS          80
#define  SCARD4404_SCRATCH_PAD_MEMORY_ADDRESS     96


/*****************************************************************************/
/** FUNCTIION PROTOTYPES                                                    **/
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif
/**
    *This function reads number of bits (ulBitsToRead)  from the specified bit-address (ulBitAddress). The data read is stored in the buffer pointed to by pbReadBuffer.
    * \note For non-readable memory address (user code, memory code, read-protected user memory) the bit value returned by the SLE4404 is always 1.
	
	* @param ulHandleCard  Handle of the smart card.
    * @param ulBitsToRead  Length of the data buffer.
	* @param ulBitAddress Start offset for the read operation. 
    * @param pbReadBuffer Pointer to the data buffer.
	* @param ulReadBufferSize Pointer to the data buffer.
	* @return pbReadBuffer Pointer to the data buffer.
	
	* @return OK Standard Error Codes (see header file ok.h)
	
	\see \ref SCard4404WriteData
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .

*/
OKERR ENTRY SCard4404ReadData(
                                 IN  SCARDHANDLE ulHandleCard,
                                 IN  ULONG       ulBitsToRead,
                                 IN  ULONG       ulBitAddress,
                                 OUT LPBYTE      pbReadBuffer,
                                 ULONG           ulReadBufferSize);

/**

	*This function writes data to the card.
	*\n Writing on a SLE4404 card means clearing bits, i.e. it is only possible to change bits from one to zero, but not vice-versa.
	\n If there is a write request where an already cleared bit should be set to 1, an error will be returned and the memory area must be erased first.

	*\note Correct verification of User Code and / or Memory Code is mandatory before calling this function.

	*@param ulHandleCard Handle of the smart card
	*@param pbData Pointer to the data buffer
	*@param ulBitsToWrite Number of bits to write
	*@param ulBitAddress Start offset for the write operation


	*@return OK Standard Error Codes (see header file ok.h)
	
	*@see \ref SCard4404ReadData
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404WriteData(
                                 IN  SCARDHANDLE  ulHandleCard,
                                 IN  LPBYTE       pbData,
                                 IN  ULONG        ulBitsToWrite,
                                 IN  ULONG        ulBitAddress);

/**
	*This function performs the erase operation on the user memory.
	\n It writes a non-written bit in the memory counter area specified when ulBitAddress is set to 0, immediatley followed by an erase-operation without incrementing the address.
	*\note Correct verification of user code and / or memory code is mandatory before calling this function.
	
	*@param ulHandleCard Handle of the smart card
	*@param ulBitAddress Adress of any non-written bit of the Memory Counter


	*@return OK Standard Error Codes (see header file ok.h)
	*@see \ref SCard4404EraseErrorCounter \n \ref SCard4404EraseScratchPadMemory
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404EraseUserMemory(
                                 IN  SCARDHANDLE  ulHandleCard,
                                 IN  ULONG        ulBitAddress);

/**
	*This function performs the erase operation on the scratch pad memory.
	* \note Correct verification of the user code is mandatory before calling this function
	
	*@param ulHandleCard Handle of the smart card
	*@param ulBitAddress Adress of any bit in the Scratch Pad Memory


	*@return OK Standard Error Codes (see header file ok.h)
	*@see \ref SCard4404EraseErrorCounter \n \ref SCard4404EraseUserMemory
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404EraseScratchPadMemory(
                                 IN  SCARDHANDLE  ulHandleCard,
                                 IN  ULONG        ulBitAddress);

/**
	*This function performs the erase operation on the error counter.
	* \note Correct verification of the user code is mandatory before calling this function.
	
	*@param ulHandleCard Handle of the smart card
	*@param ulBitAddress Adress of any bit in the Error Counter
	*@return OK Standard Error Codes (see header file ok.h)
	
	*@see \ref SCard4404EraseScratchPadMemory \n \ref SCard4404EraseUserMemory
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404EraseErrorCounter(
                                 IN  SCARDHANDLE  ulHandleCard,
                                 IN  ULONG        ulBitAddress);
/**
	*This function performs the entry of the user code.
	*It presents the User Code. It searches for a "1" bit in the error counter and writes the bit to "0". 
	*Finally it will erase the error counter. If all bits of the error counter are erased(="1") the verification was sccuessful.
	
	*@param ulHandleCard Handle of the smart card
	*@param pbData Pointer to the data buffer
	*@return OK Standard Error Codes (see header file ok.h)
	
	*@see \ref SCard4404WriteData \ref SCard4404ReadData
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404VerifyUserCode(
                                 IN  SCARDHANDLE  ulHandleCard,
                                 IN  LPBYTE       pbData);

/**
	*This function exchanges the old user code with the new one. 
	This is done by verifying the old user code first, erasing the user code area, and then writing the new user code. 
	Finally a verification of the user code is performed.
	
	*@param ulHandleCard Handle of the smart card
	*@param pbOldPin Pointer to the data buffer
	*@param pbNewPin Pointer to the data buffer
	*@return OK Standard Error Codes (see header file ok.h)
	
	*@see \ref SCard4404WriteData \n \ref SCard4404VerifyUserCode
	
	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCard4404ChangeUserCode(
								IN  SCARDHANDLE  ulHandleCard,
								IN  LPBYTE       pbOldPin,
								IN  LPBYTE       pbNewPin);
   #ifdef __cplusplus
}
   #endif

#endif  /* _INC_SC4404 */
