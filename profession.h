#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"struct.h"
#include"function.h"
#include"struct.h"
int buildPayment(_player *player, int order, int discount, int *pay) {
    card *pNode = player->cards.pNext;
    int id = -1;
    int t = 0;
    while(pNode) {
        ++t;
        if(t == order) {
            id = pNode->id - 1;
            break;
        }
        pNode = pNode->pNext;
    }
    *pay = cardType[id].pay - discount;
    if(*pay < 0) pay = 0;
    return id;
}
void Build(_player *player, int num, int id) {
    system("clear");
    player->buildings[player->numbers_of_buildings] = id;
    ++player->numbers_of_buildings;
    system("clear");
    printf(BROWN);
    printf("玩家%2d 建造 %s\n", num, cardType[id].ch_name);
    sleep(2);
}
void builder_action(_player *player, int playerNum, int privilege) {
    int i = 0;
    for(int ii = 1; ii <= 4; ++ii) {
        system("clear");
        int choose = 0;
        int discardArray[10] = {0};
        int pay = -10;
        int discount = 0;
        int id = 0;
        if(ii >= privilege) i = ii + privilege - 1;
        else i = ii + privilege - 1;
        if(i > 4) i -= 4;
        if(i == privilege) discount = 1;
        if(i == privilege && player[i - 1].specials.Library) discount = 2;
        if(i == playerNum) {
            printCard(&player[i - 1]);
            printf(BROWN"請選擇一個建築建造，或是輸入 -1 不建造\n");
            scanf("%d", &choose);
            if(choose > 0 && choose <= player[i - 1].number_of_cards) {
                id = buildPayment(&player[i - 1], choose, discount, &pay);
                if((player[i - 1].specials.Smithy && id < 5) || (player[i - 1].specials.Quarry && id >= 5)) {
                    --pay;
                    if(pay < 0) pay = 0;
                }
                if(pay < player[i - 1].number_of_cards) {
                    discard(&player[i - 1], choose);
                    int amount_of_cards = player[i - 1].number_of_cards - pay;
                    if(pay == 0) {
                        Build(&player[i - 1], i, id);
                    }
                    else if(amount_of_cards == 0) {
                        for(int j = 1; j <= pay; ++j) discard(&player[i - 1], 1);
                        Build(&player[i - 1], i, id);
                    }
                    else {
                        printCard(&player[i - 1]);
                        printf(BROWN"請選擇 %2d張牌丟棄\n", pay);
                        int j = 0;
                        int offset=0;
                        while(1) {
                            scanf("%d", &discardArray[j]);
                            if(j != 0) {
                                if(discardArray[j - 1] < discardArray[j]){
                                    ++offset;
                                    discard(&player[i - 1], discardArray[j] - offset);
                                }
                                else discard(&player[i - 1], discardArray[j]);
                            }
                            else discard(&player[i - 1], discardArray[j]);
                            if(player[i - 1].number_of_cards <= amount_of_cards) break;
                            ++j;
                        }
                        Build(&player[i - 1], i, id);
                    }
                }
                else {
                    pay = -1;
                    printf(BROWN"當前卡牌數量不足以支付\n");
                }
            }
            else if(choose == -1) printf(BROWN"玩家%2d 選擇不建造\n", i);
            else printf(BROWN"無此卡牌\n");
            sleep(2);
        }
        else {
            int choose = 0;
            card *pCard = &player[i - 1].cards;
            while(pCard) {
                ++choose;
                if(choose > 0 && choose <= player[i - 1].number_of_cards) {
                    id = buildPayment(&player[i - 1], choose, discount, &pay);
                    if((player[i - 1].specials.Smithy && id < 5) || (player[i - 1].specials.Quarry && id >= 5)) {
                        --pay;
                        if(pay < 0) pay = 0;
                    }
                    if(pay < player[i - 1].number_of_cards) {
                        discard(&player[i - 1], choose);
                        for(int j = 1; j <= pay; ++j) discard(&player[i - 1], 1);
                        Build(&player[i - 1], i, id);
                        break;
                    }
                }
                pCard = pCard->pNext;
            }
            if(pay < 0) {
                printf(BROWN"玩家%2d 選擇不建造\n", i);
                sleep(2);
            }
        }
        if(pay >= 0 && id > 5 && player[i - 1].specials.Well) {
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        if(pay >= 0 && player[i - 1].number_of_cards == 0 && player[i - 1].specials.PoorHouse) {
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        if(i == playerNum) checkChoose(player, i);
    }
    printf(NONE);
}

int computerProspecter() {
    srand(time(0));
    int choose = rand() % 4 + 1;
    return choose;
}

void prospector_action(_player * player, int playerNum, int privilege) {
    int choose = 0, id[4] = {0}, success = 1, keep = 1;
    if(player[privilege - 1].specials.Library) {
        keep = 2;
        for(int i = 0; i < keep; ++i) {
            addCard(&player[privilege - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
    }
    else if(player[privilege - 1].specials.GoldMine) {
        for(int i = 0; i < 4; ++i) id[i] = cardHeap[heapIndex - i];
        for(int i = 0; i < 4; ++i) {
            for(int j = i + 1; j < 4; ++j) {
                if(id[i] == id[j]) {
                    printf("挖礦失敗(有兩張卡費用相同)\n");
                    success = 0;
                    keep = 0;
                    sleep(2);
                    break;
                }
            }
        }
        if(success) {
            if(playerNum != privilege) {
                for(int i = 1; i <= 4; ++i) {
                }
                choose = computerProspecter();
            }
            else {
                for(int i = 0; i < 4; ++i) {
                    printf("(%d) %s %s:\n費用: %3d ,積分: %3d\n效用:\n%s\n", i + 1, cardType[id[i]].ch_name, cardType[id[i]].en_name, cardType[id[i]].pay, cardType[id[i]].point, cardType[id[i]].effective);
                }
                printf("請選擇保留一張卡片\n");
                scanf("%d", &choose);
                sleep(2);
            }
            addCard(&player[privilege - 1], id[choose - 1] + 1);
        }
    }
    else {
        addCard(&player[privilege - 1], cardHeap[heapIndex]);
        --heapIndex;
    }
    system("clear");
    printf(YELLOW"玩家%2d增加%2d張手牌\n", privilege, keep);
    sleep(2);
    printf(NONE);
    system("clear");
    if(privilege == playerNum) checkChoose(player, playerNum);
}


void councillor_Archive(_player *player, int drawCard, int keep, bool isPlayer) {
    int choose[20],offset=0;
    for(int i = 0; i < drawCard; ++i) {
        addCard(player, cardHeap[heapIndex]);
        --heapIndex;
    }
    if(isPlayer) {
        printf(PURPLE);
        printCard(player);
        printf("請選擇丟棄%2d張卡牌\n", drawCard - keep);
        for(int j = 0; j < drawCard - keep; ++j) {
            scanf("%d", &choose[j]);
            if(j != 0) {
                if(choose[j - 1] < choose[j]){
                    ++offset;
                    discard(player, choose[j] - offset);
                }
                else discard(player, choose[j]);
            }
            else discard(player, choose[j]);
        }
    }
    else for(int j = 0; j < drawCard - keep; ++j) discard(player, 1);
}
void councillor_action(_player * player, int playerNum, int privilege) {
    for(int ii = 1; ii <= 4; ++ii) {
        int i = 0, keep = 1, drawCard = 2, id[10] = {0}, choose[5] = {0};
        if(ii >= privilege) i = ii + privilege - 1;
        else i = ii + privilege - 1;
        if(i > 4) i -= 4;
        if(player[i - 1].specials.Prefecture) keep = 2;
        if(i == privilege) drawCard = 5;
        if(i == privilege && player[i - 1].specials.Library) drawCard = 8;
        if(player[i - 1].specials.Archive) {
            if(playerNum == i) {
                councillor_Archive(&player[i - 1], drawCard, keep, true);
                checkChoose(player, playerNum);
            }
            else councillor_Archive(&player[i - 1], drawCard, keep, false);
        }
        else {
            for(int j = 0; j < drawCard; ++j) id[j] = cardHeap[heapIndex - j];
            heapIndex -= drawCard;
            if(i != playerNum) {
                for(int k = 0; k < keep; ++k) {
                    choose[k] = k;
                    addCard(&player[i - 1], id[choose[k]]);
                }
            }
            else {
                printf(PURPLE);
                printf("請選擇保留%2d張卡牌\n", keep);
                for(int k = 1; k <= drawCard; ++k) {
                    printf("(%d) %s %s:\n    費用: %3d ,積分: %3d\n    效用:%s\n", k, cardType[id[k - 1] - 1].ch_name, cardType[id[k - 1] - 1].en_name, cardType[id[k - 1] - 1].pay, cardType[id[k - 1] - 1].point, cardType[id[k - 1] - 1].effective);
                }
                for(int j = 0; j < keep; ++j) {
                    scanf("%d", &choose[j]);
                    if(j != 0) {
                        if(choose[j - 1] < choose[j]) {
                            discard(player, choose[j] - 1);
                            checkChoose(player, playerNum);
                        }
                        else discard(player, choose[j]);
                    }
                }
                checkChoose(player, playerNum);
            }
        }
        printf(PURPLE);
        system("clear");
        printf("玩家%2d保留%2d張卡牌\n", i, keep);
        sleep(2);
    }
    printf(NONE);
}
