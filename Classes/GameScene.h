/*
 * GameScene.h
 *
 *  Created on: 2016��1��15��
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
	LayerColor * colorBack;//��Ϸ����
	bool m_startMove;//�Ƿ�ʼ�ƶ�
	int m_x, m_y;//��¼�ƶ���ʼ��λ��
	bool m_sound_clear;
	bool m_moved;//��¼���δ����Ƿ�����˿���ƶ�
	int m_score;
public:
	int m_dir;//�ƶ�����
	int map[GAME_ROWS][GAME_COLS];
	Vector<MovedTiled *> m_allTiled;//�������еĿ�
	void moveAllTiled(E_MOVE_DIR dir);
	void newMovedTiled();//����һ���µĿ�
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
