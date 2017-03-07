
// LayerView.cpp : implementation of the CLayerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Layer.h"
#endif

#include "LayerDoc.h"
#include "LayerView.h"
#include "Line.h"
#include "Penc.h"
#include "Ellip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLayerView

IMPLEMENT_DYNCREATE(CLayerView, CView)

BEGIN_MESSAGE_MAP(CLayerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_DRAG, &CLayerView::OnDrawDrag)
	ON_COMMAND(ID_DRAW_ELLIP, &CLayerView::OnDrawEllip)
	ON_COMMAND(ID_DRAW_LINE, &CLayerView::OnDrawLine)
	ON_COMMAND(ID_DRAW_PENC, &CLayerView::OnDrawPenc)
	ON_UPDATE_COMMAND_UI(ID_DRAW_DRAG, &CLayerView::OnUpdateDrawDrag)
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIP, &CLayerView::OnUpdateDrawEllip)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CLayerView::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PENC, &CLayerView::OnUpdateDrawPenc)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COLOR, &CLayerView::OnColor)
	ON_COMMAND(ID_FILLCOLOR, &CLayerView::OnFillcolor)
END_MESSAGE_MAP()

// CLayerView construction/destruction

CLayerView::CLayerView()
{
	// TODO: add construction code here

}

CLayerView::~CLayerView()
{
}

BOOL CLayerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLayerView drawing

void CLayerView::OnDraw(CDC* pDC)
{
	CLayerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int i=0;
	int size=m_pLayers.GetSize();
	CLs* pLayer=NULL;
	while(i<size){
		pLayer=m_pLayers[i];
		pLayer->OnDraw(pDC);
		i++;
	}

	// TODO: add draw code for native data here
}


// CLayerView printing

BOOL CLayerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLayerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLayerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLayerView diagnostics

#ifdef _DEBUG
void CLayerView::AssertValid() const
{
	CView::AssertValid();
}

void CLayerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLayerDoc* CLayerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLayerDoc)));
	return (CLayerDoc*)m_pDocument;
}
#endif //_DEBUG


// CLayerView message handlers


void CLayerView::OnDrawDrag()
{
	// TODO: Add your command handler code here
	m_nSelect=ID_DRAW_DRAG;
}


void CLayerView::OnDrawEllip()
{
	// TODO: Add your command handler code here
	m_nSelect=ID_DRAW_ELLIP;
}


void CLayerView::OnDrawLine()
{
	// TODO: Add your command handler code here
	m_nSelect=ID_DRAW_LINE;
}


void CLayerView::OnDrawPenc()
{
	// TODO: Add your command handler code here
	m_nSelect=ID_DRAW_PENC;
}


void CLayerView::OnUpdateDrawDrag(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ID_DRAW_DRAG==m_nSelect){
		pCmdUI->SetRadio(TRUE);
	}else{
		pCmdUI->SetRadio(FALSE);
	}
}


void CLayerView::OnUpdateDrawEllip(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ID_DRAW_ELLIP==m_nSelect){
		pCmdUI->SetRadio(TRUE);
	}else{
		pCmdUI->SetRadio(FALSE);
	}
}


void CLayerView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(ID_DRAW_LINE==m_nSelect);
}


void CLayerView::OnUpdateDrawPenc(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->Enable(FALSE);
	pCmdUI->SetRadio(ID_DRAW_PENC==m_nSelect);
}


void CLayerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_nSelect==ID_DRAW_DRAG){
		int size=m_pLayers.GetSize();
		if(!size){
			return;
		}
		CLs* pl=NULL;
		for(int i=0;i<size;i++){
			pl=m_pLayers[i];
			if(pl->Track(point)){
				pl->SetStateSelected();
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			}else{
				pl->SetStateNormal();
			}
		}
		pStartDrag=point;
		Invalidate(TRUE);
		return;
	}else{
		CLs* pLayer=NULL;
		switch(m_nSelect){
		case ID_DRAW_LINE:
			pLayer = new CLine();
			break;
		case ID_DRAW_PENC:
			pLayer = new CPenc();
			break;
		case ID_DRAW_ELLIP:
			pLayer = new CEllip();
			break;
		}
		if(pLayer){
			m_pLayers.Add(pLayer);
			pLayer->OnLButtonDown(nFlags,point);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CLayerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_nSelect==ID_DRAW_DRAG){
		int size=m_pLayers.GetSize();
		for(int i=0;i<size;i++){
			if(m_pLayers[i]->IsSelected()){
				m_pLayers[i]->Offset(point.x-pStartDrag.x,point.y-pStartDrag.y);
			}
		}
		Invalidate(TRUE);
		return;
	}
	int size=m_pLayers.GetSize();
	if(!size)
		return;
	CLs* pLayer=m_pLayers[size-1];
	pLayer->OnLButtonUp(nFlags,point);
	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}


void CLayerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(ID_DRAW_DRAG==m_nSelect){

		return;
	}
	CClientDC dc(this);
	int size=m_pLayers.GetSize();
	if(!size)
		return;
	CLs* pLayer=m_pLayers[size-1];
	pLayer->OnMouseMove(nFlags,point,&dc);
	CView::OnMouseMove(nFlags, point);
}


void CLayerView::OnColor()
{
	// TODO: Add your command handler code here
	CColorDialog clDialog;
	if(IDCANCEL==clDialog.DoModal()){
		return;
	}
	int size=m_pLayers.GetSize();
	CLs* pLayer=NULL;
	for(int i=0;i<size;i++){
		pLayer=m_pLayers[i];
		if(pLayer->IsSelected()){
			pLayer->SetFrameColor(clDialog.GetColor());
		}
	}
	Invalidate(TRUE);
}


void CLayerView::OnFillcolor()
{
	// TODO: Add your command handler code here
	CColorDialog clDialog;
	if(IDCANCEL==clDialog.DoModal()){
		return;
	}
	int size=m_pLayers.GetSize();
	CLs* pLayer=NULL;
	for(int i=0;i<size;i++){
		pLayer=m_pLayers[i];
		if(pLayer->IsSelected()){
			pLayer->SetFillColor(clDialog.GetColor());
		}
	}
	Invalidate(TRUE);
}
