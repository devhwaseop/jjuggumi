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

void mugunghwa_init(void);
bool m_pass_player_r(int player_p);
bool no_p_xy(int x, int y, int dir);
void m_erase(int* y, int* print_time);
void m_auto_player(void);
void m_print(int* y, int* print_time);
int* player_overlap(void);
void sim_strcat(char string[], char last_string[]);
bool m_player_a_or_d(void);
void mugunghwa(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

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
		y = N_COL-2;
		px[i] = x;
		py[i] = y;
		period[i] = randint(123, 130);
		// x세로 y가로
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	for(int i = 3;i< x_size +3;i++)
		back_buf[i][1] = '#';

	tick = 0;
}



bool m_pass_player_r(int player_p) {
	if(!player[player_p].is_alive)
		return false;

	int p_px[PLAYER_MAX] = {0};
	int p_py[PLAYER_MAX] = {0};
	// p_py[0] = 1;
	// p_py[n_player] = 1;
	for (int i = 0; i < n_player; i++) {
		if (i == 0 || i == n_player-1) {
			p_px[i] = i+2;
			p_py[i] = 1;
		}
		else {
			p_px[i] = i+2;
			p_py[i] = 2;
		}
	}

	int p = player_p;
	for (int i = 0; i < n_player + 2; i++) {
		bool a = px[p] == p_px[i];
		bool b = py[p] == p_py[i];
		if(a && b)
			return true;
	}
	return false;
}

bool no_p_xy(int x, int y, int dir) {
	bool a = (y == 1 && (x == 1 || x == N_ROW - 2));
	bool b = ((dir == 1) ? !(x == 0 && y == 0) : 0);
	bool c = !placable(x, y);
	//bool d = 0;
	for (int i = 0; i < PLAYER_MAX; i++) {
		if ((px[i] == N_ROW - 3 && py[i] == 1)) {
			if ((x == N_ROW - 3 || x == N_ROW - 2) && y == 2) {
				return true;
			}
		}
		else if ((px[i] == 2 && py[i] == 1)) {
			if ((x == 1 || x == 2) && y == 2) {
				return true;
			}
		}
	}
	return a || b || c; //|| d;
}

void m_move_random(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx, ny;  // 움직여서 다음에 놓일 자리
	if (m_pass_player_r(p)) {
		return;
	}
	//if (dir == 1) { xy0 = nx == 0 && ny == 0; }
	//else { xy0 = 1; }
	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	

	do {
		// 컴퓨터속도가 빨라 PASS_PLAYER을 감지 후 변경이 되었을 경우 때문에 판정을 넣음
		if (m_pass_player_r(p)) {
			return;
		}
		// 전진 확률 90%
		if (dir != 1) {
			if (!randint(0, 9)) { // 0이 아니면 전진. 확률 90%
				nx = px[p] + randint(-1, 1);
				ny = py[p]; //+ randint(-1, 0); // 후진 안함
			}
			else {
				nx = px[p] + randint(-1, 1);
				ny = py[p] - 1;
			}
		}
		else{
			nx = px[p] + randint(-1, 1);
			ny = py[p] + randint(-1, 0);}
	} while (no_p_xy(nx, ny, dir));

	move_tail(p, nx, ny);
}

void m_erase(int *y, int *print_time) {
	// "무궁화꽃이피었습니다" 지우기
	for (int i = 0; i < 30; i += 3) {
		gotoxy(N_ROW, i);
		printf(" ");
		gotoxy(N_ROW, i + 1);
		printf(" ");
	}
	// y 초기화
	*y = 0;
	// 다음 "무"를 약 500ms 후 출력 
	*print_time += 5;
}

void m_auto_player(void) {
	//int *player_move[PLAYER_MAX] = { 0 };
	for (int i = 1; i < n_player; i++) {
		// player 1 부터는 1/10확률중 임의로 7이 랜덤으로 반환시 사망
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
	char m_g_h[50][4] = { {"무"},{"궁"},{"화"}, {"꽃"}, {"이"}, {"피"}, {"었"}, {"습"}, {"니"}, {"다"} }; // "무 궁 화 꽃 이 피 었 습 니 다";
	gotoxy(N_ROW, *y);
	if(*y == 0){ printf("%s", m_g_h[*y/3]); }
	else { printf("%s", m_g_h[*y/3]); }

	*y = *y + 3;
	int a = 5 + (*y / 3), b = a - ( *y / 3 - 4)*2 , c = randint(0, 1);
	switch (*y) {
	// case 0:
	case 3:
	case 6:
	case 9:
	case 12: *print_time += (a + c); break;
	case 15:
	case 18:
	case 21:
	case 24:
	case 27: *print_time += (b - c); break;
	}
}

int *player_overlap(void) {
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

void sim_strcat(char string[], char last_string[]) {
	int string_num = (int)strlen(string);
	int last_string_num = (int)strlen(last_string);
	//int string_range = (int)strlen(*string);
	//for (int i = 0; i < string_range; i++) {
	//	if (*string[i] == "\0") { string_num = i; break; }
	//}
	for (int i = 0; i < last_string_num; i++) {
		string[string_num + i] = last_string[i];
	}
	string[string_num + last_string_num] = NULL;
}

bool m_player_a_or_d(void) {
	//int *p_move = m_auto_player();
	int past_tick = tick;
	int r_tick = randint(130, 250) * 10;
	int past_x[PLAYER_MAX] = {0};
	int past_y[PLAYER_MAX] = {0};
	for (int i = 0; i < n_player; i++) {
		past_x[i] = px[i];
		past_y[i] = py[i];
	}

	bool p_0 = player[0].is_alive;
	while (tick != past_tick + 3000){
		if (tick == (past_tick + r_tick * 10)) {
			draw();
		}

		key_t key = get_key();
		if (key == K_QUIT) {
			return false;
		}
		else if (p_0 && key != K_UNDEFINED) {
			move_manual(key);
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
			player[i].is_alive = false;
			back_buf[px[i]][py[i]] = ' ';
			dead_now[dn_i] = i;
			dn_i += 1;
		}
	}

	if (dn_i != 0) {
		n_alive -= dn_i;
		//char end_string[100] = { NULL };
		char *end_string;
		end_string = (char*)malloc(sizeof(char) * 100);
		char str_main[50] = "탈락자는 아래와 같습니다./";
		strcpy_s(end_string, 100, str_main);
		int strnum = 2;
		for (int i = 0; i < dn_i; i++) {
			if (i == 0 || i == 6); {
				char *d = "0" + dead_now[i];
				sim_strcat(end_string, d);
			}
			if (i != 0) {
				char str_dot[10] = ", ";
				char* dd = "0" + dead_now[i];
				sim_strcat(end_string, str_dot);
				sim_strcat(end_string, dd);
			}
			if (i == 5) {
				char str_dot[10] = ", ";
				sim_strcat(end_string, str_dot);
				char sl[2] = { '/', NULL };
				sim_strcat(end_string, sl);
				strnum = 3;
			}
		}
		char str_player[10] = " player";
		sim_strcat(end_string, str_player);
		dialog(end_string, strnum);
		free(end_string);
	}
	return true; 
}

bool m_game(int *y, int *print_time) {
	if (*y < 30 && tick >= (*print_time * 100)) {
		m_print(y, print_time);
	}
	else if (*y == 30) {
		// "#"을 "@"로 바꿈
		for (int i = 3; i < n_player - 2 + 3; i++) {
			back_buf[i][1] = '@';
			//printxy(front_buf[i][1], i, 1);
		}
		draw();

		//key_t key = get_key();
		//if (key == K_QUIT) {
		//	return false;
		//}
		//else if (key != K_UNDEFINED) {
		//	move_manual(key);
		//}

		// 삶, 죽음 판정 코드
		bool a_d = m_player_a_or_d();
		*print_time = *print_time + 30;

		if (!a_d) { return false; }
		
		for (int i = 3; i < n_player - 2 + 3; i++) {
			back_buf[i][1] = '#';
			//printxy(front_buf[i][1], i, 1);
		}
		draw();
		
		m_erase(y, print_time);
		return true;
	}
}

void mugunghwa(void) {
	mugunghwa_init();
	int *print_time;
	print_time = 5;
	int pt_bff = 0;
	int *mgh_y = 0;
	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (player[0].is_alive && key != K_UNDEFINED) {
			move_manual(key);
		}

		// player 1 부터는 랜덤으로 움직임(8방향)
		int map_mid = N_COL / 2 -1;
		for (int i = 1; i < n_player; i++) {
			if(player[i].is_alive && py[i] <= map_mid) {
				if (tick % (period[i] / 2) <= 10) {
					m_move_random(i, -1);
				}
			}
			else if (player[i].is_alive && tick % period[i] == 0) {
				m_move_random(i, -1);
			}
		}

		bool a_d = m_game(&mgh_y, &print_time);
		if (!a_d) { break; }
		else if (mgh_y == 30 && print_time >= 250) {
			// 종료 코드
			//int n_en = 0;
			char* end_string;
			end_string = (char*)malloc(sizeof(char) * 100);
			//*end_string = "생존자는 아래와 같습니다/";
			char str_main[50] = "생존자는 아래와 같습니다./";
			char nu[2] = "\0";
			strcpy_s(end_string, 100, nu);
			sim_strcat(end_string, str_main);
			char str_num[20][2] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
			int start_tf = 0;
			int strnum = 2;
			for (int i = 0; i < n_player; i++) {
				if (m_pass_player_r(i)) {
					if (start_tf == 0 || start_tf == 6) {
						sim_strcat(end_string, str_num[i]);
						start_tf++;
						continue;
					}
					else {
						char str_dot[10] = ", ";
						//char *dd = &i;
						sim_strcat(end_string, str_dot);
						sim_strcat(end_string, str_num[i]);
					}
					if (start_tf == 5) {
						char str_dot[10] = ", ";
						//char *dd = &i;
						sim_strcat(end_string, str_dot);
						char sl[2] = { '/', NULL};
						sim_strcat(end_string, sl);
						strnum = 3;
					}
					start_tf++;
				}
				else{
					player[i].is_alive = false;
					n_alive -= 1;
				}
			}

			char str_player[10] = " player";
			sim_strcat(end_string, str_player);
			dialog(end_string, strnum);
			free(end_string);
			display();
			Sleep(200);
			break;
		}


		display();
		Sleep(10);
		tick += 10;
	}
}