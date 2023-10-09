#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void mugunghwa_init(void);


int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

void map_replace(char a, char b) {
	// map의 a를 b로 변경
		for (int i = 0; i < N_ROW; i++) {
			for (int j = 0; j < N_COL; j++) {
				if (back_buf[i][j] == a) {
					back_buf[i][j] = b;
				}
			}
		}
}

void mugunghwa_init(void) {
	int x_size;
	if (n_player > 2) 
		x_size = n_player - 2;
	else x_size = 1;
	
	int init_x = 6 + x_size;

	map_init(init_x, 35);
	map_replace('#', '*');

	int start_x = init_x / 2 - n_player / 2 -1;
	int x = start_x, y ;
	for (int i = 0; i < n_player; i++) {
		// y축 오른쪽 정렬
		x += 1;
		y = 33;
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);
		// x세로 y가로
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	for(int i = 3;i< x_size +3;i++)
		back_buf[i][1] = '#';

	tick = 0;
}

//void 

void mugunghwa(void) {
	mugunghwa_init();

	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random(i, -1);
			}
		}

		display();
		Sleep(10);
		tick += 10;
	}
}