#pragma once
#include "afxwin.h"
#include "MyEditDoc.h"
class MyPView :
	public CView
{
protected:
	MyPView();
	DECLARE_DYNCREATE(MyPView)


	
// Attributes
public:
	~MyPView();
	CMyEditDoc* GetDocument() const;
	//设置标题
	void changeTitle(bool showX);
	//保存结构到文件
	void saveToFile(CString szPath);
	void loadFile(CString loadFile);
	
public:
	
	bool m_leftbtnClick;//鼠标左键是否按下	

	CPtrArray dataArray;//绘制数据集合

protected:
	DECLARE_MESSAGE_MAP()		

// Operations
public:
	
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);




#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
public:

	afx_msg void OnSet();
	afx_msg void OnLine();
	afx_msg void OnEclipse();
	afx_msg void OnSector();
	afx_msg void OnRectangle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

