// BrowView.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication17.h"
#include "BrowView.h"


// CBrowView

IMPLEMENT_DYNCREATE(CBrowView, CHtmlView)

CBrowView::CBrowView()
{

}

CBrowView::~CBrowView()
{
}

void CBrowView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBrowView, CHtmlView)
END_MESSAGE_MAP()


// CBrowView diagnostics

#ifdef _DEBUG
void CBrowView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBrowView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CBrowView message handlers


void CBrowView::OnInitialUpdate()
{
	Navigate2(__T("about:blank"),NULL,NULL);
}
