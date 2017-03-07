
// MFCApplication15Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "MFCApplication15Dlg.h"
#include "afxdialogex.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication15Dlg dialog



CMFCApplication15Dlg::CMFCApplication15Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication15Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication15Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFCApplication15Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMFCApplication15Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CMFCApplication15Dlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CMFCApplication15Dlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_SAVE, &CMFCApplication15Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_OPEN, &CMFCApplication15Dlg::OnBnClickedOpen)
END_MESSAGE_MAP()


// CMFCApplication15Dlg message handlers

BOOL CMFCApplication15Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0,__T("账号"),0,80);
	m_list.InsertColumn(1,__T("昵称"),0,80);
	m_list.InsertColumn(2,__T("性别"),0,50);
	m_list.InsertColumn(3,__T("生日"),0,80);
	m_list.InsertColumn(4,__T("血型"),0,80);
	m_list.InsertColumn(5,__T("国籍"),0,80);
	m_list.InsertColumn(6,__T("电话"),0,80);
	m_list.InsertColumn(7,__T("Email"),0,80);
	m_list.InsertColumn(8,__T("地址"),0,80);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	imgls.Create(23,17,ILC_COLOR32|ILC_MASK,4,4);
	imgls.Add(AfxGetApp()->LoadIconW(IDI_ICON1));
	imgls.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	imgls.Add(AfxGetApp()->LoadIconW(IDI_ICON3));
	imgls.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	m_list.SetImageList(&imgls,LVSIL_SMALL);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication15Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication15Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication15Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication15Dlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	CPropertySheet sh(__T("用户资料注册"),this);
	CPage1 p1;
	CPage2 p2;
	CPage3 p3;
	sh.AddPage(&p1);
	sh.AddPage(&p2);
	sh.AddPage(&p3);
	sh.SetWizardMode();
	if(IDCANCEL==sh.DoModal())
		return;
	int i=m_list.GetItemCount();
	m_list.InsertItem(i,p1.account,p2.originIndex);
	m_list.SetItemText(i,1,p1.nickname);
	m_list.SetItemText(i,2,p1.gender?__T("女"):__T("男"));
	m_list.SetItemText(i,3,p2.dateOfBirth.Format(__T("%Y-%m-%d")));
	m_list.SetItemText(i,4,p2.bloodType);
	m_list.SetItemText(i,5,p2.origin);
	m_list.SetItemText(i,6,p3.phoneNumber);
	m_list.SetItemText(i,7,p3.email);
	m_list.SetItemText(i,8,p3.address);
}


void CMFCApplication15Dlg::OnBnClickedButtonMod()
{
	// TODO: Add your control notification handler code here
	int i=m_list.GetSelectionMark();
	if(i==-1){
		AfxMessageBox(__T("请先选择要修改的一行"));
		return;
	}
	CPropertySheet sh(__T("修改用户信息"),this);
	CPage1 p1;
	CPage2 p2;
	CPage3 p3;
	sh.AddPage(&p1);
	sh.AddPage(&p2);
	sh.AddPage(&p3);
	p1.account=m_list.GetItemText(i,0);
	p1.nickname=m_list.GetItemText(i,1);
	p1.gender=m_list.GetItemText(i,2)==__T("男")?0:1;
	int year,month,day;
	CString str=m_list.GetItemText(i,3);
	USES_CONVERSION;
	char* pstr=T2A(str.GetBuffer());   //CString 转为 char*，在前面加个宏定义，USES_CONVERSION;然后用宏转换T2A。
	sscanf_s(pstr,"%d-%d-%d",&year,&month,&day);
	COleDateTime date(year,month,day,0,0,0);
	p2.dateOfBirth=date;
	p2.bloodType=m_list.GetItemText(i,4);
	p2.origin=m_list.GetItemText(i,5);
	p3.phoneNumber=m_list.GetItemText(i,6);
	p3.email=m_list.GetItemText(i,7);
	p3.address=m_list.GetItemText(i,8);
	if(IDCANCEL==sh.DoModal())
		return;
	LVITEM lt;
	lt.mask=LVIF_IMAGE;
	lt.iItem=i;
	lt.iImage=p2.originIndex;
	m_list.SetItem(&lt);
	m_list.SetItemText(i,0,p1.account);
	m_list.SetItemText(i,1,p1.nickname);
	m_list.SetItemText(i,2,p1.gender?__T("女"):__T("男"));
	m_list.SetItemText(i,3,p2.dateOfBirth.Format(__T("%Y-%m-%d")));
	m_list.SetItemText(i,4,p2.bloodType);
	m_list.SetItemText(i,5,p2.origin);
	m_list.SetItemText(i,6,p3.phoneNumber);
	m_list.SetItemText(i,7,p3.email);
	m_list.SetItemText(i,8,p3.address);
}


void CMFCApplication15Dlg::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	int i=m_list.GetSelectionMark();
	if(i==-1){
		AfxMessageBox(__T("请先选择要删除的一行"));
		return;
	}
	m_list.DeleteItem(i);
}

void CMFCApplication15Dlg::OnBnClickedSave()
{
	LPCWSTR filter=__T("文本文档(*.ff)|*.ff||");
	CFileDialog fd(FALSE,__T("*.ff"),NULL,OFN_OVERWRITEPROMPT,filter);
	if(IDCANCEL==fd.DoModal())
		return;
	CString filePath=fd.GetPathName();

	m_doc.OnSaveDocument(filePath);
}


void CMFCApplication15Dlg::OnBnClickedOpen()
{
	LPCWSTR filter=__T("文本文档(*.ff)|*.ff||");
	CFileDialog fd(TRUE,__T("*.ff"),NULL,OFN_READONLY,filter);
	if(IDCANCEL==fd.DoModal())
		return;
	CString filePath=fd.GetPathName();

	m_doc.OnOpenDocument(filePath);
}


void CMFCApplication15Dlg::Serialize(CArchive& ar)
{
	int count;
	if(ar.IsStoring()){
		count=m_list.GetItemCount();
		ar<<count;
		for(int i=0;i<count;i++){
			ar<<m_list.GetItemText(i,0);
			ar<<m_list.GetItemText(i,1);
			ar<<m_list.GetItemText(i,2);
			ar<<m_list.GetItemText(i,3);
			ar<<m_list.GetItemText(i,4);
			ar<<m_list.GetItemText(i,5);
			ar<<m_list.GetItemText(i,6);
			ar<<m_list.GetItemText(i,7);
			ar<<m_list.GetItemText(i,8);
		}
	}else{
		m_list.DeleteAllItems();
		int count;
		ar>>count;
		CString str;
		for(int i=0;i<count;i++){
			ar>>str;
			m_list.InsertItem(i,str);
			ar>>str;
			m_list.SetItemText(i,1,str);
			ar>>str;
			m_list.SetItemText(i,2,str);
			ar>>str;
			m_list.SetItemText(i,3,str);
			ar>>str;
			m_list.SetItemText(i,4,str);
			ar>>str;
			m_list.SetItemText(i,5,str);
			LVITEM lt;
			lt.mask=LVIF_IMAGE;
			lt.iItem=i;
			if(str==__T("美国")){
				lt.iImage=0;
			}
			if(str==__T("英国")){
				lt.iImage=1;
			}
			if(str==__T("加拿大")){
				lt.iImage=2;
			}
			if(str==__T("中国")){
				lt.iImage=3;
			}
			m_list.SetItem(&lt);
			ar>>str;
			m_list.SetItemText(i,6,str);
			ar>>str;
			m_list.SetItemText(i,7,str);
			ar>>str;
			m_list.SetItemText(i,8,str);
		}
	}
}
