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
void discard(_player *player, int order);
void printStart() {
    system("clear");
    printf(LIGHT_GREEN);
    printf(" ____    _    _   _       _ _   _   _    _   _\n");
    printf("/ ___|  / \\  | \\ | |     | | | | | / \\  | \\ | |\n");
    printf("\\___ \\ / _ \\ |  \\| |  _  | | | | |/ _ \\ |  \\| |\n");
    printf(" ___) / ___ \\| |\\  | | |_| | |_| / ___ \\| |\\  |\n");
    printf("|____/_/   \\_\\_| \\_|  \\___/ \\___/_/   \\_\\_| \\_|\n");
    sleep(2);
    system("clear");
    printf(BROWN);
    printf(" ____ _____  _    ____ _____\n");
    printf("/ ___|_   _|/ \\  |  _ \\_   _|\n");
    printf("\\___ \\ | | / _ \\ | |_) || |\n");
    printf(" ___) || |/ ___ \\|  _ < | |\n");
    printf("|____/ |_/_/   \\_\\_| \\_\\|_|\n");
    usleep(1000000);
    system("clear");
    printf("\n");
    printf("/ ___|_   _|/ \\  |  _ \\_   _|\n");
    printf("\\___ \\ | | / _ \\ | |_) || |\n");
    printf(" ___) || |/ ___ \\|  _ < | |\n");
    printf("|____/ |_/_/   \\_\\_| \\_\\|_|\n");
    usleep(50000);
    system("clear");
    printf("\n\n\\___ \\ | | / _ \\ | |_) || |\n ___) || |/ ___ \\|  _ < | |\n|____/ |_/_/   \\_\\_| \\_\\|_|\n");
    usleep(50000);
    system("clear");
    printf("\n\n\n ___) || |/ ___ \\|  _ < | |\n|____/ |_/_/   \\_\\_| \\_\\|_|\n");
    usleep(50000);
    system("clear");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("|____/ |_/_/   \\_\\_| \\_\\|_|\n");
    usleep(50000);
    system("clear");
    printf(NONE);
}
void printEND() {
    printf(" _____ _   _ ____\n");
    printf("| ____| \\ | |  _ \\\n");
    printf("|  _| |  \\| | | | |\n");
    printf("| |___| |\\  | |_| |\n");
    printf("|_____|_| \\_|____/\n");
    sleep(2);
}
void countPoint(_player *player) {
    system("clear");
    int point[4] = {0}, GuildHall[4] = {0}, CityHall[4] = {0}, TriumhalArch[4] = {0}, hall[4] = {0}, Palace[4] = {0}, building[4] = {0}, MaxIndex[4] = {0}, Chapel[4] = {0}, numMax = 0;
    for(int i = 0; i < 4; ++i) {
        int BuildingNum = player[i].numbers_of_buildings;
        for(int j = 0; j < BuildingNum; ++j) {
            int id = player[i].buildings[j];
            point[i] += cardType[id].point;
            point[i] += player[i].card_under;
            Chapel[i] += player[i].card_under;
            building[i] += cardType[id].point;
            if(player[i].specials.build.GuildHall) {
                if(id < 5) {
                    point[i] += 2;
                    GuildHall[i] += 2;
                }
            }
            if(player[i].specials.build.CityHall) {
                if(id >= 5) {
                    point[i] += 1;
                    CityHall[i] += 1;
                }
            }
            if(id <= 24 && id >= 22) ++hall[i];
        }
        if(player[i].specials.build.TriumhalArch) {
            if(hall[i] == 1) {
                point[i] += 4;
                TriumhalArch[i] = 4;
            }
            else if(hall[i] == 2) {
                point[i] += 6;
                TriumhalArch[i] = 6;
            }
            else if(hall[i] == 3) {
                point[i] += 8;
                TriumhalArch[i] = 8;
            }
        }
        if(player[i].specials.build.Palace) {
            Palace[i] = point[i] / 4;
            point[i] += Palace[i];
        }
        printf(LIGHT_GREEN"玩家(%d)\n建築物積分:%3d\n禮拜堂積分:%3d\n同業公會加成:%3d\n市政廳加成:%3d\n凱旋門加成:%3d\n宮殿加成:%3d\n總分:%3d\n", i + 1, building[i], Chapel[i], GuildHall[i], CityHall[i], TriumhalArch[i], Palace[i], point[i]);
        printf("--------------------------------------\n");
        if(point[i] > point[MaxIndex[0]]) {
            MaxIndex[0] = i;
            numMax = 1;
        }
        else if(point[i] == point[MaxIndex[0]]) {
            ++numMax;
            MaxIndex[numMax] = i;
        }
    }
    for(int i = 0; i < numMax; ++i) printf(BROWN"玩家%2d 是贏家!!!\n", MaxIndex[i] + 1);
    printf(NONE);
}
void Chapel(_player *player, int playNum, int privilege) {
    int use = 0, choose = -1;
    printf(LIGHT_GRAY);
    if(playNum == privilege) {
        printf("要使用禮拜堂嗎?\n(1)要\n(2)不要\n");
        if(use == 1) {
            if(player->number_of_cards <= 0) printf("卡牌不足一張，無法使用禮拜堂\n");
            else {
                int numLine = player->numbers_of_buildings / 6 + 1;
                int line = 0;
                for(int k = 0; k < numLine; ++k) {
                    if(k == 1) line = (6 > player->numbers_of_buildings) ? player->numbers_of_buildings : 6;
                    if(k == 2) line = player->numbers_of_buildings - 6;
                    for(int j = 0; j < line; ++j)printf("(%d) ┌────────────┐ ", j + 1);
                    printf("\n");
                    for(int j = 0; j < line; ++j)printf("    │            │ ");
                    printf("\n");
                    for(int j = 0; j < line; ++j)printf("    │            │ ");
                    printf("\n");
                    for(int j = 0; j < line; ++j) {
                        int id = player->buildings[j + 6 * k];
                        if(id < 25 && id >= 22) printf("    │%6s│ ", cardType[id].ch_name);
                        else if (id == 26)printf("    │  %4s  │ ", cardType[id].ch_name);
                        else printf("    │   %3s   │ ", cardType[id].ch_name);
                    }
                    printf("\n");
                    for(int j = 0; j < line; ++j)printf("    │            │ ");
                    printf("\n");
                    for(int j = 0; j < line; ++j)printf("    │            │ ");
                    printf("\n");
                    for(int j = 0; j < line; ++j)printf("    └────────────┘ ");
                    printf("\n");
                }
                printf("請選擇一張手牌放到禮拜堂之下\n");
                scanf("%d", &choose);
                discard(player, choose);
                ++player->card_under;
                printf("玩家%2d放置一張手牌到禮拜堂下\n", privilege);
            }
        }
    }
    else {
        if(player->number_of_cards >= player->card_limit) {
            discard(player, 1);
            ++player->card_under;
            printf("玩家%2d放置一張手牌到禮拜堂下\n", privilege);
        }
    }
    printf(NONE);
}
void cardRander() {
    int number = 0;
    int random = time(0);
    int r = 0;
    int repeat = 1;
    memset(cardHeap, 0x00, sizeof(cardHeap));
    heapIndex = 105;
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
        --r;
        cardHeap[i] = r;
        //printf("%d ",r);
    }
}
void addCard(_player *player, int id) {
    card *pHead = &player->cards;
    if(heapIndex < 0) heapIndex = 105;
    if( pHead == NULL ) printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
    card *pNewNode = calloc( 1, sizeof( card ) );
    if(id > 28 || id < 0) {
        int k = 0;
        printf("id: %d\n", id);
        scanf("%d", &k);
    }
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
        player[i].numbers_of_buildings = 0;
        for(int k = 0; k < 12; ++k)if(player[i].buildings[k] != -1) ++player[i].numbers_of_buildings;
        if(i + 1 == playerNum) printf(CYAN);
        int point = 0;
        for(int j = 0; j < player[i].numbers_of_buildings; ++j) point += cardType[player[i].buildings[j]].point;
        printf("玩家%2d\n卡牌數量: %d\n積分:%2d\n", i + 1, player[i].number_of_cards, player[i].point);
        int numLine = player[i].numbers_of_buildings / 6 + 1;
        int line = 0;
        for(int k = 0; k < numLine; ++k) {
            if(numLine == 2)break;
            if(k == 0) line = (6 > player[i].numbers_of_buildings) ? player[i].numbers_of_buildings : 6;
            if(k == 1) line = player[i].numbers_of_buildings - 6;
            for(int j = 0; j < line; ++j)printf("┌────────────┐ ");
            printf("\n");
            for(int j = 0; j < line; ++j)printf("│            │ ");
            printf("\n");
            for(int j = 0; j < line; ++j)printf("│            │ ");
            printf("\n");
            for(int j = 0; j < line; ++j) {
                if(player[i].buildings[j + k * 6] < 25 && player[i].buildings[j + k * 6] >= 22) printf("│%6s│ ", cardType[player[i].buildings[j + k * 6]].ch_name);
                else if (player[i].buildings[j + k * 6] == 25)printf("│  %4s  │ ", cardType[player[i].buildings[j + k * 6]].ch_name);
                else printf("│   %3s   │ ", cardType[player[i].buildings[j + k * 6]].ch_name);
            }
            printf("\n");
            for(int j = 0; j < line; ++j) {
                if(player[i].buildingInfo[j + k * 6].has_product) printf("│┌──────────┐│ ");
                else printf("│            │ ");
            }
            printf("\n");
            for(int j = 0; j < line; ++j) {
                if(player[i].buildingInfo[j + k * 6].has_product) printf("││ SAN JUAN ││ ");
                else printf("│            │ ");
            }
            printf("\n");
            for(int j = 0; j < line; ++j) {
                if(player[i].buildingInfo[j + k * 6].has_product) printf("└┴──────────┴┘ ");
                else printf("└────────────┘ ");
            }
            printf("\n");
        }
        printf("----------------------------------------------------------------------\n");
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
        int id = pCard->id;
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
    printf("選擇察看手牌或牌局\n(1)手牌\n(2)排局\n(3)兩者\n(4)跳過\n");
    scanf("%d", &c);
    switch(c) {
    case 1:
        printCard(&player[playNum - 1]);
        fgets(buffer, 10, stdin);
        printf("按 ENTER 以繼續\n");
        fgets(buffer, 10, stdin);
        break;
    case 2:
        printStatus(player, playNum);
        fgets(buffer, 10, stdin);
        printf("按 ENTER 以繼續\n");
        fgets(buffer, 10, stdin);
        break;
    case 3:
        printCard(&player[playNum - 1]);
        printf("按 ENTER 以繼續\n");
        fgets(buffer, 10, stdin);
        fgets(buffer, 10, stdin);
        printStatus(player, playNum);
        printf("按 ENTER 以繼續\n");
        fgets(buffer, 10, stdin);
        break;
    case 4:
        break;
    default:
        printf("無此選項\n");
        break;
    }
}
void playerDiscard(_player *player) {
    int cardDiscard[20], discardArray[10] = {0}, offset = 0;
    int t = player->number_of_cards - player->card_limit;
    system("clear");
    printCard(player);
    printf(RED"請丟棄 %d 張卡牌:\n", t);
    int j = 0;
    while(1) {
        scanf("%d", &discardArray[j]);
        if(j != 0) {
            offset = 0;
            for(int k = 0; k < j; ++k) if(discardArray[j] > discardArray[k]) ++offset;
            discard(player, discardArray[j] - offset);
        }
        else discard(player, discardArray[j]);
        if(player->number_of_cards <= player->card_limit) break;
        ++j;
    }
    printf(NONE);
}
void computerDicard(_player *player) {
    int i = time(0);
    srand(i);
    int r = rand() % player->number_of_cards;
    while(player->number_of_cards > player->card_limit) discard(player, 1);
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
        printf("    行動： %s\n", roles[i].action);
        printf("    特權： %s\n", roles[i].privilege);
        if(used[i]) printf(NONE);
    }
    scanf("%d", &choose);
    if(used[choose - 1]) {
        system("clear");
        printf(RED"請勿重複選擇\n"NONE);
        sleep(2);
        choose = playerChoose(used);
    }
    used[choose - 1] = 1;
    return choose;
}
