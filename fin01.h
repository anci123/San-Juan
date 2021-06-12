#pragma once
#include<stdio.h>
typedef struct _card{
    int id;
    struct _card *pNext;
}card;
typedef struct{
    int id;
    int point;
    int pay;
}cardSet;
cardSet cardType[29];
typedef struct _player{
    int id;
    card cards;
    int number_of_cards;
    int role;
    int buildings[12];
    int numbers_of_buildings;
    struct _player *pNext;
}player;
typedef struct{
    player *pHead;
} head;
void builder_action();
void builder_privilege();
void producer_action();
void producer_privilege();
void trader_action();
void trader_privilege();
void councillor_action();
void councillor_privilege();
void prospector_action();
void prospector_privilege();
