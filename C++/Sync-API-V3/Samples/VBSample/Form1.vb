Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
Imports System.Runtime.InteropServices
Imports System.Threading

Friend Class Form1
    Inherits System.Windows.Forms.Form


    Dim hContext As IntPtr
    Dim hCard As IntPtr
    'Dim hCard As ULong

	Dim isContext As Boolean
    Dim isCard As Boolean
    Dim var As String











    'UPGRADE_NOTE: str was upgraded to str_Renamed. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="A9E4979A-37FA-4718-9994-97DD76ED70A7"'
    Private Function HexStrToInt(ByVal str_Renamed As String) As Short
        Dim iStrLen As Object

        Dim i As Short
        Dim iTmp As Short
        Dim sTmp As String

        'UPGRADE_WARNING: Couldn't resolve default property of object iStrLen. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        iStrLen = Len(str_Renamed)

        iTmp = 0
        For i = 1 To Len(str_Renamed)
            iTmp = iTmp * 16
            sTmp = Mid(str_Renamed, i, 1)
            If (sTmp >= "0" And sTmp <= "9") Then
                'UPGRADE_WARNING: Couldn't resolve default property of object Switch(). Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                iTmp = iTmp + VB.Switch(1 = 1, sTmp)
            Else
                'UPGRADE_WARNING: Couldn't resolve default property of object Switch(). Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                iTmp = iTmp + VB.Switch(sTmp = "A", 10, sTmp = "a", 10, sTmp = "B", 11, sTmp = "b", 11, sTmp = "C", 12, sTmp = "c", 12, sTmp = "D", 13, sTmp = "d", 13, sTmp = "E", 14, sTmp = "e", 14, sTmp = "F", 15, sTmp = "f", 15, 1 = 1, 0)
            End If

        Next

        HexStrToInt = iTmp

    End Function

    'UPGRADE_NOTE: str was upgraded to str_Renamed. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="A9E4979A-37FA-4718-9994-97DD76ED70A7"'
    Private Function StrToArray(ByRef bArr() As Byte, ByVal str_Renamed As String) As IntPtr


        Dim rc As IntPtr


        'Convert query string to byte array
        Dim i As Short
        Dim iStrLen As Short
        Dim iTmp As Short
        Dim sTmp As String

        iStrLen = Len(str_Renamed)
        If (iStrLen = 0) Then
            StrToArray = 0
            Exit Function
        End If

        If (iStrLen Mod 2) <> 0 Then
            'UPGRADE_WARNING: Couldn't resolve default property of object rc. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            rc = MsgBox("Invalid Value", MsgBoxStyle.OkOnly, "Error")
            StrToArray = 0
            Exit Function
        End If

        'UPGRADE_WARNING: Lower bound of array bArr was changed from 1 to 0. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="0F1C9BE1-AF9D-476E-83B1-17D43BECFF20"'
        ReDim bArr((iStrLen / 2) - 1)
        iTmp = 0
        For i = 1 To iStrLen
            'sTmp = str_Renamed.Substring(i, 1)
            sTmp = Mid(str_Renamed, i, 1)
            If (sTmp >= "0" And sTmp <= "9") Or (sTmp >= "a" And sTmp <= "f") Or (sTmp >= "A" And sTmp <= "F") Then
                'UPGRADE_WARNING: Couldn't resolve default property of object Switch(). Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                iTmp = iTmp + VB.Switch(sTmp = "A", 10, sTmp = "a", 10, sTmp = "B", 11, sTmp = "b", 11, sTmp = "C", 12, sTmp = "c", 12, sTmp = "D", 13, sTmp = "d", 13, sTmp = "E", 14, sTmp = "e", 14, sTmp = "F", 15, sTmp = "f", 15, 1 = 1, sTmp)
            Else
                Me.MESSAGETEXT.Text = "Invalid Value ! Please enter hexadecimal values"
                Exit Function
            End If

            If (i Mod 2) = 0 Then
                bArr((i - 2) / 2) = iTmp
                iTmp = 0
            End If
            iTmp = iTmp * 16
        Next

        StrToArray = iStrLen / 2

    End Function







    ' Private Sub CARDTYPE_Validate(Cancel As Boolean)
    ' Private Sub CARDTYPE_Change()
    'UPGRADE_WARNING: Event CARDTYPE.SelectedIndexChanged may fire when form is initialized. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="88B12AE1-6DE0-48A0-86F1-60C0686C026A"'
    Private Sub CARDTYPE_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles CARDTYPE.SelectedIndexChanged
        If (Me.CARDTYPE.Text = "2W") Then
            Me.PIN.Text = "FFFFFF"
        Else
            Me.PIN.Text = "FFFF"

        End If
        ' Disable all Buttons
        Me.READBUTTON.Enabled = False
        Me.WRITEBUTTON.Enabled = False
        Me.PRESENTPIN.Enabled = False
        Me.INITI2CBUTTON.Enabled = False
        Me.I2CTYPE.Enabled = False

        ' Enable 2W Buttons
        If (CARDTYPE.Text = "2W") Then
            Me.READBUTTON.Enabled = True
            Me.WRITEBUTTON.Enabled = False
            Me.PRESENTPIN.Enabled = True
        End If

        ' Enable 3W Buttons
        If (CARDTYPE.Text = "3W") Then
            Me.READBUTTON.Enabled = True
            Me.WRITEBUTTON.Enabled = False
            Me.PRESENTPIN.Enabled = True
        End If

        ' Enable I2C Buttons
        If (CARDTYPE.Text = "I2C") Then
            Me.INITI2CBUTTON.Enabled = True
            Me.READBUTTON.Enabled = True
            Me.WRITEBUTTON.Enabled = False
            Me.I2CTYPE.Enabled = True
        End If

    End Sub




    Private Sub Form1_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load





        Dim var As Object = Nothing
        'var = "Scardsyn"
        'var = GetPlateform()
        ' I2C cards from ST-Microelectronics:
        I2CTYPE.Items.Add(("ST14C02C"))
        I2CTYPE.Items.Add(("ST14C04C"))
        I2CTYPE.Items.Add(("ST14E32"))
        I2CTYPE.Items.Add(("M14C04"))
        I2CTYPE.Items.Add(("M14C16"))
        I2CTYPE.Items.Add(("M14C32"))
        I2CTYPE.Items.Add(("M14C64"))
        I2CTYPE.Items.Add(("M14128"))
        I2CTYPE.Items.Add(("M14256"))
        ' I2C cards from GEMplus:
        I2CTYPE.Items.Add(("GFM2K"))
        I2CTYPE.Items.Add(("GFM4K"))
        I2CTYPE.Items.Add(("GFM32K"))
        ' I2C cards from Atmel:
        I2CTYPE.Items.Add(("AT24C01A"))
        I2CTYPE.Items.Add(("AT24C02"))
        I2CTYPE.Items.Add(("AT24C04"))
        I2CTYPE.Items.Add(("AT24C08"))
        I2CTYPE.Items.Add(("AT24C16"))
        I2CTYPE.Items.Add(("AT24C164"))
        I2CTYPE.Items.Add(("AT24C32"))
        I2CTYPE.Items.Add(("AT24C64"))
        I2CTYPE.Items.Add(("AT24C128"))
        I2CTYPE.Items.Add(("AT24C256"))
        I2CTYPE.Items.Add(("AT24CS128"))
        I2CTYPE.Items.Add(("AT24CS256"))
        I2CTYPE.Items.Add(("AT24C512"))
        I2CTYPE.Items.Add(("AT24C1024"))

        I2CTYPE.SelectedIndex = 0

        CARDTYPE.Items.Add(("2W"))
        CARDTYPE.Items.Add(("3W"))
        CARDTYPE.Items.Add(("I2C"))

        CARDTYPE.SelectedIndex = 0

    End Sub

    '
    ' Convert 1 Byte to String
    '
    Private Function GetString(ByVal curByte As Byte) As String

        GetString = New String(Chr(curByte), 1)

    End Function

    '
    ' Gets an array of bytes and its length and return a viewable
    ' dump of this byte-array
    ' For Example: a bytearray with values
    '   array(0) = &H3B
    '   array(1) = &HA2
    ' becomes the String "3B A2"
    '
    Private Function HexDump(ByRef response() As Byte, ByVal lenr As Short) As String
        Dim ifvalue As Object

        'Dim rc As Short
        Dim OUT As String = Nothing
        Dim count As Short
        Dim value As Short

        For count = 0 To lenr - 1 Step 1
            value = response(count)

            'UPGRADE_WARNING: Couldn't resolve default property of object ifvalue. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            ifvalue = Fix(value / 16)
            'UPGRADE_WARNING: Couldn't resolve default property of object ifvalue. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If ifvalue > -1 And ifvalue < 10 Then
                'UPGRADE_WARNING: Couldn't resolve default property of object ifvalue. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                OUT = OUT & New String(Chr(ifvalue + 48), 1)
            Else
                'UPGRADE_WARNING: Couldn't resolve default property of object ifvalue. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                If ifvalue > 9 And ifvalue < 16 Then
                    'UPGRADE_WARNING: Couldn't resolve default property of object ifvalue. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                    OUT = OUT & New String(Chr(ifvalue + 55), 1)
                End If
            End If

            value = Fix(value Mod 16)

            If value > -1 And value < 10 Then
                OUT = OUT & New String(Chr(value + 48), 1)
            Else
                If value > 9 And value < 16 Then
                    OUT = OUT & New String(Chr(value + 55), 1)
                End If
            End If

            OUT = OUT & " "
        Next count

        HexDump = OUT

    End Function

    '
    ' Handles errorcodes defined in Scard.bas and return an errormessage as String
    '
    Private Function HandleError(ByVal rc As IntPtr) As String
        Dim OKERR_OK As Object = Nothing

        HandleError = "Unknown Error"
        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc = OKERR_OK Then HandleError = "No Error"
        If rc = OKERR_SCARD__E_CANCELLED Then HandleError = "The action was cancelled by an SCardCancel request"
        If rc = OKERR_SCARD__E_INVALID_HANDLE Then HandleError = "The supplied handle was invalid"
        If rc = OKERR_SCARD__E_INVALID_PARAMETER Then HandleError = "One or more of the supplied parameters could not be properly interpreted"
        If rc = OKERR_SCARD__E_INVALID_TARGET Then HandleError = "Registry startup information is missing or invalid"
        If rc = OKERR_SCARD__E_NO_MEMORY Then HandleError = "Not enough memory available to complete this command"
        If rc = OKERR_SCARD__F_WAITED_TOO_LONG Then HandleError = "An internal consistency timer has expired"
        If rc = OKERR_SCARD__E_INSUFFICIENT_BUFFER Then HandleError = "The data buffer to receive returned data is too small for the returned data"
        If rc = OKERR_SCARD__E_UNKNOWN_READER Then HandleError = "The specified reader name is not recognized"
        If rc = OKERR_SCARD__E_TIMEOUT Then HandleError = "The user-specified timeout value has expired"
        If rc = OKERR_SCARD__E_SHARING_VIOLATION Then HandleError = "The smart card cannot be accessed because of other connections outstanding"
        If rc = OKERR_SCARD__E_NO_SMARTCARD Then HandleError = "The operation requires a Smart Card, but no Smart Card is currently in the device"
        If rc = OKERR_SCARD__E_UNKNOWN_CARD Then HandleError = "The specified smart card name is not recognized"
        If rc = OKERR_SCARD__E_CANT_DISPOSE Then HandleError = "The system could not dispose of the media in the requested manner"
        If rc = OKERR_SCARD__E_PROTO_MISMATCH Then HandleError = "The requested protocols are incompatible with the protocol currently in use with the smart card"
        If rc = OKERR_SCARD__E_NOT_READY Then HandleError = "The reader or smart card is not ready to accept commands"
        If rc = OKERR_SCARD__E_INVALID_VALUE Then HandleError = "One or more of the supplied parameters values could not be properly interpreted"
        If rc = OKERR_SCARD__E_SYSTEM_CANCELLED Then HandleError = "The action was cancelled by the system, presumably to log off or shut down"
        If rc = OKERR_SCARD__F_COMM_ERROR Then HandleError = "An internal communications error has been detected"
        If rc = OKERR_SCARD__F_UNKNOWN_ERROR Then HandleError = "An internal error has been detected, but the source is unknown"
        If rc = OKERR_SCARD__E_INVALID_ATR Then HandleError = "An ATR obtained from the registry is not a valid ATR string"
        If rc = OKERR_SCARD__E_NOT_TRANSACTED Then HandleError = "An attempt was made to end a non-existent transaction"
        If rc = OKERR_SCARD__E_READER_UNAVAILABLE Then HandleError = "The specified reader is not currently available for use"
        If rc = OKERR_SCARD__P_SHUTDOWN Then HandleError = "The operation has been aborted to allow the server application to exit"
        If rc = OKERR_SCARD__E_PCI_TOO_SMALL Then HandleError = "The PCI Receive buffer was too small"
        If rc = OKERR_SCARD__E_READER_UNSUPPORTED Then HandleError = "The reader driver does not meet minimal requirements for support"
        If rc = OKERR_SCARD__E_DUPLICATE_READER Then HandleError = "The reader driver did not produce a unique reader name"
        If rc = OKERR_SCARD__E_CARD_UNSUPPORTED Then HandleError = "The smart card does not meet minimal requirements for support"
        If rc = OKERR_SCARD__E_NO_SERVICE Then HandleError = "The Smart card resource manager is not running"
        If rc = OKERR_SCARD__E_SERVICE_STOPPED Then HandleError = "The Smart card resource manager has shut down"
        If rc = OKERR_SCARD__E_UNEXPECTED Then HandleError = "An unexpected card error has occurred"
        If rc = OKERR_SCARD__E_ICC_INSTALLATION Then HandleError = "No Primary Provider can be found for the smart card"
        If rc = OKERR_SCARD__E_ICC_CREATEORDER Then HandleError = "The requested order of object creation is not supported"
        If rc = OKERR_SCARD__E_UNSUPPORTED_FEATURE Then HandleError = "This smart card does not support the requested feature"
        If rc = OKERR_SCARD__E_DIR_NOT_FOUND Then HandleError = "The identified directory does not exist in the smart card"
        If rc = OKERR_SCARD__E_FILE_NOT_FOUND Then HandleError = "The identified file does not exist in the smart card"
        If rc = OKERR_SCARD__E_NO_DIR Then HandleError = "The supplied path does not represent a smart card directory"
        If rc = OKERR_SCARD__E_NO_FILE Then HandleError = "The supplied path does not represent a smart card file"
        If rc = OKERR_SCARD__E_NO_ACCESS Then HandleError = "Access is denied to this file"
        If rc = OKERR_SCARD__E_WRITE_TOO_MANY Then HandleError = "An attempt was made to write more data than would fit in the target object"
        If rc = OKERR_SCARD__E_BAD_SEEK Then HandleError = "There was an error trying to set the smart card file object pointer"
        If rc = OKERR_SCARD__E_INVALID_CHV Then HandleError = "The supplied PIN is incorrect"
        If rc = OKERR_SCARD__E_UNKNOWN_RES_MNG Then HandleError = "An unrecognized error code was returned from a layered component"
        If rc = OKERR_SCARD__E_NO_SUCH_CERTIFICATE Then HandleError = "The requested certificate does not exist"
        If rc = OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE Then HandleError = "The requested certificate could not be obtained"
        If rc = OKERR_SCARD__E_NO_READERS_AVAILABLE Then HandleError = "Cannot find a smart card reader"
        If rc = OKERR_SCARD__E_COMM_DATA_LOST Then HandleError = "A communications error with the smart card has been detected"
        If rc = OKERR_SCARD__W_UNSUPPORTED_CARD Then HandleError = "The reader cannot communicate with the smart card, due to ATR configuration conflicts"
        If rc = OKERR_SCARD__W_UNRESPONSIVE_CARD Then HandleError = "The smart card is not responding to a reset"
        If rc = OKERR_SCARD__W_UNPOWERED_CARD Then HandleError = "Power has been removed from the smart card, so that further communication is not possible"
        If rc = OKERR_SCARD__W_RESET_CARD Then HandleError = "The smart card has been reset, so any shared state information is invalid"
        If rc = OKERR_SCARD__W_REMOVED_CARD Then HandleError = "The smart card has been removed, so that further communication is not possible"
        If rc = OKERR_SCARD__W_SECURITY_VIOLATION Then HandleError = "Access was denied because of a security violation"
        If rc = OKERR_SCARD__W_WRONG_CHV Then HandleError = "The card cannot be accessed because the wrong PIN was presented"
        If rc = OKERR_SCARD__W_CHV_BLOCKED Then HandleError = "The card cannot be accessed because the maximum number of PIN entry attempts has been reached"
        If rc = OKERR_SCARD__W_EOF Then HandleError = "The end of the smart card file has been reached"
        If rc = OKERR_SCARD__W_CANCELLED_BY_USER Then HandleError = "The action was cancelled by the user"

        If rc = OKERR_PARM1 Then HandleError = "Error in parameter 1"
        If rc = OKERR_PARM2 Then HandleError = "Error in parameter 2"
        If rc = OKERR_PARM3 Then HandleError = "Error in parameter 3"
        If rc = OKERR_PARM4 Then HandleError = "Error in parameter 4"
        If rc = OKERR_PARM5 Then HandleError = "Error in parameter 5"
        If rc = OKERR_PARM6 Then HandleError = "Error in parameter 6"
        If rc = OKERR_PARM7 Then HandleError = "Error in parameter 7"
        If rc = OKERR_PARM8 Then HandleError = "Error in parameter 8"
        If rc = OKERR_PARM9 Then HandleError = "Error in parameter 9"
        If rc = OKERR_PARM10 Then HandleError = "Error in parameter 10"
        If rc = OKERR_PARM11 Then HandleError = "Error in parameter 11"
        If rc = OKERR_PARM12 Then HandleError = "Error in parameter 12"
        If rc = OKERR_PARM13 Then HandleError = "Error in parameter 13"
        If rc = OKERR_PARM14 Then HandleError = "Error in parameter 14"
        If rc = OKERR_PARM15 Then HandleError = "Error in parameter 15"
        If rc = OKERR_PARM16 Then HandleError = "Error in parameter 16"
        If rc = OKERR_PARM17 Then HandleError = "Error in parameter 17"
        If rc = OKERR_PARM18 Then HandleError = "Error in parameter 18"
        If rc = OKERR_PARM19 Then HandleError = "Error in parameter 19"
        If rc = OKERR_INSUFFICIENT_PRIV Then HandleError = "You currently do not have the rights to execute the requested action. Usually a password has to be presented in advance."
        If rc = OKERR_PW_WRONG Then HandleError = "The presented password is wrong"
        If rc = OKERR_PW_LOCKED Then HandleError = "The password has been presented several times wrong and is therefore locked. Usually use some administrator tool to unblock it."
        If rc = OKERR_PW_TOO_SHORT Then HandleError = "The lenght of the password was too short."
        If rc = OKERR_PW_TOO_LONG Then HandleError = "The length of the password was too long."
        If rc = OKERR_PW_NOT_LOCKED Then HandleError = "The password is not locked"
        If rc = OKERR_ITEM_NOT_FOUND Then HandleError = "An item (e.g. a key of a specific name) could not be found"
        If rc = OKERR_ITEMS_LEFT Then HandleError = "There are still items left, therefore e.g. the directory / structure etc. can't be deleted."
        If rc = OKERR_INVALID_CFG_FILE Then HandleError = "Invalid configuration file"
        If rc = OKERR_SECTION_NOT_FOUND Then HandleError = "Section not found"
        If rc = OKERR_ENTRY_NOT_FOUND Then HandleError = "Entry not found"
        If rc = OKERR_NO_MORE_SECTIONS Then HandleError = "No more sections"
        If rc = OKERR_ITEM_ALREADY_EXISTS Then HandleError = "The specified item alread exists."
        If rc = OKERR_ITEM_EXPIRED Then HandleError = "Some item (e.g. a certificate) has expired."
        If rc = OKERR_UNEXPECTED_RET_VALUE Then HandleError = "Unexpected return value"
        If rc = OKERR_COMMUNICATE Then HandleError = "General communication error"
        If rc = OKERR_NOT_ENOUGH_MEMORY Then HandleError = "Not enough memory"
        If rc = OKERR_BUFFER_OVERFLOW Then HandleError = "Buffer overflow"
        If rc = OKERR_TIMEOUT Then HandleError = "A timeout has occurred"
        If rc = OKERR_NOT_SUPPORTED Then HandleError = "The requested functionality is not supported at this time / under this OS / in this situation etc."
        If rc = OKERR_ILLEGAL_ARGUMENT Then HandleError = "Illegal argument"
        If rc = OKERR_READ_FIO Then HandleError = "File IO read error"
        If rc = OKERR_WRITE_FIO Then HandleError = "File IO write error"
        If rc = OKERR_INVALID_HANDLE Then HandleError = "Invalid handle"
        If rc = OKERR_GENERAL_FAILURE Then HandleError = "General failure."
        If rc = OKERR_FILE_NOT_FOUND Then HandleError = "File not found"
        If rc = OKERR_OPEN_FILE Then HandleError = "File opening failed"
        If rc = OKERR_SEM_USED Then HandleError = "The semaphore is currently use by an other process"
        If rc = OKERR_NOP Then HandleError = "No operation done"
        If rc = OKERR_NOK Then HandleError = "Function not executed"
        If rc = OKERR_FWBUG Then HandleError = "Internal error detected"
        If rc = OKERR_INIT Then HandleError = "Module not initialized"
        If rc = OKERR_FIO Then HandleError = "File IO error detected"
        If rc = OKERR_ALLOC Then HandleError = "Cannot allocate memory"
        If rc = OKERR_SESSION_ERR Then HandleError = "General error"
        If rc = OKERR_ACCESS_ERR Then HandleError = "Access not allowed"
        If rc = OKERR_OPEN_FAILURE Then HandleError = "An open command was not successful"
        If rc = OKERR_CARD_NOT_POWERED Then HandleError = "Card is not powered"
        If rc = OKERR_ILLEGAL_CARDTYPE Then HandleError = "Illegal cardtype"
        If rc = OKERR_CARD_NOT_INSERTED Then HandleError = "Card not inserted"
        If rc = OKERR_NO_DRIVER Then HandleError = "No device driver installed"
        If rc = OKERR_OUT_OF_SERVICE Then HandleError = "The service is currently not available"
        If rc = OKERR_EOF_REACHED Then HandleError = "End of file reached"
        If rc = OKERR_ON_BLACKLIST Then HandleError = "The ID is on a blacklist, the requested action is therefore not allowed."
        If rc = OKERR_CONSISTENCY_CHECK Then HandleError = "Error during consistency check"
        If rc = OKERR_IDENTITY_MISMATCH Then HandleError = "The identity does not match a defined cross-check identity"
        If rc = OKERR_MULTIPLE_ERRORS Then HandleError = "Multiple errors have occurred. Use this if there is only the possibility to return one error code, but there happened different errors before (e.g. each thread returned a different error and the controlling thread may only report one)."
        If rc = OKERR_ILLEGAL_DRIVER Then HandleError = "Illegal driver"
        If rc = OKERR_ILLEGAL_FW_RELEASE Then HandleError = "The connected hardware whose firmware is not useable by this software"
        If rc = OKERR_NO_CARDREADER Then HandleError = "No cardreader attached"
        If rc = OKERR_IPC_FAULT Then HandleError = "General failure of inter process communication"
        If rc = OKERR_WAIT_AND_RETRY Then HandleError = "The service currently does not take calls. The task has to go back to the message loop and try again at a later time (Windows 3.1 only). The code may also be used, in every situation where a ‘  wait and retry ’  action is requested."

    End Function

    '
    ' Connect to Card
    '
    Private Sub CONNECTBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles CONNECTBUTTON.Click
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        'Dim i As Short
        Dim curReader As String

        'Dim myByte As Byte
        Dim dwShareMode As IntPtr
        Dim dwPreferredProtocols As IntPtr
        Dim dwActiveProtocol As IntPtr


        ' get selected Readername from ReaderList
        If ReaderList.Text = "" Then
            MESSAGETEXT.Text = ("No Reader Selected")
            Exit Sub
        Else
            curReader = ReaderList.Text
        End If

        ' Set Mode (see Scard.bas "Modes")
        dwShareMode = SCARD_SHARE_SHARED
        ' Set preferred Protocol (see Scard.bas "Protocols")
        dwPreferredProtocols = SCARD_PROTOCOL_T0

        ' Connect
        rc = SCardConnect(hContext, curReader, dwShareMode, dwPreferredProtocols, hCard, dwActiveProtocol)
        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = HandleError(rc)
            Exit Sub
        End If

        MESSAGETEXT.Text = "Connect successfull"
        isCard = True

    End Sub

    '
    ' Disconnects from Card
    '
    Private Sub DISCONNECTBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles DISCONNECTBUTTON.Click
        Dim OKERR_OK As Object = Nothing
        Dim rc As IntPtr
        Dim dwDisposition As IntPtr

        ' check if a card is connected
        If isCard = False Then
            MESSAGETEXT.Text = "Not connected"
            Exit Sub
        End If

        ' Set Disposition (see Scard.bas "Dispositions")
        dwDisposition = SCARD_LEAVE_CARD

        'Disconnect from Card
        rc = SCardDisconnect(hCard, dwDisposition)
        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        MESSAGETEXT.Text = "Disconnect successfull"
        isCard = False

    End Sub

    '
    ' Establish Context and List Readers
    '
    Private Sub ESTCONTEXTBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles ESTCONTEXTBUTTON.Click
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim dwScope As IntPtr

        'Dim mszReaders(512) As Byte
        Dim mszReaders As String = New System.String(vbNullChar, 1024)
        Dim mszGroup(512) As Byte
        Dim pcchReaders As Long

        Dim curReader(10) As String

        ' if a Context is established, release it first
        If isContext = True Then RELCONTEXTBUTTON_Click(RELCONTEXTBUTTON, New System.EventArgs())

        ' Set Scope (see Scard.bas "Scopes")
        dwScope = SCARD_SCOPE_USER

        ' Establish Context
        rc = SCardEstablishContext(dwScope, 0, 0, hContext)

        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        ' Set maximum Length of mszReaders
        pcchReaders = 2048

        ' Create a Multistring (terminated with two '\0's)
        mszGroup(0) = &H0
        mszGroup(1) = &H0
        Try
            rc = SCardListReaders(hContext, mszGroup(LBound(mszGroup)), mszReaders, pcchReaders)
        Catch ex As Exception
            MessageBox.Show(ex.Message)

        End Try

        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        ReaderList.Items.Clear()


        Dim i As Integer

        ' Split multistring and add single Readers to list
        'For i = 0 To pcchReaders - 2 Step 1
        '    If mszReaders(i) = &H0 And i <> 0 Then
        '        ReaderList.Items.Add(curReader)
        '        ReaderList.SelectedIndex = 0
        '        curReader = ""
        '        i = i + 1
        '    End If

        '    curReader = curReader + GetString(mszReaders(i))
        'Next i
        If rc = 0 Then
            curReader = Split(mszReaders, vbNullChar)        'To split the name of the readers from the string
            While curReader(i) <> ""
                ReaderList.Items.Add(curReader(i)) 'Add the readers name into the combobox
                ReaderList.SelectedIndex = 0
                'curReader = ""
                i = i + 1

                If (i > curReader.Length - 1) Then           'checks the length of the array
                    Exit While
                End If
            End While
        Else
            'No reader is connected
        End If

        MESSAGETEXT.Text = "Establish successfull, ListReaders successfull"
        isContext = True

    End Sub

    '
    ' InitI2C
    '
    Private Sub INITI2CBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles INITI2CBUTTON.Click
        Dim OKERR_OK As Object = Nothing
        Dim NO_PREDEFINED_PARAMETERS As Object = Nothing

        Dim rc As IntPtr
        Dim CardParameters As SCARD_I2C_CARD_PARAMETERS
        Dim pCardParameters As IntPtr
        Dim lType As IntPtr
        ' Dim a As vbptr

        'Dim Address As GCHandle


        ' Type (see SCardI2C.bas "Predefined Cardtypes")
        'UPGRADE_WARNING: Couldn't resolve default property of object NO_PREDEFINED_PARAMETERS. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        lType = NO_PREDEFINED_PARAMETERS
        If I2CTYPE.Text = "ST14C02C" Then lType = SCardI2C.SCARD_I2C_TYPE.ST14C02C
        If I2CTYPE.Text = "ST14C04C" Then lType = SCardI2C.SCARD_I2C_TYPE.ST14C04C
        If I2CTYPE.Text = "ST14E32" Then lType = SCardI2C.SCARD_I2C_TYPE.ST14E32
        If I2CTYPE.Text = "M14C04" Then lType = SCardI2C.SCARD_I2C_TYPE.M14C04
        If I2CTYPE.Text = "M14C16" Then lType = SCardI2C.SCARD_I2C_TYPE.M14C16
        If I2CTYPE.Text = "M14C32" Then lType = SCardI2C.SCARD_I2C_TYPE.M14C32
        If I2CTYPE.Text = "M14C64" Then lType = SCardI2C.SCARD_I2C_TYPE.M14C64
        If I2CTYPE.Text = "M14128" Then lType = SCardI2C.SCARD_I2C_TYPE.M14128
        If I2CTYPE.Text = "M14256" Then lType = SCardI2C.SCARD_I2C_TYPE.M14256
        If I2CTYPE.Text = "GFM2K" Then lType = SCardI2C.SCARD_I2C_TYPE.GFM2K
        If I2CTYPE.Text = "GFM4K" Then lType = SCardI2C.SCARD_I2C_TYPE.GFM4K
        If I2CTYPE.Text = "GFM32K" Then lType = SCardI2C.SCARD_I2C_TYPE.GFM32K
        If I2CTYPE.Text = "AT24C01A" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C01A
        If I2CTYPE.Text = "AT24C02" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C02
        If I2CTYPE.Text = "AT24C04" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C04
        If I2CTYPE.Text = "AT24C08" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C08
        If I2CTYPE.Text = "AT24C16" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C16
        If I2CTYPE.Text = "AT24C164" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C164
        If I2CTYPE.Text = "AT24C32" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C32
        If I2CTYPE.Text = "AT24C64" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C64
        If I2CTYPE.Text = "AT24C128" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C128
        If I2CTYPE.Text = "AT24C256" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C256
        If I2CTYPE.Text = "AT24CS128" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24CS128
        If I2CTYPE.Text = "AT24CS256" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24CS256
        If I2CTYPE.Text = "AT24C512" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C512
        If I2CTYPE.Text = "AT24C1024" Then lType = SCardI2C.SCARD_I2C_TYPE.AT24C1024


        ' get pointer do CardParameters
        'UPGRADE_ISSUE: VarPtr function is not supported. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="367764E5-F3F8-4E43-AC3E-7FE0B5E074E2"'
        pCardParameters = VarPtr(CardParameters)
        ' Dim pCardParameters As GCHandle = GCHandle.Alloc(CardParameters)










        'pCardParameters = Address(CardParameters)

        ' Init
        'rc = SCardI2CInit(hCard, pCardParameters, lType)

        If (IntPtr.Size = "8") Then
            rc = SCardI2CInitx64(hCard, pCardParameters, lType)
        Else
            rc = SCardI2CInit(hCard, pCardParameters, lType)
        End If




        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = HandleError(rc)
            Exit Sub
        End If

        Me.WRITEBUTTON.Enabled = True

        MESSAGETEXT.Text = "InitI2C successfull"

    End Sub

    Private Sub PRESENTPIN_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles PRESENTPIN.Click
        Dim OKERR_OK As Object = Nothing
        Dim rc As IntPtr
        Dim ulPINLen As IntPtr
        Dim bPin() As Byte = Nothing


        If (Me.CARDTYPE.Text = "3W") Then
            Me.PIN.Text = "FFFF"
        Else
            Me.PIN.Text = "FFFFFF"
        End If
        ulPINLen = StrToArray(bPin, Me.PIN.Text)
        If ulPINLen = 0 Then
            Exit Sub
        End If

        If (Me.CARDTYPE.Text = "2W") Then
            If (IntPtr.Size = "8") Then
                rc = SCard2WBPPresentPINx64(hCard, ulPINLen, bPin)
            Else
                rc = SCard2WBPPresentPIN(hCard, ulPINLen, bPin)

            End If

        End If
        If (Me.CARDTYPE.Text = "3W") Then
            If (IntPtr.Size = "8") Then
                rc = SCard3WBPPresentPINx64(hCard, ulPINLen, bPin)

            Else
                rc = SCard3WBPPresentPIN(hCard, ulPINLen, bPin)

            End If
        End If

            'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If rc <> OKERR_OK Then
                MESSAGETEXT.Text = HandleError(rc)
                Exit Sub
            End If

            Me.WRITEBUTTON.Enabled = True

            MESSAGETEXT.Text = "PresentPin successfull"

    End Sub

    Private Sub PresentPin2W_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim ulPINLen As IntPtr
        Dim bPin(1) As Byte

        ulPINLen = StrToArray(bPin, Me.PIN.Text)
        If ulPINLen = 0 Then
            Exit Sub
        End If
        If (IntPtr.Size = "8") Then
            rc = SCard2WBPPresentPINx64(hCard, ulPINLen, bPin)
        Else
            rc = SCard2WBPPresentPIN(hCard, ulPINLen, bPin)
        End If

        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = HandleError(rc)
            Exit Sub
        End If

        MESSAGETEXT.Text = "2W - PresentPin successfull"

    End Sub

    Private Sub PRESENTPIN3W_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim ulPINLen As IntPtr
        Dim bPin() As Byte = Nothing

        'ulPINLen = StrToArray(bPin, Me.PIN.Text)
        'If ulPINLen = 0 Then
        '    Exit Sub
        'End If

        'rc = SCard3WBPPresentPIN(hCard, ulPINLen, bPin(LBound(bPin)))

        If (IntPtr.Size = "8") Then
            rc = SCard3WBPPresentPINx64(hCard, ulPINLen, bPin)
        Else
            rc = SCard3WBPPresentPIN(hCard, ulPINLen, bPin)
        End If




        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = HandleError(rc)
            Exit Sub
        End If

        MESSAGETEXT.Text = "3W - PresentPin successfull"

    End Sub

    Private Sub READBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles READBUTTON.Click
        Dim OKERR_OK As Object = Nothing
        Dim rc As IntPtr
        Dim bData() As Byte
        Dim ulBytesToRead As IntPtr
        'Dim pbData(500) As Byte

        Dim cData As String = New System.String(vbNullChar, 2048)

        ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
        ReDim bData(ulBytesToRead)


        If (Me.CARDTYPE.Text = "2W") Then
            ' Read
            If (IntPtr.Size = "8") Then
                'rc = SCard2WBPReadDatax64(hCard, ulBytesToRead, bData(LBound(bData)), 0L)
                rc = SCard2WBPReadDatax64(hCard, ulBytesToRead, bData, 0L)
            Else
                rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
            End If
            'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If rc <> OKERR_OK Then
                MESSAGETEXT.Text = HandleError(rc)
                Exit Sub
            End If
        End If

            If (Me.CARDTYPE.Text = "3W") Then
                'Try
                ' Read
                If (IntPtr.Size = "8") Then
                ' rc = SCard3WBPReadDatax64(hCard, ulBytesToRead, cData, 0)
                rc = SCard3WBPReadDatax64(hCard, ulBytesToRead, bData, 0)
                Else
                rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
                End If
                'rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
                'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                If rc <> OKERR_OK Then
                    MESSAGETEXT.Text = (HandleError(rc))
                    Exit Sub
                End If
                'Catch
                '    If rc <> OKERR_OK Then
                '        MESSAGETEXT.Text = (HandleError(rc))
                '        Exit Sub
                '    End If
                '    MessageBox.Show(HandleError(rc))
                'End Try


            End If

            If (Me.CARDTYPE.Text = "I2C") Then
                ' Read
                If (IntPtr.Size = "8") Then
                rc = SCardI2CReadDatax64(hCard, bData, ulBytesToRead, 0, ulBytesToRead)
                'rc = SCardI2CReadDatax64(hCard, bData(LBound(bData)), ulBytesToRead, 0, ulBytesToRead)
                Else
                rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulBytesToRead, 0, ulBytesToRead)
                End If
                'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                If rc <> OKERR_OK Then
                    MESSAGETEXT.Text = (HandleError(rc))
                    Exit Sub
                End If
            End If

        Dim OUT As String = ""
        'If (IntPtr.Size = "8") Then
        'bData = strtobyte(cData)
        ' End If

        ' Create a Hexdump from returned data
        OUT = OUT & HexDump(bData, ulBytesToRead)

        MESSAGETEXT.Text = "Read successfull"

        ' Show Data
        REPLYDATA.Text = OUT

    End Sub

    '
    ' Read 100 Bytes from 2WCard
    '
    Private Sub READBUTTON2W_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte
        Dim ulBytesToRead As IntPtr

        ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
        ReDim bData(ulBytesToRead)

        ' Read
        'rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
        If (IntPtr.Size = "8") Then
            rc = SCard2WBPReadDatax64(hCard, ulBytesToRead, bData, 0)
        Else
            rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
        End If
        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = HandleError(rc)
            Exit Sub
        End If

        Dim OUT As String = Nothing

        ' Create a HexDump from returned Data
        OUT = OUT & HexDump(bData, ulBytesToRead)

        MESSAGETEXT.Text = "Read2W successfull"

        ' Show Data
        REPLYDATA.Text = OUT

    End Sub

    '
    ' Read 100 Bytes from 3WCard
    '
    Private Sub READBUTTON3W_Click()
        Dim ulReadBufferSize As Object = Nothing
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte
        Dim ulBytesToRead As IntPtr

        ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
        ReDim bData(ulBytesToRead)


        If (Me.CARDTYPE.Text = "2W") Then
            ' Read
            'rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)



            If (IntPtr.Size = "8") Then
                rc = SCard2WBPReadDatax64(hCard, ulBytesToRead, bData, 0)
            Else
                rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
            End If


            'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If rc <> OKERR_OK Then
                MESSAGETEXT.Text = HandleError(rc)
                Exit Sub
            End If
        End If

            If (Me.CARDTYPE.Text = "3W") Then
                ' Read
            'rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)


            If (IntPtr.Size = "8") Then
                rc = SCard3WBPReadDatax64(hCard, ulBytesToRead, bData, 0)
            Else
                rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
            End If




            'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If rc <> OKERR_OK Then
                MESSAGETEXT.Text = (HandleError(rc))
                Exit Sub
            End If
        End If

            If (Me.CARDTYPE.Text = "I2C") Then
                ' Read
                'UPGRADE_WARNING: Couldn't resolve default property of object ulReadBufferSize. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            'rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)

            If (IntPtr.Size = "8") Then
                rc = SCardI2CReadDatax64(hCard, bData, ulReadBufferSize, 0, ulBytesToRead)
            Else
                rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)
            End If







                'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
                If rc <> OKERR_OK Then
                    MESSAGETEXT.Text = (HandleError(rc))
                    Exit Sub
                End If
            End If

        Dim OUT As String = Nothing

            ' Create a Hexdump from returned data
            OUT = OUT & HexDump(bData, ulBytesToRead)

            MESSAGETEXT.Text = "Read successfull"

            ' Show Data
            REPLYDATA.Text = OUT

    End Sub

    '
    ' Read 100 Bytes from I2CCard
    '
    Private Sub READBUTTONI2C_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte
        Dim ulReadBufferSize As IntPtr
        Dim ulBytesToRead As IntPtr

        ulBytesToRead = CInt(BYTESTOREAD.Text)
        ulReadBufferSize = ulBytesToRead
        ReDim bData(ulReadBufferSize)

        ' Read
        'rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)


        If (IntPtr.Size = "8") Then
            rc = SCardI2CReadDatax64(hCard, bData, ulReadBufferSize, 0, ulBytesToRead)
        Else
            rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)
        End If





        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        Dim OUT As String = ""

        'Create Hexdump from returned data
        OUT = OUT & HexDump(bData, ulBytesToRead)

        MESSAGETEXT.Text = "ReadI2C successfull"
        ' Show data
        REPLYDATA.Text = OUT

    End Sub

    '
    ' Release context
    '
    Private Sub RELCONTEXTBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles RELCONTEXTBUTTON.Click
        Dim OKERR_OK As Object = Nothing
        Dim rc As IntPtr

        ' if a Card is connected, disconnect first
        If isCard = True Then DISCONNECTBUTTON_Click(DISCONNECTBUTTON, New System.EventArgs())

        ' check if a context is established
        If isContext = False Then
            MESSAGETEXT.Text = "No context established"
            Exit Sub
        End If

        ' release
        'UPGRADE_WARNING: Couldn't resolve default property of object rc. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        rc = SCardReleaseContext(hContext)

       





        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        'UPGRADE_WARNING: Couldn't resolve default property of object rc. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            'UPGRADE_WARNING: Couldn't resolve default property of object rc. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        ' remove readers from readerlist
        ReaderList.Items.Clear()
        MESSAGETEXT.Text = "Release successfull"

        isContext = False

    End Sub

    Private Sub Form1_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed

        ' release context before closing application
        If isContext = True Then RELCONTEXTBUTTON_Click(RELCONTEXTBUTTON, New System.EventArgs())

    End Sub

    Private Sub WRITEBUTTON_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles WRITEBUTTON.Click
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte = Nothing
        Dim bDataLen As IntPtr
        Dim iAdress As IntPtr

        iAdress = HexStrToInt(Me.Adress.Text)
        bDataLen = StrToArray(bData, Me.WRITEDATA.Text)

        If bDataLen = 0 Then
            Exit Sub
        End If

        If (Me.CARDTYPE.Text = "2W") Then
            If (IntPtr.Size = "8") Then
                rc = SCard2WBPWriteDatax64(hCard, bDataLen, bData(LBound(bData)), iAdress)
            Else
                rc = SCard2WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress)
            End If
        End If

        If (Me.CARDTYPE.Text = "3W") Then
            If (IntPtr.Size = "8") Then
                rc = SCard3WBPWriteDatax64(hCard, bDataLen, bData(LBound(bData)), iAdress, 0)
            Else
                rc = SCard3WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress, 0)
            End If
        End If

        If (Me.CARDTYPE.Text = "I2C") Then
            If (IntPtr.Size = "8") Then
                rc = SCardI2CWriteDatax64(hCard, bData(LBound(bData)), bDataLen, iAdress, bDataLen)
            Else
                rc = SCardI2CWriteData(hCard, bData(LBound(bData)), bDataLen, iAdress, bDataLen)
            End If
        End If

            'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
            If rc <> OKERR_OK Then
                MESSAGETEXT.Text = (HandleError(rc))
                Exit Sub
            End If

            MESSAGETEXT.Text = "WriteData successfull"

    End Sub

    Private Sub WRITEBUTTON2W_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte = Nothing

        Dim bDataLen As IntPtr
        Dim iAdress As IntPtr

        iAdress = HexStrToInt(Me.Adress.Text)

        bDataLen = StrToArray(bData, Me.WRITEDATA.Text)

        If bDataLen = 0 Then
            Exit Sub
        End If

        rc = SCard2WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress)


        If (IntPtr.Size = "8") Then
            rc = SCard2WBPWriteDatax64(hCard, bDataLen, bData(LBound(bData)), iAdress)
        Else
            rc = SCard2WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress)
        End If





        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        MESSAGETEXT.Text = "2W WriteData successfull"

    End Sub

    Private Sub WRITEBUTTON3W_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte = Nothing
        Dim bDataLen As IntPtr
        Dim iAdress As IntPtr

        iAdress = HexStrToInt(Me.Adress.Text)

        bDataLen = StrToArray(bData, Me.WRITEDATA.Text)

        If bDataLen = 0 Then
            Exit Sub
        End If

        'rc = SCard3WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress, 0)

        If (IntPtr.Size = "8") Then
            rc = SCard3WBPWriteDatax64(hCard, bDataLen, bData(LBound(bData)), iAdress, 0)
        Else
            rc = SCard3WBPWriteData(hCard, bDataLen, bData(LBound(bData)), iAdress, 0)
        End If





        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        End If

        MESSAGETEXT.Text = "3W WriteData successfull"

    End Sub

    Private Sub WRITEBUTTONI2C_Click()
        Dim OKERR_OK As Object = Nothing

        Dim rc As IntPtr
        Dim bData() As Byte = Nothing
        Dim ulWriteBufferSize As IntPtr
        Dim ulBytesToWrite As IntPtr
        ' Dim intIx As Short
        Dim iAdress As IntPtr

        'ulWriteBufferSize = BYTESTOREAD.Text
        'ulBytesToWrite = ulWriteBufferSize
        'ReDim bData(ulBytesToWrite)

        ulBytesToWrite = StrToArray(bData, Me.WRITEDATA.Text)
        ulWriteBufferSize = ulBytesToWrite

        iAdress = HexStrToInt(Me.Adress.Text)

        'For intIx = LBound(bData) To UBound(bData)
        '    bData(intIx) = intIx Mod 256
        'Next intIx
        ' Write
        'rc = SCardI2CWriteData(hCard, bData(LBound(bData)), ulWriteBufferSize, iAdress, ulBytesToWrite)

        If (IntPtr.Size = "8") Then
            rc = SCardI2CWriteDatax64(hCard, bData(LBound(bData)), ulWriteBufferSize, iAdress, ulBytesToWrite)
        Else
            rc = SCardI2CWriteData(hCard, bData(LBound(bData)), ulWriteBufferSize, iAdress, ulBytesToWrite)
        End If

        'UPGRADE_WARNING: Couldn't resolve default property of object OKERR_OK. Click for more: 'ms-help://MS.VSCC.v90/dv_commoner/local/redirect.htm?keyword="6A50421D-15FE-4896-8A1B-2EC21E9037B2"'
        If rc <> OKERR_OK Then
            MESSAGETEXT.Text = (HandleError(rc))
            Exit Sub
        Else
            MsgBox("Write OK,click ok to reread data..")
            Call READBUTTONI2C_Click()
        End If

    End Sub




    Private Sub PIN_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles PIN.TextChanged

    End Sub

    Private Sub Frame3_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Frame3.Enter

    End Sub
End Class