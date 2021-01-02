#pragma once

#include "stdafx.h"
#include "resource.h"
#include "afxcolorbutton.h"
#include "afxwin.h"
#include "MyPView.h"

struct DlgSet{
	CPoint m_startPoint;//���λ��
	CPoint m_endPoint;//�յ�λ��
	int m_type;//�滭���� 0��ֱ�� 1.��Բ 2.���� 3.����
	COLORREF m_color;//��ǰ������ɫ
	int m_lineWidth;//��ǰ�����߿�
	int m_lineType;//���� 0.ʵ�ߡ�����
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
