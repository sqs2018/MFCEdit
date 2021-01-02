
// MyEditView.h : interface of the CMyEditView class
//

#pragma once


class CMyEditView : public CEditView
{
protected: // create from serialization only
	CMyEditView();
	DECLARE_DYNCREATE(CMyEditView)

// Attributes
public:
	CMyEditDoc* GetDocument() const;
	void saveToFile(CString szPath);
// Operations
public:
	void changeTitle(bool showX);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMyEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChange();
};

#ifndef _DEBUG  // debug version in MyEditView.cpp
inline CMyEditDoc* CMyEditView::GetDocument() const
   { return reinterpret_cast<CMyEditDoc*>(m_pDocument); }
#endif

