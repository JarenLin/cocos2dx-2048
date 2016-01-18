/*
 * SplashScene.cpp
 *
 *  Created on: 2016年1月15日
 *      Author: Bible
 */

#include "SplashScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

bool SplashScene::init(){
	if(!Layer::init()){
		return false;
	}
	auto sceneWidth = Director::getInstance()->getWinSize().width;
	auto sceneHeight = Director::getInstance()->getWinSize().height;
	CCLog("SceneWidth==%f\tSceneHeight==%f\n", sceneWidth, sceneHeight);
	//显示游戏名称
	auto labelGame=Label::createWithBMFont("fonts/futura-48.fnt", "2048");
	labelGame->setPosition(sceneWidth / 2, sceneHeight / 2 - labelGame->getContentSize().height/2);
	this->addChild(labelGame);
	labelGame->setScale(3.0);
	//显示游戏单位
	auto labelGameVer = Label::createWithBMFont("fonts/futura-48.fnt", "Jaren 2015.1.16");
	labelGameVer->setPosition(sceneWidth / 2, sceneHeight / 4);
	this->addChild(labelGameVer);
	labelGameVer->setScale(1.5);
	//计划任务：3秒后跳转到游戏场景
	this->scheduleOnce(schedule_selector(SplashScene::jumpToGame), 3);
	//加载游戏资源
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("SoundClear.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("SoundMove.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("SoundNoMove.wav");
	return true;
}

Scene * SplashScene::createScene(){
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

void SplashScene::jumpToGame(float t) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressInOut::create(0.5,scene));
}
