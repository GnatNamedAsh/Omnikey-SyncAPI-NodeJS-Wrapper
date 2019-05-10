/**
•
•@file	    :
•@brief     :	  *
•<Long description> * ?

•$Id$ *
•@date      : Oct 31, 2011
•@version :2.0.0.0
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/

#ifndef _INC_OKOS
#define _INC_OKOS


/* Disabling warnings allows usage of WIN32 <windows.h> at warning level 4   */

#if defined _MSC_VER
   /* remove defined S_BOOT because MSC6.00 doesn't support #pragma warning  */
   #if defined S_MSDOS || defined S_WIN
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm. */
      #pragma warning (disable: 4057) /*indirection to slightly diff. types  */
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
      #pragma warning (disable: 4209) /*non.ex. benign typedef redefinition  */
      #pragma warning (disable: 4505) /*unreferenced functions removed       */
      #pragma warning (disable: 4699) /*Precompiled Headers ...              */
   #elif defined S_VXD || defined S_WNT || defined S_KNT
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm. */
      #pragma warning (disable: 4057) /*'uns. char *' differs in indirection */
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
      #pragma warning (disable: 4115) /*named type definition in parentheses */
      #pragma warning (disable: 4200) /*non.ex. zero-sized array in str/union*/
      #pragma warning (disable: 4201) /*non.ex. nameless struct/union        */
      #pragma warning (disable: 4209) /*non.ex. benign typedef redefinition  */
      #pragma warning (disable: 4214) /*non.ex. bit field types other th. int*/
      #pragma warning (disable: 4514) /*unreferenced inline function removed */
   #endif
#endif /* _MSC_VER */

#if defined S_VXD
   /* standard definitions moved from CFLAGS to reduce CL command line length     */
   #define _X86_
   #define WANTVXDWRAPS
   #define VTOOLSD
   #define IS_32
   #if defined OKDEBUG
      #define DEBUG
   #endif
   #if defined WFW311 && !defined WIN31
      #define WIN31
   #endif
   /* Disabling warnings allows usage of <vtoolsc.h> at warning level 4           */
   #pragma warning (disable: 4032) /*formal parameter 1 has different type when...*/
   #pragma warning (disable: 4229) /*anachronism used: modifiers on data ignored  */
#endif

#endif /* _INC_OKOS */
