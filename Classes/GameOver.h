#ifndef __GameOver__
#define __GameOver__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class GameOver:Layer
{
public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);
	void menuCallBack(Ref * pObj);
};

#endif