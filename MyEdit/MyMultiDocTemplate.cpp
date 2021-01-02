#include "stdafx.h"
#include "MyMultiDocTemplate.h"


CMyMultiDocTemplate::CMyMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass):CMultiDocTemplate(nIDResource,pDocClass,pFrameClass,pViewClass)
{
}


CMyMultiDocTemplate::Confidence CMyMultiDocTemplate::MatchDocType(LPCTSTR lpszPathName,
					CDocument*& rpDocMatch){
   ASSERT(lpszPathName != NULL);

       rpDocMatch = NULL;

 

       // go through all documents

       POSITION pos = GetFirstDocPosition();

       while (pos != NULL)

       {

              CDocument* pDoc = GetNextDoc(pos);

              if (lstrcmpi(pDoc->GetPathName(), lpszPathName) == 0)//AfxComparePath(pDoc->GetPathName(), lpszPathName))此处由于找不到AfxComparePath所在的头文件，存疑。。。

              {

                     // already open

                     rpDocMatch = pDoc;

                     return yesAlreadyOpen;

              }

       }

 

       // see if it matches our default suffix

       CString strFilterExt=_T(".p");

       if (GetDocString(strFilterExt, CDocTemplate::filterExt) &&

         !strFilterExt.IsEmpty())

       {

              // see if extension matches

              ASSERT(strFilterExt[0] == '.');

              LPCTSTR lpszDot = _tcsrchr(lpszPathName, '.');

              int iStart = 0;

              if(lpszDot != NULL)

              {

                     do

                     {

                            CString strExtention = strFilterExt.Tokenize(_T(";"),iStart);//将扩展名分割

                            if(iStart != -1)

                            {

                                   if(lstrcmpi(lpszDot, strExtention) == 0)

                                          return yesAttemptNative;

                            }

                     }while(iStart != -1);

              }

              //if (lpszDot != NULL && lstrcmpi(lpszDot, strFilterExt) == 0)

              //     return yesAttemptNative; // extension matches, looks like ours

       }

 

       // otherwise we will guess it may work

       return yesAttemptForeign;
}

CMyMultiDocTemplate::~CMyMultiDocTemplate(void)
{
}
