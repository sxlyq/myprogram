
// MFCApplication10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication10.h"
#include "MFCApplication10Dlg.h"
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


// CMFCApplication10Dlg dialog



CMFCApplication10Dlg::CMFCApplication10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCApplication10Dlg message handlers

BOOL CMFCApplication10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	nSelect=0;
	int i=0;
	CBitmap bmp;
	while(i<COUNT){
		bmp.DeleteObject();
		bmp.LoadBitmapW(i+IDB_BITMAP1);
		mdc[i].CreateCompatibleDC(NULL);
		mdc[i].SelectObject(bmp);
		i++;
	}
	BITMAP bm;
	bmp.GetBitmap(&bm);
	m_size.x=bm.bmWidth;
	m_size.y=bm.bmHeight;
	
	pos[0]=CPoint(m_size.x/2-45,m_size.y-30);
	pos[1]=CPoint(m_size.x/2-15,m_size.y-30);
	pos[2]=CPoint(m_size.x/2+15,m_size.y-30);
	pos[3]=CPoint(m_size.x/2+45,m_size.y-30);

	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left,rect.top,bm.bmWidth,bm.bmHeight,FALSE);
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

void CMFCApplication10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication10Dlg::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0,0,m_size.x,m_size.y,&mdc[nSelect],0,0,SRCCOPY);
	CPen pen(PS_NULL,1,RGB(0,0,0));
	dc.SelectObject(pen);
	CBrush br1(RGB(255,255,255));
	CBrush br2(RGB(0,100,255));
	dc.SelectObject(br1);
	int i=0;
	while(i<COUNT){
		if(i!=nSelect){
			dc.Ellipse(pos[i].x-10,pos[i].y-10,pos[i].x+10,pos[i].y+10);
		}
		i++;
	}
	dc.SelectObject(br2);
	dc.Ellipse(pos[nSelect].x-10,pos[nSelect].y-10,pos[nSelect].x+10,pos[nSelect].y+10);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication10Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int i=0;
	while(i<COUNT){
		CRect rect(pos[i].x-10,pos[i].y-10,pos[i].x+10,pos[i].y+10);
		if(rect.PtInRect(point)){
			nSelect=i;
			break;
		}
		i++;
	}
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}