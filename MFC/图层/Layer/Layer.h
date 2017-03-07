
// Layer.h : main header file for the Layer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLayerApp:
// See Layer.cpp for the implementation of this class
//

class CLayerApp : public CWinApp
{
public:
	CLayerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLayerApp theApp;
