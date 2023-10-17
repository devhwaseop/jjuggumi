#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
    /*
    //printf("********\n********\n     **\n     **\n     **\n     **\n******\n******\n");//대문자 J
    //printf("**   **\n**   **\n**   **\n**   **\n**   **\n******\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                     <º))))><        <º))))><               \n");
    printf("\n");
    printf("                      <º))))><        <º))))><             \n");
    printf("\n");
    printf("                       <º))))><         <º))))><           \n");
    printf("\n");
    printf("                                     ＿＿＿    \n");
    printf("                                   <　      >  \n");
    printf("                  ♪.¸♬ .¸♬        < 　　     > \n");
    printf("                                 <  　 　     >\n");
    printf("                                 ｜  　      ｜\n");
    printf("                                 ｜ ●　  ●   ｜\n");
    printf("                                 ｜    ▽　   ｜\n");
    printf("        ミ[°°]ミ                 ｜          ｜\n");
    printf("                                 ｜          ｜\n");
    printf("        <ニ：ミ                  ｜          ｜\n");
    printf("                                 ｜＿＿＿＿＿｜\n");
    printf("                                  )))))))))))) \n");
    printf("                                  )))))))))))) \n");

    */



    int i, j;
    // int a;
    int num_steps = 100; // 움직일 총 단계 수

    printf("Press to game start!(> = press enter)");
    getchar();
    printf("나는 사업에 실패하여 사채업자에게 쫒기는 인생을 살고있다......>");
    getchar();
    printf("이렇게 살순없어!>");
    getchar();
    printf("나는 구글에 많은 도박 불법사이트를 알아보던 도중 발신자 표시전환으로 전화가온다  ♪.¸♬ .¸♬>");
    getchar();
    printf("한남대학교 공대 지하실에 당신의 인생을 바꿔줄 전설의 쭈꾸미게임이 있습니다............>");
    getchar();
    printf("전설의...쭈꾸미게임? 고민할여지가 없이 기회가 왔다는 생각에 들뜬마음으로 한남대학교를 찾아간다.>");
    getchar();

    for (i = 0; i < 100; i++) {
        system("cls"); // 화면을 지우는 명령 (Windows)

        if (i == 15) {
            printf("                 (0_0)??????");
            Sleep(2000);
            system("cls");
            Sleep(2000);
            printf("뭔가가있다??????????????????>");
            getchar();
            printf("설마..........>");
            getchar();
            printf("그 전설의..........................>");
            getchar();
            printf("JJJJ   U   U   GGGG    GGGG    U   U    M   M     II     ????\n");
            printf("  J    U   U  G       G        U   U    MM MM     II     ????\n");
            printf("  J    U   U  G  GGG  G  GGG   U   U    M M M     II     ????\n");
            printf("  J    U   U  G    G  G    G   U   U    M   M     II     ????\n");
            printf("JJJ     UUU    GGGG   GGGGG    UUUUU    M   M     II     ????\n");
            printf(">");
            getchar();
            system("cls");

            printf("                                _＿＿＿    \n");
            printf("                              <　      >  \n");
            printf("        ♪.¸♬ .¸♬             < 　　     > \n");
            printf("                            <  　 　     >\n");
            printf("                            ｜  　      ｜\n");
            printf("                            ｜ ●　  ●   ｜\n");
            printf("                            ｜    ▽　   ｜\n");
            printf("         ミ[°°]ミ           ｜          ｜\n");
            printf("                            ｜          ｜\n");
            printf("                            ｜          ｜\n");
            printf("                            ｜＿＿＿＿＿｜\n");
            printf("                             )))))))))))) \n");
            printf("                             )))))))))))) \n");
            break;
        }
        for (j = 0; j <= i; j++) {

            printf(" "); // 빈 칸 추가
            if (i == 10 && j == 10) {


            }

        }
        printf("(^ ∇ ^)\n");
        Sleep(300); // 각 스텝 간의 시간 간격
    }

    printf("쭈꾸미 게임 시작!>");


    getchar();



    return 0;
}
