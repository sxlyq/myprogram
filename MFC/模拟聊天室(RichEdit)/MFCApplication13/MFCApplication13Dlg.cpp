
// MFCApplication13Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication13.h"
#include "MFCApplication13Dlg.h"
#include "afxdialogex.h"

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


// CMFCApplication13Dlg dialog



CMFCApplication13Dlg::CMFCApplication13Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication13Dlg::IDD, pParent)
	, inputStr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication13Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, inputStr);
	DDX_Control(pDX, IDC_RICHEDIT21, richEditCtrl);
}

BEGIN_MESSAGE_MAP(CMFCApplication13Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication13Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication13Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplication13Dlg message handlers

BOOL CMFCApplication13Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CHARFORMAT2W cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2W));  //有时如果不调用ZeroMemory对CHARFORMAT进行清空的话，会导致一些设置无法生效的
	cf.cbSize=sizeof(CHARFORMAT2W);
	cf.dwMask=CFM_COLOR|CFM_FACE|CFM_SIZE;
	cf.crTextColor=RGB(0,255,0);
	cf.yHeight=250;
	StrCpyW(cf.szFaceName,__T("隶书"));

	richEditCtrl.SetDefaultCharFormat(cf);
	richEditCtrl.SetWindowTextW(__T("【系统】欢迎进入MFC聊天室\n"));
	lines=1;
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

void CMFCApplication13Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication13Dlg::OnPaint()
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
HCURSOR CMFCApplication13Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCApplication13Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int nBegin=richEditCtrl.LineIndex(lines);  //lines==1时，修改第二行内容
	richEditCtrl.SetSel(nBegin,-1);   // zero-based index
	CTime now=CTime::GetCurrentTime();
	CString str=now.Format("%Y-%m-%d %H::%M::%S");
	richEditCtrl.ReplaceSel(str+__T("\r\n"));
	int nEnd=nBegin+richEditCtrl.LineLength(lines)*2;
	richEditCtrl.SetSel(nBegin,nEnd);
	CHARFORMAT2W cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2W));
	cf.cbSize=sizeof(cf);
	cf.dwMask=CFM_COLOR|CFM_FACE|CFM_SIZE;
	cf.crTextColor=RGB(255,0,0);
	cf.yHeight=250;
	StrCpyW(cf.szFaceName,__T("宋体"));
	richEditCtrl.SetSelectionCharFormat(cf);
	
	lines++;

	nBegin=richEditCtrl.LineIndex(lines);
	richEditCtrl.SetSel(nBegin,-1); 
	UpdateData(TRUE);
	richEditCtrl.ReplaceSel(inputStr+__T("\r\n"));
	nEnd=nBegin+richEditCtrl.LineLength(lines)*2;
	int len3=richEditCtrl.GetWindowTextLengthW();
	richEditCtrl.SetSel(nBegin,nEnd);
	cf.crTextColor=RGB(255,255,0);
	richEditCtrl.SetSelectionCharFormat(cf);
	/*
	PARAFORMAT2 parafm;
	parafm.cbSize=sizeof(PARAFORMAT2);
	parafm.dwMask=PFM_ALIGNMENT;
	parafm.wAlignment = PFA_CENTER;
	richEditCtrl.SetParaFormat(parafm);
	*/
	richEditCtrl.SetSel(-1,-1);  //不选任何内容
	lines++;
}


void CMFCApplication13Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
