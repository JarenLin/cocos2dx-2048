/*
 * GameScene.h
 *
 *  Created on: 2016年1月15日
 *      Author: Bible
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <iostream>
#include "cocos2d.h"
#include "gamedefine.h"
#include "MovedTiled.h"
USING_NS_CC;

class GameScene:Layer {
private:
	LayerColor * colorBack;//游戏背景
	bool m_startMove;//是否开始移动
	int m_x, m_y;//记录移动开始的位置
	bool m_sound_clear;
	bool m_moved;//记录当次触摸是否产生了块的移动
	int m_score;
public:
	int m_dir;//移动方向
	int map[GAME_ROWS][GAME_COLS];
	Vector<MovedTiled *> m_allTiled;//保存所有的块
	void moveAllTiled(E_MOVE_DIR dir);
	void newMovedTiled();//产生一个新的块
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	static Scene * createScene();
	CREATE_FUNC(GameScene);
	bool init();
	void setBkColor(MovedTiled * tiled);
};

#endif /* GAMESCENE_H_ */
