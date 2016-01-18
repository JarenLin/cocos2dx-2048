/*
 * GameScene.cpp
 *
 *  Created on: 2016年1月15日
 *      Author: Bible
 */

#include "GameScene.h"
#include "gamedefine.h"
#include "MovedTiled.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"

using namespace CocosDenshion;

Scene * GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto sceneWidth = Director::getInstance()->getWinSize().width;
	auto sceneHeight = Director::getInstance()->getWinSize().height;
	//初始化游戏标题
	auto labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "2048");
	auto titleHeight = labelGame->getContentSize().height;
	labelGame->setPosition(Point(sceneWidth / 2,sceneHeight - titleHeight));
	this->addChild(labelGame);
	labelGame->setScale(3.0);
	//初始化游戏的网格
	auto tiledWidth = GAME_TILED_WIDTH*4 + GAME_TILED_BOARD_WIDTH*(4+1);
	auto tiledHeight = tiledWidth;
	//CCLog("tiledWidth == %d\ttiledHeight == %d\n",tiledWidth,tiledHeight);
	colorBack = LayerColor::create(Color4B(170, 170, 170, 255), tiledWidth, tiledHeight);
	colorBack->setPosition(Point((sceneWidth - tiledWidth)/2,(sceneHeight - tiledHeight)/2));
	this->addChild(colorBack);
	//初始化网络中的每一块
	auto oneTiledWidth = GAME_TILED_WIDTH;
	auto oneTiledHeight = oneTiledWidth;
	for (int row = 0; row < GAME_ROWS; row++) {
		for (int col = 0; col < GAME_COLS; col++) {
			auto layerTiled = LayerColor::create(Color4B(70,70,70,255),oneTiledWidth,oneTiledHeight);
			layerTiled->setPosition(Point(oneTiledWidth*col + 2*col + 2,oneTiledHeight*row + 2*row + 2));
			colorBack->addChild(layerTiled);
		}
	}
	//初始化网格数组
	for (int i = 0; i < GAME_ROWS; i++) {
		for (int j = 0; j < GAME_COLS; j++) {
			map[i][j] = 0;
		}
	}	
	//初始化数字块
	newMovedTiled();
	//触摸的处理
	auto event = EventListenerTouchOneByOne::create();
	
	event->onTouchBegan = [&](Touch* tou, Event *eve) {//[$]表示需要引用外部的对象
		m_x = tou->getLocation().x;
		m_y = tou->getLocation().y;
		m_startMove = true;
		return true;
	};
	
	event->onTouchMoved=[&](Touch* tou, Event *eve) {
		int x = tou->getLocation().x;
		int y = tou->getLocation().y;
		if (m_startMove && (abs(m_x - x) > 10 || abs(m_y - y) > 10)) {//判定触摸移动的方向
			m_startMove = false;
			E_MOVE_DIR dir;
			if (abs(m_x - x) > abs(m_y - y)) {
				if (m_x < x) {
					dir = E_MOVE_DIR::RIGHT;
				}
				else
				{
					dir = E_MOVE_DIR::LEFT;
				}
			}
			else {
				if (m_y < y) {
					dir = E_MOVE_DIR::UP;
				}
				else {
					dir = E_MOVE_DIR::DOWN;
				}

			}
			moveAllTiled(dir);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event,this);
	//初始化得分榜
	m_score = 0;
	labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "Score : ");
	labelGame->setScale(3.0);
	auto scoreHeight = labelGame->getContentSize().height;
	auto scoreWidth = labelGame->getContentSize().width;
	labelGame->setPosition(Point(sceneWidth/2 - scoreWidth, sceneHeight - scoreHeight*2 - titleHeight));
	this->addChild(labelGame);

	labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "0");
	labelGame->setScale(2.5);
	labelGame->setPosition(Point(sceneWidth / 2 + scoreWidth + labelGame->getContentSize().width*5, sceneHeight - scoreHeight * 2 - titleHeight));
	this->addChild(labelGame);
	labelGame->setTag(120);

	return true;
}

void GameScene::moveAllTiled(E_MOVE_DIR dir) {
	m_sound_clear = false;
	m_moved = false;
	//移动所有的块,消除
	switch (dir)
	{
	case E_MOVE_DIR::UP:
		moveUp();
		break;
	case E_MOVE_DIR::DOWN:
		moveDown();
		break;
	case E_MOVE_DIR::LEFT:
		moveLeft();
		break;
	case E_MOVE_DIR::RIGHT:
		moveRight();
		break;
	default:
		break;
	}
	//播放音乐
	if (m_sound_clear == true) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("SoundClear.wav");
	}
	else if(m_moved == true)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("SoundMove.wav");
	}
	else {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("SoundNoMove.wav");
	}
	//分数变化
	Label * labelScore = (Label *)this->getChildByTag(120);
	labelScore->setString(StringUtils::format("%d",m_score));
	//产生新的块
	if (m_moved == true) {
		newMovedTiled();
	}
}

void GameScene::newMovedTiled() {//一定要在空白区域产生
	auto freecount = 0;
	freecount = 16 - m_allTiled.size();
	auto num = rand() % freecount;
	auto rows = -1, cols = -1;
	bool flag_find = false;
	for (int i = 0; i < GAME_ROWS; i++) {
		for (int j = 0; j < GAME_COLS; j++)
		{
			if (0 == map[i][j])
			{
				if (num == 0)//找到了第几个空的块，有可能是第零个
				{				
					rows = i;
					cols = j;
					flag_find = true;
					break;
				}
				num--;
			}
		}
		if (flag_find)
			break;
	}

	if (flag_find) {//如果找到了空的位置，就放置一个随机位置
		auto tiled = MovedTiled::create();
		colorBack->addChild(tiled);
		tiled->showAt(rows, cols);
		m_allTiled.pushBack(tiled);
		map[rows][cols] = m_allTiled.getIndex(tiled) + 1;
		setBkColor(tiled);
	}
	if (freecount == 1)
	{//判定游戏输赢
		CCLog("freecount == 1");
		for (int row = 0; row < GAME_ROWS; row++)
		{
			for (int col = 0; col < GAME_COLS; col++)
			{
				int old_num = m_allTiled.at(map[row][col] - 1)->m_number;
				int new_num = 0;
				if (row + 1 < GAME_ROWS) {
					new_num = m_allTiled.at(map[row + 1][col]-1)->m_number;
					if (old_num == new_num) {
						return;
					}
				if (row - 1 >= 0) {
					new_num = m_allTiled.at(map[row - 1][col] - 1)->m_number;
					if (old_num == new_num) {
				}
						return;
					}
				}
				if (col + 1 < GAME_COLS) {
					new_num = m_allTiled.at(map[row][col + 1]-1)->m_number;
					if (old_num == new_num) {
						return;
					}
				}
				if (col - 1 >= 0) {
					new_num = m_allTiled.at(map[row][col - 1] - 1)->m_number;
					if (old_num == new_num) {
						return;
					}
				}
			}
			auto scene = GameOver::createScene();
			Director::getInstance()->replaceScene(TransitionFadeDown::create(2.0, scene));
			return;
		}
		return;
	}
}

void GameScene::moveUp() {
	//所有的行向上移动
	for (int j = 0; j < GAME_COLS; j++)
	{
		for (int i = GAME_ROWS - 1; i >=0; i--)
		{
			if (map[i][j]>0) {//找到了一个存在的块，那么，将该块不断网上移，直到顶部。
				for (int row = i; row < GAME_ROWS - 1; row++)
				{
					if (map[row + 1][j] == 0) {
						map[row + 1][j] = map[row][j];
						map[row][j] = 0;
						m_allTiled.at(map[row + 1][j] - 1)->moveTo(row + 1, j);
						m_moved = true;
					}
					else {
						//判断是否可以消除块						
						int upNumber = m_allTiled.at(map[row + 1][j] -1)->m_number;
						int downNumber = m_allTiled.at(map[row][j] - 1)->m_number;
						if (upNumber == downNumber) {
							m_score += upNumber*2;
							m_sound_clear = true;
							m_moved = true;
							m_allTiled.at(map[row+1][j]-1)->doubleNumber();
							m_allTiled.at(map[row][j]-1)->removeFromParent();
							int index = map[row][j];
							m_allTiled.erase(index - 1);
							map[row][j] = 0;
							for (int i = 0; i < GAME_ROWS; i++)
							{
								for (int j = 0; j < GAME_COLS; j++)
								{
									if (map[i][j]>index) {
										map[i][j]--;
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}
void GameScene::moveDown() {
	//所有的行向下移动
	for (int j = 0; j < GAME_COLS; j++)
	{
		for (int i = 0; i < GAME_ROWS; i++)
		{
			if (map[i][j]>0) {//找到了一个存在的块，那么，将该块不断网上移，直到顶部。
				for (int row = i; row > 0; row--)
				{
					if (map[row-1][j] == 0) {
						map[row-1][j] = map[row][j];
						map[row][j] = 0;
						m_allTiled.at(map[row - 1][j] - 1)->moveTo(row - 1, j);
						m_moved = true;
					}
					else {
						//判断是否可以消除块						
						int upNumber = m_allTiled.at(map[row][j] - 1)->m_number;
						int downNumber = m_allTiled.at(map[row - 1][j] - 1)->m_number;						
						if (upNumber == downNumber) {
							m_score += upNumber*2;
							m_sound_clear = true;
							m_moved = true;
							m_allTiled.at(map[row - 1][j] - 1)->doubleNumber();
							m_allTiled.at(map[row][j] - 1)->removeFromParent();
							int index = map[row][j];
							m_allTiled.erase(index - 1);
							map[row][j] = 0;
							for (int i = 0; i < GAME_ROWS; i++)
							{
								for (int j = 0; j < GAME_COLS; j++)
								{
									if (map[i][j]>index) {
										map[i][j]--;
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}
void GameScene::moveLeft() {
	//所有的行向左移动
	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_COLS; j++)
		{
			if (map[i][j]>0) {//找到了一个存在的块，那么，将该块不断网上移，直到顶部。
				for (int cols = j; cols >0; cols--)
				{
					if (map[i][cols - 1] == 0) {
						map[i][cols - 1] = map[i][cols];
						map[i][cols] = 0;
						m_allTiled.at(map[i][cols - 1] - 1)->moveTo(i, cols - 1);
						m_moved = true;
					}
					else {
						//判断是否可以消除块						
						int upNumber = m_allTiled.at(map[i][cols] - 1)->m_number;
						int downNumber = m_allTiled.at(map[i][cols - 1] - 1)->m_number;
						if (upNumber == downNumber) {
							m_score += upNumber*2;
							m_sound_clear = true;
							m_moved = true;
							m_allTiled.at(map[i][cols - 1] - 1)->doubleNumber();
							m_allTiled.at(map[i][cols] - 1)->removeFromParent();
							int index = map[i][cols];
							m_allTiled.erase(index - 1);
							map[i][cols] = 0;
							for (int i = 0; i < GAME_ROWS; i++)
							{
								for (int j = 0; j < GAME_COLS; j++)
								{
									if (map[i][j]>index) {
										map[i][j]--;
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}

}
void GameScene::moveRight() {
	//所有的行向右移动
	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = GAME_COLS - 1; j >= 0; j--)
		{
			if (map[i][j]>0) {//找到了一个存在的块，那么，将该块不断网上移，直到顶部。
				for (int cols = j; cols < GAME_COLS - 1; cols++)
				{
					if (map[i][cols + 1] == 0) {
						map[i][cols + 1] = map[i][cols];
						map[i][cols] = 0;
						m_allTiled.at(map[i][cols + 1] - 1)->moveTo(i, cols + 1);
						m_moved = true;
					}
					else {
						//判断是否可以消除块						
						int upNumber = m_allTiled.at(map[i][cols] - 1)->m_number;
						int downNumber = m_allTiled.at(map[i][cols + 1] - 1)->m_number;
						if (upNumber == downNumber) {
							m_score += upNumber*2;
							m_sound_clear = true;
							m_moved = true;
							m_allTiled.at(map[i][cols + 1] - 1)->doubleNumber();
							m_allTiled.at(map[i][cols] - 1)->removeFromParent();
							int index = map[i][cols];
							m_allTiled.erase(index - 1);
							map[i][cols] = 0;
							for (int i = 0; i < GAME_ROWS; i++)
							{
								for (int j = 0; j < GAME_COLS; j++)
								{
									if (map[i][j]>index) {
										map[i][j]--;
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}

// 设置数字
void GameScene::setBkColor(MovedTiled * tiled) {
	int number = tiled->m_number;
	auto layerColorBG = tiled->getChildByTag(110);
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
	default:
		break;
	}
}