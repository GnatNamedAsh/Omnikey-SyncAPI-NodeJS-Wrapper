// ReadMemory.h : main header file for the READMEMORY application
//


//#define _CRT_SECURE_NO_WARNINGS_




#if !defined(AFX_READMEMORY_H__4E4A6A29_50FC_49D7_94B0_8D873994F2CA__INCLUDED_)
#define AFX_READMEMORY_H__4E4A6A29_50FC_49D7_94B0_8D873994F2CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReadMemoryApp:
// See ReadMemory.cpp for the implementation of this class
//

class CReadMemoryApp : public CWinApp
{
public:
	CReadMemoryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadMemoryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReadMemoryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READMEMORY_H__4E4A6A29_50FC_49D7_94B0_8D873994F2CA__INCLUDED_)
