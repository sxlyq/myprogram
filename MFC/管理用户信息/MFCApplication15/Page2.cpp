// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "Page2.h"
#include "afxdialogex.h"


// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2()
	: CPropertyPage(CPage2::IDD)
	, bloodType(_T(""))
	, dateOfBirth(COleDateTime::GetCurrentTime())
	, origin(_T(""))
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_BLOOD_TYPE, bloodType);
	DDX_DateTimeCtrl(pDX, IDC_DATE_OF_BIRTH, dateOfBirth);
	DDX_CBString(pDX, IDC_ORIGIN, origin);
	DDX_Control(pDX, IDC_ORIGIN, originCtrl);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
END_MESSAGE_MAP()


// CPage2 message handlers


BOOL CPage2::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* psheet=(CPropertySheet*)GetParent();
	psheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);
	CComboBox* cm1=(CComboBox*)GetDlgItem(IDC_BLOOD_TYPE);
	cm1->InsertString(0,__T("A"));
	cm1->InsertString(1,__T("B"));
	cm1->InsertString(2,__T("AB"));
	cm1->InsertString(3,__T("O"));
	CComboBox* cm2=(CComboBox*)GetDlgItem(IDC_ORIGIN);
	cm2->InsertString(0,__T("美国"));
	cm2->InsertString(1,__T("英国"));
	cm2->InsertString(2,__T("加拿大"));
	cm2->InsertString(3,__T("中国"));
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}


BOOL CPage2::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class
	originIndex=originCtrl.GetCurSel();
	return CPropertyPage::OnKillActive();
}
