Option Strict Off
Option Explicit On
Module Scard







    ' *******************************************************
    ' Common SCard functions
    ' *******************************************************

    '
    ' Establish a context to resource manager
    ' Parameters:
    '       dwScope         = Scope (see Scopes)
    '       pvReserved1     = Reserved for further use
    '       pvReserved2     = Reserved for further use
    '       phContext       = Pointer to Context
    '
    Public Declare Function SCardEstablishContext Lib "WINSCARD" (ByVal dwScope As Integer, ByVal pvReserved1 As Integer, ByVal pvReserved2 As Integer, ByRef phContext As IntPtr) As IntPtr

    '
    ' Release current Context
    ' Parameters:
    '       hContext        = current Context
    '
    Public Declare Function SCardReleaseContext Lib "WINSCARD" (ByVal hContext As IntPtr) As IntPtr

    '
    ' List all availiable Readers
    ' Parameters:
    '       hContext        = current Context
    '       mszGroups       = multistring, containing groupnames
    '                          if mszGroups is not null only Readers which are
    '                          in specified groups are listed
    '       mszReaders      = multistring, containing all availiable Readers
    '       pcchReaders     = Length of mszReaders in Bytes
    '
    Public Declare Function SCardListReaders Lib "WINSCARD" Alias "SCardListReadersA" (ByVal hContext As IntPtr, ByVal mszGroups As Byte, ByVal mszReaders As String, ByRef pcchReaders As Long) As IntPtr

    '
    ' Connect to one specific Reader
    ' Parameters:
    '       hContext                = current Context
    '       szReaders               = name of a Reader
    '       dwShareMode             = Share Mode (see ShareModes)
    '       dwPreferredProtocols    = Preferred Protocol (see Protocols)
    '       hCard                   = Handle to Card
    '       dwActiveProtocol        = Returned Protocol
    '
    Public Declare Function SCardConnect Lib "WINSCARD" Alias "SCardConnectA" (ByVal hContext As IntPtr, ByVal szReader As String, ByVal dwShareMode As IntPtr, ByVal dwPreferredProtocols As IntPtr, ByRef hCard As IntPtr, ByRef dwActiveProtocol As IntPtr) As IntPtr

    '
    ' Disconnect from Card
    ' Parameters:
    '       hCard           = Handle to Card
    '       dwDisposition   = Action to do with Card (see Dispositions)
    '
    Public Declare Function SCardDisconnect Lib "WINSCARD" (ByVal hCard As IntPtr, ByVal dwDisposition As IntPtr) As IntPtr

    ' *******************************************************
    ' Constants
    ' *******************************************************

    '
    ' Scopes
    '
    Public Const SCARD_SCOPE_USER As Integer = 0 'The context is a user context, and any
    ' database operations are performed within the
    ' domain of the user.
    Public Const SCARD_SCOPE_TERMINAL As Integer = 1 'The context is that of the current terminal,
    ' and any database operations are performed
    ' within the domain of that terminal.  (The
    ' calling application must have appropriate
    ' access permissions for any database actions.)
    Public Const SCARD_SCOPE_SYSTEM As Integer = 2 'The context is the system context, and any
    ' database operations are performed within the
    ' domain of the system.  (The calling
    ' application must have appropriate access
    ' permissions for any database actions.)

    '
    ' Share Modes
    '
    Public Const SCARD_SHARE_EXCLUSIVE As Integer = 1 ' This application is not willing to share this
    ' card with other applications.
    Public Const SCARD_SHARE_SHARED As Integer = 2 ' This application is willing to share this
    ' card with other applications.
    Public Const SCARD_SHARE_DIRECT As Integer = 3 ' This application demands direct control of
    ' the reader, so it is not available to other
    ' applications.

    '
    ' Protocols
    '
    Public Const SCARD_PROTOCOL_UNDEFINED As Integer = &H0 ' There is no active protocol.
    Public Const SCARD_PROTOCOL_T0 As Integer = &H1 ' T=0 is the active protocol.
    Public Const SCARD_PROTOCOL_T1 As Integer = &H2 ' T=1 is the active protocol.
    Public Const SCARD_PROTOCOL_RAW As Integer = &H10000 ' Raw is the active protocol.


    '
    ' Dispositions (after disconnecting)
    '
    Public Const SCARD_LEAVE_CARD As Integer = 0 ' Don't do anything special on close
    Public Const SCARD_RESET_CARD As Integer = 1 ' Reset the card on close
    Public Const SCARD_UNPOWER_CARD As Integer = 2 ' Power down the card on close
    Public Const SCARD_EJECT_CARD As Integer = 3 ' Eject the card on close

    '
    ' Smart Card Error Codes
    ' All for SCARD error codes of the resource manager , a OK error code exists.
    '
    Public Const OKERR_SCARD__E_CANCELLED As Integer = &H80100002 '@cnst  The action was cancelled by an SCardCancel request
    Public Const OKERR_SCARD__E_INVALID_HANDLE As Integer = &H80100003 '@cnst  The supplied handle was invalid
    Public Const OKERR_SCARD__E_INVALID_PARAMETER As Integer = &H80100004 '@cnst  One or more of the supplied parameters could not be properly interpreted
    Public Const OKERR_SCARD__E_INVALID_TARGET As Integer = &H80100005 '@cnst  Registry startup information is missing or invalid
    Public Const OKERR_SCARD__E_NO_MEMORY As Integer = &H80100006 '@cnst  Not enough memory available to complete this command
    Public Const OKERR_SCARD__F_WAITED_TOO_LONG As Integer = &H80100007 '@cnst  An internal consistency timer has expired
    Public Const OKERR_SCARD__E_INSUFFICIENT_BUFFER As Integer = &H80100008 '@cnst  The data buffer to receive returned data is too small for the returned data
    Public Const OKERR_SCARD__E_UNKNOWN_READER As Integer = &H80100009 '@cnst  The specified reader name is not recognized
    Public Const OKERR_SCARD__E_TIMEOUT As Integer = &H8010000A '@cnst  The user-specified timeout value has expired
    Public Const OKERR_SCARD__E_SHARING_VIOLATION As Integer = &H8010000B '@cnst  The smart card cannot be accessed because of other connections outstanding
    Public Const OKERR_SCARD__E_NO_SMARTCARD As Integer = &H8010000C '@cnst  The operation requires a Smart Card, but no Smart Card is currently in the device
    Public Const OKERR_SCARD__E_UNKNOWN_CARD As Integer = &H8010000D '@cnst  The specified smart card name is not recognized
    Public Const OKERR_SCARD__E_CANT_DISPOSE As Integer = &H8010000E '@cnst  The system could not dispose of the media in the requested manner
    Public Const OKERR_SCARD__E_PROTO_MISMATCH As Integer = &H8010000F '@cnst  The requested protocols are incompatible with the protocol currently in use with the smart card
    Public Const OKERR_SCARD__E_NOT_READY As Integer = &H80100010 '@cnst  The reader or smart card is not ready to accept commands
    Public Const OKERR_SCARD__E_INVALID_VALUE As Integer = &H80100011 '@cnst  One or more of the supplied parameters values could not be properly interpreted
    Public Const OKERR_SCARD__E_SYSTEM_CANCELLED As Integer = &H80100012 '@cnst  The action was cancelled by the system, presumably to log off or shut down
    Public Const OKERR_SCARD__F_COMM_ERROR As Integer = &H80100013 '@cnst  An internal communications error has been detected
    Public Const OKERR_SCARD__F_UNKNOWN_ERROR As Integer = &H80100014 '@cnst  An internal error has been detected, but the source is unknown
    Public Const OKERR_SCARD__E_INVALID_ATR As Integer = &H80100015 '@cnst  An ATR obtained from the registry is not a valid ATR string
    Public Const OKERR_SCARD__E_NOT_TRANSACTED As Integer = &H80100016 '@cnst  An attempt was made to end a non-existent transaction
    Public Const OKERR_SCARD__E_READER_UNAVAILABLE As Integer = &H80100017 '@cnst  The specified reader is not currently available for use
    Public Const OKERR_SCARD__P_SHUTDOWN As Integer = &H80100018 '@cnst  The operation has been aborted to allow the server application to exit
    Public Const OKERR_SCARD__E_PCI_TOO_SMALL As Integer = &H80100019 '@cnst  The PCI Receive buffer was too small
    Public Const OKERR_SCARD__E_READER_UNSUPPORTED As Integer = &H8010001A '@cnst  The reader driver does not meet minimal requirements for support
    Public Const OKERR_SCARD__E_DUPLICATE_READER As Integer = &H8010001B '@cnst  The reader driver did not produce a unique reader name
    Public Const OKERR_SCARD__E_CARD_UNSUPPORTED As Integer = &H8010001C '@cnst  The smart card does not meet minimal requirements for support
    Public Const OKERR_SCARD__E_NO_SERVICE As Integer = &H8010001D '@cnst  The Smart card resource manager is not running
    Public Const OKERR_SCARD__E_SERVICE_STOPPED As Integer = &H8010001E '@cnst  The Smart card resource manager has shut down
    Public Const OKERR_SCARD__E_UNEXPECTED As Integer = &H8010001F '@cnst  An unexpected card error has occurred
    Public Const OKERR_SCARD__E_ICC_INSTALLATION As Integer = &H80100020 '@cnst  No Primary Provider can be found for the smart card
    Public Const OKERR_SCARD__E_ICC_CREATEORDER As Integer = &H80100021 '@cnst  The requested order of object creation is not supported
    Public Const OKERR_SCARD__E_UNSUPPORTED_FEATURE As Integer = &H80100022 '@cnst  This smart card does not support the requested feature
    Public Const OKERR_SCARD__E_DIR_NOT_FOUND As Integer = &H80100023 '@cnst  The identified directory does not exist in the smart card
    Public Const OKERR_SCARD__E_FILE_NOT_FOUND As Integer = &H80100024 '@cnst  The identified file does not exist in the smart card
    Public Const OKERR_SCARD__E_NO_DIR As Integer = &H80100025 '@cnst  The supplied path does not represent a smart card directory
    Public Const OKERR_SCARD__E_NO_FILE As Integer = &H80100026 '@cnst  The supplied path does not represent a smart card file
    Public Const OKERR_SCARD__E_NO_ACCESS As Integer = &H80100027 '@cnst  Access is denied to this file
    Public Const OKERR_SCARD__E_WRITE_TOO_MANY As Integer = &H80100028 '@cnst  An attempt was made to write more data than would fit in the target object
    Public Const OKERR_SCARD__E_BAD_SEEK As Integer = &H80100029 '@cnst  There was an error trying to set the smart card file object pointer
    Public Const OKERR_SCARD__E_INVALID_CHV As Integer = &H8010002A '@cnst  The supplied PIN is incorrect
    Public Const OKERR_SCARD__E_UNKNOWN_RES_MNG As Integer = &H8010002B '@cnst  An unrecognized error code was returned from a layered component
    Public Const OKERR_SCARD__E_NO_SUCH_CERTIFICATE As Integer = &H8010002C '@cnst  The requested certificate does not exist
    Public Const OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE As Integer = &H8010002D '@cnst  The requested certificate could not be obtained
    Public Const OKERR_SCARD__E_NO_READERS_AVAILABLE As Integer = &H8010002E '@cnst  Cannot find a smart card reader
    Public Const OKERR_SCARD__E_COMM_DATA_LOST As Integer = &H8010002F '@cnst  A communications error with the smart card has been detected
    Public Const OKERR_SCARD__W_UNSUPPORTED_CARD As Integer = &H80100065 '@cnst  The reader cannot communicate with the smart card, due to ATR configuration conflicts
    Public Const OKERR_SCARD__W_UNRESPONSIVE_CARD As Integer = &H80100066 '@cnst  The smart card is not responding to a reset
    Public Const OKERR_SCARD__W_UNPOWERED_CARD As Integer = &H80100067 '@cnst  Power has been removed from the smart card, so that further communication is not possible
    Public Const OKERR_SCARD__W_RESET_CARD As Integer = &H80100068 '@cnst  The smart card has been reset, so any shared state information is invalid
    Public Const OKERR_SCARD__W_REMOVED_CARD As Integer = &H80100069 '@cnst  The smart card has been removed, so that further communication is not possible
    Public Const OKERR_SCARD__W_SECURITY_VIOLATION As Integer = &H8010006A '@cnst  Access was denied because of a security violation
    Public Const OKERR_SCARD__W_WRONG_CHV As Integer = &H8010006B '@cnst  The card cannot be accessed because the wrong PIN was presented
    Public Const OKERR_SCARD__W_CHV_BLOCKED As Integer = &H8010006C '@cnst  The card cannot be accessed because the maximum number of PIN entry attempts has been reached
    Public Const OKERR_SCARD__W_EOF As Integer = &H8010006D '@cnst  The end of the smart card file has been reached
    Public Const OKERR_SCARD__W_CANCELLED_BY_USER As Integer = &H8010006E '@cnst  The action was cancelled by the user

    Public Const OKERR_PARM1 As Integer = &H81000000 'Error in parameter 1
    Public Const OKERR_PARM2 As Integer = &H81000001 'Error in parameter 2
    Public Const OKERR_PARM3 As Integer = &H81000002 'Error in parameter 3
    Public Const OKERR_PARM4 As Integer = &H81000003 'Error in parameter 4
    Public Const OKERR_PARM5 As Integer = &H81000004 'Error in parameter 5
    Public Const OKERR_PARM6 As Integer = &H81000005 'Error in parameter 6
    Public Const OKERR_PARM7 As Integer = &H81000006 'Error in parameter 7
    Public Const OKERR_PARM8 As Integer = &H81000007 'Error in parameter 8
    Public Const OKERR_PARM9 As Integer = &H81000008 'Error in parameter 9
    Public Const OKERR_PARM10 As Integer = &H81000009 'Error in parameter 10
    Public Const OKERR_PARM11 As Integer = &H8100000A 'Error in parameter 11
    Public Const OKERR_PARM12 As Integer = &H8100000B 'Error in parameter 12
    Public Const OKERR_PARM13 As Integer = &H8100000C 'Error in parameter 13
    Public Const OKERR_PARM14 As Integer = &H8100000D 'Error in parameter 14
    Public Const OKERR_PARM15 As Integer = &H8100000E 'Error in parameter 15
    Public Const OKERR_PARM16 As Integer = &H8100000F 'Error in parameter 16
    Public Const OKERR_PARM17 As Integer = &H81000010 'Error in parameter 17
    Public Const OKERR_PARM18 As Integer = &H81000011 'Error in parameter 18
    Public Const OKERR_PARM19 As Integer = &H81000012 'Error in parameter 19
    Public Const OKERR_INSUFFICIENT_PRIV As Integer = &H81100000 'You currently do not have the rights to execute the requested action. Usually a password has to be presented in advance.
    Public Const OKERR_PW_WRONG As Integer = &H81100001 'The presented password is wrong
    Public Const OKERR_PW_LOCKED As Integer = &H81100002 'The password has been presented several times wrong and is therefore locked. Usually use some administrator tool to unblock it.
    Public Const OKERR_PW_TOO_SHORT As Integer = &H81100003 'The lenght of the password was too short.
    Public Const OKERR_PW_TOO_LONG As Integer = &H81100004 'The length of the password was too long.
    Public Const OKERR_PW_NOT_LOCKED As Integer = &H81100005 'The password is not locked
    Public Const OKERR_ITEM_NOT_FOUND As Integer = &H81200000 'An item (e.g. a key of a specific name) could not be found
    Public Const OKERR_ITEMS_LEFT As Integer = &H81200001 'There are still items left, therefore e.g. the directory / structure etc. can't be deleted.
    Public Const OKERR_INVALID_CFG_FILE As Integer = &H81200002 'Invalid configuration file
    Public Const OKERR_SECTION_NOT_FOUND As Integer = &H81200003 'Section not found
    Public Const OKERR_ENTRY_NOT_FOUND As Integer = &H81200004 'Entry not found
    Public Const OKERR_NO_MORE_SECTIONS As Integer = &H81200005 'No more sections
    Public Const OKERR_ITEM_ALREADY_EXISTS As Integer = &H81200006 'The specified item alread exists.
    Public Const OKERR_ITEM_EXPIRED As Integer = &H81200007 'Some item (e.g. a certificate) has expired.
    Public Const OKERR_UNEXPECTED_RET_VALUE As Integer = &H81300000 'Unexpected return value
    Public Const OKERR_COMMUNICATE As Integer = &H81300001 'General communication error
    Public Const OKERR_NOT_ENOUGH_MEMORY As Integer = &H81300002 'Not enough memory
    Public Const OKERR_BUFFER_OVERFLOW As Integer = &H81300003 'Buffer overflow
    Public Const OKERR_TIMEOUT As Integer = &H81300004 'A timeout has occurred
    Public Const OKERR_NOT_SUPPORTED As Integer = &H81300005 'The requested functionality is not supported at this time / under this OS / in this situation etc.
    Public Const OKERR_ILLEGAL_ARGUMENT As Integer = &H81300006 'Illegal argument
    Public Const OKERR_READ_FIO As Integer = &H81300007 'File IO read error
    Public Const OKERR_WRITE_FIO As Integer = &H81300008 'File IO write error
    Public Const OKERR_INVALID_HANDLE As Integer = &H81300009 'Invalid handle
    Public Const OKERR_GENERAL_FAILURE As Integer = &H8130000A 'General failure. Use this error code in cases where no other errors match and it is not worth to define a new error code.
    Public Const OKERR_FILE_NOT_FOUND As Integer = &H8130000B 'File not found
    Public Const OKERR_OPEN_FILE As Integer = &H8130000C 'File opening failed
    Public Const OKERR_SEM_USED As Integer = &H8130000D 'The semaphore is currently use by an other process
    Public Const OKERR_NOP As Integer = &H81F00001 'No operation done
    Public Const OKERR_NOK As Integer = &H81F00002 'Function not executed
    Public Const OKERR_FWBUG As Integer = &H81F00003 'Internal error detected
    Public Const OKERR_INIT As Integer = &H81F00004 'Module not initialized
    Public Const OKERR_FIO As Integer = &H81F00005 'File IO error detected
    Public Const OKERR_ALLOC As Integer = &H81F00006 'Cannot allocate memory
    Public Const OKERR_SESSION_ERR As Integer = &H81F00007 'General error
    Public Const OKERR_ACCESS_ERR As Integer = &H81F00008 'Access not allowed
    Public Const OKERR_OPEN_FAILURE As Integer = &H81F00009 'An open command was not successful
    Public Const OKERR_CARD_NOT_POWERED As Integer = &H81F0000A 'Card is not powered
    Public Const OKERR_ILLEGAL_CARDTYPE As Integer = &H81F0000B 'Illegal cardtype
    Public Const OKERR_CARD_NOT_INSERTED As Integer = &H81F0000C 'Card not inserted
    Public Const OKERR_NO_DRIVER As Integer = &H81F0000D 'No device driver installed
    Public Const OKERR_OUT_OF_SERVICE As Integer = &H81F0000E 'The service is currently not available
    Public Const OKERR_EOF_REACHED As Integer = &H81F0000F 'End of file reached
    Public Const OKERR_ON_BLACKLIST As Integer = &H81F00010 'The ID is on a blacklist, the requested action is therefore not allowed.
    Public Const OKERR_CONSISTENCY_CHECK As Integer = &H81F00011 'Error during consistency check
    Public Const OKERR_IDENTITY_MISMATCH As Integer = &H81F00012 'The identity does not match a defined cross-check identity
    Public Const OKERR_MULTIPLE_ERRORS As Integer = &H81F00013 'Multiple errors have occurred. Use this if there is only the possibility to return one error code, but there happened different errors before (e.g. each thread returned a different error and the controlling thread may only report one).
    Public Const OKERR_ILLEGAL_DRIVER As Integer = &H81F00014 'Illegal driver
    Public Const OKERR_ILLEGAL_FW_RELEASE As Integer = &H81F00015 'The connected hardware whose firmware is not useable by this software
    Public Const OKERR_NO_CARDREADER As Integer = &H81F00016 'No cardreader attached
    Public Const OKERR_IPC_FAULT As Integer = &H81F00017 'General failure of inter process communication
    Public Const OKERR_WAIT_AND_RETRY As Integer = &H81F00018 'The service currently does not take calls. The task has to go back to the message loop and try again at a later time (Windows 3.1 only). The code may also be used, in every situation where a ‘  wait and retry ’  action is requested.
End Module