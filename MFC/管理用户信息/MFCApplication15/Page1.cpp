// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)

CPage1::CPage1()
	: CPropertyPage(CPage1::IDD)
	, account(_T(""))
	, nickname(_T(""))
	, gender(FALSE)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, account);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, nickname);
	DDX_Radio(pDX, IDC_GENDER, gender);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
END_MESSAGE_MAP()


// CPage1 message handlers


BOOL CPage1::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* psheet=(CPropertySheet*)GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT);
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}
