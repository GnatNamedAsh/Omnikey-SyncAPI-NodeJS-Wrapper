Option Strict Off
Option Explicit On

Module SCard2WBP
	' ********************************************
	' Functions
	' ********************************************
	'
	' Read Bytes to Card
	' Parameters:
	'       hCard           = Handle to current Card
	'       ulBytesToRead   = Number of Bytes to Read
	'       pbData          = Array of Bytes containing data
	'       ulAddress       = Offset where read starts
	'
    Public Declare Function SCard2WBPReadData Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulBytesToRead As IntPtr, ByRef pbData As Byte, ByVal ulAddress As IntPtr) As IntPtr
    Public Declare Function SCard2WBPReadDatax64 Lib "scardsynx64" Alias "SCard2WBPReadData" (ByVal hCard As IntPtr, ByVal ulBytesToRead As IntPtr, ByVal pbData As Byte(), ByVal ulAddress As IntPtr) As IntPtr
	'
	' Read Protection Bits of first 32 Bytes
	'       hCard           = Handle to current Card
	'       ulDataLen       = Length of pbData (have to be 4)
	'       pbData          = Returned Data
	'
    Public Declare Function SCard2WBPReadProtectionMemory Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte) As IntPtr
    Public Declare Function SCard2WBPReadProtectionMemoryx64 Lib "scardsynx64" Alias "SCard2WBPReadProtectionMemory" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte) As IntPtr
	
	'
	' Write Bytes to Card
	' Parameters:
	'       hCard           = Handle to current Card
	'       ulDataLen       = Size of pbData
	'       pbData          = Array of Bytes storing data
	'       ulAddress       = Offset where write starts
	'
    Public Declare Function SCard2WBPWriteData Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte, ByVal ulAddress As IntPtr) As IntPtr
    Public Declare Function SCard2WBPWriteDatax64 Lib "scardsynx64" Alias "SCard2WBPWriteData" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte, ByVal ulAddress As IntPtr) As IntPtr
	'
	' Compare bytes and protect them if they are equal
	' Parameters:
	'       hCard       = Handle to current Card
	'       bData       = Bytes to compare with
	'       ulAddress   = Starting to compare at this Address
	'
    Public Declare Function SCard2WBPCompareAndProtect Lib "scardsyn" (ByVal hCard As IntPtr, ByRef bData As Byte, ByVal ulAddress As IntPtr) As IntPtr
    Public Declare Function SCard2WBPCompareAndProtectx64 Lib "scardsynx64" Alias "SCard2WBPCompareAndProtect" (ByVal hCard As IntPtr, ByRef bData As Byte, ByVal ulAddress As IntPtr) As IntPtr
	
	'
	' Presents a PIN
	' Parameters:
	'       hCard        = Handle to current Card
	'       ulPINLen     = Length of PIN (have to be 3)
	'       pbPIN        = Byte-array containing PIN
	'
    Public Declare Function SCard2WBPPresentPIN Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulPINLen As IntPtr, ByVal pbPIN() As Byte) As IntPtr
    Public Declare Function SCard2WBPPresentPINx64 Lib "scardsynx64" Alias "SCard2WBPPresentPIN" (ByVal hCard As IntPtr, ByVal ulPINLen As IntPtr, ByVal pbPIN() As Byte) As IntPtr

	
	'
	' Change PIN of current Card
	' Parameters:
	'       hCard           = Handle to current Card
	'       ulOldPINLen     = Length of old PIN (have to be 3)
	'       pbOldPIN        = Byte-array containing old PIN
	'       ulNewPINLen     = Length of new PIN (have to be 3)
	'       pbNewPIN        = Byte-array containing new PIN
	'
    Public Declare Function SCard2WBPChangePIN Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulOldPINLen As IntPtr, ByRef pbOldPIN As Byte, ByVal ulNewPINLen As IntPtr, ByRef pbNewPIN As Byte) As IntPtr
    Public Declare Function SCard2WBPChangePINx64 Lib "scardsynx64" Alias "SCard2WBPChangePIN" (ByVal hCard As IntPtr, ByVal ulOldPINLen As IntPtr, ByRef pbOldPIN As Byte, ByVal ulNewPINLen As IntPtr, ByRef pbNewPIN As Byte) As IntPtr
	
	'
	' Check if PIN is presented
	' Parameters
	'       hCard           = Handle to current Card
	'       pfPinPresented  = TRUE  (1) if PIN is already presented
	'                         FALSE (0) if PIN is not presented
	'       ATTENTION:  In VB TRUE is -1 in C/C++ TRUE is 1
	'                   FALSE is 0 in VB and C/C++
	'
    Public Declare Function SCard2WBPIsPinPresented Lib "scardsyn" (ByVal hCard As IntPtr, ByRef pfPinPresented As IntPtr) As IntPtr
    Public Declare Function SCard2WBPIsPinPresentedx64 Lib "scardsynx64" Alias "SCard2WBPIsPinPresented" (ByVal hCard As IntPtr, ByRef pfPinPresented As IntPtr) As IntPtr
End Module