#include "MovedTiled.h"

void MovedTiled::showAt(int r, int c) {
	moveTo(r,c);
	auto bk = this->getChildByTag(110);
	bk->runAction(Sequence::create(ScaleTo::create(0.3,1.2),ScaleTo::create(0.2,1.0),NULL));
}
void MovedTiled::moveTo(int r, int c) {
	this->m_row = r;
	this->m_col = c;
	this->setPosition(Point(c*GAME_TILED_WIDTH +(c+1)*GAME_TILED_BOARD_WIDTH,r*GAME_TILED_HEIGHT+(r+1)*GAME_TILED_BOARD_WIDTH));
}

bool MovedTiled::init() {
	if (!Node::init()) {
		return false;
	}
	//背景
	auto bk = LayerColor::create(Color4B(200,200,200,255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
	this->addChild(bk);
	bk->setTag(110);
	//数字
	int n = rand() % 10;
	this->m_number = n > 0 ? 2 : 4;
	auto label = Label::createWithSystemFont(StringUtils::format("%d",this->m_number),"宋体",15);
	label->setTag(10);
	label->setColor(Color3B::BLACK);
	bk->addChild(label);
	label->setPosition(Point(bk->getContentSize().width/2,bk->getContentSize().height/2));
	label->setScale(3);
	return true;
}
void MovedTiled::doubleNumber() {
	this->m_number = this->m_number * 2;
	auto bk = this->getChildByTag(110);
	Label * label = (Label*)bk->getChildByTag(10);
	if (this->m_number >= 128 && this->m_number <= 512) {
		label->setScale(2);
	}
	if (this->m_number >= 1024 && this->m_number <= 2048) {
		label->setScale(1.5);
	}
	if (this->m_number == 2048) {
		CCLog("You Win!!");
	}
	label->setString(StringUtils::format("%d",this->m_number));

	label->setColor(cocos2d::Color3B(255, 255, 255));
	setBkColor(this->m_number);	

	bk->runAction(Sequence::create(ScaleTo::create(0.1, 0.9), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 1.0), NULL));
}
// 设置数字
void MovedTiled::setBkColor(int num) {
	int number = num;
	auto layerColorBG = this->getChildByTag(110);
	auto label = (Label*)layerColorBG->getChildByTag(10);
	// 判断大小调整颜色
	switch (number) {
		case 2:
			layerColorBG->setColor(cocos2d::Color3B(240, 230, 220));
			label->setColor(cocos2d::Color3B(0, 0, 0));
			break;
		case 4:
			layerColorBG->setColor(cocos2d::Color3B(240, 220, 200));
			label->setColor(cocos2d::Color3B(0, 0, 0));
			break;
		case 8:
			layerColorBG->setColor(cocos2d::Color3B(240, 180, 120));
			break;
		case 16:
			layerColorBG->setColor(cocos2d::Color3B(240, 140, 90));
			break;
		case 32:
			layerColorBG->setColor(cocos2d::Color3B(240, 120, 90));
			break;
		case 64:
			layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
			break;
		case 128:
			layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
			break;
		case 256:
			layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
			break;
		case 512:
			layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
			break;
		case 1024:
			layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
			break;
		case 2048:
			layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
			break;
		default:
			break;
	}
}