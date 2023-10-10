#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <stdbool.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void mugunghwa_init(void);
void map_replace(char a, char b);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

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
		// y�� ������ ����
		x += 1;
		y = 33;
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);
		// x���� y����
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	for(int i = 3;i< x_size +3;i++)
		back_buf[i][1] = '#';

	tick = 0;
}

void map_replace(char a, char b) {
	// map�� a�� b�� ����
	for (int i = 0; i < N_ROW; i++) {
		for (int j = 0; j < N_COL; j++) {
			if (back_buf[i][j] == a) {
				back_buf[i][j] = b;
			}
		}
	}
}

void m_move_random(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�
	int xy0 = 1;
	
	//if (dir == 1) { xy0 = nx == 0 && ny == 0; }
	//else { xy0 = 1; }
	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	do {
		// ���� Ȯ�� 1/2
		if (dir != 1) {
			if (randint(0, 1)) {
				nx = px[p] + randint(-1, 1);
				ny = py[p] + randint(-1, 0); // ���� ����
			}
			else {
				nx = px[p] + randint(-1, 1);
				ny = py[p] - 1;
			}
		}
		else{
			xy0 = nx == 0 && ny == 0;
			nx = px[p] + randint(-1, 1);
			ny = py[p] + randint(-1, 0);
		}
	} while (!placable(nx, ny) && xy0);

	move_tail(p, nx, ny);
}

void mugunghwa_string(int *y, int *print_time) {
	int x = N_ROW;
	if (*y == 30) {
		for (int i = 3; i < n_player - 2 + 3; i++){
			front_buf[i][1] = '@';
		printxy(front_buf[i][1], i, 1);
		}
		key_t key = get_key();
		if (key == K_QUIT) {
			return K_QUIT;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			// player 1 ���ʹ� 1/10Ȯ���� ���Ƿ� 7�� �������� ��ȯ�� ���
			if (randint(0, 9) == 7) {
				m_move_random(i, 1);
				//player[i] = false;
			}
		}

		// ��� ���� ���� �ڵ� ��������

		// "����ȭ�����Ǿ����ϴ�" �����
		for (int i = 0; i < 30; i+=3) {
			gotoxy(x, i);
			printf(" ");
			gotoxy(x, i+1);
			printf(" ");
		}
		// y �ʱ�ȭ
		*y = 0;
		// ���� "��"�� �� 500ms �� ��� 
		*print_time += 5;
	}
	if (*y < 30 && tick >= (*print_time * 100)) {
		char m_g_h[50] = "�� �� ȭ �� �� �� �� �� �� ��";
		gotoxy(x, *y);
		printf("%c%c", m_g_h[*y], m_g_h[*y+1]);
		
		*y = *y + 3;
		int a = 5, b = 3, c = randint(0, 1);
		switch (*y) {
		case 0: *print_time += randint(a, a += b +c); break;
		case 3: *print_time += randint(a, a += b +c); break;
		case 6: *print_time += randint(a, a += b +c); break;
		case 9: *print_time += randint(a, a += b +c); break;
		case 12: *print_time += randint(a, a += b +c); break;
		case 15: *print_time += randint(a, a -= b +c); break;
		case 18: *print_time += randint(a, a -= b +c); break;
		case 21: *print_time += randint(a, a -= b +c); break;
		case 24: *print_time += randint(a, a -= b +c); break;
		case 27: *print_time += randint(a, a -= b +c); break;
		}

	}
}

void mugunghwa(void) {
	mugunghwa_init();
	int *print_time = 5;
	int pt_bff = 0;
	int *mgh_y = 0;
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
				m_move_random(i, -1);
			}
		}

		mugunghwa_string(&mgh_y, &print_time);

		display();
		Sleep(10);
		tick += 10;
	}
}