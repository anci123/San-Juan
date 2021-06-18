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
            id = pNode->id;
            break;
        }
        pNode = pNode->pNext;
    }
    *pay = cardType[id].pay - discount;
    if(player->specials.byte & 1ULL << (id - 5)) {
        printf(BROWN"此特殊建築已建造過，不可重複建築\n");
        id = -1;
    }
    if(*pay < 0) pay = 0;
    return id;
}
void Build(_player *player, int num, int id) {
    if(!player->specials.build.Crane) {
        system("clear");
        player->buildings[player->numbers_of_buildings] = id;
        ++player->numbers_of_buildings;
        player->point += cardType[id].point;
        player->specials.byte += 1ULL << (id - 5);
        if(id == 5) player->card_limit = 12;
        system("clear");
        printf(BROWN);
        printf("玩家%2d 建造 %s\n", num, cardType[id].ch_name);
        sleep(2);
    }
}
int Crane(_player *player, int *discount, int *CraneId) {
    int choose = 0;
    int numLine = player->numbers_of_buildings / 6 + 1;
    int line = 0;
    for(int k = 0; k < numLine; ++k) {
        if(k == 0) line = (6 > player->numbers_of_buildings) ? player->numbers_of_buildings : 6;
        if(k == 1) line = player->numbers_of_buildings - 6;
        for(int j = 0; j < line; ++j)printf("(%d) ┌────────────┐ ", j + 1);
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    │            │ ");
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    │            │ ");
        printf("\n");
        for(int j = 0; j < line; ++j) {
            int id = player->buildings[j + k * 6];
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
    printf("請選擇一棟建築予以覆蓋\n");
    scanf("%d", &choose);
    *discount += cardType[player->buildings[choose - 1]].pay;
    *CraneId = player->buildings[choose - 1];
    return choose - 1;
}
void BlackMarket(_player *player, int *pay) {
    int choose[2] = {0}, limit = 2, house_with_produt = 0, houseId[12] = {0}, houseOrder[12] = {0};
    if(limit > *pay) limit = *pay;
    if(limit > player->numbers_of_products) limit = player->numbers_of_products;
    int k = 0;
    for(int j = 0; j < player->numbers_of_buildings; ++j) {
        if(player->buildings[j] < 5 && player->buildingInfo[j].has_product) {
            ++house_with_produt;
            houseId[k] = player->buildings[j];
            houseOrder[k] = j;
            ++k;
        }
    }
    int numLine = house_with_produt / 6 + 1;
    int line = 0;
    for(int k = 0; k < numLine; ++k) {
        if(k == 0) line = (6 > house_with_produt) ? house_with_produt : 6;
        if(k == 1) line = house_with_produt - 6;
        for(int j = 0; j < line; ++j)printf("(%d) ┌────────────┐ ", j + 1);
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    │            │ ");
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    │            │ ");
        printf("\n");
        for(int j = 0; j < line; ++j) {
            if(houseId[j] < 25 && houseId[j] >= 22) printf("    │%6s│ ", cardType[houseId[j + k * 6]].ch_name);
            else if (houseId[j] == 26)printf("    │  %4s  │ ", cardType[houseId[j + k * 6]].ch_name);
            else printf("    │   %3s   │ ", cardType[houseId[j + k * 6]].ch_name);
        }
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    │┌──────────┐│ ");
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    ││ SAN JUAN ││ ");
        printf("\n");
        for(int j = 0; j < line; ++j)printf("    └┴──────────┴┘ ");
        printf("\n");
    }
    printf("請選擇%2d張卡牌上的貨物支付建築費用\n", limit);
    for(int j = 0; j < limit; ++j) {
        scanf("%d", &choose[j]);
        player->buildingInfo[houseOrder[choose[j] - 1]].has_product = false;
        --player->numbers_of_products;
        --*pay;
    }
    if(*pay < 0) *pay = 0;
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
        int useCrane = 0, CraneId = -1, CraneOrder = -1;
        i = ii + privilege - 1;
        if(i > 4) i -= 4;
        if(i == privilege) discount = 1;
        if(i == privilege && player[i - 1].specials.build.Library) discount = 2;
        if(i == playerNum) {
            if(player[i - 1].specials.build.Crane && i == playerNum) {
                printf("要使用起重機嗎?\n(1)要\n(2)不要\n");
                scanf("%d", &useCrane);
                if(useCrane == 1) CraneOrder = Crane(&player[i - 1], &discount, &CraneId);
            }
            printCard(&player[i - 1]);
            printf(BROWN"請選擇一個建築建造，或是輸入 -1 不建造\n");
            scanf("%d", &choose);
            system("clear");
            if(choose > 0 && choose <= player[i - 1].number_of_cards) {
                id = buildPayment(&player[i - 1], choose, discount, &pay);
                if(id >= 0) {
                    if((player[i - 1].specials.build.Smithy && id < 5) || (player[i - 1].specials.build.Quarry && id >= 5)) {
                        --pay;
                        if(pay < 0) pay = 0;
                    }
                    if(pay < player[i - 1].number_of_cards) {
                        discard(&player[i - 1], choose);
                        if(player[i - 1].specials.build.BlackMarket && pay > 0 && i == playerNum && player[i - 1].numbers_of_products > 0) BlackMarket(&player[i - 1], &pay);
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
                            int offset = 0;
                            while(1) {
                                scanf("%d", &discardArray[j]);
                                if(j != 0) {
                                    offset = 0;
                                    for(int k = 0; k < j; ++k) if(discardArray[j] > discardArray[k]) ++offset;
                                    discard(&player[i - 1], discardArray[j] - offset);
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
            }
            else if(choose == -1) printf(BROWN"玩家%2d 選擇不建造\n", i);
            else printf(BROWN"無此卡牌\n");
            if(choose >= 0 && pay >= 0 && player[i - 1].specials.build.Crane) {
                player[i - 1].specials.byte -= 1ULL << (CraneId - 5);
                player[i - 1].buildings[CraneOrder] = id;
                player[i - 1].point += cardType[id].point;
                player[i - 1].point -= cardType[CraneId].point;
                player[i - 1].specials.byte += 1ULL << (id - 5);
                if(player[i - 1].buildingInfo[CraneOrder].has_product) --player[i - 1].numbers_of_products;
                player[i - 1].buildingInfo[CraneOrder].has_product = 0;
                system("clear");
                printf(BROWN);
                printf(BROWN"玩家%2d 建造 %s\n", i, cardType[id].ch_name);
            }
            sleep(2);
        }
        else {
            int buildSuccess = 0;
            int choose = 0;
            card *pCard = &player[i - 1].cards;
            while(pCard) {
                ++choose;
                if(choose > 0 && choose <= player[i - 1].number_of_cards) {
                    id = buildPayment(&player[i - 1], choose, discount, &pay);
                    if(id >= 0) {
                        if((player[i - 1].specials.build.Smithy && id < 5) || (player[i - 1].specials.build.Quarry && id >= 5)) {
                            --pay;
                            if(pay < 0) pay = 0;
                        }
                        if(pay < player[i - 1].number_of_cards) {
                            discard(&player[i - 1], choose);
                            for(int j = 1; j <= pay; ++j) discard(&player[i - 1], 1);
                            buildSuccess = 1;
                            Build(&player[i - 1], i, id);
                            break;
                        }
                    }
                }
                pCard = pCard->pNext;
            }
            if(!buildSuccess) {
                printf(BROWN"玩家%2d 選擇不建造\n", i);
                sleep(2);
            }
        }
        printf(BROWN);
        if(pay >= 0 && player[i - 1].number_of_cards <= 1 && player[i - 1].specials.build.PoorHouse) {
            printf("玩家%2d已打出救濟院且當前卡牌數量不多於一張，增加一張手牌\n", i);
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
            sleep(2);
        }
        if(pay >= 0 && id >= 5 && player[i - 1].specials.build.Carpenter) {
            printf("玩家%2d已打出木工場且建造特殊建築，增加一張手牌\n", i);
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
            sleep(2);
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
    if(player[privilege - 1].specials.build.Library) {
        keep = 2;
        for(int i = 0; i < keep; ++i) {
            addCard(&player[privilege - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
    }
    else if(player[privilege - 1].specials.build.GoldMine) {
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
            addCard(&player[privilege - 1], id[choose - 1]);
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
    checkChoose(player, playerNum);
}


void councillor_Archive(_player *player, int drawCard, int keep, bool isPlayer) {
    int choose[20], offset = 0;
    for(int i = 0; i < drawCard; ++i) {
        addCard(player, cardHeap[heapIndex]);
        --heapIndex;
    }
    if(isPlayer) {
        system("clear");
        printf(PURPLE);
        printCard(player);
        printf("請選擇丟棄%2d張卡牌\n", drawCard - keep);
        for(int j = 0; j < drawCard - keep; ++j) {
            scanf("%d", &choose[j]);
            if(j != 0) {
                offset = 0;
                for(int k = 0; k < j; ++k) if(choose[j] > choose[k]) ++offset;
                discard(player, choose[j] - offset);
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
        if(player[i - 1].specials.build.Prefecture) keep = 2;
        if(i == privilege) drawCard = 5;
        if(i == privilege && player[i - 1].specials.build.Library) drawCard = 8;
        if(player[i - 1].specials.build.Archive) {
            if(playerNum == i) {
                councillor_Archive(&player[i - 1], drawCard, keep, true);
                checkChoose(player, playerNum);
            }
            else councillor_Archive(&player[i - 1], drawCard, keep, false);
        }
        else {
            for(int j = 0; j < drawCard; ++j) id[j] = cardHeap[heapIndex - j];
            heapIndex -= drawCard;
            if(heapIndex < 0) heapIndex = 105;
            if(i != playerNum) {
                for(int k = 0; k < keep; ++k) {
                    choose[k] = k;
                    addCard(&player[i - 1], id[k]);
                }
            }
            else {
                printf(PURPLE);
                if(keep == drawCard) {
                    for(int k = 0; k < keep; ++k) {
                        choose[k] = k;
                        addCard(&player[i - 1], id[k]);
                    }
                }
                else {
                    printf("請選擇保留%2d張卡牌\n", keep);
                    for(int k = 1; k <= drawCard; ++k) {
                        printf("(%d) %s %s:\n    費用: %3d ,積分: %3d\n    效用:%s\n", k, cardType[id[k - 1]].ch_name, cardType[id[k - 1]].en_name, cardType[id[k - 1]].pay, cardType[id[k - 1]].point, cardType[id[k - 1]].effective);
                    }
                    for(int j = 0; j < keep; ++j) {
                        scanf("%d", &choose[j]);
                        addCard(&player[i - 1], id[choose[j] - 1]);
                    }
                    checkChoose(player, playerNum);
                }
            }
        }
        printf(PURPLE);
        system("clear");
        printf("玩家%2d保留%2d張卡牌\n", i, keep);
        sleep(2);
    }
    printf(NONE);
}

void producer_action(_player * player, int playerNum, int privilege) {
    printf(LIGHT_RED);
    for(int ii = 1; ii <= 4; ++ii) {
        int limit = 1, i = 0, house_can_produce = 0, houseId[12] = {0}, houseOrder[12] = {0}, choose[12] = {0}, chooseLimit = 0;
        if(ii >= privilege) i = ii + privilege - 1;
        else i = ii + privilege - 1;
        if(i > 4) i -= 4;
        if(i == privilege) limit = 2;
        if(i == privilege && player[i - 1].specials.build.Library) limit = 3;
        if(player[i - 1].specials.build.Aqueduct) ++limit;
        int k = 0;
        for(int j = 0; j < player[i - 1].numbers_of_buildings; ++j) {
            if(player[i - 1].buildings[j] < 5 && !player[i - 1].buildingInfo[j].has_product) {
                ++house_can_produce;
                houseId[k] = player[i - 1].buildings[j];
                houseOrder[k] = j;
                ++k;
            }
        }
        if(i == playerNum) {
            if(house_can_produce) {
                printf(LIGHT_RED);
                chooseLimit = house_can_produce < limit ? house_can_produce : limit;
                if(chooseLimit >= house_can_produce) {
                    for(int j = 0; j < chooseLimit; ++j) {
                        player[i - 1].buildingInfo[houseOrder[j]].has_product = true;
                        ++player[i - 1].numbers_of_products;
                    }
                }
                else {
                    int numLine = house_can_produce / 6 + 1;
                    int line = 0;
                    for(int k = 0; k < numLine; ++k) {
                        if(k == 0) line = (6 > house_can_produce) ? house_can_produce : 6;
                        if(k == 1) line = house_can_produce - 6;
                        for(int j = 0; j < line; ++j)printf("(%d) ┌────────────┐ ", j + 1 + k * 6);
                        printf("\n");
                        for(int j = 0; j < line; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < line; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < line; ++j) {
                            if(houseId[j] < 25 && houseId[j] >= 22) printf("    │%6s│ ", cardType[houseId[j + k * 6]].ch_name);
                            else if (houseId[j] == 26)printf("    │  %4s  │ ", cardType[houseId[j + k * 6]].ch_name);
                            else printf("    │   %3s   │ ", cardType[houseId[j + k * 6]].ch_name);
                        }
                        printf("\n");
                        for(int j = 0; j < line; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < line; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < line; ++j)printf("    └────────────┘ ");
                        printf("\n");
                    }
                    printf(LIGHT_RED"請選擇%2d張卡牌生產貨物\n", chooseLimit);
                    for(int j = 0; j < chooseLimit; ++j) {
                        scanf("%d", &choose[j]);
                        printf("%2u\n", player[i - 1].buildings[houseOrder[choose[j] - 1]]);
                        player[i - 1].buildingInfo[houseOrder[choose[j] - 1]].has_product = true;
                        ++player[i - 1].numbers_of_products;
                    }
                }
            }
            else {
                printf(LIGHT_RED"當前無空的生產建築可生產貨物\n");
                sleep(2);
            }
        }
        else {
            if(house_can_produce) {
                chooseLimit = house_can_produce < limit ? house_can_produce : limit;
                for(int j = 0; j < chooseLimit; ++j) {
                    player[i - 1].buildingInfo[houseOrder[j]].has_product = true;
                    ++player[i - 1].numbers_of_products;
                }
            }
        }
        system("clear");
        printf(LIGHT_RED"玩家%2d生產%2d貨物\n", i, chooseLimit);
        sleep(2);
        if(player[i - 1].specials.build.Well && chooseLimit >= 2) {
            printf(LIGHT_RED"玩家%2d已打出水井且生產兩個以上的貨物，增加一張手牌\n", i);
            sleep(2);
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        if(i == playerNum)checkChoose(player, playerNum);
        system("clear");
    }
    printf(NONE);
}

void trader_action(_player * player, int playerNum, int privilege) {
    printf(LIGHT_PURPLE);
    ++priceOrder;
    if(priceOrder > 4) priceOrder = 0;
    printf("商品價目表：\n");
    printf("┌───┬───┬───┬───┬───┐ \n");
    printf("│ %d │ %d │ %d │ %d │ %d │ \n", price[priceOrder][0], price[priceOrder][1], price[priceOrder][2], price[priceOrder][3], price[priceOrder][4]);
    printf("└───┴───┴───┴───┴───┘ \n");
    sleep(2);
    for(int ii = 1; ii <= 4; ++ii) {
        system("clear");
        int limit = 1, i = 0, chooseLimit = 0, house_with_produt = 0, houseOrder[12] = {0}, houseId[12] = {0}, choose[12] = {0};
        int value = 0;
        if(ii >= privilege) i = ii + privilege - 1;
        else i = ii + privilege - 1;
        if(i > 4) i -= 4;
        if(i == privilege) limit = 2;
        if(i == privilege && player[i - 1].specials.build.Library) limit = 3;
        if(player[i - 1].specials.build.TradingPost) ++limit;
        int k = 0;
        for(int j = 0; j < player[i - 1].numbers_of_buildings; ++j) {
            if(player[i - 1].buildings[j] < 5 && player[i - 1].buildingInfo[j].has_product) {
                ++house_with_produt;
                houseId[k] = player[i - 1].buildings[j];
                houseOrder[k] = j;
                ++k;
            }
        }
        player[i - 1].numbers_of_products = house_with_produt;
        if(i == playerNum) {
            if(house_with_produt) {
                printf(LIGHT_PURPLE);
                chooseLimit = house_with_produt < limit ? house_with_produt : limit;
                value = 0;
                if(chooseLimit >= house_with_produt) {
                    for(int j = 0; j < chooseLimit; ++j) {
                        player[i - 1].buildingInfo[houseOrder[j]].has_product = false;
                        --player[i - 1].numbers_of_products;
                        value += price[priceOrder][houseId[j]];
                    }
                }
                else {
                    int numLine = house_with_produt / 6 + 1;
                    int line = 0;
                    for(int k = 0; k < numLine; ++k) {
                        if(k == 0) line = (6 > house_with_produt) ? house_with_produt : 6;
                        if(k == 1) line = house_with_produt - 6;
                        for(int j = 0; j < house_with_produt; ++j)printf("(%d) ┌────────────┐ ", j + 1);
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j)printf("    │            │ ");
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j) {
                            if(houseId[j + k * 6] < 25 && houseId[j + k * 6] >= 22) printf("    │%6s│ ", cardType[houseId[j + k * 6]].ch_name);
                            else if (houseId[j + k * 6] == 26)printf("    │  %4s  │ ", cardType[houseId[j + k * 6]].ch_name);
                            else printf("    │   %3s   │ ", cardType[houseId[j + k * 6]].ch_name);
                        }
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j)printf("    │┌──────────┐│ ");
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j)printf("    ││ SAN JUAN ││ ");
                        printf("\n");
                        for(int j = 0; j < house_with_produt; ++j)printf("    └┴──────────┴┘ ");
                        printf("\n");
                    }
                    printf("商品價目表：\n");
                    printf("┌───┬───┬───┬───┬───┐ \n");
                    printf("│ %d │ %d │ %d │ %d │ %d │ \n", price[priceOrder][0], price[priceOrder][1], price[priceOrder][2], price[priceOrder][3], price[priceOrder][4]);
                    printf("└───┴───┴───┴───┴───┘ \n");
                    printf("請選擇%2d張卡牌上的貨物販售\n", chooseLimit);
                    value = 0;
                    for(int j = 0; j < chooseLimit; ++j) {
                        scanf("%d", &choose[j]);
                        player[i - 1].buildingInfo[houseOrder[choose[j] - 1]].has_product = false;
                        --player[i - 1].numbers_of_products;
                        int id = houseId[choose[j] - 1];
                        value += price[priceOrder][id];
                    }
                }
            }
            else {
                printf(LIGHT_PURPLE"當前無貨物可販售\n");
                sleep(2);
            }
        }
        else {
            if(house_with_produt) {
                chooseLimit = house_with_produt < limit ? house_with_produt : limit;
                value = 0;
                for(int j = 0; j < chooseLimit; ++j) {
                    player[i - 1].buildingInfo[houseOrder[j]].has_product = false;
                    --player[i - 1].numbers_of_products;
                    int id = houseId[j];
                    value += price[priceOrder][id];
                }
            }
        }
        for(int j = 0; j < value; ++j) {
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        system("clear");
        printf(LIGHT_PURPLE"玩家%2d賣出%2d個貨物，得到%2d張手牌\n", i, chooseLimit, value);
        sleep(2);
        if(player[i - 1].specials.build.MarketHall) {
            printf(LIGHT_PURPLE"玩家%2d已打出市場，增加一張手牌\n", i);
            sleep(2);
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        if(player[i - 1].specials.build.MarketStand && chooseLimit >= 2) {
            printf(LIGHT_PURPLE"玩家%2d已打出攤販且賣出兩個以上的貨物，增加一張手牌\n", i);
            sleep(2);
            addCard(&player[i - 1], cardHeap[heapIndex]);
            --heapIndex;
        }
        printf(NONE);
        if(i == playerNum) checkChoose(player, playerNum);
    }
    printf(NONE);
}
