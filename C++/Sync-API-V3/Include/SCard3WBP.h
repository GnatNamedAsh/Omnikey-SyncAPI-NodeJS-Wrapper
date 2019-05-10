/**
 @brief Function declaration supporting 3 Wire Bus protocol credentials.

 @file SCard3WBP.h
 
 @copyright
 Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef __SCARD3WBP_H__
#define __SCARD3WBP_H__

#include <windows.h>
#ifndef S_WNT
    #define S_WNT
#endif
#include <ok.h>
#include <winscard.h>

#define SCARD3W_MAX_DATA_LEN	1024L
#define SCARD3W_PIN_LEN			2U

#ifdef __cplusplus
extern "C" {
#endif
/**
@brief Reads 8 bits data without protect bit.

This function corresponds to the 'Read 8 bits data without protect bit' operation (refer to the manual) and reads one or multiple bytes from the card.
This function is used to read a block of data of up to 1024 bytes (the maximum storage capacity) from the card into a buffer referenced by pbData.
ulAddress specifies the start address for the read operation on the card.

@note Note that ulAddress + ulBytesToRead must not be greater than 1024 (e.g. there is no wrap around).

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulBytesToRead	Number of bytes to read
@param pbReadBuffer		Pointer to the buffer
@param ulAddress		Start Offset for read operation

@return OK Standard Error Codes, see header file ok.h

@see SCard3WBPWriteData

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard3WBPReadData(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulBytesToRead,
					OUT	LPBYTE		pbReadBuffer,
					IN	ULONG		ulAddress);

/**
@brief Writes and erases with or without protect bit.

This function uses either the 'Erase and write without protect bit' operation or 'Erase and write with protect bit' operation to write one or multiple byte to the card.
This is used to write a block of data of up to 1024 bytes (the maximum storage capacity) to the card.
ulAddress specifies the start address for the write operation on the card.

@note ulAddress + ulDataLen must not be greater than 1024 (e.g. there is no wrap around).

fProtect = TRUE will set the write protection for every byte written.
The PIN must have been presented successfully before writing is possible on the SLE 4428 card.
After writing the block of data, the function performs an internal read-back and compare operation to verify that every byte has been written correctly.

@param ulHandleCard		Handle of the smart card
@param ulDataLen		Length of the data buffer
@param pbData			Pointer to the data buffer
@param ulAddress		Start offset of write operation
@param fProtect		Write and if 'TRUE' set protect bit

@return OK Standard Error Codes, see header file ok.h

@see	SCard3WBPReadData
@see	SCard3WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq 
*/
OKERR ENTRY SCard3WBPWriteData(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulDataLen,
					IN	LPBYTE		pbData,
					IN	ULONG		ulAddress,
					IN	BOOL		fProtect);

/**
@brief Writes protect bit with data comparision (verification).

This function corresponds to the 'Write protect bit with data comparision' operation (refer to the manual) to set a byte 'read only'.
This function is used to compare the byte bData and a byte in the card referenced by ulAdress. If they match, the byte is write-protected.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param bData			Byte to be matched
@param ulAddress		Memory address

@return OK Standard Error Codes, see header file ok.h

@see SCard3WBPWriteData

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard3WBPCompareAndProtect(
					IN	SCARDHANDLE	ulHandleCard,
					IN	BYTE		bData,
					IN	ULONG		ulAddress);

/**
@brief Reads 9 bits data with protect bit.

This function uses the 'Read 9 bits data with protect bit' operation (refer to the card manual) to determine if a byte is 'read only'.
This function is used to check a byte in the card referenced by ulAddress.
The flag referenced by pfProtect holds TRUE if the byte has the write protection set.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulAddress		Memory address
@param pfProtected		Pointer to the result

@return OK Standard Error Codes, see header file ok.h

@see     SCard3WBPWriteData
@see	SCard3WBPCompareAndProtect 

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard3WBPVerifyProtectBit(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulAddress,
					OUT	LPBOOL		pfProtected);

/**
@brief Reads 9 bits data with protect bit.

This function uses the 'Read 9 bits data with protect bit' operation (refer to the card manual) to determine if a byte is 'read only'.
This function is used to check the protection bits of the card starting at ulAddress.
The values of the protection bits (TRUE or FALSE) are stored in the passed buffer.

@note If the protection bits of 10 bytes are checked, the buffer must have a size of at least 10 bytes.

The protection bit of the first byte is stored in the first byte of the buffer, the protection bit of the second byte is stored in the second byte of the buffer, etc.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulBytesToRead	Number of bytes to check
@param pbReadBuffer		Pointer to the buffer
@param ulAddress		Start offset for check operation

@return OK Standard Error Codes, see header file ok.h

@see	SCard3WBPWriteData
@see	SCard3WBPCompareAndProtect

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq 
*/
OKERR ENTRY SCard3WBPVerifyProtectBitEx(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulBytesToRead,
					OUT	LPBYTE		pbReadBuffer,
					IN	ULONG		ulAddress);

/**
@brief Checks and returns if the PIN of the card is already presented.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param pfPinPresented	TRUE if PIN is already presented

@return OK Standard Error Codes, see header file ok.h

@see SCard3WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard3WBPIsPinPresented(
					IN	SCARDHANDLE	ulHandleCard,
					OUT	LPBOOL		pfPinPresented);

/**
@brief Enables erasing and writing of the card.

This function uses the 'Write error counter', the Compare 1st PIN, and the 2nd PIN operation (refer to the manual) to unlock the card.
This function is used to enable erasing and writing of the card. The PIN is referenced by pbPIN and must be two bytes long, so ulPinLen must be two.

@note The function sets the error counter to the maximum value of 8 retries after enabling. Refer to the card manual for details on PIN,
transport code and error counter.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulPINLen			Length of the PIN (must be 2)
@param pbPIN			Pointer to the PIN

@return OK Standard Error Codes, see header file ok.h

@see	SCard3WBPChangePIN
@see	SCard3WBPWriteData

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq 
*/
OKERR ENTRY SCard3WBPPresentPIN(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulPINLen,
					IN	LPBYTE		pbPIN);

/**
@brief Changes the PIN of the card.

This function changes the PIN of the card. The length of the old (current) and the new PIN must be two bytes.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulOldPINLen		Length of the old PIN (must be 2)
@param pbOldPIN			Pointer to the old PIN
@param ulNewPINLen		Length of the new PIN (must be 2)
@param pbNewPIN			Pointer to the new PIN

@return OK Standard Error Codes, see header file ok.h

@see SCard3WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard3WBPChangePIN(
					IN	SCARDHANDLE	ulHandleCard,
					IN	ULONG		ulOldPINLen,
					IN	LPBYTE		pbOldPIN,
					IN	ULONG		ulNewPINLen,
					IN	LPBYTE		pbNewPIN);

#ifdef __cplusplus
}
#endif

#endif
