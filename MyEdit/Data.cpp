#include "stdafx.h"
#include "Data.h"

IMPLEMENT_SERIAL(CData, CObject, 1)

CData::CData(){
}
CData::CData(CPoint m_startPoint,CPoint m_endPoint,int m_type,COLORREF m_color,int m_lineWidth,int m_lineType)
{
	this->m_startPoint=m_startPoint;
	this->m_endPoint=m_endPoint;
	this->m_type=m_type;
	this->m_color=m_color;
	this->m_lineWidth=m_lineWidth;
	this->m_lineType=m_lineType;
}

void CData::Serialize(CArchive& ar)
{
    CObject::Serialize(ar);
    if(ar.IsStoring())//保存，加载为ar.IsLoading()
    {
        ar <<m_startPoint<<m_endPoint<<m_type<<m_color<<m_lineWidth<<m_lineType;
    }
	else //加载
    {
        ar >>m_startPoint>>m_endPoint>>m_type>>m_color>>m_lineWidth>>m_lineType;
    }
}
CData::~CData(void)
{
}
