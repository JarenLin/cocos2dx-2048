#include "GameOver.h"
#include "gamedefine.h"
#include "GameScene.h"

bool GameOver::init() {
	if (!Layer::init()) {
		return false;
	}
	//��ʾ��Ϸ����
	auto labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "GAME OVER");
	labelGame->setScale(3.0);
	labelGame->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + labelGame->getContentSize().height / 2);
	this->addChild(labelGame);
	//���¿�ʼ��Ϸ
	auto label = Label::createWithBMFont("fonts/futura-48.fnt", "Restart Game");
	label->setScale(2.0);
	auto labelItem = MenuItemLabel::create(label,CC_CALLBACK_1(GameOver::menuCallBack,this));	
	labelItem->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 4 - labelItem->getContentSize().height / 2);
	auto menu = Menu::create(labelItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	
	return true;
}
void GameOver::menuCallBack(Ref * pObj) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5,scene));//��ת����Ϸ���������¿�ʼ��Ϸ.
}
Scene * GameOver::createScene() {
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}