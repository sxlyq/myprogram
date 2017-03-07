#include "stdafx.h"
#include "Ellip.h"


CEllip::CEllip(void)
{
	rect.bottom=-1;
	rect.right=-1;
}


CEllip::~CEllip(void)
{
}

void CEllip::OnDraw(CDC* dc){
	CPen* prevPen;
	CBrush* prevBrush;
	CPen pen(PS_SOLID,1,frameColor);
	CBrush brush(fillColor);
	prevPen=dc->SelectObject(&pen);
	prevBrush=dc->SelectObject(&brush);
	dc->Ellipse(rect);
	dc->SelectObject(prevPen);
	dc->SelectObject(prevBrush);
	if(state==STATE_SELECTED){
		dc->FillSolidRect(rect.CenterPoint().x-5,rect.top-5,10,10,RGB(255,255,0));
		dc->FillSolidRect(rect.right-5,rect.CenterPoint().y-5,10,10,RGB(255,255,0));
		dc->FillSolidRect(rect.left-5,rect.CenterPoint().y-5,10,10,RGB(255,255,0));
		dc->FillSolidRect(rect.CenterPoint().x-5,rect.bottom-5,10,10,RGB(255,255,0));
	}
}

void CEllip::OnLButtonDown(UINT nFlags, CPoint point){
	rect.TopLeft()=point;   //TopLeft()返回值是引用，所以可以作为左值
	topLeft=point;
}

void CEllip::OnLButtonUp(UINT nFlags, CPoint point){
	rect.BottomRight()=point;
	rect.NormalizeRect();   //为了解决椭圆从右往左画，从下往上画的问题
}

void CEllip::OnMouseMove(UINT nFlags, CPoint point, CDC* dc){
	if(!dc)
		return;
	if(nFlags&MK_LBUTTON){
		dc->SelectStockObject(NULL_BRUSH);
		dc->SetROP2(R2_NOT);
		if(rect.right>-1){
			dc->Ellipse(rect);
		}
		rect.TopLeft()=topLeft;
		rect.BottomRight()=point;
		rect.NormalizeRect();
		dc->Ellipse(rect);
	}
}

BOOL CEllip::Track(CPoint point){
	if(rect.PtInRect(point)){
		return TRUE;
	}
	return FALSE;
}

void CEllip::Offset(int x,int y){
	rect.OffsetRect(x,y);
}