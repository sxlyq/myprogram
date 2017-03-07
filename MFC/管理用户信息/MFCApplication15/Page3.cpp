// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "Page3.h"
#include "afxdialogex.h"


// CPage3 dialog

IMPLEMENT_DYNAMIC(CPage3, CPropertyPage)

CPage3::CPage3()
	: CPropertyPage(CPage3::IDD)
	, address(_T(""))
	, email(_T(""))
	, phoneNumber(_T(""))
{

}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDRESS, address);
	DDX_Text(pDX, IDC_EMAIL, email);
	DDX_Text(pDX, IDC_PHONE_NUM, phoneNumber);
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
END_MESSAGE_MAP()


// CPage3 message handlers


BOOL CPage3::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* psheet=(CPropertySheet*)GetParent();
	psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_FINISH);
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}


BOOL CPage3::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	return CPropertyPage::OnWizardFinish();
}
