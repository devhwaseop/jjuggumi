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

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
int ix[ITEM_MAX], iy[ITEM_MAX], n_created_item;
ITEM created_item[ITEM_MAX];

void nightgame_init(void) {
	// 아이템 갯수 설정
	n_created_item = n_player - 1;
	if (3 > n_player) { n_created_item = 2; }
	map_init(15, 35);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
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
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = randint(1, N_COL - 2);
		} while (!placable(x, y));
		ix[i] = x;
		iy[i] = y;
		period[i] = randint(100, 500);
		
		// 랜덤 아이템 초기화 (조건: 초기화 때 선언)
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
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!n_placable(nx, ny)) {
		return;
	}

	n_move_tail(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤
void n_move_random(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do {
		nx = px[p] + randint(-1, 1);
		ny = py[p] + randint(-1, 1);
	} while (!n_placable(nx, ny));

	n_move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void n_move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

// 아이템을 먹고 나오면 아이템을 표시하기 위한 함수
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
	// x 좌표 이동
	if (current.x < target.x) {
		current.x = (current.x + 1 <= target.x) ? current.x + 1 : target.x;
	}
	else if (current.x > target.x) {
		current.x = (current.x - 1 >= target.x) ? current.x - 1 : target.x;
	}

	// y 좌표 이동
	if (current.y < target.y) {
		current.y = (current.y + 1 <= target.y) ? current.y + 1 : target.y;
	}
	else if (current.y > target.y) {
		current.y = (current.y - 1 >= target.y) ? current.y - 1 : target.y;
	}

	return current;
}

// 두 점의 거리를 계산하는 함수
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
		// player 0만 손으로 움직임(4방향)
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
			char m[30] = { "테스트1/테스트 2" };
			dialog(m, 2);
		}
		*/

		// player 1 부터는 랜덤으로 움직임(8방향)
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