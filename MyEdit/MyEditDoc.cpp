
// MyEditDoc.cpp : implementation of the CMyEditDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyEdit.h"
#endif

#include "MyEditDoc.h"
#include "afxdatarecovery.h"

#include <propkey.h>
#include "MyPView.h"
#include "Data.h"
#include "MyEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyEditDoc

IMPLEMENT_DYNCREATE(CMyEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyEditDoc, CDocument)
END_MESSAGE_MAP()

extern CMultiDocTemplate* pDocTemplate;//文本
extern CMultiDocTemplate* pDocTemplateP;//绘图
// CMyEditDoc construction/destruction

CMyEditDoc::CMyEditDoc()
{
	// TODO: add one-time construction code here

}

CMyEditDoc::~CMyEditDoc()
{
}

BOOL CMyEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


BOOL CMyEditDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace ){

	CDocTemplate* templateTemp=GetDocTemplate();
	
	//文本
	if(templateTemp==pDocTemplate){
		static WCHAR szFilter[] = _T("文本文件(*.t)"); 
		CFileDialog fd(FALSE,_T("t"),_T("文本"),OFN_OVERWRITEPROMPT,szFilter,NULL,0); 
		//fd.m_ofn.lpstrTitle=_T("保存");
		 if( IDCANCEL == fd.DoModal() ) 
		{ 
			return FALSE; 
		} 

		CString szPath = fd.GetPathName(); 
		OnSaveDocument(szPath); 
		POSITION posDoc = pDocTemplate->GetFirstDocPosition();
		while( posDoc != NULL )
		{
			CDocument* pDoc = pDocTemplate->GetNextDoc( posDoc );
			POSITION posView = pDoc->GetFirstViewPosition();
			while( posView != NULL )
			{
				CMyEditView* pView = (CMyEditView*)pDoc->GetNextView( posView );
				//改变标题状态
				pView->saveToFile(szPath);         
					          
			}
		}
	}
	//绘图
	else{
		static WCHAR szFilter[] = _T("绘图文件(*.p)"); 
		CFileDialog fd(FALSE,_T("p"),_T("绘图"),OFN_OVERWRITEPROMPT,szFilter,NULL,0); 
			//fd.m_ofn.lpstrTitle=_T("保存");
		 if( IDCANCEL == fd.DoModal() ) 
		{ 
			return FALSE; 
		} 

		CString szPath = fd.GetPathName(); 
		//OnSaveDocument(szPath); 
		
			
		POSITION posDoc = pDocTemplateP->GetFirstDocPosition();
		while( posDoc != NULL )
		{
			CDocument* pDoc = pDocTemplateP->GetNextDoc( posDoc );
			POSITION posView = pDoc->GetFirstViewPosition();
			while( posView != NULL )
			{
				MyPView* pView = (MyPView*)pDoc->GetNextView( posView );
				//保存文件
				pView->saveToFile(szPath);         
					          
			}
		}
		


	}

	
   

	return TRUE;
}

// CMyEditDoc serialization

void CMyEditDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != NULL)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMyEditDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMyEditDoc::InitializeSearchContent()
{
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// Use the entire text file content as the search content.
	SetSearchContent(m_strSearchContent);
}

void CMyEditDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyEditDoc diagnostics

#ifdef _DEBUG
void CMyEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


//获取文件后缀
CString GetExtName(CString fileName)
{
    int pos = fileName.Find(_T(".")); //获取 . 的位置
    if (pos == -1){ //如果没有找到，直接返回该字符串
        return fileName;
    }
    else{
        return GetExtName(fileName.Mid(pos + 1)); //找到了的话，往深层遍历，直到最底层
    }
}

// CMyEditDoc commands


BOOL CMyEditDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	#ifdef _DEBUG
	if (IsModified())
		TRACE(traceAppMsg, 0, "Warning: OnOpenDocument replaces an unsaved document.\n");
#endif

	ENSURE(lpszPathName);

	CFileException* pfe = new CFileException;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, pfe);
	if (pFile == NULL)
	{
		TRY
		{
			ReportSaveLoadException(lpszPathName, pfe,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		}
		END_TRY
		
		return FALSE;
	}



	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize
	
	CString fileExt=GetExtName(lpszPathName);
	//如果是.p文件
	if(fileExt==(_T("p"))){

		CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
		loadArchive.m_pDocument = this;
		loadArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			CData data;
			if (pFile->GetLength() != 0){
				Serialize(loadArchive);     // load me
			}
			loadArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);
			DeleteContents();   // remove failed contents

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			}
			END_TRY
		
			return FALSE;
		}
		END_CATCH_ALL

		SetModifiedFlag(FALSE);     // start off with unmodified


	}
	//如果是.t文件
	else if(fileExt==(_T("t"))){

		CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
		loadArchive.m_pDocument = this;
		loadArchive.m_bForceFlat = FALSE;
		TRY
		{
			CWaitCursor wait;
			if (pFile->GetLength() != 0)
				Serialize(loadArchive);     // load me
			loadArchive.Close();
			ReleaseFile(pFile, FALSE);
		}
		CATCH_ALL(e)
		{
			ReleaseFile(pFile, TRUE);
			DeleteContents();   // remove failed contents

			TRY
			{
				ReportSaveLoadException(lpszPathName, e,
					FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			}
			END_TRY
		
			return FALSE;
		}
		END_CATCH_ALL

		SetModifiedFlag(FALSE);     // start off with unmodified




	}else{
		AfxMessageBox(_T("不能读取对应的类型"));
		return FALSE;
	}
	return TRUE;

}
