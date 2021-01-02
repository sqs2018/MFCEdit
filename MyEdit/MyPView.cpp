#include "stdafx.h"
#include "MyPView.h"
#include "MyEditDoc.h"
#include "SetDlg.h"
#include "resource.h"
#include "Data.h"
#include "SetDlg.h"




IMPLEMENT_DYNCREATE(MyPView, CView)

BEGIN_MESSAGE_MAP(MyPView, CView)
	ON_COMMAND(ID_SET, &MyPView::OnSet)
	ON_COMMAND(ID_LINE, &MyPView::OnLine)
	ON_COMMAND(ID_ECLIPSE, &MyPView::OnEclipse)
	ON_COMMAND(ID_SECTOR, &MyPView::OnSector)
	ON_COMMAND(ID_RECTANGLE, &MyPView::OnRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()





MyPView::MyPView(void)
{
	// TODO: add construction code here
	//初始化默认数据
	
	m_leftbtnClick=false;
}


BOOL MyPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
	
	return bPreCreated;
}





// CMyEditView printing

BOOL MyPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CView::OnPreparePrinting(pInfo);
}

void MyPView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CView::OnBeginPrinting(pDC, pInfo);
}

void MyPView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CView::OnEndPrinting(pDC, pInfo);
}
void MyPView::OnDraw(CDC* pDC){

}

// CMyEditView diagnostics

#ifdef _DEBUG
void MyPView::AssertValid() const
{
	CView::AssertValid();
}

void MyPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyEditDoc* MyPView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyEditDoc)));
	return (CMyEditDoc*)m_pDocument;
}
#endif //_DEBUG


MyPView::~MyPView(void)
{
}


//点击菜单设置
void MyPView::OnSet()
{
	// TODO: Add your command handler code here
	CSetDlg dlg;
	dlg.DoModal();
}
//选中菜单
void menuCheck(int ID){
	CMenu *pMenu=AfxGetApp()->m_pMainWnd->GetMenu(); 
	CMenu* subMenu=pMenu->GetSubMenu(4);
	if(subMenu){
		subMenu->CheckMenuItem(ID_LINE,MF_BYCOMMAND|MF_UNCHECKED);
		subMenu->CheckMenuItem(ID_ECLIPSE,MF_BYCOMMAND|MF_UNCHECKED);
		subMenu->CheckMenuItem(ID_SECTOR,MF_BYCOMMAND|MF_UNCHECKED);
		subMenu->CheckMenuItem(ID_RECTANGLE,MF_BYCOMMAND|MF_UNCHECKED);
	}
	subMenu->CheckMenuItem(ID,MF_BYCOMMAND|MF_CHECKED);
}


//点击菜单直线
void MyPView::OnLine()
{
	
	menuCheck(ID_LINE);
	// TODO: Add your command handler code here
	CSetDlg::DIALOGSET.m_type=0;
}

//点击菜单椭圆
void MyPView::OnEclipse()
{
	menuCheck(ID_ECLIPSE);
	// TODO: Add your command handler code here
	CSetDlg::DIALOGSET.m_type=1;
}

//点击菜单扇形
void MyPView::OnSector()
{
	menuCheck(ID_SECTOR);
	// TODO: Add your command handler code here
	CSetDlg::DIALOGSET.m_type=2;
}

//点击菜单矩形
void MyPView::OnRectangle()
{
	menuCheck(ID_RECTANGLE);
	// TODO: Add your command handler code here
	CSetDlg::DIALOGSET.m_type=3;
}

//鼠标左键按下
void MyPView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//设置左键按下
	m_leftbtnClick=true;
	//设置起点
	CSetDlg::DIALOGSET.m_startPoint=point;
	CSetDlg::DIALOGSET.m_endPoint=point;
	CView::OnLButtonDown(nFlags, point);
}


void MyPView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_leftbtnClick){
		m_leftbtnClick=false;
		 CClientDC   ClientDC(this);  
		 CPen pen, *oldPen;
		 CBrush brush,*oldBrush;
		CSetDlg::DIALOGSET.m_endPoint=point;
		pen.CreatePen(CSetDlg::DIALOGSET.m_lineType,CSetDlg::DIALOGSET.m_lineWidth,CSetDlg::DIALOGSET.m_color);
		 oldPen = ClientDC.SelectObject(&pen);
	 
		 oldBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		  ClientDC.SelectObject(oldBrush);
		//类型
		switch(CSetDlg::DIALOGSET.m_type){
			case 0://直线	
				 ClientDC.DPtoLP(&point);
				 ClientDC.SetROP2( R2_COPYPEN ); 
				 ClientDC.MoveTo(CSetDlg::DIALOGSET.m_startPoint);  
				 ClientDC.LineTo(CSetDlg::DIALOGSET.m_endPoint);  	
				 ClientDC.SelectObject(oldPen);
				break;
			case 1://椭圆			
				ClientDC.Ellipse(CSetDlg::DIALOGSET.m_startPoint.x,CSetDlg::DIALOGSET.m_startPoint.y,CSetDlg::DIALOGSET.m_endPoint.x,CSetDlg::DIALOGSET.m_endPoint.y);			 
				break;
			case 2://2.扇形
				RECT rect;
				rect.top=CSetDlg::DIALOGSET.m_startPoint.y;
				rect.left=CSetDlg::DIALOGSET.m_startPoint.x;
				rect.right=CSetDlg::DIALOGSET.m_endPoint.x;
				rect.bottom=CSetDlg::DIALOGSET.m_endPoint.y;
				ClientDC.Pie(&rect,CSetDlg::DIALOGSET.m_startPoint,CSetDlg::DIALOGSET.m_endPoint);				
				break;
			case 3:// 3.矩形
				ClientDC.Rectangle(CSetDlg::DIALOGSET.m_startPoint.x,CSetDlg::DIALOGSET.m_startPoint.y,CSetDlg::DIALOGSET.m_endPoint.x,CSetDlg::DIALOGSET.m_endPoint.y);
				break;
		}
		//存储数据
		CData* cdata=new CData(CSetDlg::DIALOGSET.m_startPoint,CSetDlg::DIALOGSET.m_endPoint,CSetDlg::DIALOGSET.m_type,CSetDlg::DIALOGSET.m_color,CSetDlg::DIALOGSET.m_lineWidth,CSetDlg::DIALOGSET.m_lineType);
		dataArray.Add(cdata);
		//修改标题
		changeTitle(true);
	}
	 

	CView::OnLButtonUp(nFlags, point);
}

//鼠标移动
void MyPView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_leftbtnClick&&CSetDlg::DIALOGSET.m_type==0)
	{
		 CClientDC   ClientDC(this); 
		 ClientDC.DPtoLP(&point);  
		 ClientDC.SelectStockObject(NULL_BRUSH);
 
		 CPen pen, *oldPen;
		 pen.CreatePen(CSetDlg::DIALOGSET.m_lineType,CSetDlg::DIALOGSET.m_lineWidth,CSetDlg::DIALOGSET.m_color);
		 oldPen = ClientDC.SelectObject(&pen);
		 ClientDC.SetROP2(R2_NOT);  
		 ClientDC.MoveTo(CSetDlg::DIALOGSET.m_startPoint);  
		 ClientDC.LineTo(CSetDlg::DIALOGSET.m_endPoint);   
		 CSetDlg::DIALOGSET.m_endPoint = point;   
		 ClientDC.MoveTo(CSetDlg::DIALOGSET.m_startPoint);  
		 ClientDC.LineTo(CSetDlg::DIALOGSET.m_endPoint);  
		 ClientDC.SelectObject(oldPen);
	}
	CView::OnMouseMove(nFlags, point);
}

//界面重绘
void MyPView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	if(dataArray.GetSize()>0){
		for(int i=0;i<dataArray.GetSize();i++){
			CData* data=(CData*)dataArray.GetAt(i);
			CPen pen, *oldPen;
			CBrush brush,*oldBrush;
			
			pen.CreatePen(data->m_lineType,data->m_lineWidth,data->m_color);
			oldPen = dc.SelectObject(&pen);	 
			oldBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			dc.SelectObject(oldBrush);
			//类型
			switch(data->m_type){
				case 0://直线	
						//dc.DPtoLP(data->m_endPoint);
						dc.SetROP2( R2_COPYPEN ); 
						dc.MoveTo(data->m_startPoint);  
						dc.LineTo(data->m_endPoint);  	
						dc.SelectObject(oldPen);
					break;
				case 1://椭圆			
					dc.Ellipse(data->m_startPoint.x,data->m_startPoint.y,data->m_endPoint.x,data->m_endPoint.y);			 
					break;
				case 2://2.扇形
					RECT rect;
					rect.top=data->m_startPoint.y;
					rect.left=data->m_startPoint.x;
					rect.right=data->m_endPoint.x;
					rect.bottom=data->m_endPoint.y;
					dc.Pie(&rect,data->m_startPoint,data->m_endPoint);
					break;
				case 3:// 3.矩形
					dc.Rectangle(data->m_startPoint.x,data->m_startPoint.y,data->m_endPoint.x,data->m_endPoint.y);
					break;
			}
		}

	}
	// Do not call CView::OnPaint() for painting messages
}
//修改标题
void MyPView::changeTitle(bool showX){
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

void MyPView::saveToFile(CString szPath){
	CFile file(szPath,CFile::modeCreate | CFile::modeWrite); //定义一个文件流对象
	CArchive ar(&file,CArchive::store);  //定义一个序列化对象和文件流对象绑定并指定归档方式为储存，加载的方式为CArchive::load
	int length=dataArray.GetSize();
	ar<<length;
	for(int i=0;i<dataArray.GetSize();i++){
			CData* data=(CData*)dataArray.GetAt(i);
			ar<<data;
	}

	ar.Close();
	changeTitle(false);
}

//加载.p文件
void MyPView::loadFile(CString loadFile){
	CFile file(loadFile,CFile::modeRead); //定义一个文件流对象
	CArchive ar(&file,CArchive::load); 
	//可能有内存问题
	dataArray.RemoveAll();
	int length=0;
	ar>>length;
	for(int i=0;i<length;i++){
		CData* data=new CData;
		ar>>data;
		dataArray.Add(data);
	}
	
	ar.Close();
	int temp=10;


}