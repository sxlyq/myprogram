#include "stdafx.h"
#include "Line.h"
#include <math.h>

CLine::CLine(void)
{
	m_pEnd.x=-1;
	m_pEnd.y=-1;
}


CLine::~CLine(void)
{
}

void CLine::OnDraw(CDC* dc){
	if(state==STATE_SELECTED){
		dc->FillSolidRect(m_pStart.x-5,m_pStart.y-5,10,10,RGB(255,255,0));
		dc->FillSolidRect(m_pEnd.x-5,m_pEnd.y-5,10,10,RGB(255,255,0));
	}
	CPen* prevPen;
	CPen pen(PS_SOLID,1,frameColor);
	prevPen=dc->SelectObject(&pen);
	dc->MoveTo(m_pStart);
	dc->LineTo(m_pEnd);
	dc->SelectObject(prevPen);
}

void CLine::OnLButtonDown(UINT nFlags, CPoint point){
	m_pStart=point;
}

void CLine::OnLButtonUp(UINT nFlags, CPoint point){
	m_pEnd=point;
}

void CLine::OnMouseMove(UINT nFlags, CPoint point, CDC* dc){
	if(!dc)
		return;
	if(nFlags&MK_LBUTTON){
		dc->SetROP2(R2_NOT);
		if(m_pEnd.x>-1){
			dc->MoveTo(m_pStart);
			dc->LineTo(m_pEnd);
		}
		dc->MoveTo(m_pStart);
		dc->LineTo(point);
		m_pEnd=point;
	}
}

BOOL CLine::Track(CPoint point){
	if(m_pStart.y==m_pEnd.y){
		if(abs(point.y-m_pStart.y)<3){
			if((point.x-m_pStart.x)*(point.x-m_pEnd.x)<0){
				return TRUE;
			}else{
				return FALSE;
			}
		}else{
			return FALSE;
		}
	}
	if(m_pStart.x==m_pEnd.x){
		if(abs(point.x-m_pStart.x)<3){
			if((point.y-m_pStart.y)*(point.y-m_pEnd.y)<0){
				return TRUE;
			}else{
				return FALSE;
			}
		}else{
			return FALSE;
		}
	}
	int ratio1=(m_pStart.x-m_pEnd.x)/(m_pStart.y-m_pEnd.y);
	int ratio2=(m_pStart.x-point.x)/(m_pStart.y-point.y);
	if(ratio1==ratio2){
		return TRUE;
	}else{
		if(ratio1>10){
			if(ratio1>ratio2){
				if(ratio1-ratio2<ratio1*0.1){
					return TRUE;
				}else{
					return FALSE;
				}
			}else{
				if(ratio2-ratio1<ratio1*0.1){
					return TRUE;
				}else{
					return FALSE;
				}
			}
		}else{
			return FALSE;
		}
	}
	return FALSE;
}

void CLine::Offset(int x,int y){
	m_pStart.Offset(x,y);
	m_pEnd.Offset(x,y);
}