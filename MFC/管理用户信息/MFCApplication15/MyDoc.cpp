// MyDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication15.h"
#include "MyDoc.h"


// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

CMyDoc::CMyDoc()
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMyDoc::~CMyDoc()
{
}


BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()


// CMyDoc diagnostics

#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CMyDoc serialization

void CMyDoc::Serialize(CArchive& ar)
{
	AfxGetMainWnd()->Serialize(ar);
}
#endif


// CMyDoc commands
