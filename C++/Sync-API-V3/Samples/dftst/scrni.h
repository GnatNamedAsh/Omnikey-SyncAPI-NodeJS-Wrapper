/**
•
•@file scrni.h
•@brief     :	  

•$Id$ *
•@date      : Oct 31, 2011
•@version 
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/

#ifndef _INC_SCRNI
#define _INC_SCRNI

#ifdef VMS
   #ifndef S_VMS
      #define S_VMS
   #endif
#endif

/****************************************************************************/
/* Wichtige Konstanten                                                      */
/****************************************************************************/
/* @consts SCRN Cancel keys | Cancel keys defined in VMS and other systems
*/

#ifdef S_VMS
#define _CANCEL_KEY      ' '         /*@cnst _CANCEL_KEY | ' ' | Key for
canceling text input under VMS systems (blank)*/
#else
#define _CANCEL_KEY      _ESC        /*@cnst _CANCEL_KEY | _ESC | Key for
canceling text input under other systems (escape)*/
#endif

#if defined S_BOOT
   #define toupper(a)   (((a)>='a' && (a)<='z') ? ((a)&0xdf) : (a))
   #define isprint(a)   ((a)>=32 && (a)<=126)
   #define isdigit(a)   ((a)>='0' && (a)<= '9')
   #define isxdigit(a)  (isdigit(a) || ((a)>='a' && (a)<='f') || \
                         ((a)>='A' && (a)<='F'))
#endif

/***** Typ der einzugebenden Zahl bei SCRNGetNumber *****/

#define TYPE_SHORT         1
#define TYPE_LONG          2

/****************************************************************************/
/* Funktions-Prototypen                                                     */
/****************************************************************************/

#if defined S_WIN || defined S_MSDOS
   VOID SCRNOutText(CHAR chOut, USHORT usPosition, BOOL fHideInput);
#endif

ULONG  ENTRY  SCRNGetUnsigned(ULONG, ULONG, BYTE);

#endif /* _INC_SCRNI */
