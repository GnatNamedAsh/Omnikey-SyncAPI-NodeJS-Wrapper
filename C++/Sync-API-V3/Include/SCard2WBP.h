/**
 @brief Function declaration supporting 2 Wire Bus protocol credentials.

 @file SCard2WBP.h
 
 @copyright
 Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef __SCARD2WBP_H__
#define __SCARD2WBP_H__

#include <windows.h>
#ifndef S_WNT
    #define S_WNT
#endif
#include <ok.h>
#include <winscard.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCARD2W_MAX_DATA_LEN	256U
#define SCARD2W_PIN_LEN			3U

/**
@brief Reads main memory

This function corresponds to the 'Read Main Memory' operation (refer to the manual) and reads one or multiple bytes from the card.
The function reads out the content of the main memory (LSB first) starting at the given address (ulAddress=0...255).
Read access to the main memory is always possible.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulBytesToRead	Length of the data buffer
@param pbData			Pointer to the data buffer
@param ulAddress		Start offset for the read operation (0..255)

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPWriteData

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPReadData(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulBytesToRead,
						OUT	LPBYTE		pbData,
						IN	ULONG		ulAddress);

/**
@brief Reads protection memory

This function corresponds to the 'Read Protection Memory' operation (refer to the manual) and reads the protection bits of the first 32 bytes (byte 0 - byte 31).
Please note that the bit order of each byte is reversed, as shown below:
Bit 0 of returned byte 1 covers byte 7 of the protection memory
Bit 1 of returned byte 1 covers byte 6 of the protection memory
...
Bit 7 of returned byte 1 covers byte 0 of the protection memory
Bit 0 of returned byte 2 covers byte 15 of the protection memory

@note The length of ulDataLen must be four byte.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulDataLen		Length of the data buffer (must be 4)
@param pbData			Pointer to the data buffer

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPCompareAndProtect

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPReadProtectionMemory(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulDataLen,
						OUT	LPBYTE		pbData);

/**
@brief Updates main memory.

This function corresponds to the 'Update Main Memory' operation (refer to the manual) and writes one or multiple bytes to the card.
The function writes the data in the main memory starting at the given address (ulAddress = 0...255).

@note The SLE 4442 requieres a correct presention of the PIN (function SCard2WBPPresentPIN must have been called) for altering main memory data.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulDataLen		Length of the data buffer
@param pbData			Pointer to the data buffer
@param ulAddress		Start offset for the write operation (0..255)

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPReadData
@see SCard2WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPWriteData(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulDataLen,
						IN	LPBYTE		pbData,
						IN	ULONG		ulAddress);

/**
@brief Writes protection memory.

This function corresponds to the 'Write Protection Memory' operation (refer to the manual).
The execution of this command involves a comparison of the entered data byte bData with the assigned byte in the EEPROM (assigned by ulAddress).
If they match, the protection bit is written, making the data unchangeable. If there is not a match, writing of the protection bit is suppressed.

@note Only the first 32 byte (0...31) of the main memory can be protected.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param bData			Byte to be matched
@param ulAddress		Memory address (0...31)

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPReadProtectionMemory

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPCompareAndProtect(
						IN	SCARDHANDLE	ulHandleCard,
						IN	BYTE		bData,
						IN	ULONG		ulAddress);

/**
@brief Reads the error counter.

This function reads the error counter from the 'Securtiy Memory'.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param pbCounter		Pointer to the error counter

@return OK Standard Error Codes, see header file ok.h

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPReadErrorCounter(
						IN	SCARDHANDLE	ulHandleCard,
						OUT	LPBYTE		pbCounter);

/**
@brief  Checks and returns if PIN is already presented.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param pfPinPresented	TRUE if PIN is already presented

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPIsPinPresented(
						IN	SCARDHANDLE	ulHandleCard,
						OUT	LPBOOL		pfPinPresented);

/**
@brief Enables erasing and writing of the card.

This function sends the PIN pbPin to the card, which is followed by some cardcommands which checks the PIN.

@note The SLE 4442 requires a correct verification of the 'Programmable Security Code' (PSC) stored in the Security Memory for altering data.
\n In this API the PSC is called PIN.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulPINLen			Length of the PIN (must be 3)
@param pbPIN			Pointer to the PIN

@return OK Standard Error Codes, see header file ok.h
@return OKERR_OK if PIN is correct
@return OKERR_PW_WRONG if PIN is incorrect

@see SCard2WBPChangePIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCard2WBPPresentPIN(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulPINLen,
						IN	LPBYTE		pbPIN);

/**
@brief Changes the PIN of the card.

This function changes the PIN of the card. The length of the old (current) and the new PIN must be three bytes.

@note In this API the 'Programmable Security Code' (PSC) is called PIN.

@param ulHandleCard		Handle of the smart card (get from SCardConnect)
@param ulOldPINLen		Length of the old PIN (must be 3)
@param pbOldPIN			Pointer to the old PIN
@param ulNewPINLen		Length of the new PIN (must be 3)
@param pbNewPIN			Pointer to the new PIN

@return OK Standard Error Codes, see header file ok.h

@see SCard2WBPPresentPIN

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq 
*/
OKERR ENTRY SCard2WBPChangePIN(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulOldPINLen,
						IN	LPBYTE		pbOldPIN,
						IN	ULONG		ulNewPINLen,
						IN	LPBYTE		pbNewPIN);

						
OKERR ENTRY SCard2WBPReadSecurityMemory(
						IN	SCARDHANDLE	ulHandleCard,
						IN	ULONG		ulDataLen,
						OUT	LPBYTE		pbData);

#ifdef __cplusplus
}
#endif

#endif
