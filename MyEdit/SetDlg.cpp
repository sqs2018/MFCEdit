// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyEdit.h"
#include "SetDlg.h"
#include "afxdialogex.h"




// CSetDlg dialog

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
{
	
}

//对话框设置
DlgSet CSetDlg::DIALOGSET={(0,0),(0,0),0,0x000000,1,0};
CSetDlg::~CSetDlg()
{
}
BOOL CSetDlg::OnInitDialog(){
	 CDialogEx::OnInitDialog();

	 m_colorBtn.SetColor(CSetDlg::DIALOGSET.m_color);
	 CString str;
	 str.Format(_T("%d"),CSetDlg::DIALOGSET.m_lineWidth);
	 m_lineWidthEdit.SetWindowText(str);
	 m_lineTypeCB.SetCurSel(CSetDlg::DIALOGSET.m_lineType);
	return TRUE;
}
void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorBtn);
	DDX_Control(pDX, IDC_EDIT1, m_lineWidthEdit);
	DDX_Control(pDX, IDC_COMBO1, m_lineTypeCB);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDlg message handlers

//点击设置按钮
void CSetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//添加设置功能
	DIALOGSET.m_color=m_colorBtn.GetColor();
	DIALOGSET.m_lineWidth=GetDlgItemInt(IDC_EDIT1);
	DIALOGSET.m_lineType=m_lineTypeCB.GetCurSel();
	CDialogEx::OnOK();
}
