#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void mugunghwa_init(void);


int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void mugunghwa_init(void) {
	map_init(11, 35);
	int start_x = 9 / 2 - n_player / 2;
	int x = start_x, y ;
	for (int i = 0; i < n_player; i++) {
		// y�� ������ ����
		x += 1;
		y = 33;
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);
		// x���� y����
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	for(int i = 3;i<5+3;i++)
		back_buf[i][1] = '@';

	tick = 0;
}

void mugunghwa(void) {
	mugunghwa_init();

	system("cls");
	display();
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
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