Option Strict Off
Option Explicit On

Module SCard3WBP

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

    Public Declare Function SCard3WBPReadData Lib "scardsyn" Alias "SCard3WBPReadData" (ByVal hCard As IntPtr, ByVal ulBytesToRead As IntPtr, ByRef bData As Byte, ByVal ulAddress As IntPtr) As IntPtr
    Public Declare Function SCard3WBPReadDatax64 Lib "scardsynx64" Alias "SCard3WBPReadData" (ByVal hCard As IntPtr, ByVal ulBytesToRead As IntPtr, ByVal bData As Byte(), ByVal ulAddress As IntPtr) As IntPtr
    'Public Declare Function SCard3WBPReadData Lib var (ByVal hCard As Integer, ByVal ulBytesToRead As Integer, ByRef bData As Byte, ByVal ulAddress As Integer) As Integer


    '
    ' Checks if Byte at ulAddress is Protected
    ' Parameters:
    '       hCard           = Handle to current Card
    '       ulAddress       = Address of Byte to verify
    '       pfProtected     = Returns TRUE  (1) if Byte is protected
    '                         Returns FALSE (0) if Byte is not protected
    '
    '   ATTENTION:  In VB TRUE is -1 in C/C++ TRUE is 1
    '               FALSE is 0 in VB and C/C++
    Public Declare Function SCard3WBPVerifyProtectBit Lib "scardsyn" Alias "SCard3WBPVerifyProtectBit" (ByVal hCard As IntPtr, ByVal ulAddress As IntPtr, ByRef pfProtected As IntPtr) As IntPtr
    Public Declare Function SCard3WBPVerifyProtectBitx64 Lib "scardsynx64" Alias "SCard3WBPVerifyProtectBit" (ByVal hCard As IntPtr, ByVal ulAddress As IntPtr, ByRef pfProtected As IntPtr) As IntPtr
    '
    ' Writes Data to Card
    ' Parameters:
    '       hCard           = Handle to current Card
    '       ulDataLen       = Length of Data Buffer (pbData)
    '       pbData          = Data Buffer
    '       ulAddress       = Address where to start writing
    '       fProtect        = Set the protectbit if this is TRUE (1)
    '
    '   ATTENTION:  In VB TRUE is -1 in C/C++ TRUE is 1
    '               FALSE is 0 in VB and C/C++
    Public Declare Function SCard3WBPWriteData Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte, ByVal ulAddress As IntPtr, ByVal fProtect As IntPtr) As IntPtr
    Public Declare Function SCard3WBPWriteDatax64 Lib "scardsynx64" Alias "SCard3WBPWriteData" (ByVal hCard As IntPtr, ByVal ulDataLen As IntPtr, ByRef pbData As Byte, ByVal ulAddress As IntPtr, ByVal fProtect As IntPtr) As IntPtr
    '
    ' Compare bytes and protect them if they are equal
    ' Parameters:
    '       hCard       = Handle to current Card
    '       bData       = Bytes to compare with
    '       ulAddress   = Starting to compare at this Address
    '
    Public Declare Function SCard3WBPCompareAndProtect Lib "scardsyn" (ByVal hCard As IntPtr, ByRef bData As Byte, ByVal ulAddress As IntPtr) As IntPtr
    Public Declare Function SCard3WBPCompareAndProtectx64 Lib "scardsynx64" Alias "SCard3WBPCompareAndProtect" (ByVal hCard As IntPtr, ByRef bData As Byte, ByVal ulAddress As IntPtr) As IntPtr

    '
    ' Presents a PIN
    ' Parameters:
    '       hCard        = Handle to current Card
    '       ulPINLen     = Length of PIN (have to be 2)
    '       pbPIN        = Byte-array containing PIN
    '
    Public Declare Function SCard3WBPPresentPIN Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulPINLen As IntPtr, ByVal pbPIN() As Byte) As IntPtr

    Public Declare Function SCard3WBPPresentPINx64 Lib "scardsynx64" Alias "SCard3WBPPresentPIN" (ByVal hCard As IntPtr, ByVal ulPINLen As IntPtr, ByVal pbPIN() As Byte) As IntPtr

    '
    ' Change PIN of current Card
    ' Parameters:
    '       hCard           = Handle to current Card
    '       ulOldPINLen     = Length of old PIN (have to be 2)
    '       pbOldPIN        = Byte-array containing old PIN
    '       ulNewPINLen     = Length of new PIN (have to be 2)
    '       pbNewPIN        = Byte-array containing new PIN
    '
    Public Declare Function SCard3WBPChangePIN Lib "scardsyn" (ByVal hCard As IntPtr, ByVal ulOldPINLen As IntPtr, ByRef pbOldPIN As Byte, ByVal ulNewPINLen As IntPtr, ByRef pbNewPIN As Byte) As IntPtr
    Public Declare Function SCard3WBPChangePINx64 Lib "scardsynx64" Alias "SCard3WBPChangePIN" (ByVal hCard As IntPtr, ByVal ulOldPINLen As IntPtr, ByRef pbOldPIN As Byte, ByVal ulNewPINLen As IntPtr, ByRef pbNewPIN As Byte) As IntPtr
    '
    ' Check if PIN is presented
    ' Parameters
    '       hCard           = Handle to current Card
    '       pfPinPresented  = TRUE  (1) if PIN is already presented
    '                         FALSE (0) if PIN is not presented
    '
    '   ATTENTION:  In VB TRUE is -1 in C/C++ TRUE is 1
    '               FALSE is 0 in VB and C/C++
    Public Declare Function SCard3WBPIsPinPresented Lib "scardsyn" (ByVal hCard As IntPtr, ByRef pfPinPresented As IntPtr) As IntPtr
    Public Declare Function SCard3WBPIsPinPresentedx64 Lib "scardsynx64" Alias "SCard3WBPIsPinPresented" (ByVal hCard As IntPtr, ByRef pfPinPresented As IntPtr) As IntPtr
End Module