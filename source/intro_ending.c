#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <string.h>

void intro(void);
void ending(void);

void intro(void) {
    int i, j;
    // int a;
    int num_steps = 100; // ������ �� �ܰ� ��

    for (i = 0; i < 100; i++) {
        system("cls"); // ȭ���� ����� ��� (Windows)

        if (i == 9) {
            printf("                 (0_0)??????");
            Sleep(500);
            printf("\n");
            system("cls");

            printf("JJJJ   U   U   GGGG    GGGG    U   U    M   M     II     ????\n");
            printf("  J    U   U  G       G        U   U    MM MM     II     ????\n");
            printf("  J    U   U  G  GGG  G  GGG   U   U    M M M     II     ????\n");
            printf("  J    U   U  G    G  G    G   U   U    M   M     II     ????\n");
            printf("JJJ     UUU    GGGG   GGGGG    UUUUU    M   M     II     ????\n");
            Sleep(1200);
            system("cls");

            printf("                                _�ߣߣ�    \n");
            printf("                              <��      >  \n");
            printf("        ��.���� .����             < ����     > \n");
            printf("                            <  �� ��     >\n");
            printf("                            ��  ��      ��\n");
            printf("                            �� �ܡ�  ��   ��\n");
            printf("                            ��    �䡡   ��\n");
            printf("         ��[�ơ�]��           ��          ��\n");
            printf("                            ��          ��\n");
            printf("                            ��          ��\n");
            printf("                            ���ߣߣߣߣߣ�\n");
            printf("                             )))))))))))) \n");
            printf("                             )))))))))))) \n");
            break;
        }
        for (j = 0; j <= i; j++) {

            printf(" "); // �� ĭ �߰�
            if (i == 10 && j == 10) {


            }

        }
        printf("(^ �� ^)\n");
        Sleep(100); // �� ���� ���� �ð� ����
    }

    printf("�޲ٹ� ���� ����!>");
    Sleep(600);

}

void ending(void) {
    system("cls");
    map_init(11, 39);
    map_replace('#', '!');
    draw();
    int mid_x = 11 / 2;
    int mid_y = 39 / 2;
    int alive_p_num = 0;
    int alive_player[PLAYER_MAX] = { 0 };
    for (int i = 0; i < PLAYER_MAX; i++) {
        if (player[i] == true) {
            alive_player[alive_p_num] = i;
            alive_p_num += 1;
        }
    }
    char* ending_str;
    ending_str = (char*)malloc(sizeof(char) * 100);
    char nu[2] = "\0";
    strcpy_s(ending_str, 100, nu);
    // sim_strcat(ending_str, str_main);
    if (alive_p_num == 1) { // n_alive
        char win1[60] = "!!!!!!!!!! �����մϴ�. !!!!!!!!!!";
        char win2[60] = "! �Ʒ��� player�� ������Դϴ�. !";
        char p[2] = { '0' + alive_player[0], NULL };
        sim_strcat(ending_str, p);
        char p_str[10] = " player";
        sim_strcat(ending_str, p_str);
        gotoxy(mid_x - 1, (mid_y - (((int)strlen(win1)) / 2)));
        printf("%s", win1);
        gotoxy(mid_x, (mid_y - (((int)strlen(win2)) / 2)));
        printf("%s", win2);
        gotoxy(mid_x + 1, (mid_y - (((int)strlen(ending_str)) / 2)));
        printf("%s", ending_str);
        free(ending_str);
    }
    else {
        char n_win1[60] = "!! ����ڸ� ������ ���߽��ϴ�. !!";
        char n_win2[60] = "! �Ʒ��� player�� �������Դϴ�. !";
        for (int i = 0; i < alive_p_num; i++) {
            if (i != 0) {
                char str_dot[10] = ", ";
                char dd[2] = { '0' + alive_player[i], NULL };;
                sim_strcat(ending_str, str_dot);
                sim_strcat(ending_str, dd);
                continue;
            }
            else if (i == 0); {
                char d[2] = { '0' + alive_player[i], NULL };
                sim_strcat(ending_str, d);
            }
        }
        char p_str[10] = " player";
        sim_strcat(ending_str, p_str);
        gotoxy(mid_x - 1, (mid_y - (((int)strlen(n_win1)) / 2)));
        printf("%s", n_win1);
        gotoxy(mid_x, (mid_y - (((int)strlen(n_win2)) / 2)));
        printf("%s", n_win2);
        gotoxy(mid_x + 1, (mid_y - (((int)strlen(ending_str)) / 2)));
        printf("%s", ending_str);
        free(ending_str);
    }
    gotoxy(11, 0);
}
