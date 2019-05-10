
/*****************************************************************************/
/** function SCRNClear()                                                    **/
/*****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#if defined S_OS2_32
   #define INCL_VIO
   #include <os2.h>
#elif defined S_WIN || defined S_MSDOS
   #include <graph.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
#endif

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

#if defined S_BOOT
   #define MK_FP(s,o)   ((void far *) ((((ULONG)s)<<16l)|(ULONG)o))
   LPBYTE pbLines    	= MK_FP(0x0040,0x0084);
   LPWORD pwColums 	   = MK_FP(0x0040,0x004A);
   BYTE bActColor       = 0x07;
#endif

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function clears the entire screen and sets the current cursor position
to the left upper corner (1,1).
@xref SCRNClearBlock
@xref SCRNSetCursorPosition
*/

VOID ENTRY SCRNClear(
           VOID)
{
#if defined S_OS2_32
   USHORT OldStatus;

   VioGetAnsi(&OldStatus, 0);      /* get old ANSI Status */

   VioSetAnsi(1, 0);               /* Set ANSI Support ON */
   VioWrtTTY("\33[2J", 4, 0);      /* Clear Screen with ANSI Sequence */

   VioSetAnsi(OldStatus, 0);       /* Activate previous ANSI Status */

   return;

#elif defined S_WIN || defined S_MSDOS
   _clearscreen(_GCLEARSCREEN);
   SCRNSetCursorPosition (1,1);

   return;

#elif defined S_UNIX || defined S_VMS
  wclear(stdscr);

#elif defined S_WNT
   HANDLE hStdOut;
   CONSOLE_SCREEN_BUFFER_INFO sScreenInfo;
   BOOL   fOk;
   DWORD  dummy;
   COORD  Coord;

   /* Windows 95 and Windows NT implementation uses Win32 Console API       */

   /* Handle fuer Std-Output ermitteln */
   hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   /* Bildschirmgroesse ermitteln */
   fOk = GetConsoleScreenBufferInfo(hStdOut,&sScreenInfo);
   if (fOk == FALSE)
      return;

   Coord.X = 0;
   Coord.Y = 0;

   /* Bildschirm loeschen */
   fOk = FillConsoleOutputCharacter(hStdOut,' ',
         (sScreenInfo.dwMaximumWindowSize.X*
         sScreenInfo.dwMaximumWindowSize.Y),Coord,&dummy);
   if (fOk == FALSE)
      return;

   /* Cursor links oben setzen */
   SetConsoleCursorPosition(hStdOut,Coord);
   return;
#elif defined S_BOOT
	_asm
		{

		//
		// Clear Screen Window
		//

		pusha	
		mov	ax,0600h						// Funktion 06	(Scroll up)
		mov	bh,bActColor            // Color
		mov	ch,0
      mov   cl,0
      mov   dh,24
		mov	dl,79
		int	10h
		popa
		}

   SCRNSetCursorPosition(1,1);
   return;

#else
   #error "Kein Zielsystem definiert"
#endif
}


#if defined S_BOOT

VOID ENTRY SCRNSetColor(BYTE bBackGround,BYTE bForeGround)
{
	bActColor = (BYTE)((bBackGround << 4) | bForeGround);
}

#endif


/****************************************************************************/
/** function SCRNClearBlock()                                              **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#include <stdlib.h>

#include <ok.h>
//#include <mem.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function clears a rectangular block on the screen. The block is
specified by the points (<i usRow1>,<i usColumn1>) and
(<i usRow2>,<i usColumn2>), including this points. <nl>
After the deletion process the cursor is positioned in the left upper corner
of the block.
@xref SCRNClear
@xref SCRNSetCursorPosition
*/

VOID ENTRY SCRNClearBlock(
           USHORT usRow1,     //@parm in | Row coordinate of left upper
                              //corner.
           USHORT usColumn1,  //@parm in | Column coordinate of left upper
                              //corner.
           USHORT usRow2,     //@parm in | Row coordinate of right lower
                              //corner.
           USHORT usColumn2)  //@parm in | Column coordinate of right lower
                              //corner.
{
   USHORT usTemp;                      /* Fuer Vertauschen falscher Eingaben*/
   USHORT usWidth;                     /* Breite des zu loeschenden Blocks */
   USHORT usCurrentLine;               /* Aktuelle Zeile */
   GPSTR  pszBlank;                    /* String mit Leerzeichen */

   /****** Eingabe pruefen ******/

   if (usRow1 > usRow2)                /* eventuell Ordnen des Inputs */
      {
      usTemp = usRow2;
      usRow2 = usRow1;
      usRow1 = usTemp;
      }

   if (usColumn1 > usColumn2)
      {
      usTemp    = usColumn2;
      usColumn2 = usColumn1;
      usColumn1 = usTemp;
      }

   /****** Erstellen einer Leerzeile in geforderter Breite ******/
   usWidth = (USHORT)(usColumn2 - usColumn1 + 1);

   if ((pszBlank=(GPSTR)malloc((UINT)usWidth+1)) == NULL)
      return;
  // MemSet(pszBlank, (UINT) usWidth+1, ' ', usWidth);
   memset(pszBlank,' ', usWidth);
   pszBlank[usWidth]='\0';

   /****** Loeschen des Bildschirmblocks ******/
   for(usCurrentLine=usRow1; usCurrentLine<=usRow2; usCurrentLine++)
      SCRNPutTextAt(usCurrentLine, usColumn1, pszBlank);

   /****** Setze Cursor in linke-obere Ecke des Blocks ******/
   SCRNSetCursorPosition(usRow1, usColumn1);

   free(pszBlank);
   return;
}


/***************************************************************************/
/**Function SCRNExit()                                                    **/
/***************************************************************************/


/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_WIN
   #include <stdio.h>
   #include <graph.h>
   #include <windows.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#endif

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Globale Variable                                                       **/
/****************************************************************************/

#ifdef S_WIN
   extern INT iSCRNMainWinHandle;
#endif

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function is intended to be called before an application that uses the
SCRN module terminates. It will free all resources eventually allocated by
the SCRN module like window handles and memory.
@xref SCRNInit
*/
VOID ENTRY SCRNExit(
           VOID)
{
#if defined S_WIN
   if (iSCRNMainWinHandle != 0)       /* Handle zeigt auf ein Fenster */
      _wgclose(iSCRNMainWinHandle);   /* Fensterspeicher freigeben */

   PostQuitMessage(0);
   return;
#elif defined S_UNIX || defined S_VMS
   wclear(stdscr);
   keypad(stdscr,FALSE);
   endwin();
#else
   return;
#endif
}

/****************************************************************************/
/** function SCRNGetText()                                                 **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if !defined S_BOOT
   #include <stdlib.h>
   #include <stdio.h>
   #include <ctype.h>
   #if ! defined S_UNIX
      #include <conio.h>
   #endif
#endif

#include <ok.h>
//#include <mem.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function calls the function <f SCRNGetText2> with parameter
<p fHideInput> == FALSE.
<nl>
See <f SCRNGetText2> for further information.

@rcode TRUE           | Input was entered correctly.
@rcode FALSE          | Input was aborted using the cancel key (ESC).

@xref SCRNGetText2
@xref SCRNGetULong
*/
BOOL ENTRY SCRNGetText(
           USHORT usFieldLen,    //@parm in | Length of entry field.
           GPSTR pszText,        //@parm out | Text buffer.
           USHORT usTextLen)     //@parm in | Length of text buffer.
{
   return SCRNGetText2(usFieldLen, pszText, usTextLen, FALSE);
}


/****************************************************************************/
/** function SCRNGetTextAt()                                               **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function gets a text from the keyboard and displays it on the screen
at the location specified by the coordinates <p usRow> and <p usColumn>.
<nl>
This function is equivalent to the subsequent call of <cr>
<f SCRNSetCursorPosition>(<p usRow>, <p usColumn>); <cr>
<f SCRNGetText>(<p usFieldLen>, <p pszText>, <p usTextLen>);

@rcode TRUE           | Input was entered correctly.
@rcode FALSE          | Input was aborted using the cancel key (ESC).

@xref SCRNGetText
@xref SCRNGetText2
@xref SCRNSetCursorPosition
*/
BOOL ENTRY SCRNGetTextAt(
           USHORT usRow,      //@parm in | Row coordinate.
           USHORT usColumn,   //@parm in | Column coordinate.
           USHORT usFieldLen, //@parm in | Length of entry field.
           GPSTR pszText,     //@parm out | Text buffer.
           USHORT usTextLen)  //@parm in | Length of text buffer.
{
   SCRNSetCursorPosition(usRow, usColumn);
   return SCRNGetText(usFieldLen, pszText, usTextLen);
}





/****************************************************************************/
/** function SCRNGetChar()                                                       **/
/****************************************************************************/




/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_OS2_32 || defined S_MSDOS
   #include <conio.h>
#elif defined S_WIN
   #include <graph.h>
   #include <io.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
   #include <stdio.h>
   #include <conio.h>
#endif

#if defined S_BOOT
   #include <bios.h>
#else
   #include <stdlib.h>
   #include <stdio.h>
   #include <ctype.h>
#endif

#include <ok.h>
#include "scrn.h"

/****************************************************************************/
/** LOCAL INCLUDES                                                         **/
/****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/**  LOCAL DEFINITIONS                                                     **/
/****************************************************************************/

#if defined S_BOOT
   static INT iKbdRead  = 0xFFFF;
#endif

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function gets a character from the current cursor position and returns
its value as the functions return code.

@xref SCRNGetText
*/
INT ENTRY SCRNGetChar(
          VOID)
{
#if defined S_OS2_32
      return (getch());
#elif defined S_WIN
      return (_inchar());
#elif defined S_UNIX || defined S_VMS
      return (wgetch(stdscr));
#elif defined S_WNT || defined S_MSDOS
      return (_getch());
#elif defined S_BOOT
      INT iKey,
          iAscii;

      // Init old or newer keyboard (F11 F12..)

      if (iKbdRead == 0xFFFF)
         {
         if ( (*(LPBYTE)0x00400096) & 0x10 )
            iKbdRead = _NKEYBRD_READ;
         else
            iKbdRead = _KEYBRD_READ;

         }

      // Read a char

      iKey = _bios_keybrd( iKbdRead);


      // and return only the Ascii code


      iAscii = iKey & 0x00ff;

      if (iAscii==0xe0)
         iAscii=0;

      return iAscii;
#else
      #error "Kein Zielsystem definiert"
#endif
}


/****************************************************************************/
/**function SCRNGetULong()                                                 **/
/****************************************************************************/


/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function gets an ULONG number (0 to 4.294.967.295) at the current cursor
position and returns this value.
<nl>
If the input is not a valid value (not between <p ulMin> and <p ulMax>) the
input field is deleted and the input must be repeated. If
<p ulMin> = <p ulMax> = 0, the maximum value range is valid. The length of
the entry field is automatically derived from <p ulMin> and <p ulMax>.
<nl>
Hexadecimal input is also possible; for this purpose, the input has to start
with <c "$x"> or <c "$X">; however, this input is case-insensitive. Only an
even number of hex-digits may be entered.
<nl>
The following inputs are equivalent:<nl>
    <tab> <b correct> <tab> <b wrong>       <cr>
(1) <tab> 15          <tab>                 <cr>
(2) <tab> $x0000000f  <tab> $x 00 00 00 0F  <cr>
(3) <tab> $X0F        <tab> $x00003135      <cr>
(4) <tab> $x000F      <tab>                 <nl>

The hex-digits are interpreted as numbers and accordingly returned. Therefore
the input <b '$x31353233'> means the number <b '825569843'>, in contrast to
<f SCRNGetText> where <b '$x31353233'> means the digit sequence <b '1523'>.
<nl>
For correction during input the 'Backspace' key can be used. Cursor shifting
using arrow keys is not possible.

@xref SCRNGetText
@xref SCRNGetULongAt

@rem:(INT) This function calls the function <f SCRNGetUnsigned> with <p bType>
specified as ULONG.
*/
ULONG ENTRY SCRNGetULong(
            ULONG ulMin,   //@parm in | Minimum value allowed.
            ULONG ulMax)   //@parm in | Maximum value allowed.
{
   return(SCRNGetUnsigned(ulMin, ulMax, TYPE_LONG));
}



/****************************************************************************/
/** function SCRNGetULongAt()                                              **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function gets an ULONG number from a location on the screen specified by
<p usRow> and <p usColumn>.
<nl>
This function is equivalent to the subsequent call of <cr>
<f SCRNSetCursorPosition>(<p usRow>, <p usColumn>); <cr>
<f SCRNGetULong>(<p ulMin>, <p ulMax>);

@xref SCRNGetULong
@xref SCRNGetTextAt
*/
ULONG ENTRY SCRNGetULongAt(
            USHORT usRow,     //@parm in | Row coordinate.
            USHORT usColumn,  //@parm in | Column coordinate.
            ULONG  ulMin,     //@parm in | Minimum value allowed.
            ULONG  ulMax)     //@parm in | Maximum value allowed.
{
   SCRNSetCursorPosition(usRow, usColumn);

   return(SCRNGetUnsigned(ulMin, ulMax, TYPE_LONG));
}



/****************************************************************************/
/** function SCRNInit()                                                    **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_WIN
   #include <graph.h>
   #include <io.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#endif

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Globale Variable                                                       **/
/****************************************************************************/

#if defined S_WIN
   INT iSCRNMainWinHandle = 0;
#endif

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function is intended to be called before any other SCRN function.
It will do the necessary initializaton tasks to enable the other functions to
work correctly (e.g. create a window).
@xref SCRNExit
*/
VOID ENTRY SCRNInit(
           VOID)
{
#if defined S_WIN
   INT    iStatus;
   INT    iHandle;
   struct _wsizeinfo sSize;

/* Minimize Std-text window */
   sSize._version = _QWINVER;
   sSize._type = _WINSIZEMIN;
   iHandle = _wgetfocus();
   iStatus = _wsetsize(iHandle, &sSize);

/* Close the default "Graphic1" GCW, because renaming is not possible */
   iStatus = (INT)_setvideomode(_TEXTC80);
   iHandle = (INT)_wggetactive();
   iStatus = (INT)_wgclose(iHandle);

/* Open a GCW named ... in which to put out text */

   iSCRNMainWinHandle = (INT)_wgopen("Testapplikation");
   iStatus            = (INT)_wgsetactive(iSCRNMainWinHandle);
   iStatus            = (INT)_setvideomode(_TEXTC80);
   iStatus            = (INT)_setbkcolor(0);
   iStatus            = (INT)_settextcolor(7);

   iStatus            = (INT)_wsetexit(_WINEXITPERSIST);
   iStatus            = _wmenuclick(_WINTILE);  /* Fenster in voller Breite */
   SCRNClear();
   _wyield();

   return;
#elif defined S_UNIX || defined S_VMS
   initscr();
   cbreak();
   noecho();
   leaveok(stdscr, TRUE);
   keypad(stdscr,TRUE);
#else
   return;
#endif
}

/****************************************************************************/
/**function SCRNPutTextAt()                                                **/
/****************************************************************************/

/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#include <ok.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function displays a text on the screen at the location specified by
<p usRow> and <p usColumn>.
<nl>
This function is equivalent to the subsequent call of <cr>
<f SCRNSetCursorPosition>(<p usRow>, <p usColumn>); <cr>
<f SCRNPutText>(<p pszText>);

@xref SCRNPutText
@xref SCRNPutHex
*/
VOID ENTRY SCRNPutTextAt(
           USHORT usRow,      //@parm in | Row coordinate.
           USHORT usColumn,   //@parm in | Column coordinate.
           GPSTR pszText)     //@parm in | Text buffer.
{
   SCRNSetCursorPosition(usRow, usColumn);
   SCRNPutText(pszText);

   return;
}



/****************************************************************************/
/** function SCRNSetCursorPosition()                                       **/
/****************************************************************************/



/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_OS2_32
   #define INCL_VIO
   #include <os2.h>
#elif defined S_WIN || defined S_MSDOS
   #include <graph.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
#endif

#include <ok.h>
#include "scrn.h"

#if defined S_BOOT
   extern LPBYTE pbLines;
   extern LPWORD pwColums;
#endif

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
@func
This function sets the cursor at a location on the screen specified by
<p usRow> and <p usColumn>. The upper, left corner is defined as (1,1).

@modif 09/30/1996 | R.Aufreiter | Corrected cursor offset under NT.

@xref SCRNClear
*/
VOID ENTRY SCRNSetCursorPosition(
           USHORT usRow,      //@parm in | Row coordinate.
           USHORT usColumn)   //@parm in | Column coordinate.
{
#if defined S_WIN || defined S_MSDOS
   _settextposition(usRow, usColumn);

#elif defined S_OS2_32 || defined S_UNIX || defined S_VMS
   /* Bei uns ist linke, obere Ecke (1,1), hier (0,0), deshalb -1 */

   if (usRow > 0)
      usRow--;

   if (usColumn > 0)
      usColumn--;

   #ifdef S_VMS
      mvaddstr(usRow, usColumn, "");
      refresh();
   #elif defined S_UNIX
      wmove(stdscr, usRow, usColumn);
   #elif defined S_OS2_32
      VioSetCurPos(usRow, usColumn, 0);
   #else
      #error "Kein Zielsystem definiert"
   #endif

#elif defined S_WNT
   HANDLE hStdOut;
   COORD  Coord;

   /* Bei uns ist linke, obere Ecke (1,1), hier (0,0), deshalb -1 */

   if (usRow > 0)
      usRow--;

   if (usColumn > 0)
      usColumn--;

   /* Handle fuer Std-Output ermitteln */
   hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   Coord.X = usColumn;
   Coord.Y = usRow;

   /* Cursor an gegebene Position setzen */
   SetConsoleCursorPosition(hStdOut,Coord);
#elif S_BOOT
	if (usRow > *pbLines)
		usRow = (*pbLines) + 1;

	if (usColumn > *pwColums)
		usColumn = *pwColums;

	if (usRow > 0)
		usRow--;

	if (usColumn > 0)
		usColumn--;


	_asm
		{
		pusha
		//
		// Set cursor pos in page 0
		//
		mov	ah,02h
		mov	bh,00h
		mov	dh,byte ptr usRow
		mov	dl,byte ptr usColumn
		int	10h
		popa
		}
#endif

   return;
}



/****************************************************************************/
/** finction SCRNPutText()                                                          **/
/****************************************************************************/



/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_WIN || defined S_MSDOS
   #include <graph.h>
   #include <io.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
#endif

#if !defined S_BOOT
   #include <stdio.h>
#endif

#include <ok.h>
//#include <str.h>
#include "scrn.h"

#if defined S_BOOT
   extern BYTE bActColor;
#endif

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/

#if defined S_BOOT
/*****************************************************************************
@func
This function prints a character at the current cursor position in page 0.
(only S_BOOT model)
@modif 1/7/1997 | C. Gusenbauer | initial version
******************************************************************************/

VOID ENTRY SCRNPutChar(
                       CHAR cChar) //@parm in | the character
{

	_asm
		{
		mov	al,cChar
      mov   ah,0Eh               // Print a character
      mov   bh,0
		mov	bl,bActColor         // Only graphics mode matter this
		int	10h
		}

   return;
}
#endif

/*
@func
This function displays the string <p pszText> on the screen at the current
cursor position.
<nl>
<i Note:> The string has to be NULL-terminated!
<nl>
If using the SCRN module, this function should always be used instead of
<f printf>, since there is no guarantee, that <f printf> will display text
on the same target (window) as the SCRN module does. If you don't want to
miss the formatting features of <f printf>, you have to create a string
using <f sprintf> and afterwards display this string using <b SCRNPutText>.
<nl>
Escape sequences like '\\n' or '\\a' can be used within the string as in
<f printf>.

@xref SCRNPutTextAt
@xref SCRNPutHex

@ex This example shows, how the SCRN module is used for screen output. |
   #include <ok.h>
   #include <scrn.h>

   main()
   {
      CHAR  szText[15];
      SHORT iValue = 200;

      SCRNInit();                   // Initialize SCRN module //
      SCRNClear();                  // Clears the entire screen //

      SCRNSetCursorPosition(2, 3);  // Set Cursor to line 2, column 3 //
      SCRNPutText("Hello World");   // Display "Hello World" //

      // Create a formatted text to be displayed by SCRNPutText //

      sprintf(szText, "Wert: %d", ivalue);

      SCRNPutTextAt(5, 3, szText);

      // Deletes the first two letters of the two text lines //
      SCRNClearBlock(2, 3, 5, 4);

      SCRNExit();                   // Close SCRN session //
      exit(0);                      // Terminate program //
   }
*/

VOID ENTRY SCRNPutText(
           GPSTR pszText)  //@parm in | Text to be displayed.
{
#if defined S_OS2_32
   printf("%s", pszText);
   fflush(stdout);

#elif defined S_WIN || S_MSDOS
   _outtext(pszText);

#elif defined S_UNIX || defined S_VMS
   waddstr(stdscr, pszText);
   refresh();

#elif defined S_WNT
   DWORD  dummy;
   HANDLE hStdOut;

   hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   WriteFile(hStdOut, pszText, strlen(pszText), &dummy, NULL);
#elif defined S_BOOT
   INT	i;

   //	--------------------------------------------------
   // Print a string at the current cursor pos in page 0
   //	--------------------------------------------------
   for (i=0;i<StrLen(pszText);i++)
      {
      SCRNPutChar(*(pszText+i));
      if (*(pszText+i) == '\n')				//	If there is a NewLine
         SCRNPutChar('\r');					//	also add a Carriage return
      }
#endif

   return;
}

/****************************************************************************/
/** function SCRNGetText2()                                                **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_OS2_32
   #include <conio.h>
#elif defined S_WIN || defined S_MSDOS
   #include <graph.h>
   #include <io.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
   #include <stdio.h>
   #include <conio.h>
#endif

#if !defined S_BOOT
   #include <stdlib.h>
   #include <stdio.h>
   #include <ctype.h>
   #include <limits.h>
#endif


#include <ok.h>
//#include <mem.h>
#include "scrn.h"
#if defined S_BOOT
#include <str.h>
#endif


/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
** Die Reihenfolge der 'if' Statements in der WHILE Schleife hat einen
** tieferen Sinn und sollte nicht willkuerlich geaendert werden!
*/
/*
@func
This function permits the user to enter a string at the current cursor
position (diplayed either as clear text or hidden as a sequence of '*') and
returns this string in <p pszText>.
<nl>
The number of input characters is limited by <p usFieldLen>. The returned
string is always NULL-terminated; therefore <p usTextLen> has to be at least
(<p usFieldLen>+1) long. Otherwise <p usFieldLen> is cut accordingly.
<nl>
The input of characters is also possible in hexadecimal values. For this
purpose, the input has to start with <c "$x"> or <c "$X">; however, this form
of entry is case-insensitive.
Furthermore only an even number of hex-digits can be entered as always two
digits make up a byte. The length of the input field is extended automatically
in hex-mode. The following inputs are equivalent: <nl>
    <tab> <b correct>    <tab> <tab> <b wrong> <cr>
(1) <tab> abKL12         <tab> <cr>
(2) <tab> $x61624B4c3132 <tab> <cr>
(3) <tab> $X61624b4c3132 <tab> $x 61 62 4B 4C 31 32 <nl>

The string is always returned as in (1) (binary form).
<nl>
To abort a text input press 'blank' under Open-VMS and 'ESC' on
other systems. You may always use 'Backspace' to correct your input. The
arrow keys are not supported for input.

@rcode TRUE           | Input was entered correctly.
@rcode FALSE          | Input was aborted using the cancel key (ESC).

@xref SCRNGetText
@xref SCRNGetTextAt
@xref SCRNGetULong

@ex This example shows the usage of the SCRN functions in a typical way. |
   #include <ok.h>
   #include <scrn.h>

   main()
   {
      CHAR     pszText[25];
      USHORT   usValue;
      ULONG    ulValue;

      SCRNInit();             // Initialize SCRN module //
      SCRNClear();            // Clears the entire screen //
      SCRNSetCursorPosition(2, 3);

      // Entry of the first name //

      SCRNPutText("First Name: ");
      SCRNGetText(24, pszText, 25);

      // Input of a number between 0 and 150 //

      SCRNPutTextAt(4, 3, "Age:");
      usValue = SCRNGetUShortAt(4, 10, 0, 150);

      // Input of a number between 0 and 65535 //

      SCRNPutTextAt(6, 1, "Number: ");
      usValue = SCRNGetUShort(0, 0);

      // Input of a large number between 10 and 200000 and output of the
      result //

      SCRNPutTextAt(8, 2, "Number between 10 and 200000: ");
      ulValue = SCRNGetULong(10, 200000);
      sprintf(pszText, "The input was: %lu", ulValue);
      SCRNPutTextAt(10, 2, pszText);

      SCRNExit();             // Close SCRN session //
      exit(0);                // Terminate program //
   }

*/
BOOL ENTRY SCRNGetText2(
           USHORT usFieldLen, //@parm in | Length of entry field.
           GPSTR pszText,     //@parm out | Text buffer.
           USHORT usTextLen,  //@parm in | Length of text buffer.
           BOOL fHideInput)   //@parm in | Specifies whether characters on
                              //screen are displayed as clear text (FALSE)
                              //or '*' (TRUE).
{
   BOOL   bHex = FALSE;            /* Eingabe in Hex ja/nein */
   USHORT usHexInputLen;           /* Laenge der Eingabe in Hex Form */
   GPSTR  pszInput = NULL;         /* Hilfsfeld fuer Eingabe */
   USHORT usPosition = 0;          /* Aktuelle Position im Eingabefeld */
   USHORT usCurrentLen;            /* Gerade erlaubte Groesse des
                                      Eingabefeldes
                                      je nachdem ob Eingabe in Hex Modus
                                      oder nicht. */
   USHORT i;
   CHAR  szTmp[] = {0,0,0};
   ULONG ulTmp;
#if defined S_UNIX
   INT   iinc;
#elif defined S_WNT
   DWORD  dummy;
   HANDLE hStdOut;
   CHAR   szOutChar[2];
#endif

   /****** Vorbereitende Arbeiten ******/

   #if defined S_WNT
      /* Windows 95 and Windows NT implementation uses Win32 Console API */

      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      szOutChar[1] = '\0';
   #endif

   if (usTextLen == 0 || pszText == NULL)
      return TRUE;
                        /* Anpassen des Feldes an Laenge von pszText*/
   if (usTextLen < usFieldLen+(USHORT)1)
      usFieldLen = (USHORT)(usTextLen - 1);

   pszText[0] = '\0';
   pszText[usFieldLen] = '\0';
   usHexInputLen = (USHORT)(usFieldLen*2 + 2);     /* Laenge des Feldes in Hex Form */
   if ((pszInput = (GPSTR)malloc(usHexInputLen+1)) == NULL)
      return TRUE;
   usCurrentLen = usFieldLen;

   #if defined S_UNIX || defined S_VMS
      wrefresh(stdscr);
   #endif

   /****** Eingabeschleife ******/

   while(usPosition <= usCurrentLen)
      {
#if defined S_OS2_32
      pszInput[usPosition] = (CHAR)getch();
#elif defined S_WIN || defined S_MSDOS
      pszInput[usPosition] = (CHAR)_inchar();
#elif defined S_UNIX || defined S_VMS
      iinc = wgetch(stdscr);
#elif defined S_WNT
      pszInput[usPosition] = (CHAR)_getch();
#elif defined S_BOOT
      pszInput[usPosition] = (CHAR) SCRNGetChar();
#else
      #error "Kein Zielsystem definiert"
#endif

#if defined S_OS2_32 || defined S_WIN || defined S_MSDOS || defined S_BOOT
      /*** CANCEL Taste gedrueckt, sofort beenden ***/
      if (pszInput[usPosition] == _ESC)
         {
         free(pszInput);
         return FALSE;
         }
#elif defined S_UNIX
      /*** Cancel Taste gedrueckt ==> sofort abbrechen ***/
      if (iinc == _CANCEL_KEY)
         return FALSE;

      #if defined S_AIX        /* Backspace Taste erzeugt anderen Scancode */
         if (iinc == _BACKSPACE_SCAN_AIX)
            iinc = _BACKSPACE;
      #elif defined S_VMS      /* Backspace Taste erzeugt anderen Scancode */
         if (iinc == _BACKSPACE_SCAN_VMS)
            iinc = _BACKSPACE;
      #elif defined S_SOLARIS
      #elif defined S_HPUX
      #else
         #error "Kein Zielsystem definiert"
      #endif

      /*** Andere Funktionstasten ignorieren ***/
      if (iinc > 255)
         iinc = 0;

      pszInput[usPosition] = (CHAR)iinc;

#elif defined S_WNT
      /*** CANCEL Taste gedrueckt, sofort beenden ***/
      if (pszInput[usPosition] == _ESC)
         {
         free(pszInput);
         return FALSE;
         }
#else
      #error "Kein Zielsystem definiert"
#endif

      /*** Am Ende des Feldes sind nur BACKSPACE und RETURN zulaessig ***/
      if (usPosition == usCurrentLen && pszInput[usPosition] != _BACKSPACE &&
          pszInput[usPosition] != _RETURN)
         continue;

      /*** BACKSPACE gedrueckt => letzten Buchstaben loeschen ***/
      if (pszInput[usPosition] == _BACKSPACE)
         {
         if (usPosition > 0)         /* Normaler Rueckschritt */
            {
            usPosition--;
#if defined S_OS2_32
            putchar(_BACKSPACE);
            putchar(' ');
            putchar(_BACKSPACE);
            fflush(stdout);
#elif defined S_MSDOS || defined S_WIN
            SCRNOutText(_BACKSPACE,1,FALSE);
#elif defined S_UNIX || defined S_VMS
            waddch(stdscr, _BACKSPACE);
            waddch(stdscr, ' ');
            waddch(stdscr, _BACKSPACE);
            wrefresh(stdscr);
#elif defined S_WNT
            szOutChar[0] = _BACKSPACE;
            WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
            WriteFile(hStdOut, " ", 1, &dummy, NULL);
            WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
            SCRNPutChar((CHAR)_BACKSPACE);
            SCRNPutChar((CHAR)' ');
            SCRNPutChar((CHAR)_BACKSPACE);
#else
      #error "Kein Zielsystem definiert"
#endif
            }

         /*** Es wurde moeglicherweise der '\' am Beginn eines 1 Byte langen
              Feldes geloescht => Felderweiterung auf 2 rueckgaengig machen ***/
         if (usFieldLen == 1 && usPosition == 0)
            usCurrentLen = 1;

         /*** Falls '\x' geloescht, wieder in ASCII Eingabemodus schalten ***/
         if (bHex == TRUE && usPosition == 1)
            {
            bHex = FALSE;
            usCurrentLen = usFieldLen;
            if (usFieldLen == 1)     /* Bei 1-stell. Feld auf Anfang setzen */
               {
               usPosition--;
#if defined S_OS2_32
               putchar(_BACKSPACE);
               putchar(' ');
               putchar(_BACKSPACE);
               fflush(stdout);
#elif defined S_MSDOS || defined S_WIN
               SCRNOutText(_BACKSPACE,1,FALSE);
#elif defined S_UNIX || defined S_VMS
               waddch(stdscr, _BACKSPACE);
               waddch(stdscr, ' ');
               waddch(stdscr, _BACKSPACE);
               wrefresh(stdscr);
#elif defined S_WNT
               szOutChar[0] = _BACKSPACE;
               WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
               WriteFile(hStdOut, " ", 1, &dummy, NULL);
               WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
               SCRNPutChar((CHAR)_BACKSPACE);
               SCRNPutChar((CHAR)' ');
               SCRNPutChar((CHAR)_BACKSPACE);
#else
      #error "Kein Zielsystem definiert"
#endif
               }
            }
         continue;
         }

      /*** RETURN gedrueckt => Ende der Eingabe ***/
      if (pszInput[usPosition] == _RETURN)
         /* Hex Eingaben muessen gerade viele Ziffern haben */
         if (bHex == TRUE && (usPosition & 0x0001))
            continue;
         else
            {
            pszInput[usPosition]='\0';
            break;
            }

      /*** Falls Cursor oder Funktionstaste gedrueckt, => ignorieren ***/
#if defined S_UNIX || defined S_VMS
         if (pszInput[usPosition] == 0)
            continue;
#elif defined S_OS2_32
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)getch();
         continue;
         }
#elif defined S_WIN || S_MSDOS
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)_inchar();
         SCRNOutText(pszInput[usPosition], usPosition, FALSE);
         continue;
         }
#elif defined S_WNT
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)_getch();
         continue;
         }
#elif defined S_BOOT
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         // hier nicht, da das Zeichen direkt mit int 16h geholt wird
         pszInput[usPosition] = (CHAR)SCRNGetChar();
         continue;
         }
#endif

      /*** Falls Sonstiges Steuerzeichen gedrueckt, => ignorieren ***/
      if ((pszInput[usPosition] == _TAB) || (pszInput[usPosition] == _ESC))
         continue;

      /*** Bei Hex Eingabe keine Hex-Ziffer gedrueckt => ignorieren ***/
      if (bHex == TRUE && isxdigit(pszInput[usPosition]) == 0)
         continue;

      /*** Falls bei Einstelliger Eingabe als erstes Zeichen '\' gedrueckt
           wurde, darf als zweites nur 'x' oder bereits abgefragtes
           Steuerzeichen eingegeben werden. ***/
      if (usFieldLen == 1 && usPosition == 1 && toupper(pszInput[1]) != 'X')
         continue;

      /*** Feldlaenge=1 und \ gedrueckt => wahrscheinlich soll Hex-Zahl
           eingegeben werden, deshalb Feld fuer die Eingabe von 'x' um
           eine Stelle erweitern ***/
      if (usFieldLen == 1 && usPosition == 0 && pszInput[0] == _BACKSLASH)
         usCurrentLen = 2;

      /*** Der String soll in Hex Form eingegeben werden ***/
      if (usPosition == 1 && toupper(pszInput[1]) == 'X' &&
          pszInput[0] == _BACKSLASH)
         {
         bHex = TRUE;
         usCurrentLen = usHexInputLen;
         }

      if (fHideInput)
         {
         /*** Stern anzeigen ***/
#if defined S_OS2_32
         putchar('*');
         fflush(stdout);
#elif defined S_WIN || defined S_MSDOS
         SCRNOutText('*',1, FALSE);
#elif defined S_UNIX || defined S_VMS
         waddch(stdscr, '*');
         wrefresh(stdscr);
#elif defined S_WNT
         WriteFile(hStdOut, "*", 1, &dummy, NULL);
#elif defined S_BOOT
         SCRNPutChar('*');
#else
         #error "Kein Zielsystem definiert"
#endif
         }
      else
         {
         /*** Eingegebenen Buchstaben anzeigen ***/
#if defined S_OS2_32
         putchar(pszInput[usPosition]);
         fflush(stdout);
#elif defined S_WIN || defined S_MSDOS
         SCRNOutText(pszInput[usPosition], usPosition, FALSE);
#elif defined S_UNIX || defined S_VMS
         waddch(stdscr, pszInput[usPosition]);
         wrefresh(stdscr);
#elif defined S_WNT
         szOutChar[0] = pszInput[usPosition];
         WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
         SCRNPutChar((CHAR)pszInput[usPosition]);
#else
         #error "Kein Zielsystem definiert"
#endif
         }
      usPosition++;
      }

   if (bHex == TRUE)            /* Eingabe erfolgte in Hex => konvertieren */
      {
      for(i=2; i < usPosition; i+=2)
         {
			 //MemCpy((GPVOID)szTmp, 2, &pszInput[i],2);
			  memcpy((GPVOID)szTmp,&pszInput[i],2);

			 ulTmp = strtol(szTmp, NULL,16);
			 pszText[(i-2)/2] = (BYTE) ulTmp;
			 pszText[((i-2)/2)+1] = 0;

         /*--- sscanf crasht mit "Bus error" auf SUN, daher obiger work around
            sscanf(&pszInput[i], "%02x", &pszText[(i-2)/2]); ---*/
         }
      }
   else
      //MemCpy((GPVOID)pszText, usTextLen, (GPVOID)pszInput, usPosition+1);
      memcpy((GPVOID)pszText,(GPVOID)pszInput, (((long)usPosition+1)<=((long)usTextLen)) ? usPosition+1 : usTextLen);

   free(pszInput);
   return TRUE;
}

/****************************************************************************/
/** function SCRNGetUnsigned()                                             **/
/****************************************************************************/
/****************************************************************************/
/** GLOBAL INCLUDES                                                        **/
/****************************************************************************/

#if defined S_OS2_32
   #include <conio.h>
#elif defined S_WIN || defined S_MSDOS
   #include <io.h>
   #include <graph.h>
#elif defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_WNT
   #include <okos.h>
   #include <windows.h>
   #include <stdio.h>
   #include <conio.h>
#endif

#if !defined S_BOOT
   #include <stdlib.h>
   #include <stdio.h>
   #include <ctype.h>
#endif

#include <limits.h>

#include <ok.h>
//#include <str.h>
#include "scrn.h"

/*****************************************************************************/
/** LOCAL INCLUDES                                                          **/
/*****************************************************************************/

#include "scrni.h"

/****************************************************************************/
/** Konstanten                                                             **/
/****************************************************************************/

#define _DIGITS_OF_ULONG_MAX 10         /* Anzahl der Ziffern von ULONG_MAX */

#if defined S_WIN || defined S_MSDOS
/****************************************************************************/
/** Interne Funktion                                                       **/
/****************************************************************************/
VOID SCRNOutText(
     CHAR chOut,
     USHORT usPosition,
     BOOL fHideInput)
{
   struct _rccoord sTextPos;
   CHAR   szHelp[2] = " ";

   szHelp[0]=chOut;
   if (szHelp[0] != _BACKSPACE)
      {
      if (!fHideInput)
         _outtext(szHelp);
      }
   else if (usPosition > 0)
      {
      sTextPos = _gettextposition();
      _settextposition((SHORT)sTextPos.row,(SHORT)(sTextPos.col-1));
      _outtext(" ");
      _settextposition((SHORT)sTextPos.row,(SHORT)(sTextPos.col-1));
      }
}

#endif

/****************************************************************************/
/** Implementation                                                         **/
/****************************************************************************/
/*
**
** Die Reihenfolge der 'if' Statements in der WHILE Schleife hat einen
** tieferen Sinn und sollte nicht willkuerlich geaendert werden!
*/
/*
@func
This function serves as universal input routine. The length of the wanted
hex-input is fitted to 4 or 8 digits, depending on the type. <nl>
Only values between the limits <p ulMin> and <p ulMax> are valid. <nl>
The parameter <p bType> specifies the type of the number (e.g. ULONG). If the
number is inserted in hexadecimal format the first two characters have to be
"$x".
@xref SCRNGetULong
*/

ULONG ENTRY SCRNGetUnsigned(
            ULONG ulMin,      //@parm in | Min. value.
            ULONG ulMax,      //@parm in | Max. value.
            BYTE bType)       //@parm in | Type of number (TYPE_SHORT or
                              //           TYPE_LONG).
{
   ULONG  ulTemp;                  /* Hilfsvar. zum Vertauschen */
   ULONG  ulResult;                /* gueltige Eingabezahl */
   BOOL   bInputOK = FALSE;        /* Eingabe in gueltigem Bereich? */
   BOOL   bHex = FALSE;            /* Eingabe in Hex ja/nein */
   USHORT usFieldLen;              /* Dezimale Groesse des Eingabefeldes */
   USHORT usHexInputLen;           /* Laenge der Eingabe in Hex Form */
   CHAR   pszInput[_DIGITS_OF_ULONG_MAX+1]; /* Hilfsfeld fuer Eingabe, muss
                                   mind. 11 Bytes lang sein fuer Hex Eingabe */
   USHORT usPosition = 0;          /* Aktuelle Position im Eingabefeld */
   USHORT usCurrentLen;            /* Gerade erlaubte Groesse des Eingabefeldes
                                      je nachdem ob Eingabe in Hex Modus
                                      oder nicht. */
   USHORT i;
   CHAR   pszMaxULong[_DIGITS_OF_ULONG_MAX+1]; /* ULONG_MAX als String zur
                                      Eingabepruefung da 'scanf' bei Zahlen
                                      groesser ULONG_MAX nicht mehr korrekt
                                      funktioniert */

#if defined S_UNIX || defined S_VMS
   INT   iinc;
#elif defined S_WNT
      DWORD  dummy;
      HANDLE hStdOut;
      CHAR szOutChar[2];
#endif

   /****** Vorbereitende Arbeiten ******/

   #if defined S_WNT
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      szOutChar[1] = '\0';
   #endif

   //StrPrintf(pszMaxULong, "%lu", ULONG_MAX);
	  sprintf(pszMaxULong, "%lu", ULONG_MAX);

   if (ulMin > ulMax)                /* ggf. Vertauschen von Min. und Max. */
      {
      ulTemp = ulMax;
      ulMax  = ulMin;
      ulMin  = ulTemp;
      }

   if (bType == TYPE_SHORT)
      {
      if (ulMax == 0)                       /* Maximaler Eingabebereich */
         ulMax = USHRT_MAX;
      usHexInputLen = sizeof(USHORT)*2+2;   /* Laenge des Feldes in Hex Form */
      }
   else                /* Default = ULONG */
      {
      if (ulMax == 0)                       /* Maximaler Eingabebereich */
         ulMax = ULONG_MAX;
      usHexInputLen = sizeof(ULONG)*2+2;    /* Laenge des Feldes in Hex Form */
      }

   //StrPrintf(pszInput, "%lu", ulMax);		/* Laenge des Eingabefeldes bestimmen */
   sprintf(pszInput, "%lu", ulMax);
   usFieldLen   = (USHORT)strlen(pszInput);
   usCurrentLen = usFieldLen;

#if defined S_UNIX || defined S_VMS
   refresh();
#endif

   /****** Eingabeschleife ******/

   while (bInputOK == FALSE)
      {
      while(usPosition <= usCurrentLen)
         {
#if defined S_OS2_32
         pszInput[usPosition] = (CHAR)getch();
#elif defined S_WIN || defined S_MSDOS
         pszInput[usPosition] = (CHAR)_inchar();
#elif defined S_UNIX || defined S_VMS
         iinc = wgetch(stdscr);

         #if defined S_AIX        /* Backspace Taste erzeugt anderen Scancode */
            if (iinc == _BACKSPACE_SCAN_AIX)
               iinc = _BACKSPACE;
         #elif defined S_VMS      /* Backspace Taste erzeugt anderen Scancode */
            if (iinc == _BACKSPACE_SCAN_VMS)
               iinc = _BACKSPACE;
         #elif defined S_SOLARIS
         #elif defined S_HPUX
         #else
            #error "Kein Zielsystem definiert"
         #endif

         if (iinc > 255)                    /* Funktionstaste; ignorieren */
            iinc = 0;

         pszInput[usPosition] = (CHAR)iinc;
#elif defined S_WNT
         pszInput[usPosition] = (CHAR)_getch();
#elif defined S_BOOT
         pszInput[usPosition] = (CHAR)SCRNGetChar();
#else
   #error "Kein Zielsystem definiert"
#endif

         /*** Am Ende des Feldes sind nur BACKSPACE und RETURN zulaessig ***/
         if (usPosition == usCurrentLen && pszInput[usPosition] != _BACKSPACE
             && pszInput[usPosition] != _RETURN)
            continue;

         /*** BACKSPACE gedrueckt => letzten Buchstaben loeschen ***/
         if (pszInput[usPosition] == _BACKSPACE)
            {
            if (usPosition > 0)         /* Normaler Rueckschritt */
               {
#if defined S_OS2_32
               putchar(_BACKSPACE);
               putchar(' ');
               putchar(_BACKSPACE);
               fflush(stdout);
#elif defined S_WIN || defined S_MSDOS
               SCRNOutText(_BACKSPACE, usPosition, FALSE);
#elif defined S_UNIX || defined S_VMS
               waddch(stdscr,_BACKSPACE);
               waddch(stdscr, ' ');
               waddch(stdscr,_BACKSPACE);
               wrefresh(stdscr);
#elif defined S_WNT
               szOutChar[0] = _BACKSPACE;
               WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
               WriteFile(hStdOut, " ", 1, &dummy, NULL);
               WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
               SCRNPutChar((CHAR)_BACKSPACE);
               SCRNPutChar((CHAR)' ');
               SCRNPutChar((CHAR)_BACKSPACE);
#else
   #error "Kein Zielsystem definiert"
#endif
               usPosition--;
               }

            /*** Es wurde moeglicherweise der '\' am Beginn eines 1 Byte langen
                 Feldes geloescht => Felderweiterung auf 2 rueckgaengig machen ***/
            if (usFieldLen == 1 && usPosition == 0)
               usCurrentLen = 1;

            /*** Falls '\x' geloescht, wieder in ASCII Eingabemodus schalten ***/
            if (bHex == TRUE && usPosition == 1)
               {
               bHex = FALSE;
               usCurrentLen = usFieldLen;
               if (usFieldLen == 1)  /* Bei 1-stell. Feld auf Anfang setzen */
                  {
                  usPosition--;
#if defined S_OS2_32
                  putchar(_BACKSPACE);
                  putchar(' ');
                  putchar(_BACKSPACE);
                  fflush(stdout);

#elif defined S_WIN || defined S_MSDOS
                  SCRNOutText(_BACKSPACE,1,FALSE);

#elif defined S_UNIX || defined S_VMS
                  waddch(stdscr,_BACKSPACE);
                  waddch(stdscr, ' ');
                  waddch(stdscr,_BACKSPACE);
                  wrefresh(stdscr);
#elif defined S_WNT
                  szOutChar[0] = _BACKSPACE;
                  WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
                  WriteFile(hStdOut, " ", 1, &dummy, NULL);
                  WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
                  SCRNPutChar((CHAR)_BACKSPACE);
                  SCRNPutChar((CHAR)' ');
                  SCRNPutChar((CHAR)_BACKSPACE);
#else
   #error "Kein Zielsystem definiert"
#endif
                  }
               }
            continue;
            }

         /*** RETURN gedrueckt => Ende der Eingabe ***/
         if (pszInput[usPosition] == _RETURN)
            {
            /* Hex Eingaben muessen gerade viele Ziffern haben, es darf keine
               Leereingaben geben. */
            if ((bHex == TRUE && (usPosition & 0x0001)) ||
                (usPosition == 0))
               continue;
            else
               {
               pszInput[usPosition]='\0';
               break;
               }
            }

         /*** Falls Cursor oder Funktionstaste gedrueckt, => ignorieren ***/
#if defined S_UNIX || defined S_VMS
         if (pszInput[usPosition] == 0)
            continue;
#elif defined S_OS2_32
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)getch();
         continue;
         }
#elif defined S_WIN || S_MSDOS
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)_inchar();
         SCRNOutText(pszInput[usPosition], usPosition, FALSE);
         continue;
         }
#elif defined S_WNT
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)_getch();
         continue;
         }
#elif defined S_BOOT
      if ((pszInput[usPosition] == 0) || (pszInput[usPosition] == 0xE0))
         {
         pszInput[usPosition] = (CHAR)SCRNGetChar();
         continue;
         }
#endif

         /*** Falls Sonstiges Steuerzeichen gedrueckt, => ignorieren ***/
         if ((pszInput[usPosition] == _TAB) || (pszInput[usPosition] == _ESC))
            continue;

         /*** Bei Hex Eingabe (erst ab 3. Zeichen moeglich) keine Hex-Ziffer
              gedrueckt => ignorieren ***/
         if (bHex == TRUE && isxdigit(pszInput[usPosition]) == 0)
            continue;

         /*** Als erstes Zeichen darf nur '\' oder eine Ziffer gedrueckt
              werden. ***/
         if (usPosition == 0 && pszInput[0] != _BACKSLASH &&
             isdigit(pszInput[0]) == 0)
            continue;

         /*** Falls als erstes Zeichen '\' gedrueckt wurde, darf als zweites
              nur 'x' eingegeben werden. ***/
         if (usPosition == 1 && pszInput[0] == _BACKSLASH &&
             toupper(pszInput[1]) != 'X')
            continue;

         /*** Im Dezimal-Modus duerfen nur Ziffern eingegeben werden. ***/
         if (usPosition > 0 && pszInput[0] != _BACKSLASH &&
             isdigit(pszInput[usPosition]) == 0)
            continue;

         /*** Feldlaenge=1 und '\' gedrueckt => wahrscheinlich soll Hex-Zahl
              eingegeben werden, deshalb Feld fuer die Eingabe von 'x' um
              eine Stelle erweitern ***/
         if (usFieldLen == 1 && usPosition == 0 && pszInput[0] == _BACKSLASH)
            usCurrentLen = 2;

         /*** Der String soll in Hex Form eingegeben werden ***/
         if (usPosition == 1 && toupper(pszInput[1]) == 'X' &&
             pszInput[0] == _BACKSLASH)
            {
            bHex = TRUE;
            usCurrentLen = usHexInputLen;
            }

         /*** Eingegebene Ziffer anzeigen ***/
#if defined S_OS2_32
         putchar(pszInput[usPosition]);
         fflush(stdout);

#elif defined S_WIN || defined S_MSDOS
         SCRNOutText(pszInput[usPosition], usPosition, FALSE);

#elif defined S_UNIX || defined S_VMS
         waddch(stdscr,pszInput[usPosition]);
         wrefresh(stdscr);

#elif defined S_WNT
         szOutChar[0] = pszInput[usPosition];
         WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
         SCRNPutChar((CHAR)pszInput[usPosition]);
#else
   #error "Kein Zielsystem definiert"
#endif
         usPosition++;
         }

      /*** Eingabe als Zahl ermitteln ***/
      #ifndef S_BOOT
         if (bHex == TRUE)         /* Eingabe erfolgte in Hex => konvertieren */
            sscanf_s(&pszInput[2], "%lx", &ulResult);
         else
            sscanf_s(pszInput, "%lu", &ulResult);
      #else
         if (bHex == TRUE)         /* Eingabe erfolgte in Hex => konvertieren */
            StrScanf(&pszInput[2], "%lx", &ulResult);
         else
            StrScanf(pszInput, "%lu", &ulResult);
      #endif

      /*** Eingabe auf Gueltigkeit pruefen ***/
      if ((ulResult < ulMin) || (ulResult > ulMax) ||
          (usPosition == _DIGITS_OF_ULONG_MAX && bHex == FALSE &&
           strcmp(pszInput, pszMaxULong) > 0))
         {                        /* Eingabe ungueltig => wiederholen */
         for (i=0; i < usPosition; i++)
            {
#if defined S_OS2_32
            putchar(_BACKSPACE);
            putchar(' ');
            putchar(_BACKSPACE);
            fflush(stdout);
#elif defined S_WIN || defined S_MSDOS
            SCRNOutText(_BACKSPACE,1,FALSE);
#elif defined S_UNIX || defined S_VMS
            waddch(stdscr,_BACKSPACE);
            waddch(stdscr, ' ');
            waddch(stdscr,_BACKSPACE);
            wrefresh(stdscr);
#elif defined S_WNT
            szOutChar[0] = _BACKSPACE;
            WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
            WriteFile(hStdOut, " ", 1, &dummy, NULL);
            WriteFile(hStdOut, szOutChar, 1, &dummy, NULL);
#elif defined S_BOOT
            SCRNPutChar((CHAR)_BACKSPACE);
            SCRNPutChar((CHAR)' ');
            SCRNPutChar((CHAR)_BACKSPACE);
#else
   #error "Kein Zielsystem definiert"
#endif
            }
         usPosition   = 0;
         usCurrentLen = usFieldLen;
         bHex = FALSE;
         }
      else                        /* Eingabe gueltig */
         bInputOK = TRUE;
      }
   return(ulResult);
}
