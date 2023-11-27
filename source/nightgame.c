#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기


void nightgame_init(void) {
	
	int init_x = 6 + n_alive/2;

	map_init(init_x, 35);
	map_replace('#', '*');

	int start_x = init_x / 2 - n_player / 2 - 1;
	int x = start_x, y;
	for (int i = 0; i < n_player; i++) {
		// y축 오른쪽 정렬
		x += 1;
		y = N_COL - 2;
		px[i] = x;
		py[i] = y;
		period[i] = randint(123, 130);
		// x세로 y가로
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	for (int i = 3; i < x_size + 3; i++)
		back_buf[i][1] = '#';

	tick = 0;
}

void nightgame(void) {
	nightgame_init();
}