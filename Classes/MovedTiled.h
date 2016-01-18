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
	void showAt(int r, int c);//在一个位置显示一个快
	void moveTo(int r, int c);//移动这个块到某个位置
	void doubleNumber();//X2
	CREATE_FUNC(MovedTiled);
	bool init();
	void setBkColor(int num);
};

