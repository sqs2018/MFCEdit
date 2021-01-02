
// MyEdit.h : main header file for the MyEdit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyEditApp:
// See MyEdit.cpp for the implementation of this class
//

class CMyEditApp : public CWinApp
{
public:
	CMyEditApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void  OnFileNew();
	virtual void OnFileNewP();
	virtual void OnFileOpen();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyEditApp theApp;
