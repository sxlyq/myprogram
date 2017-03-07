#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();
	virtual ~CPage2();

// Dialog Data
	enum { IDD = IDD_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	CString bloodType;
	COleDateTime dateOfBirth;
	int originIndex;
	CString origin;
	CComboBox originCtrl;
	virtual BOOL OnKillActive();
};
