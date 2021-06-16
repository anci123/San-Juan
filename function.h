#pragma once
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"
int cardHeap[106];
int heapIndex;//代表現在抽到第幾張
void cardRander() {
    int number = 0;
    int random = time(0);
    int r = 0;
    int repeat = 1;
    memset(cardHeap, 0x00, sizeof(cardHeap));
    heapIndex=105;
    while(number < 106) {
        while(repeat) {
            repeat = 0;
            srand(random);
            r = rand() % 106 + 5;
            for(int i = 0; i <= number; ++i) {
                if(r == cardHeap[i]) {
                    repeat = 1;
                    ++random;
                    break;
                }
            }
        }
        cardHeap[number] = r;
        ++number;
        ++random;
        repeat = 1;
    }
    for(int i = 0; i < 106; ++i) {
        int r = cardHeap[i];
        if(r <= 10) r = 1;
        else if(r <= 42) {
            r -= 11;
            r /= 8;
            r += 2;
        }
        else if(r <= 102) {
            r -= 43;
            r /= 3;
            r += 6;
        }
        else {
            r -= 103;
            r /= 2;
            r += 26;
        }
        cardHeap[i] = r;
    }
}
void addCard(_player *player,int id) {
    card *pHead = &player->cards;
    if( pHead == NULL ) printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
    card *pNewNode = calloc( 1, sizeof( card ) );
    pNewNode -> id = id;
    pNewNode -> pNext = NULL;
    card *pNode = pHead;

    while( pNode -> pNext ) {
        pNode = pNode -> pNext;
    }
    pNode -> pNext = pNewNode;
    ++player->number_of_cards;
}
void discard(_player *player, int order) {
    card *pNode = player->cards.pNext;
    card *pPrev = &player->cards;
    int index = 0;
    while(pNode) {
        ++index;
        if(index == order) {
            pPrev->pNext = pNode->pNext;
            --player->number_of_cards;
            free(pNode);
        }
        pPrev = pNode;
        pNode = pNode->pNext;
    }
}

void printStatus(_player *player, int playerNum) {
    system("clear");
    printf(NONE);
    for(int i = 0; i < 4; ++i) {
        if(i + 1 == playerNum) printf(CYAN);
        int point = 0;
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) point += cardType[player[i].buildings[j]].point;
        printf("玩家%2d\n卡牌數量: %d\n積分:%2d\n", i + 1, player[i].number_of_cards, player[i].point);
        for(int j = 0; j < player[i].numbers_of_buildings; ++j)printf("┌────────────┐ ");
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j)printf("│            │ ");
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j)printf("│            │ ");
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) {
            if(player[i].buildings[j] < 25 && player[i].buildings[j] >= 22) printf("│%6s│ ", cardType[player[i].buildings[j]].ch_name);
            else if (player[i].buildings[j] == 26)printf("│  %4s  │ ", cardType[player[i].buildings[j]].ch_name);
            else printf("│   %3s   │ ", cardType[player[i].buildings[j]].ch_name);
        }
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) {
            if(player[i].buildingInfo->has_product) printf("│┌──────────┐│ ");
            else printf("│            │ ");
        }
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) {
            if(player[i].buildingInfo->has_product) printf("││ SAN JUAN ││ ");
            else printf("│            │ ");
        }
        printf("\n");
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) {
            if(player[i].buildingInfo->has_product) printf("└┴──────────┴┘ ");
            else printf("└────────────┘ ");
        }
        printf("\n");
        if(i + 1 == playerNum) printf(NONE);
    }
}
void printCard(_player *player) {
    system("clear");
    printf(NONE);
    int t = 0;
    card *pCard = player->cards.pNext;
    printf(CYAN"你的卡牌:\n");
    if(pCard == NULL || player->number_of_cards == 0) printf("無\n");
    while(pCard) {
        int id = pCard->id - 1;
        ++t;
        printf("(%d) %s %s:\n    費用: %3d ,積分: %3d\n    效用:%s\n", t, cardType[id].ch_name, cardType[id].en_name, cardType[id].pay, cardType[id].point, cardType[id].effective);
        pCard = pCard->pNext;
    }
    printf(NONE);
}
void checkChoose(_player *player, int playNum) {
    system("clear");
    printf(NONE);
    int c = 0;
    char buffer[10] = {0};
    printf("選擇察看手牌或牌局\n(1)手牌\n(2)排局\n(3)兩者\n");
    scanf("%d", &c);
    switch(c) {
    case 1:
        printCard(&player[playNum - 1]);
        fgets(buffer, 10, stdin);
        break;
    case 2:
        printStatus(player, playNum);
        fgets(buffer, 10, stdin);
        break;
    case 3:
        printCard(&player[playNum - 1]);
        printf("按 ENTER 以繼續\n");
        fgets(buffer, 10, stdin);
        fgets(buffer, 10, stdin);
        printStatus(player, playNum);
        break;
    default:
        printf("無此選項\n");
        break;
    }
    printf("按 ENTER 以繼續\n");
    fgets(buffer, 10, stdin);
}
void playerDiscard(_player *player) {
    int cardDiscard[20];
    int t = player->number_of_cards - player->card_limit;
    printf("請丟棄 %d 張卡牌:\n", t);
    for(int i = 0; i < t; ++i) scanf("%d", &cardDiscard[i]);
    for(int i = 0; i < t; ++i) discard(player, cardDiscard[i]);
}
void computerDicard(_player *player) {
    int i = time(0);
    srand(i);
    int r = rand() % player->number_of_cards;
    while(player->number_of_cards > player->card_limit) {
        srand(i);
        r = rand() % player->card_limit;
        discard(player, r);
        ++i;
    }
}

int computerChooseRole(int *used) {
    int t = time(0);
    int r = 0;
    while(1) {
        srand(t);
        r = rand() % 5;
        ++t;
        if(used[r] != 1) break;
        else continue;
    }
    used[r] = 1;
    return r + 1;
}
int playerChoose(int *used) {
    int choose = 0;
    system("clear");
    printf("請選擇一個角色(灰色代表已選過):\n");
    for(int i = 0; i < 5; ++i) {
        if(used[i]) printf(DARY_GRAY);
        printf("(%d) %s\n", i + 1, roles[i].name);
        printf("    行動： %s\n",roles[i].action);
        printf("    特權： %s\n",roles[i].privilege);
        if(used[i]) printf(NONE);
    }
    scanf("%d", &choose);
    if(used[choose - 1]) {
        system("clear");
        printf(RED"請勿重複選擇\n"NONE);
        sleep(1);
        choose = playerChoose(used);
    }
    used[choose - 1] = 1;
    return choose;
}
