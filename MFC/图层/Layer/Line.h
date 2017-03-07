#pragma once
#include "ls.h"
class CLine :
	public CLs
{
private:
	CPoint m_pStart,m_pEnd;
public:
	CLine(void);
	virtual ~CLine(void);

	virtual void Offset(int x,int y);
	virtual BOOL Track(CPoint point);
	virtual void OnDraw(CDC* dc);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* dc=NULL);
};

