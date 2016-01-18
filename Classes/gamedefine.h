/*
 * gamedefine.h
 *
 *  Created on: 2016年1月16日
 *      Author: Bible
 */

#ifndef GAMEDEFINE_H_
#define GAMEDEFINE_H_

#define GAME_SCREEN_WIDTH 320
#define GAME_SCREEN_HEIGHT 480

//把屏幕宽分成6份，网格是4 x 4
#define GAME_ROWS 4
#define GAME_COLS 4
//一格的边框和网格外边框的大小
#define GAME_TILED_BOARD_WIDTH 2  //网格实线的宽度
#define GAME_TILED_WIDTH 60
#define GAME_TILED_HEIGHT 60

enum class E_MOVE_DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#endif /* GAMEDEFINE_H_ */
