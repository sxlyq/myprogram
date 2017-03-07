#include "stdafx.h"
#include "Penc.h"


CPenc::CPenc(void)
{
}


CPenc::~CPenc(void)
{
}

void CPenc::OnDraw(CDC* dc){
	int size=m_arr.GetSize();
	if(!size)
		return;
	CPen* prevPen;
	CPen pen(PS_SOLID,1,frameColor);
	prevPen=dc->SelectObject(&pen);
	dc->Polyline(m_arr.GetData(),size);
	dc->SelectObject(prevPen);
	if(state==STATE_SELECTED){
		dc->FillSolidRect(m_arr[0].x-5,m_arr[0].y-5,10,10,RGB(255,255,0));
		dc->FillSolidRect(m_arr[size-1].x-5,m_arr[size-1].y-5,10,10,RGB(255,255,0));
	}
}

void CPenc::OnLButtonDown(UINT nFlags, CPoint point){
	m_arr.Add(point);
}

void CPenc::OnLButtonUp(UINT nFlags, CPoint point){
	m_arr.Add(point);
}

void CPenc::OnMouseMove(UINT nFlags, CPoint point, CDC* dc){
	if(!m_arr.GetSize()){
		return;
	}
	//Add point when left button is down.
	if(nFlags&MK_LBUTTON){   
		//为了节省存储空间，两点之间的距离尽量大于3再添加
		CPoint pt=m_arr[m_arr.GetSize()-1];
		int x=pt.x-point.x;
		int y=pt.y-point.y;
		if(x*x+y*y>=9){
			dc->MoveTo(pt);
			dc->LineTo(point);
			m_arr.Add(point);
		}
	}
}

BOOL CPenc::Track(CPoint point){
	int size=m_arr.GetSize();
	for(int i=0;i<size;i++){
		if((m_arr[i].x-point.x)*(m_arr[i].x-point.x)+(m_arr[i].y-point.y)*(m_arr[i].y-point.y)<20){
			return TRUE;
		}
	}
	return FALSE;
}

void CPenc::Offset(int x,int y){
	int size=m_arr.GetSize();
	for(int i=0;i<size;i++){
		m_arr[i].Offset(x,y);
	}
}