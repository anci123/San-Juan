#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"
#include"function.h"
#include"profession.h"
void producer_action(_player * player, int playerNum, int privilege) {
}
void trader_action(_player * player, int playerNum, int privilege) {}
int main() {
    int start=0;
    _player player[4];
    cardRander();
    memset(player, 0x00, sizeof(player));
    for(int i = 0; i < 4; ++i) {
        player[i].id = i;
        player[i].buildings[0] = 0;
        player[i].numbers_of_buildings = 1;
        player[i].point = 1;
        player[i].cards.id = 0;
        player[i].cards.pNext = NULL;
        for(int j = 0; j < 4; ++j){
            addCard(&player[i],cardHeap[heapIndex]);
            --heapIndex;
        }
        player[i].card_limit = 4;
        player[i].role = 0;
        player[i].pNext = NULL;
    }//初始化四個玩家的struct
    system("clear");
    int level = 1;
    printf("選擇遊戲等級\n(1)level 1\n(2)level 2\n");
    scanf("%d", &level);
    system("clear");
    int playerNum = 0;
    printf("選擇玩家號碼:\n(1)玩家 1\n(2)玩家 2\n(3)玩家 3\n(4)玩家 4\n(5)隨機\n");
    scanf("%d", &playerNum);
    if(playerNum == 5) {
        srand(time(0));
        playerNum = rand() % 4 + 1;
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
        if(ii >= governor) i = ii - governor + 1;
        else i = ii + governor - 1;
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
            else choose = computerChooseRole(usedRole);
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
        }
        for(int j = 0; j < 4; ++j) {
            if(player[j].card_limit < player[j].number_of_cards) {
                if(j + 1 == playerNum) playerDiscard(&player[j]);
                else computerDicard(&player[j]);
            }
        }
        ++governor;
        ++ii;
        if(governor > 4) governor = 1;
    }
    return 0;
}
