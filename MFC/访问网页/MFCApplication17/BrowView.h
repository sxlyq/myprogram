#pragma once

#ifdef _WIN32_WCE
#error "CHtmlView is not supported for Windows CE."
#endif 

// CBrowView html view

class CBrowView : public CHtmlView
{
	DECLARE_DYNCREATE(CBrowView)

public:
	CBrowView();           // protected constructor used by dynamic creation
	virtual ~CBrowView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};


