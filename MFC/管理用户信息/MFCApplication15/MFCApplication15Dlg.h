
// MFCApplication15Dlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "MyDoc.h"

// CMFCApplication15Dlg dialog
class CMFCApplication15Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication15Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonDel();
	CListCtrl m_list;
private:
	CImageList imgls;  //没有将CImageList设置为窗体成员变量导致CListCtrl不显示图片
	CImageList imgHeader;
	CMyDoc m_doc;
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedOpen();
	virtual void Serialize(CArchive& ar);
};
