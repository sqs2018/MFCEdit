#pragma once
#include "afx.h"
#include <map>
//数据工具类
class CData :
	public CObject
{
public:
	DECLARE_SERIAL(CData)  
	CData();
	CData(CPoint m_startPoint,CPoint m_endPoint,int m_type,COLORREF m_color,int m_lineWidth,int m_lineType);
	~CData(void);
	CPoint m_startPoint;//起点位置
	CPoint m_endPoint;//终点位置
	int m_type;//绘画类型 0。直线 1.椭圆 2.扇形 3.矩形
	COLORREF m_color;//当前设置颜色
	int m_lineWidth;//当前设置线宽
	int m_lineType;//线型 0.实线。。。
	//存储数据
	 //std::map<int,CPtrArray> DataMap;
	 //static CPtrArray getArray();
	 //static CPtrArray addArray();

	void Serialize(CArchive& ar);//重写了Serialize成员函数


};

