#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
typedef struct _card{
    int id;
    struct _card *pNext;
}card;
typedef struct{
    int id;
    char en_name[20];
    char ch_name[20];
    int pay;
    int point;
    char effective[500];
}cardSet;
cardSet cardType[29]={
    {1,"Indigo plant","染料廠",1,1,"無"},
    {2,"Sugar mill","蔗糖廠",2,1,"無"},
    {3,"Tobacco storage","菸草廠",3,2,"無"},
    {4,"Coffee roaster","咖啡廠",4,2,"無"},
    {5,"Silver smelter","白銀廠",5,3,"無"},
    {6,"Tower","塔樓　",3,2,"各回合玩家計算手牌前，已打出此張卡牌的玩家手牌上限可增加至12張"},
    {7,"Chapel","禮拜堂",3,2,"各回合玩家計算手牌前，已打出此張卡牌的玩家可挑選其中1張手牌正面朝下置於此張卡牌底下"},
    {8,"Smithy","鐵匠鋪",1,1,"建築師階段時，已打出此張卡牌的玩家在建造生產建築物時可少支付1張手牌"},
    {9,"Poor house","救濟院",2,1,"建築師階段時，已打出此張卡牌的玩家在行動完成後，若玩家手牌張數不多於1張時，可從卡牌堆抽取1張卡牌加入手牌"},
    {10,"Black market","黑市　",2,1,"建築師階段時，已打出此張卡牌的玩家最多可用2個貨品(即置於自家生產建築下方的卡牌)取代支付費用(手牌)，1個貨品只能替代1張手牌"},
    {11,"Crane","起重機",2,1,"建築師階段時，已打出此張卡牌的玩家可支付興建新建築物與原先擁有舊建築物的費用差額，將新建築物蓋在舊建築物的上方。被覆蓋的卡牌不計分亦無效能，被覆蓋的生產建築其上方貨品則須棄置，被覆蓋的禮拜堂其上方卡牌仍可保留計分"},
    {12,"Carpenter","木工場",3,2,"建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可從卡牌堆上方抽取1張卡牌"},
    {13,"Quarry","採石場",4,2,"建築師階段時，已打出此張卡牌的玩家在建造特殊建築物時可少支付1張手牌"},
    {14,"Well","水井　",2,1,"生產者階段時，已打出此張卡牌的玩家若生產2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"},
    {15,"Aqueduct","溝渠　",3,2,"生產者階段時，已打出此張卡牌的玩家可多生產1個貨品"},
    {16,"Market stand","攤販　",2,1,"商人階段時，已打出此張卡牌的玩家若賣出2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌"},
    {17,"Market hall","市場　",4,2,"商人階段時，已打出此張卡牌的玩家在行動完成後，可從卡牌堆上方抽取1張卡牌加入手牌"},
    {18,"Trading post","交易所",2,1,"商人階段時，已打出此張卡牌的玩家可多賣出1個貨品"},
    {19,"Archive","檔案館",1,1,"市長階段時，已打出此張卡牌的玩家在挑選卡牌時，可將卡牌堆上方抽取的卡牌全數加入手牌後再進行挑選，並將挑選外的其餘卡牌丟棄"},
    {20,"Prefecture","辦公處",3,2,"市長階段時，已打出此張卡牌的玩家從卡牌堆上抽取卡牌後，挑選其中2張加入手牌"},
    {21,"Gold mine","金礦坑",1,1,"淘金者階段時，已打出此張卡牌的玩家可在行動完成後，從卡牌堆上方翻開4張卡牌，若4張卡牌的費用皆不相同，可挑選其中1張加入手牌。但只要任2張出現相同費用，則須全數棄置"},
    {22,"Library","圖書館",5,3,"已打出此張卡牌的玩家在下列各階段行使特殊行動時，可提升其特殊行動能力\n建築師階段時，可少支付2張手牌\n生產者階段時，最多可生產3個貨品\n商人階段時，已打出此張卡牌的玩家最多可賣出3個貨品\n市長階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取8張卡牌，挑選其中1張加入手牌\n淘金者階段時，已打出此張卡牌的玩家可從卡牌堆上方抽取2張卡牌加入手牌"},
    {23,"Statue","雕鑄像紀念碑",3,3,"無"},
    {24,"Victory column","勝利柱紀念碑",4,4,"無"},
    {25,"Hero","英雄像紀念碑",5,5,"無"},
    {26,"Guild hall","同業會館",6,0,"遊戲結束時，已打出此張卡牌的玩家每擁有1棟生產建築物可額外獲得2分"},
    {27,"City hall","市政廳",6,0,"遊戲結束時，已打出此張卡牌的玩家每擁有1棟特殊建築物(包括此張卡牌)可額外獲得1分"},
    {28,"Triumhal arch","凱旋門",6,0,"遊戲結束時，已打出此張卡牌的玩家若擁有1種紀念碑卡可額外獲得4分，擁有2種紀念碑卡可額外獲得6分，擁有3種紀念碑卡可額外獲得8分"},
    {29,"Palace","宮殿　",6,0,"遊戲結束時，已打出此張卡牌的玩家可額外獲得該玩家總分的四分之一分數(採無條件捨去)"},
};

typedef struct _specail{
    uint8_t Chapel:1;
    uint8_t Smithy:1;
    uint8_t PoorHouse:1;
    uint8_t BlackMarket:1;
    uint8_t Crane:1;
    uint8_t Carpenter:1;
    uint8_t Quarry:1;
    uint8_t Well:1;
    uint8_t Aqueduct:1;
    uint8_t MarketStand:1;
    uint8_t MarketHall:1;
    uint8_t TradingPost:1;
    uint8_t Archive:1;
    uint8_t Prefecture:1;
    uint8_t GoldMine:1;
    uint8_t Library:1;
    uint8_t GuildHall:1;
    uint8_t CityHall:1;
    uint8_t TriumhalArch:1;
    uint8_t Palace:1;
}__attribute__((packed)) special_effective;
typedef struct _c{
    bool has_product;
    bool card_under;
}c;

typedef struct _player{
    int id;
    card cards;
    int number_of_cards;
    int role;
    int buildings[12];
    int numbers_of_buildings;
    int point;
    int product_limit;
    int card_limit;
    c buildingInfo[12];
    int numbers_of_products;
    //card cardHead;
    //int building_discount;
    special_effective specials;
    struct _player *pNext;
}_player;

typedef struct _role{
    char name[20];
    char privilege[100];
    char action[200];
}role;
role roles[]={
    {"建築師","建造建築時,可減少支付1張手牌，但建築最後支付的費用不能少於0","可從手牌中選擇一張牌並建造，再根據其費用支付對應手牌張數"},
    {"生產者","最多可生產2個貨物","最多可生產1個貨物\n    (從牌堆抽一張卡背面朝上放在自家生產建築物上方，每棟生產建築物最多生產一個貨物)"},
    {"商人","最多可賣出2個貨品","賣出1個貨品(丟棄1張自家生產建築上方的卡牌，並對應貨品價格抽取對應數量的卡牌)"},
    {"市長","從牌堆抽取5張卡牌，挑選1張加入手牌，其餘則丟置棄牌區","從牌堆抽取2張卡牌，挑選1張加入手牌，其餘則丟置棄牌區"},
    {"淘金者","從牌堆抽取1張卡牌加入手牌","無"}
};

