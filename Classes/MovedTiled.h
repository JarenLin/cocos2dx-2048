#pragma once
#include <iostream>
#include <cocos2d.h>
#include "gamedefine.h"
USING_NS_CC;
class MovedTiled:public Node
{
public:
	int m_row;
	int m_col;
	int m_number;
	void showAt(int r, int c);//��һ��λ����ʾһ����
	void moveTo(int r, int c);//�ƶ�����鵽ĳ��λ��
	void doubleNumber();//X2
	CREATE_FUNC(MovedTiled);
	bool init();
	void setBkColor(int num);
};

