Option Strict Off
Option Explicit On
Module SCardI2C
	' ********************************************
	' Data Types
	' ********************************************
	
	'
	' Predefined Cardtypes
	'
	Enum SCARD_I2C_TYPE
		NO_PREDEFINED_CARD_PARAMETERS = 0
		' I2C cards from ST-Microelectronics:
		ST14C02C
		ST14C04C
		ST14E32
		M14C04
		M14C16
		M14C32
		M14C64
		M14128
		M14256
		' I2C cards from GEMplus:
		GFM2K
		GFM4K
		GFM32K
		' I2C cards from Atmel:
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
		AT24C1024
		I2C_TYPE_ENUM_TAIL ' must always be the last entry in this enum!!
	End Enum
	
	'
	' Card Parameters Structure
	'
	Public Structure SCARD_I2C_CARD_PARAMETERS
		Dim ucPageSize As Byte ' Maximal number of bytes that can be written in a successive manner, in a single device select phase.
		Dim ucNumberOfAddressBytes As Byte ' Number of bytes used to address the memory in the I2C card.
		Dim ulMemorySize As Short ' The size of the e2prom allocated in the card
	End Structure
	
	' ********************************************
	' Functions
	' ********************************************
	
	'
	' Initialize an I2C Card
	' Parameters:
	'       hCard               = Handle to current Card
	'       pCardParameters     = Pointer to a SCARD_I2C_CARD_PARAMETERS type
	'       lType               = Predefined Cardtype (SCARD_I2C_TYPE)
	'
    Public Declare Function SCardI2CInit Lib "scardsyn" (ByVal hCard As IntPtr, ByRef pCardParameters As IntPtr, ByVal lType As IntPtr) As IntPtr
    Public Declare Function SCardI2CInitx64 Lib "scardsynx64" Alias "SCardI2CInit" (ByVal hCard As IntPtr, ByRef pCardParameters As IntPtr, ByVal lType As IntPtr) As IntPtr
	
	'
	' Read Bytes from Card
	' Parameters:
	'       hCard               = Handle to current Card
	'       pbReadBuffer        = Array of Bytes where data should be stored in
	'       ulReadBufferSize    = Size of ReadBuffer
	'       ulAddress           = Offset where read starts
	'       ulBytesToRead       = Number of Bytes to read
	'
    Public Declare Function SCardI2CReadData Lib "scardsyn" (ByVal hCard As IntPtr, ByRef pbReadBuffer As Byte, ByVal ulReadBufferSize As IntPtr, ByVal ulAddress As IntPtr, ByVal ulBytesToRead As IntPtr) As IntPtr
    Public Declare Function SCardI2CReadDatax64 Lib "scardsynx64" Alias "SCardI2CReadData" (ByVal hCard As IntPtr, ByVal pbReadBuffer As Byte(), ByVal ulReadBufferSize As IntPtr, ByVal ulAddress As IntPtr, ByVal ulBytesToRead As IntPtr) As IntPtr

	
	'
	' Write Bytes to Card
	' Parameters:
	'       hCard               = Handle to current Card
	'       pbWriteBuffer       = Array of Bytes storing data
	'       ulWriteBufferSize   = Size of WriteBuffer
	'       ulAddress           = Offset where write starts
	'       ulBytesToWrite      = Number of Bytes to write
	'
    Public Declare Function SCardI2CWriteData Lib "scardsyn" (ByVal hCard As IntPtr, ByRef pbWriteBuffer As Byte, ByVal ulWriteBufferSize As IntPtr, ByVal ulAddress As IntPtr, ByVal ulBytesToWrite As IntPtr) As IntPtr
    Public Declare Function SCardI2CWriteDatax64 Lib "scardsynx64" Alias "SCardI2CWriteData" (ByVal hCard As IntPtr, ByRef pbWriteBuffer As Byte, ByVal ulWriteBufferSize As IntPtr, ByVal ulAddress As IntPtr, ByVal ulBytesToWrite As IntPtr) As IntPtr

    Public Function VarPtr(ByVal e As Object) As Integer
        Dim GC As GCHandle = GCHandle.Alloc(e, GCHandleType.Pinned)
        Dim GC2 As Integer = GC.AddrOfPinnedObject.ToInt32
        GC.Free()
        Return GC2
    End Function
    Public Function strtobyte(ByVal str As String) As Byte()

        Dim encoding As New System.Text.ASCIIEncoding()

        Return encoding.GetBytes(str)

    End Function

    '    Public Function GetPlateform() As String

    '        Dim var1 As Char
    '        If (IntPtr.Size = "8") Then
    '            var1 = "scardsynx64"
    '        Else
    '            var1 = "scardsyn"
    '        End If
    '        Return var1
    '    End Function
End Module