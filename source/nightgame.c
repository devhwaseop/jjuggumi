#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void nightgame_init(void);
void n_move_manual(key_t key);
void n_move_random(int i, int dir);
void n_move_tail(int i, int nx, int ny);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
int ix[ITEM_MAX], iy[ITEM_MAX], n_created_item;
ITEM created_item[ITEM_MAX];

void nightgame_init(void) {
	// ������ ���� ����
	n_created_item = n_player - 1;
	if (3 > n_player) { n_created_item = 2; }
	map_init(15, 35);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = 600; //randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}

	for (int i = 0; i < n_created_item; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		ix[i] = x;
		iy[i] = y;
		period[i] = randint(100, 500);
		
		// ���� ������ �ʱ�ȭ (����: �ʱ�ȭ �� ����)
		created_item[i] = item[randint(0, ITEM_MAX)];
		
		back_buf[ix[i]][iy[i]] = 'I';  //
	}

	tick = 0;
}

bool n_placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		(back_buf[row][col] != ' ' &&
		back_buf[row][col] != 'I')) {
		return false;
	}
	return true;
}

void n_move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!n_placable(nx, ny)) {
		return;
	}

	n_move_tail(0, nx, ny);
}

// 0 <= dir < 4�� �ƴϸ� ����
void n_move_random(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�

	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	

	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!n_placable(nx, ny));

	n_move_tail(p, nx, ny);
}

// back_buf[][]�� ���
void n_move_tail(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

// �������� �԰� ������ �������� ǥ���ϱ� ���� �Լ�
void item_mark(void) {
	for (int i = 0; i < n_created_item; i++) {
		int x = ix[i];
		int y = iy[i];
		if (back_buf[x][y] == ' ') {
			back_buf[x][y] = 'I';
		}
	}
	return;
}

typedef struct {
	int x;
	int y;
} Point;

Point moveTowards(Point target, Point current) {
	// x ��ǥ �̵�
	if (current.x < target.x) {
		current.x = (current.x + 1 <= target.x) ? current.x + 1 : target.x;
	}
	else if (current.x > target.x) {
		current.x = (current.x - 1 >= target.x) ? current.x - 1 : target.x;
	}

	// y ��ǥ �̵�
	if (current.y < target.y) {
		current.y = (current.y + 1 <= target.y) ? current.y + 1 : target.y;
	}
	else if (current.y > target.y) {
		current.y = (current.y - 1 >= target.y) ? current.y - 1 : target.y;
	}

	return current;
}

// �� ���� �Ÿ��� ����ϴ� �Լ�
Point calculateDistance(int p) {
	//double distance_player[PLAYER_MAX] = { 0 };
	//double distance_item[ITEM_MAX] = { 0 };
	double distance = 0.0;
	typedef struct{
		char p_or_i;
		int index;
		double distance;
	} distance_struct;
	distance_struct ds = { 'p', INT_MAX, 1000.0};
	for (int i = 0; i < n_player; i++) {
		if (i == p) { continue; }
		distance = sqrt(pow(px[i] - px[p], 2) + pow(py[i] - py[p], 2));
		if (distance < ds.distance) {
			ds.distance = distance;
			ds.index = i;
		}
	}
	
	for (int i = 0; i < n_created_item; i++) {
		distance = sqrt(pow(px[i] - px[p], 2) + pow(py[i] - py[p], 2));
		if (distance < ds.distance) {
			ds.p_or_i = 'I';
			ds.distance = distance;
			ds.index = i;
		}
	}
	Point r = {0, 0};
	if (ds.p_or_i == 'I') {
		r.x = ix[ds.index];
		r.y = iy[ds.index];
	}
	else if (ds.p_or_i == 'p') {
		r.x = px[ds.index];
		r.y = py[ds.index];
	}
	return r; //sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int get_player_item(int p) {
	for (int i = 0; i < n_created_item; i++) {
		if (px[p] == ix[i] && py[p] == iy[i]) {
			return i;
		}
	}
	return -1;	
}

void nightgame(void) {
	nightgame_init();

	system("cls");
	display();
	
	Point move;
	Point a_player;
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			n_move_manual(key);
		}

		/*
		if (get_player_item(0) != -1) {
			ix[px[0]] = -1;
			iy[py[0]] = -1;
			char m[30] = { "�׽�Ʈ1/�׽�Ʈ 2" };
			dialog(m, 2);
		}
		*/

		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				a_player.x = px[i];
				a_player.y = py[i];
				move = calculateDistance(i);
				move = moveTowards(move, a_player);

				if (!n_placable(move.x, move.y)) {
					do {
						move.x = px[i] + randint(-1, 1);
						move.y = py[i] + randint(-1, 1);
					} while (!n_placable(move.x, move.y));
				}

				n_move_tail(i, move.x, move.y);

				// n_move_random(i, -1);
			}
		}

		//item_mark();
		display();
		Sleep(10);
		tick += 10;
	}
}