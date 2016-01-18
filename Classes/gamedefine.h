/*
 * gamedefine.h
 *
 *  Created on: 2016��1��16��
 *      Author: Bible
 */

#ifndef GAMEDEFINE_H_
#define GAMEDEFINE_H_

#define GAME_SCREEN_WIDTH 320
#define GAME_SCREEN_HEIGHT 480

//����Ļ��ֳ�6�ݣ�������4 x 4
#define GAME_ROWS 4
#define GAME_COLS 4
//һ��ı߿��������߿�Ĵ�С
#define GAME_TILED_BOARD_WIDTH 2  //����ʵ�ߵĿ��
#define GAME_TILED_WIDTH 60
#define GAME_TILED_HEIGHT 60

enum class E_MOVE_DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#endif /* GAMEDEFINE_H_ */
