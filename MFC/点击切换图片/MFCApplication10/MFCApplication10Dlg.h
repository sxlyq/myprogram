
// MFCApplication10Dlg.h : header file
//

#pragma once


// CMFCApplication10Dlg dialog
class CMFCApplication10Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication10Dlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION10_DIALOG };
	enum {COUNT=4};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int nSelect;
	CDC mdc[COUNT];
	CPoint m_size;
	CPoint pos[COUNT];
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
