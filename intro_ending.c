#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
    /*
    //printf("********\n********\n     **\n     **\n     **\n     **\n******\n******\n");//�빮�� J
    //printf("**   **\n**   **\n**   **\n**   **\n**   **\n******\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                     <��))))><        <��))))><               \n");
    printf("\n");
    printf("                      <��))))><        <��))))><             \n");
    printf("\n");
    printf("                       <��))))><         <��))))><           \n");
    printf("\n");
    printf("                                     �ߣߣ�    \n");
    printf("                                   <��      >  \n");
    printf("                  ��.���� .����        < ����     > \n");
    printf("                                 <  �� ��     >\n");
    printf("                                 ��  ��      ��\n");
    printf("                                 �� �ܡ�  ��   ��\n");
    printf("                                 ��    �䡡   ��\n");
    printf("        ��[�ơ�]��                 ��          ��\n");
    printf("                                 ��          ��\n");
    printf("        <�ˣ���                  ��          ��\n");
    printf("                                 ���ߣߣߣߣߣ�\n");
    printf("                                  )))))))))))) \n");
    printf("                                  )))))))))))) \n");

    */



    int i, j;
    // int a;
    int num_steps = 100; // ������ �� �ܰ� ��

    printf("Press to game start!(> = press enter)");
    getchar();
    printf("���� ����� �����Ͽ� ��ä���ڿ��� �i��� �λ��� ����ִ�......>");
    getchar();
    printf("�̷��� �������!>");
    getchar();
    printf("���� ���ۿ� ���� ���� �ҹ�����Ʈ�� �˾ƺ��� ���� �߽��� ǥ����ȯ���� ��ȭ���´�  ��.���� .����>");
    getchar();
    printf("�ѳ����б� ���� ���Ͻǿ� ����� �λ��� �ٲ��� ������ �޲ٹ̰����� �ֽ��ϴ�............>");
    getchar();
    printf("������...�޲ٹ̰���? ����ҿ����� ���� ��ȸ�� �Դٴ� ������ ��Ḷ������ �ѳ����б��� ã�ư���.>");
    getchar();

    for (i = 0; i < 100; i++) {
        system("cls"); // ȭ���� ����� ��� (Windows)

        if (i == 15) {
            printf("                 (0_0)??????");
            Sleep(2000);
            system("cls");
            Sleep(2000);
            printf("�������ִ�??????????????????>");
            getchar();
            printf("����..........>");
            getchar();
            printf("�� ������..........................>");
            getchar();
            printf("JJJJ   U   U   GGGG    GGGG    U   U    M   M     II     ????\n");
            printf("  J    U   U  G       G        U   U    MM MM     II     ????\n");
            printf("  J    U   U  G  GGG  G  GGG   U   U    M M M     II     ????\n");
            printf("  J    U   U  G    G  G    G   U   U    M   M     II     ????\n");
            printf("JJJ     UUU    GGGG   GGGGG    UUUUU    M   M     II     ????\n");
            printf(">");
            getchar();
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
        Sleep(300); // �� ���� ���� �ð� ����
    }

    printf("�޲ٹ� ���� ����!>");


    getchar();



    return 0;
}
