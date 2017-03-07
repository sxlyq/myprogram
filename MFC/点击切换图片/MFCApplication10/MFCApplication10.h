
// MFCApplication10.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplication10App:
// See MFCApplication10.cpp for the implementation of this class
//

class CMFCApplication10App : public CWinApp
{
public:
	CMFCApplication10App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication10App theApp;