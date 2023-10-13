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
			nx = px[p] + randint(-1, 1);
			ny = py[p] + randint(-1, 0);}
	} while (!placable(nx, ny) || ((dir == 1) ? (nx == 0 && ny == 0) : 0) );

	move_tail(p, nx, ny);
}

void m_erase(int *y, int *print_time) {
	// "����ȭ�����Ǿ����ϴ�" �����
	for (int i = 0; i < 30; i += 3) {
		gotoxy(N_ROW, i);
		printf(" ");
		gotoxy(N_ROW, i + 1);
		printf(" ");
	}
	// y �ʱ�ȭ
	*y = 0;
	// ���� "��"�� �� 500ms �� ��� 
	*print_time += 5;
}

// ������ �÷��̾ true�� ���� �� �迭�� ��ȯ
int m_auto_player() {
	//int *player_move[PLAYER_MAX] = { 0 };
	for (int i = 1; i < n_player; i++) {
		// player 1 ���ʹ� 1/10Ȯ���� ���Ƿ� 7�� �������� ��ȯ�� ���
		//if (!player[i]) { player_move[i] = true; }
		//else if (randint(0, 9) == 7) {
		if (randint(0, 9) == 7) {
			m_move_random(i, 1);
			//player_move[i] = true;
		}
	}
	//return player_move ;
}
void m_print(int *y, int *print_time) {
	char m_g_h[50][4] = { {"��"},{"��"},{"ȭ"}, {"��"}, {"��"}, {"��"}, {"��"}, {"��"}, {"��"}, {"��"} }; // "�� �� ȭ �� �� �� �� �� �� ��";
	gotoxy(N_ROW, *y);
	if(*y == 0){ printf("%s", m_g_h[*y/3]); }
	else { printf("%s", m_g_h[*y/3]); }

	*y = *y + 3;
	int a = 5, b = 3, c = randint(0, 1);
	switch (*y) {
	case 0: *print_time += randint(a, a += b + c); break;
	case 3: *print_time += randint(a, a += b + c); break;
	case 6: *print_time += randint(a, a += b + c); break;
	case 9: *print_time += randint(a, a += b + c); break;
	case 12: *print_time += randint(a, a += b + c); break;
	case 15: *print_time += randint(a, a -= b + c); break;
	case 18: *print_time += randint(a, a -= b + c); break;
	case 21: *print_time += randint(a, a -= b + c); break;
	case 24: *print_time += randint(a, a -= b + c); break;
	case 27: *print_time += randint(a, a -= b + c); break;
	}
}

int *player_overlap() {
	int d_true[PLAYER_MAX] = { 0 };
	int p;

	for (int row = 1; row <= N_ROW-2; row++) {
		for (int col = 1; col <= N_COL-2; col++) {
			if (front_buf[row][col] != ' ' && front_buf[row][col] != '#' && front_buf[row][col] != '@') {
				p = front_buf[row][col];
				p = p - 48; // '0' = 48
				d_true[p] = true;
				break;
			}
		}
	}
	return d_true;
}

bool m_player_a_or_d() {
	//int *p_move = m_auto_player();
	int past_tick = tick;
	int r_tick = randint(130, 250) * 10;
	int past_x[PLAYER_MAX] = {0};
	int past_y[PLAYER_MAX] = {0};
	for (int i = 0; i < n_player; i++) {
		past_x[i] = px[i];
		past_y[i] = py[i];
	}

	bool p_0 = player[0];
	while (tick != past_tick + 3000){
		if (tick == r_tick * 10) { 
			draw();
		}

		key_t key = get_key();
		if (key == K_QUIT) {
			return false;
		}
		else if (p_0 && key != K_UNDEFINED) {
			move_manual(key);
			break;
			draw();
		}

		Sleep(10);
		tick += 10;
	}
	int *p_overlap = player_overlap();
	int dead_now[PLAYER_MAX] = { 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 };
	int dn_i = 0;
	for (int i = 0; i < n_player; i++) {
		if (past_x[i] == px[i] && past_y[i] == py[i])
			continue;
		
		if (p_overlap[i]) {
			player[i] = false;
			back_buf[px[i]][py[i]] = ' ';
			dead_now[dn_i] = i;
			dn_i += 1;
		}
	}
	if (dn_i != 0) {
		n_alive -= dn_i;
		// ���̾�α� ��� ������� ��� ������ 
	}
	return true; 
}

bool m_game(int *y, int *print_time) {
	if (*y < 30 && tick >= (*print_time * 100)) {
		m_print(y, print_time);
	}
	else if (*y == 30) {
		// "#"�� "@"�� �ٲ�
		for (int i = 3; i < n_player - 2 + 3; i++) {
			front_buf[i][1] = '@';
			printxy(front_buf[i][1], i, 1);
		}

		key_t key = get_key();
		if (key == K_QUIT) {
			return false;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		// ��, ���� ���� �ڵ�
		bool a_d = m_player_a_or_d();
		*print_time = *print_time + 30;

		if (!a_d) { return false; }

		m_erase(y, print_time);
		return true;
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
		else if (player[0] && key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (player[i] && tick % period[i] == 0) {
				m_move_random(i, -1);
			}
		}

		bool a_d = m_game(&mgh_y, &print_time);
		if (!a_d) { break; }

		display();
		Sleep(10);
		tick += 10;
	}
}