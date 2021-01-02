#pragma once

#include "stdafx.h"
#include "resource.h"
#include "afxcolorbutton.h"
#include "afxwin.h"
#include "MyPView.h"

struct DlgSet{
	CPoint m_startPoint;//起点位置
	CPoint m_endPoint;//终点位置
	int m_type;//绘画类型 0。直线 1.椭圆 2.扇形 3.矩形
	COLORREF m_color;//当前设置颜色
	int m_lineWidth;//当前设置线宽
	int m_lineType;//线型 0.实线。。。
};




// CSetDlg dialog

class CSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetDlg();
	static DlgSet DIALOGSET;
	

// Dialog Data
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton m_colorBtn;
	CEdit m_lineWidthEdit;
	CComboBox m_lineTypeCB;
	afx_msg void OnBnClickedOk();
};
