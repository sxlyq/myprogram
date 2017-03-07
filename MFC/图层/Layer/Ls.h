#pragma once
class CLs
{
protected:
	enum{STATE_NORMAL,STATE_SELECTED};
	int state;
	COLORREF frameColor,fillColor;
public:
	void SetStateSelected();
	void SetStateNormal();
	BOOL IsSelected();
	void SetFrameColor(COLORREF color);
	void SetFillColor(COLORREF color);
	COLORREF GetFrameColor();
	COLORREF GetFillColor();
	virtual void Offset(int x,int y)=0;
	virtual BOOL Track(CPoint point)=0;
	virtual void OnDraw(CDC* dc)=0;
	virtual void OnLButtonDown(UINT nFlags, CPoint point)=0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point)=0;
	virtual void OnMouseMove(UINT nFlags, CPoint point, CDC* dc)=0;
	CLs(void);
	virtual ~CLs(void);
};

