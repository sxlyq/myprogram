
// MFCApplication17.h : main header file for the MFCApplication17 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplication17App:
// See MFCApplication17.cpp for the implementation of this class
//

class CMFCApplication17App : public CWinApp
{
public:
	CMFCApplication17App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
public:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication17App theApp;
