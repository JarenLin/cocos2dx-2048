/*
 * SplashScene.cpp
 *
 *  Created on: 2016��1��15��
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
	//��ʾ��Ϸ����
	auto labelGame=Label::createWithBMFont("fonts/futura-48.fnt", "2048");
	labelGame->setPosition(sceneWidth / 2, sceneHeight / 2 - labelGame->getContentSize().height/2);
	this->addChild(labelGame);
	labelGame->setScale(3.0);
	//��ʾ��Ϸ��λ
	auto labelGameVer = Label::createWithBMFont("fonts/futura-48.fnt", "Jaren 2015.1.16");
	labelGameVer->setPosition(sceneWidth / 2, sceneHeight / 4);
	this->addChild(labelGameVer);
	labelGameVer->setScale(1.5);
	//�ƻ�����3�����ת����Ϸ����
	this->scheduleOnce(schedule_selector(SplashScene::jumpToGame), 3);
	//������Ϸ��Դ
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
