
// MyEditView.cpp : implementation of the CMyEditView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyEdit.h"
#endif

#include "MyEditDoc.h"
#include "MyEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyEditView

IMPLEMENT_DYNCREATE(CMyEditView, CEditView)

BEGIN_MESSAGE_MAP(CMyEditView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_CONTROL_REFLECT(EN_CHANGE, &CMyEditView::OnEnChange)
END_MESSAGE_MAP()

// CMyEditView construction/destruction

CMyEditView::CMyEditView()
{
	// TODO: add construction code here

}

CMyEditView::~CMyEditView()
{
}

BOOL CMyEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CMyEditView printing

BOOL CMyEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMyEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMyEditView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CMyEditView diagnostics

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyEditDoc* CMyEditView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyEditDoc)));
	return (CMyEditDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyEditView message handlers


void CMyEditView::OnEnChange()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEditView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	changeTitle(true);



}
void CMyEditView::saveToFile(CString szPath){
	
	changeTitle(false);
}

//修改标题
void CMyEditView::changeTitle(bool showX){
	WCHAR titleC[MAX_PATH];

	int length=GetParentFrame()->GetWindowText(titleC,100);

	bool hasX=false;
	for(int i=0;i<length;i++){
		if(titleC[i]=='*'){
			hasX=true;
			break;
		}
	}
	if(showX&&!hasX){
		titleC[length]='-';
		titleC[length+1]='*';
		titleC[length+2]='\0';
	}
	//如果有星，且不显示* 则把*去掉
	if(!showX&&hasX){
		titleC[length-2]='\0';
	}
	GetParentFrame()->SetWindowText(titleC);
}
