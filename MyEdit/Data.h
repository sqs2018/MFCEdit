#pragma once
#include "afx.h"
#include <map>
//���ݹ�����
class CData :
	public CObject
{
public:
	DECLARE_SERIAL(CData)  
	CData();
	CData(CPoint m_startPoint,CPoint m_endPoint,int m_type,COLORREF m_color,int m_lineWidth,int m_lineType);
	~CData(void);
	CPoint m_startPoint;//���λ��
	CPoint m_endPoint;//�յ�λ��
	int m_type;//�滭���� 0��ֱ�� 1.��Բ 2.���� 3.����
	COLORREF m_color;//��ǰ������ɫ
	int m_lineWidth;//��ǰ�����߿�
	int m_lineType;//���� 0.ʵ�ߡ�����
	//�洢����
	 //std::map<int,CPtrArray> DataMap;
	 //static CPtrArray getArray();
	 //static CPtrArray addArray();

	void Serialize(CArchive& ar);//��д��Serialize��Ա����


};

