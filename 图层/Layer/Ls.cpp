#include "stdafx.h"
#include "Ls.h"


CLs::CLs(void)
{
	state=STATE_NORMAL;
	frameColor=RGB(0,0,0);
	fillColor=RGB(255,255,255);
}


CLs::~CLs(void)
{
}

void CLs::SetStateSelected(){
	state=STATE_SELECTED;
}
	
void CLs::SetStateNormal(){
	state=STATE_NORMAL;
}

BOOL CLs::IsSelected(){
	if(state==STATE_SELECTED)
		return TRUE;
	else
		return FALSE;
}

void CLs::SetFrameColor(COLORREF color){
	frameColor=color;
}

void CLs::SetFillColor(COLORREF color){
	fillColor=color;
}

COLORREF CLs::GetFrameColor(){
	return frameColor;
}

COLORREF CLs::GetFillColor(){
	return fillColor;
}