/**
 @brief Function declaration supporting I2C Bus protocol credentials.

 @file SCardI2C.h
 
 @copyright
 Copyright (c) 2017 HID Global Corporation/ASSA ABLOY AB. All rights reserved.
*/

#ifndef __SCARDI2C_H__
	#define __SCARDI2C_H__

#include <windows.h>
#ifndef S_WNT
    #define S_WNT
#endif	

#include "ok.h"
#include <winscard.h>

// All structures and unions are aligned with 1.
// The initila pack value is saved in old_value, it will be restore with pop below.
#pragma pack(push,old_value,1)

// DEFINE card types: the constants below are according the i2c card type used
typedef enum _SCARD_I2C_TYPE
{
	NO_PREDEFINED_CARD_PARAMETERS = 0,
	// I2C cards from ST-Microelectronics:
	ST14C02C,
	ST14C04C,
	ST14E32,
	M14C04,
	M14C16,
	M14C32,
	M14C64,
	M14128,
	M14256,
	// I2C cards from GEMplus:
	GFM2K,
	GFM4K,
	GFM32K,
	// I2C cards from Atmel:
	AT24C01A,
	AT24C02,
	AT24C04,
	AT24C08,
	AT24C16,
	AT24C164,
	AT24C32,
	AT24C64,
	AT24C128,
	AT24C256,
	AT24CS128,
	AT24CS256,
	AT24C512,
	AT24C1024,
	I2C_TYPE_ENUM_TAIL	// must always be the last entry in this enum!!
} SCARD_I2C_TYPE, *PSCARD_I2C_TYPE;


typedef struct _SCARD_I2C_CARD_PARAMETERS
{
	UCHAR   ucPageSize;								// Maximal number of bytes that can be written in a successive manner, in a single device select phase.
  	UCHAR 	ucNumberOfAddressBytes;					// Number of bytes used to address the memory in the I2C card.
  	ULONG 	ulMemorySize;							// The size of the e2prom allocated in the card
}
SCARD_I2C_CARD_PARAMETERS, *PSCARD_I2C_CARD_PARAMETERS;
#define SCARD_I2C_CARD_PARAMETERS_SIZE             sizeof(SCARD_I2C_CARD_PARAMETERS)

// The order in the following table has to be according above enum field.
static const SCARD_I2C_CARD_PARAMETERS   stI2cCardParameterTable[] =
{
	// ucPageSize, ucNumberOfAddressBytes, ulMemorySize

	{   0,   0,     0},     // NO_PREDEFINED_CARD_PARAMETERS = 0, values of this entry doesn't care
	// I2C cards from ST-Microelectronics:
	{   8,   1,   256},     // ST14C02C
	{   8,   1,   512},     // ST14C04C
	{  32,   2,  4096},     // ST14E32
	{  16,   1,   512},     // M14C04
	{  16,   1,  2048},     // M14C16
	{  32,   2,  4096},     // M14C32
	{  32,   2,  8192},     // M14C64
	{  64,   2, 16384},     // M14128
	{  64,   2, 32768},     // M14256
	// I2C cards from GEMplus:
	{   8,   1,   256},     // GFM2K
	{  16,   1,   512},     // GFM4K
	{  32,   2,  4096},     // GFM32K
	// I2C cards from Atmel:
	{   8,   1,   128},     // AT24C01A
	{   8,   1,   256},     // AT24C02
	{  16,   1,   512},     // AT24C04
	{  16,   1,  1024},     // AT24C08
	{  16,   1,  2048},     // AT24C16
	{  16,   1,  2048},     // AT24C164
	{  32,   2,  4096},     // AT24C32
	{  32,   2,  8192},     // AT24C64
	{  64,   2, 16384},     // AT24C128
	{  64,   2, 32768},     // AT24C256
	{  64,   2, 16384},     // AT24CS128
	{  64,   2, 32768},     // AT24CS256
	{ 128,   2, 65536},     // AT24C512
	{   0,   2, 131072}     // AT24C1024 , page size = 0 means 256 bytes
};

#define SCARDI2C_MAX_DATA_LEN          131072	// 0x20000

   #ifdef __cplusplus
extern "C" {
   #endif

/**
@brief Initializes protocol specific parameters of the dynamic library.

The function initializes the card and protocol specific parameters of the driver for communication with the I2C bus card.
It has to be called once before any use of \b SCardI2CReadData or \b SCardI2CWriteData.
There is no corresponding function in the card itself. The card is specified with \b Type.
In this case, the card parameters are internally initialized according to the corresponding manufacturer specification, and pCardParameters pointer is not evaluated.
When \b Type = \b NO_PREDEFINED_CARD_PARAMETERS, each card parameter is defined in a \e CardParameters structure which has to be allocated
and initialized by the calling application. Its address is submitted as pCardParameters pointer in the call of this function.
@note It is expected, that the card is already connected.

The following \b Type constants can be used:

ST-Microelectronics:
ST14C02C
ST14C04C
ST14E32
M14C04
M14C16
M14C32
M14C64
M14128
M14256

GEMplus (Gemalto):
GFM2K
GFM4K
GFM32K

Atmel:
AT24C01A
AT24C02
AT24C04
AT24C08
AT24C16
AT24C164
AT24C32
AT24C64
AT24C128
AT24C256
AT24CS128
AT24CS256
AT24C512
AT241024

@param ulHandleCard		Handle to a I2C bus card, provided from the "smart card resource manager" after connecting the card (SCardConnect).
@param pCardParameters	Pointer to a structure holding I2C card parameters. Used only if Type = NO_PREDEFINED_CARD_PARAMETERS.
@param Type				Predefined type of the used I2C card.

@return	OK Standard Error Codes, see header file ok.h

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCardI2CInit(
                        IN SCARDHANDLE	 				ulHandleCard,
                        IN SCARD_I2C_CARD_PARAMETERS	*pCardParameters,
                        IN SCARD_I2C_TYPE				Type);

/**
@brief Reads number of bytes starting from the specified memory address.

Reads a number of bytes, starting from the specified memory address \b ulAddress, and saves the content in the read buffer pointed to by \b pbReadBuffer.
The function uses internal I2C bus sequential read for number of bytes. Better performance is acheived when a block of bytes is read with one call of this function instead calling it in a loop reading 1 byte.

@param ulHandleCard			Handle (get from SCardConnect)
@param pbReadBuffer			Pointer to the buffer, where the data read from the card are to be stored
@param ulReadBufferSize		Size of the read buffer
@param ulAddress			Memory address to read from
@param ulBytesToRead		Number of bytes to be read from the ulAddress address

@return	OK Standard Error Codes, see header file ok.h

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCardI2CReadData(
						IN	SCARDHANDLE   ulHandleCard,
						IN	BYTE    *pbReadBuffer,
						IN	ULONG    ulReadBufferSize,
                        IN	ULONG    ulAddress,
                        IN	ULONG    ulBytesToRead);

/**
@brief Writes number of bytes to the specified card memory.

Writes number of bytes \b (ulBytesToWrite) to the specified card memory, starting from \b ulAddress.
The data to be written is taken from the buffer pointed to by \b pbWriteBuffer.
The function uses internal I2C bus sequential write for the number of bytes. Better performance is acheived when a block of bytes is written with one call of this function, instead of calling it in a loop writing 1 byte at a time.

@param ulHandleCard			Handle of the smartcard (get from SCardConnect)
@param pbWriteBuffer		Pointer to the write buffer, holding the data to be written
@param ulWriteBufferSize	Size of the write buffer
@param ulAddress			Size of the writMemory address in the I2C card where to start writinge buffer
@param ulBytesToWrite		Number of bytes to be written in the ulAddress address

@return	OK Standard Error Codes, see header file ok.h

@attention For AVR controller based readers, please see: \ref HowChangeVoltageSeq
*/
OKERR ENTRY SCardI2CWriteData(
						IN	SCARDHANDLE   ulHandleCard,
						IN	BYTE     *pbWriteBuffer,
						IN	ULONG    ulWriteBufferSize,
                        IN	ULONG    ulAddress,   	
                        IN	ULONG    ulBytesToWrite);

#ifdef __cplusplus
}
#endif

#pragma pack(pop,old_value)
// Restore the old packing value.
 
#endif /* #ifndef __SCARDI2C_H__ */
