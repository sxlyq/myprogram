
// LayerView.h : interface of the CLayerView class
//

#pragma once

#include "Ls.h"

class CLayerView : public CView
{
private:
	int m_nSelect;
	CArray<CLs*> m_pLayers;
	CPoint pStartDrag;
protected: // create from serialization only
	CLayerView();
	DECLARE_DYNCREATE(CLayerView)

// Attributes
public:
	CLayerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLayerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawDrag();
	afx_msg void OnDrawEllip();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPenc();
	afx_msg void OnUpdateDrawDrag(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllip(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawPenc(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnColor();
	afx_msg void OnFillcolor();
};

#ifndef _DEBUG  // debug version in LayerView.cpp
inline CLayerDoc* CLayerView::GetDocument() const
   { return reinterpret_cast<CLayerDoc*>(m_pDocument); }
#endif

