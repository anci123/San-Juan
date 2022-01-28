#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"
#include"function.h"
#include"profession.h"
int main() {
    printStart();
    //int start = 0;
    int end = 0;
    _player player[4];
    cardRander();
    memset(player, 0x00, sizeof(player));
    for(int i = 0; i < 4; ++i) {
        for(int k = 0; k < 12; ++k) player[i].buildings[k] = -1;
        player[i].buildings[0] = 0;
        player[i].numbers_of_buildings = 1;
        player[i].point = 1;
        player[i].cards.id = 0;
        player[i].cards.pNext = NULL;
        player[i].specials.byte = 0;
        player[i].card_under = 0;
        player[i].id = i;
        for(int j = 0; j < 4; ++j) {
            addCard(&player[i], cardHeap[heapIndex]);
            --heapIndex;
        }
        player[i].card_limit = 4;
    }//初始化四個玩家的struct
    system("clear");
    int playerNum = 0;
    printf("選擇玩家號碼:\n(1)玩家 1\n(2)玩家 2\n(3)玩家 3\n(4)玩家 4\n(5)隨機\n");
    scanf("%d", &playerNum);
    if(playerNum == 5) {
        srand(time(0));
        playerNum = rand() % 4 + 1;
    }
    system("clear");
    for(int k = 0; k < 4; ++k) {
        if(k + 1 != playerNum) {
            while(level[k] < 1 || level[k] > 2) {
                printf("選擇玩家%2d 遊戲等級\n(1)level 1\n(2)level 2\n", k + 1);
                scanf("%d", &level[k]);
            }
        }
    }
    system("clear");
    checkChoose(player, playerNum);
    for(int i = 0; i < 4; ++i) player[i].card_limit = 7;
    int governor = rand() % 4 + 1;
    int ii = 0;
    while(1) {
        ii %= 4 + 1;
        int i = 0;
        int usedRole[5] = {0};
        i = ii + governor - 1;
        if(i > 4)i -= 4;
        system("clear");
        printf(BLUE"玩家 %d 是總督(從他開始)\n", governor);
        sleep(2);
        printf(NONE);
        for(int jj = 1; jj <= 4; ++jj) {
            int j = 0;
            int choose = 0;
            if(jj >= governor) j = jj + governor - 1;
            else j = jj + governor - 1;
            if(j > 4) j -= 4;

            if(j == playerNum) choose = playerChoose(usedRole);
            else {
                if(level[j - 1] == 1) choose = computerChooseRole(usedRole);
                else if(level[j - 1] == 2) choose = computerChooseRole_level2(usedRole);
            }
            system("clear");
            printf(GREEN"玩家%2d 選擇 %s\n", j, roles[choose - 1].name);
            sleep(2);
            printf(NONE);
            switch(choose) {
            case 1:
                builder_action(player, playerNum, j);
                break;
            case 2:
                producer_action(player, playerNum, j);
                break;
            case 3:
                trader_action(player, playerNum, j);
                break;
            case 4:
                councillor_action(player, playerNum, j);
                break;
            case 5:
                prospector_action(player, playerNum, j);
                break;
            default:
                break;
            }
            if(player[j - 1].specials.build.Chapel) Chapel(&player[j - 1], playerNum, j);
        }
        /*for(int jj = 1; jj <= 4; ++jj) {
            int j = 0;
            if(jj >= governor) j = jj + governor - 1;
            else j = jj + governor - 1;
            if(j > 4) j -= 4;
        }*/
        for(int k = 0; k < 4; ++k) {
            if(player[k].numbers_of_buildings == 12) {
                printEND();
                system("clear");
                end = 1;
                break;
            }
        }
        if(end == 1)break;
        for(int k = 0; k < 4; ++k) {
            if(player[k].card_limit < player[k].number_of_cards) {
                if(k + 1 == playerNum) playerDiscard(&player[k]);
                else computerDicard(&player[k]);
            }
        }
        ++governor;
        ++ii;
        if(governor > 4) governor = 1;
        if(end) break;
    }
    countPoint(player);
    return 0;
}
