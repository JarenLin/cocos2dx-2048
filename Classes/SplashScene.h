/*
 * SplashScene.h
 *
 *  Created on: 2016��1��15��
 *      Author: Bible
 */

#ifndef SPLASHSCENE_H_
#define SPLASHSCENE_H_

#include <cocos2d.h>
#include "gamedefine.h"
USING_NS_CC;

class SplashScene:Layer {
	bool init();
public :
	CREATE_FUNC(SplashScene);
	static Scene * createScene();
	void jumpToGame(float t);
};

#endif /* SPLASHSCENE_H_ */
