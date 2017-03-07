#pragma once
#include "ls.h"
class CEllip :
	public CLs
{
private:
	CRect rect;
	CPoint topLeft;
public:
	CEllip(void);
	virtual ~CEllip(void);

	virtual void Offset(int x,int y);
	virtual BOOL Track(CPoint point);
	virtual void OnDraw(CDC* dc);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* dc=NULL);
};

