/**
@brief Function declaration supporting SM credentials

@file SCardSM.h

@copyright
Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef _INC_SCARD_SM
   #define _INC_SCARD_SM
	
#include <windows.h>
#ifndef S_WNT
	#define S_WNT
#endif
	
#include <ok.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define MAX_USER_ZONES 										8
#define MAX_USER_ZONE_LENGTH								256
#define MAX_PAGE_LENGTH										64

#define DEFAULT_SM_SLAVE_ADDRESS							0xb0
#define PASSWORD_LENGTH										3

#define HOST_RANDOM_NUMBER_LEN								8


//	
// Verify password command b3,b2 indicating the passoword index used in the compare operation
//				
#define AT88SC153_WRITE_PASSWORD_0_INDEX					0x00
#define AT88SC153_READ_PASSWORD_0_INDEX						0x02
#define AT88SC153_WRITE_PASSWORD_1_INDEX					0x01
#define AT88SC153_READ_PASSWORD_1_INDEX						0x03
//
// Secure code password is the same as WRITE_PASSWORD_1
//
#define AT88SC153_SECURE_CODE_INDEX							0x01

//
// Fuse indeces
//
#define AT88SC153_FAB_FUSE_INDEX							0x01
#define AT88SC153_CMA_FUSE_INDEX							0x02
#define AT88SC153_PER_FUSE_INDEX							0x04


#define AT88SC153_PASSWORD_CONFIG_ZONE_ADR  				0x30
#define AT88SC1608_PASSWORD_CONFIG_ZONE_ADR  				0x40


#define AT88SC153_AUTHENTICATION_ATTEMPTS_COUNTER_ADR		0x20

// Limits of the bit field
#define AT88SC153_VERIFY_PASSWORD_INDEX_MASK				0x03
#define AT88SC1608_VERIFY_PASSWORD_INDEX_MASK				0x0f

#define PAC_SUCCESS 										0xff
#define AAC_SUCCESS 										0xff

//ct->
#define AT88SC101_MAX_SIZE								    1520
#define AT88SC102_MAX_SIZE								    1568
#define AT88SC1003_MAX_SIZE								    1600

#define AT88SC10X_FUSE_MANUFACTURER							1
#define AT88SC10X_FUSE_ISSUER								2
#define AT88SC10X_FUSE_ECEN									3
//<-ct

// Constants used as a SecureMemory card type

typedef enum _SCARD_SECURE_MEMORY_TYPE
   {
   AT88SC153 = 0,
   AT88SC1608,
   AT88SC101,
   AT88SC102,
   AT88SC1003,
	// .......
	NOT_SUPPORTED
   }
SCARD_SECURE_MEMORY_TYPE, *PSCARD_SECURE_MEMORY_TYPE;

/**
	* SCardSmInit Initializes the shared library for SecureMemory card specified with <b>Type</b>.
	*\n The function must be called once at the beginning before using any other command and when a new card is inserted in the reader.
	*\n AT88SC153 only:
	*\n The I2c bus slave address in the most significant 4 bits of the command byte will be set to 0xB0.
	*\n Any second chip select (i2c-bus device slave) address set so far will be disabled.
	*\n AT88SC1608 only:
	*\n Initializes the user zone address register with 0 through calling SCardSmSetUserZoneAddress library function.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param Type Type of the SecureMemory card for which the library will be initialized

	* @return NO_ERROR	The shared library is initialized
	* @return OKERR_INIT	The shared library is not initialized, because SecureMemory card type is not supported

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmInit(
						IN SCARDHANDLE	ulHandleCard, 	
						IN SCARD_SECURE_MEMORY_TYPE   Type
						);

/**
	* SCardSmReadUserZone
	\note Only for AT88SC153 and AT88SC1608
	
	This function reads a number of bytes from the specified user zone.
	When the "Read Password Enable" Bit in the access register AR, corresponding to the selected user zone, is set, 
	"Verify Password" must be executed with read or write password to allow read operations in the user zone. 
	Password select bits PWx define which of the password sets must be presented to allow access to the user zone.
	*\n AT88SC1608: Executes also the command "Set user zone address" (0xB2), in case the user zone parameter is different from the current user zone. 
	\note After SCardSmInit() function the current user zone is 0.


	* @param ulHandleCard Handle to the SecureMemory card
	* @param pbReadBuffer Pointer to the buffer where to store the read data
	* @param ulReadBufferSize Read buffer size
	* @param ulUserZone User zone number to read from
	* @param ulByteAdr Address to start reading from, relative to zone begin
	* @param ulBytesToRead Number of bytes to read
	* @param pulBytesRead Number of bytes actually read

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_ILLEGAL_ARGUMENT	"Roll over" to the first byte in the page is imminent

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmReadUserZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer,
								IN ULONG    	ulReadBufferSize,	
								IN ULONG 		ulUserZone,			
								IN ULONG    	ulByteAdr,   		
								IN ULONG    	ulBytesToRead,		
								OUT PULONG  	pulBytesRead	
								);

/**
	* SCardSmReadConfigurationZone
	\note Only for AT88SC153 and AT88SC1608.
	
	Reads number of bytes from the configuration zone. 
	When secure code password is not successfully verified some configuration sub-zones will not be able to read and instead the internal value - 0xFF or the fuse byte will be received from the card. 
	For more details see the data sheets of the corresponding SecureMemory card.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param pbReadBuffer Pointer to the buffer where the data read will be stored
	* @param ulReadBufferSize Read buffer size
	* @param ulByteAdr Address in the configuration zone to start reading from
	* @param ulBytesToRead Number of bytes to read
	* @param pulBytesRead Number of bytes actually read

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_ENOUGH_MEMORY	Read buffer size provided is smaller than bytes to read
	* @return OKERR_ILLEGAL_ARGUMENT	"Roll over" to the first byte in the zone is imminent

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmReadConfigurationZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer,
								IN ULONG    	ulReadBufferSize,		
								IN ULONG    	ulByteAdr,
								IN ULONG    	ulBytesToRead,
								OUT PULONG  	pulBytesRead
								);

/**
	* SCardSmWriteUserZone 
	\note Only for AT88SC153 and AT88SC1608.
	
	Writes bytes in the defined user zone.
	\n Write address plus bytes to write may be longer than a write page size and the write operation can cross a page border. 
	In this case the write operation is split in pages and several internal write page commands are issued. 
	This is transparent to the user application and it doesn't have to bother about the write page size. 
	At the end of each internal write page command a 20[ms] delay for the "write cycle time, Twr" is imposed according to the requirements of the AT88SC153 and AT88SC1608 devices.
	\n If write address plus bytes to write are longer than the zone size an error will be returned indicating possible "roll over" to the beginning of the user zone.
	*\n Please note that the ability to write in particular addresses from the user zone is dependent on successful write password verification and settings in the corresponding access register.

	*\n AT88SC1608:
	*\n Executes internally also the command 0xB2 "Set user zone address", in case the user zone parameter is different from the current user zone and the last is updated.
	*\note During the personalization (PER=1) the WPE bit in the access register is forced active and writing in the user zone is only successful after password verification.


	* @param ulHandleCard Handle to the SecureMemory card.
	* @param pbWriteBuffer Pointer to the buffer where the data read will be stored.
	* @param ulUserZone User zone to read from
	* @param ulByteAdr Page relative byte number of the start address
	* @param ulBytesToWrite Number of bytes to write
	* @param pulBytesWritten Number of bytes actually written

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_ILLEGAL_ARGUMENT	"Roll over" is imminent or an invalid user zone number as parameter.

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmWriteUserZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbWriteBuffer,
								IN ULONG 		ulUserZone,
								IN ULONG    	ulByteAdr,
								IN ULONG    	ulBytesToWrite,
								OUT PULONG  	pulBytesWritten	
								);

/**
	* SCardSmWriteConfigurationZone
	*\n Only for AT88SC153 and AT88SC1608:
	*\n Writes bytes in the defined configuration zone address. Please refer to the AT88SC153 and AT88SC1608 data sheets to get the address, 
	the meanings and the access rights to particular configuration sub-zones.
	*\n The write address plus bytes to write can be longer than a write page size and the write operation can cross a page border. 
	In this case the write operation is split in pages and several internal write page commands are issued. 
	This is transparent to the user application and it doesn't have to bother about the write page size. 
	At the end of each internal write page command a 20[ms] delay for the "write cycle time, Twr" is imposed according to the requirements of the AT88SC153 and AT88SC1608 devices.
	*\n If write address plus bytes to write are longer than the zone size an error will be returned indicating possible roll over to the beginning of the selected user zone.
	*\n Please note, that the ability to write on particular addresses from the configuration zone is dependent from successful secure code verification.
	*\n This command can also be used for setting a new read and write password for the different user zones.


	* @param ulHandleCard Handle to the SecureMemory card
	* @param pbWriteBuffer Pointer to the buffer where the data read will be stored.
	* @param ulByteAdr Address in the configuration zone to start writing
	* @param ulBytesToWrite Number of bytes to write
	* @param pulBytesWritten Number of bytes actually written after execution of the command

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_ILLEGAL_ARGUMENT	"Roll over" is imminent
	* @return OKERR_WRITE_FIO	The number of bytes actually written is not equal to the number of bytes intended to write

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .

*/
OKERR ENTRY SCardSmWriteConfigurationZone(
	  					 		IN SCARDHANDLE ulHandleCard,   		
	  					  		IN PBYTE   		pbWriteBuffer,
	  					  		IN ULONG    	ulByteAdr,   			
	  					  		IN ULONG    	ulBytesToWrite,		
	  					  		OUT PULONG  	pulBytesWritten	
	  					  		);

/**
	* SCardSmVerifyPassword
	*\n Only for AT88SC153 and AT88SC1608:
	*\n The function verifies the password present in the buffer with the password index <b>ucPasswordIndex</b> in the password configuration sub-zone.
	*\n If the password verification is successful, after the operation the corresponding password attempts counter will be reset and will have the value 0xff. 
	Otherwise, the next higher significant bit from the PAC will be cleared.

	* @param ulHandleCard Handle to the SecureMemory card.
	* @param pbPasswordBuffer Pointer to the buffer holding the 3 byte long password. The bytes are send to the card beginning with the first byte, index 0 of the buffer.
	* @param ucPasswordIndex Index of the password set used in the verification. Bit-3 is 0 for write and 1 for read password sets.
	* @param pucAttemptCounter Pointer to an address where the new value of the corresponding password attempts counter (PAC) received form the card will be written

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .

*/
OKERR ENTRY SCardSmVerifyPassword(
	  					 		IN SCARDHANDLE ulHandleCard,   			
	  					  		IN PBYTE   		pbPasswordBuffer,
								IN	UCHAR			ucPasswordIndex,			
								OUT PUCHAR		pucAttemptCounter			
	  					  		);

/**
	* SCardSmReadFuses
	*\n Only for AT88SC153 and AT88SC1608:
	*\n Reads the fuses byte


	* @param ulHandleCard Handle to the SecureMemory card.
	* @param pbReadBuffer Pointer to the buffer where the data read will be stored.


	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmReadFuses(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer
								);

/**
	* SCardSmWriteFuses
	*\n Only for AT88SC153 and AT88SC1608:
	*\n Blows a fuse bit from the fuses register in the configuration zone.
	*\n The fuses are blown (set to 0) sequentially: FAB,CMA,PER.
	*\n Write fuses command is only enabled when the secure code is verified successfully.
	*\n AT88SC1608: The command has the same code as write configuration zone, but consists only from command and address=0x80 bytes, without a data byte. 
	Each time the command is called, the next available fuse is blown.

	* @param ulHandleCard Handle to the SecureMemory card.
	* @param pucFuseIndex	in 	at88sc153 only

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmWriteFuses(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pucFuseIndex
								);


/**
	* SCardSmInitializeAuthentication Not supported.
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized

	@warning Function supported by 8051 controller based readers only, please refer to Sync API developer guide for more details.
*/
OKERR ENTRY SCardSmInitializeAuthentication(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pbHostRandomNumber
								);

/**
	* SCardSmVerifyAuthentication Not supported

	* @param ulHandleCard Handle to the SecureMemory card.
	* @param pucAttemptsCounter	Authentication Attempt counter after the operation

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmVerifyAuthentication(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pbHostRandomNumber,
								OUT PUCHAR		pucAttemptsCounter
								);

//
// AT88SC153 only
//
/**
	* SCardSmUseSlaveAddress
	*\n Initializes the shared library to use the specified second slave address to refer a particular AT88SC153 card.

	*\n After successful execution of this function all SecureMemory card commands will have codes with this slave address in the MSb [b7..b4]. Any other cards connected to the same I2C bus,
	and still having default slave address 0xB0, will not be able to respond to the SecureMemory card commands.
	*\n Before using this command the DEVICE CONFIGURATION REGISTER at address 0x18 from the configuration space must be initialized with chip select bits CS3,SC2,SC1,SC0 equal to the
	most significant bits of the slave address. Address 0xB0 is default primary and don't has to be set in the DEVICE CONFIGURATION REGISTER.
	*\n If the DEVICE CONFIGURATION REGISTER is not properly initialized before calling this function and subsequent commands fail, please call this function again with the default slave
	 address 0xB0 or call again SCardSmInit. SCardSmInit function sets 0xB0 as a slave address in the SecureMemory commands.
	*\n This function applies to AT88SC153 SecureMemory cards only, is library internal and performs no physical card operation.

	* @param ucSlaveAddress	in 	Slave address that will be used with the command codes

	* @return OKERR_NOT_SUPPORTED	The command is not relevant for the currently initialized SecureMemory card type

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmUseSlaveAddress(
				 				IN UCHAR    	ucSlaveAddress
								);


/**
	* SCardSmSetUserZoneAddress
	*\n The function sets the user zone address register with the address of the user zone which is intended to be referenced with the following user zone read and write commands.
	*\n The command is for SecureMemory cards from type AT88SC1608 only.


	* @param ulHandleCard Handle to the SecureMemory card
	* @param ucUserZone user zone address to be set in the register

	* @return OK Standard Error Codes	(See header file ok.h)

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmSetUserZoneAddress(
								IN SCARDHANDLE ulHandleCard,
								IN UCHAR 		ucUserZone	
								);


/**
	* SCardSmAT88SC10xRead
	*\n AT88SC10x only:
	*\n This function reads data bit by bit from the card. It always reads a multiple of 8 bits to fill complete bytes. For memory location, area sizes and access rights refer to the AT88SC10x
	data sheets. Some memory areas need authentication to be read. When you try to read such an area without authenticating to the card, 0xFFs will be returned in the buffer.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param ulBitAddress Start bit to read from
	* @param ulBitsToRead Number of bits to read from the card
	* @param pbReadBuffer Pointer to the read buffer
	* @param ulReadBufferSize Size of the read buffer
	* @param pulBitsRead number of bits read (optional: may be NULL)
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xRead (
                             IN SCARDHANDLE  ulHandleCard,
                             IN ULONG        ulBitAddress,
                             IN ULONG        ulBitsToRead,
                             OUT LPBYTE      pbReadBuffer,
                             IN ULONG        ulReadBufferSize,
                             OUT PULONG      pulBitsRead
                           );

/**
	* SCardSmAT88SC10xErase
	*\n AT88SC10x only:
	*\n This function erases one or more 16-bit words in memory. In Security Level 2, the application zones can only be erased with the command SCardSmAt88SC10xEraseAZ.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param ulWordAddress Start word to begin erasing
	* @param ulWordsToErase Number of words to erase

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xErase (
                              IN SCARDHANDLE  ulHandleCard,
                              IN ULONG        ulWordAddress,
                              IN ULONG        ulWordsToErase
                            );

/**
	* SCardSmAT88SC10xEraseAZ
	*\n AT88SC10x only:
	*\n This function erases a complete application zone. This function only works in Security Level 2.
	*\n If fUseEraseCounter==TRUE, the erase counter is decreased.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param ucAzNumber Number of the application zone (1, 2, or 3)
	* @param pbCompareBuffer	Buffer containing 32/48 Bit Password (EZ1/EZ2/EZ3)
	* @param fUseEraseCounter Use Erase Counter (TRUE/FALSE)
	* @param pucEC In Security Level 2 the EC2 is returned as a number between 0 and 128 (optional: may be NULL)

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xEraseAZ (
                                IN SCARDHANDLE  ulHandleCard,
                                IN UCHAR        ucAzNumber,
                                IN PBYTE        pbCompareBuffer,
                                IN BOOL         fUseEraseCounter,
                                OUT PUCHAR      pucEC
                              );

/**
	* SCardSmAT88SC10xCompareSC
	*\n AT88SC10x only:
	*\n This function handles the authentification to the card by comparing the Security Code (two bytes).
	*\n The attempt counter is returned in pucAC. If it is 0xff, the password verification was successful.

	* @param ulHandleCard 	Handle to the SecureMemory card
	* @param pbCompareBuffer	Buffer containing 16 Bit Password (SC)
	* @param pucAC 	Attempt counter (optional: may be NULL)

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_PW_WRONG	Password does not match
	* @return OKERR_PW_LOCKED	No password attempt left
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xCompareSC (
                                  IN SCARDHANDLE  ulHandleCard,
                                  IN PBYTE        pbCompareBuffer,
                                  OUT PUCHAR      pucAC
                                );

/**
	* SCardSmAT88SC10xBlowFuse
	*\n AT88SC10x only:
	*\n This function blows the Manufacturer, Issuer or ECEN fuse. Blowing Fuses is only possible in Security Level 1, so you have to set the FUS Pin to HIGH in advance by using the function SCardSmAT88SC10xSetFusPin.
	
	* @param ulHandleCard 	Handle to the SecureMemory card
	* @param ucFuse 	Fuse to blow (AT88SC10X_FUSE_MANUFACTURER, AT88SC10X_FUSE_ISSUER, AT88SC10X_FUSE_ECEN)
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xBlowFuse (
                                 IN SCARDHANDLE  ulHandleCard,
                                 IN UCHAR        ucFuse
                               );

/**
	* SCardSmAT88SC10xWrite
	*\n AT88SC10x only:
	*\n This function allows to write data from pbWriteBuffer bit by bit to the card. Writing starts at ulBitAddress and ulBitsToWrite are written. Only zeros are written, so if the memory is not erased, you have to erase it in advance.

	* @param ulHandleCard Handle to the SecureMemory card
	* @param ulBitAddress Start Bit to write
	* @param ulBitsToWrite Number of bits to write
	* @param pbWriteBuffer Pointer to the write buffer
	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xWrite (
                              IN SCARDHANDLE  ulHandleCard,
                              IN ULONG        ulBitAddress,
                              IN ULONG        ulBitsToWrite,
                              IN LPBYTE       pbWriteBuffer
                            );

/**
	* SCardSmAT88SC10xSetFusPin
	*\n AT88SC10x only:
	*\n Sets C4 (FUS) High (ucFUS = 1) or Low (ucFUS = 0). The card is in security level 2, if the FUS Pin is Low or the Issuer Fuse is blown (0). 
	The card is in security level 1, if the FUS Pin is High and the Issuer Fuse is unblown (1).

	* @param ulHandleCard Handle to the SecureMemory card
	* @param ucFUS Desired status of the FUS pin (C4).

	* @return OK Standard Error Codes	(See header file ok.h)
	* @return OKERR_INIT	The shared library is not initialized
	* @return OKERR_NOT_SUPPORTED	The command is not supported for the actual card

	\warning Function supported by 8051 controller based readers only. Please refer to \ref Description-ReaderAndSupportedCard .
*/
OKERR ENTRY SCardSmAT88SC10xSetFusPin (
                                  IN SCARDHANDLE  ulHandleCard,
                                  IN UCHAR        ucFUS
                                );

//<-ct


#ifdef __cplusplus
}
#endif

#endif  /* _INC_SCARD_SM */