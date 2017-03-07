
// MFCApplication13Dlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CMFCApplication13Dlg dialog
class CMFCApplication13Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication13Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCAPPLICATION13_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	long lines;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString inputStr;
	CRichEditCtrl richEditCtrl;
};
