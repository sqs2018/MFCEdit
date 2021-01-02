
// MyEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MyEdit.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MyEditDoc.h"
#include "MyEditView.h"
#include "MyPView.h"
#include "SetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyEditApp

BEGIN_MESSAGE_MAP(CMyEditApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMyEditApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CMyEditApp::OnFileNew)
	ON_COMMAND(ID_FILE_NEWP, &CMyEditApp::OnFileNewP)
	ON_COMMAND(ID_FILE_OPEN, &CMyEditApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMyEditApp construction

CMyEditApp::CMyEditApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MyEdit.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMyEditApp object

CMyEditApp theApp;
CMultiDocTemplate* pDocTemplate;//文本
CMultiDocTemplate* pDocTemplateP;//绘图


// CMyEditApp initialization

BOOL CMyEditApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	
	pDocTemplate = new CMultiDocTemplate(IDR_MyEditTYPE,
		RUNTIME_CLASS(CMyEditDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMyEditView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(ID_MYEDITVIEW);//区分两个view
	
	AddDocTemplate(pDocTemplate);


	pDocTemplateP = new CMultiDocTemplate(IDR_MyEditTYPE,
		RUNTIME_CLASS(CMyEditDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(MyPView));
	if (!pDocTemplateP)
		return FALSE;
	pDocTemplateP->SetContainerInfo(ID_MYPVIEW);//区分两个view
	AddDocTemplate(pDocTemplateP);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
		//return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CMyEditApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}





// CMyEditApp message handlers

//新建绘图文件
void CMyEditApp::OnFileNewP(){

	if (NULL == m_pDocManager)
        return;
    // first template position 

	
    if (!pDocTemplateP)
        return;
    // create new doc and add to manager
    CDocument* pDoc = pDocTemplateP->OpenDocumentFile(NULL);
    if (!pDoc)
    {
        return;
    }
    // set doc title 
    pDoc->SetTitle(_T("绘图"));

    // unnecessary
    // Test is not the first document
    POSITION posDoc =  pDocTemplateP->GetFirstDocPosition();
    if (posDoc)
    {
        auto p = pDocTemplateP->GetNextDoc(posDoc);
        if (p == pDoc)
        {
            TRACE(_T("new doc title is %s\n"), p->GetTitle());
        }
        else
        {
            TRACE(_T("first doc title is %s\n"), p->GetTitle());
            TRACE(_T("new doc title is %s\n"), pDoc->GetTitle());
        }
    }

}

//新建文件
void  CMyEditApp::OnFileNew(){
	if (NULL == m_pDocManager)
        return;
    // first template position 
    POSITION posTemplate =  m_pDocManager->GetFirstDocTemplatePosition();
    // if NULL no template
    if (NULL == posTemplate)
    {
        return;
    }
    // first template 
    CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(posTemplate);
    if (!pTemplate)
        return;
    // create new doc and add to manager
    CDocument* pDoc = pTemplate->OpenDocumentFile(NULL);
    if (!pDoc)
    {
        return;
    }
    // set doc title 
    pDoc->SetTitle(_T("文本文件"));

    // unnecessary
    // Test is not the first document
    POSITION posDoc =  pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
        auto p = pTemplate->GetNextDoc(posDoc);
        if (p == pDoc)
        {
            TRACE(_T("new doc title is %s\n"), p->GetTitle());
        }
        else
        {
            TRACE(_T("first doc title is %s\n"), p->GetTitle());
            TRACE(_T("new doc title is %s\n"), pDoc->GetTitle());
        }
    }

}
//获取文件后缀
CString GetExtNameNew(CString fileName)
{
    int pos = fileName.Find(_T(".")); //获取 . 的位置
    if (pos == -1){ //如果没有找到，直接返回该字符串
        return fileName;
    }
    else{
        return GetExtNameNew(fileName.Mid(pos + 1)); //找到了的话，往深层遍历，直到最底层
    }
}

//打开文件
void CMyEditApp::OnFileOpen(){
	LPCTSTR szFilter = L"绘图文件(*.p)|*.p|文本文件(*.t)|*.t||";   
 
    CFileDialog oFileDlg(TRUE, L".p", NULL, 4|2, szFilter);
	
    if(oFileDlg.DoModal() == IDOK){
		
		CString szPath = oFileDlg.GetPathName(); 
		CString extName=GetExtNameNew(szPath);
		if(extName=="p"){
			//获取文件后缀
			 // create new doc and add to manager
			CDocument* pDoc = pDocTemplateP->OpenDocumentFile(NULL);
			if (!pDoc)
			{
				return;
			}
			POSITION posView = pDoc->GetFirstViewPosition();
			while( posView != NULL )
			{
				MyPView* pView = (MyPView*)pDoc->GetNextView(posView);
				pView->loadFile(szPath);
			}
			
		
		}else{
			//获取文件后缀
		 // create new doc and add to manager
			CDocument* pDoc = pDocTemplate->OpenDocumentFile(szPath);
			if (!pDoc)
			{
				return;
			}
		
		}
		
		
		//OpenDocumentFile(oFileDlg.m_ofn.lpstrFile); 

	}

}




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMyEditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMyEditApp message handlers



