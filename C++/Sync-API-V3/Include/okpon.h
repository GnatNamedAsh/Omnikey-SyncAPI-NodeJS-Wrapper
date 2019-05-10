/**
•
•@file	    okpon.h
•@brief     :	  *
•<Long description> * ?

•$Id$ *
•@date      : Oct 31, 2011
•@version :2.0.0.0
•@author $Author$
•
•Copyright (c) 2000 - 2011 HID Global Corp.
**********************************************************************/

#if defined _MSC_VER
   #if !(defined S_KOS2_16) && !(defined S_BOOT)
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
   #endif

   #if defined S_MSDOS || defined S_BOOT || defined S_WIN
      #pragma pack(2)
   #elif defined S_VXD || defined S_WNT || defined S_KNT
      #pragma pack(8)
   #elif defined S_KOS2_16
      #pragma pack(4)
   #endif
#endif /* _MSC_VER */

/* OS2 */
#ifdef __OS2__
   #pragma pack(4)
#endif

