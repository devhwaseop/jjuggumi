#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include <stdlib.h>
#include "canvas.h"
#include <string.h>

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);
void dialog(char message[], int m_num);

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void map_init(int n_row, int n_col) {
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

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

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	// 2 추가
	printf("%22s%11s%9s\n", "intl", "str", "stm");
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s", p, player[p].is_alive ? "alive" : "DEAD");		
		
		printf("%9d(%d)", player[p].intel, item[p].intel_buf);
		printf("%10d(%d)", player[p].str, item[p].str_buf);
		printf("%7d%%\n", player[p].stamina);
	}
}
/*
int char_len(char message[]) {
	int count = 0;
	int size = ((int)sizeof(message) / sizeof(message[0]));
	for (int i = 0; i < size; i++) {
		if (message[i] == '\0') {
			//count++;
			return count;
		}
		else if (i != 0 && !(message[i - 1] & 0x80) && message[i] & 0x80) {
			count += 1;
		}
		else {
			count++;
		}
	}
	return count;
}

// 전글자가 utf-8 이고,
// 현재 글자가 아스키 코드인지 식별하는 함수
int ASCII_id(char message[], int j, int start_message_index) {
	if (j == start_message_index)
		return 0;
	if (message[j - start_message_index - 1] & 0x80 && !(message[j - start_message_index] & 0x80))
		return 1;
	return 0;
}
*/

// message[]를 받아서 '/'를 기준으로 나누어 줄바꿈을 해줌.
// 줄 개수를 따로 "m_num" 변수로 받아서 사용됨. //시간관계와 편의상
void dialog(char message[], int m_num) {
	int mid_row = N_ROW/2 , mid_col = N_COL/2;
	int s_row = mid_row - (m_num > 1 ? 3 : 2), s_col = 2;
	int row = mid_row + (m_num < 3 ? 2 : 3)+1, col = N_COL - 2;
	int num_r = mid_row, num_c = s_col + 2;
	int str_start = num_c + 2;
	int str_end = col - 2;
	int full_str_range = str_end - str_start;
	int message_range = (int)strlen(message); // char_len(message); 

	for (int i = s_row; i < row; i++) {
		for (int j = s_col; j < col; j++) {
			if (i == s_row || i == row-1 || j == s_col || j == col-1)
				front_buf[i][j] = '*';
			else
				front_buf[i][j] = ' ';
			printxy(front_buf[i][j], i, j);
		}
	}

	if (m_num == 1) {
		message_range /= 2; 
		full_str_range /= 2;
		full_str_range -= message_range;
		str_start += full_str_range;
		gotoxy(mid_row, str_start);
		printf("%s", message);
	}
	else {
		int str_arr_n[4] = { 0 };
		for (int i = 0; i < m_num;i++) {
			int j = 0;
			if (i != 0) {
				j = str_arr_n[i]+1;
			}
			for (; j < message_range; j++) {
				if (message[j] == '/') {
					str_arr_n[i + 1] = j;
					break;
				}
			}
				if (str_arr_n[i + 1] == 0) {
					str_arr_n[i + 1] = message_range;
					break;
			}
		}
		int start_x = mid_row - 1;
		for (int i = 0; i < m_num; i++) {
			message_range = (str_arr_n[i + 1]- str_arr_n[i]) /2; // char_len(message);
			int f_s_range = full_str_range / 2;
			f_s_range -= message_range;
			int s_start = str_start + f_s_range;
			for (int l = s_start; l < s_start + str_arr_n[i + 1]; l++) {
				front_buf[start_x][l] = '?';
			}
			gotoxy(start_x, s_start);
			int j = 0;
			if (i != 0) {
				j = str_arr_n[i]+1;
			}
			for (; j < str_arr_n[i + 1]; j++) {
				printf("%c", message[j]);
				// if (i == 0) { printf("%c", message[j]); }
				// else{printf("%c", message[j]); }
			}
			start_x += 1;
		}
	}

	// ASCLL '1' == 49
	for (char i = '1'; i < DIALOG_DURATION_SEC + '1'; i++) {
		front_buf[num_r][num_c] = i;
		printxy(front_buf[num_r][num_c], num_r, num_c);
		Sleep(1000);
	}
}
