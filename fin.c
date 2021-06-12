#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"fin01.h"
#include"fin02.h"

int main() {
    cardRander();
    int heapIndex=0;
    head Head;
    initList( &Head );
    for(int i = 1; i <= 4; ++i) {
        player *pNewNode = calloc( 1, sizeof( player ) );
        pNewNode->id = i;
        pNewNode->buildings[0] = 1;
        card cardHead = {0, NULL};
        for(int j=0;j<4+i;++j){
            addCard(&cardHead,cardHeap[heapIndex]);
            ++heapIndex;
        }
        pNewNode -> pNext = NULL;
        player *pNode = Head.pHead;
        if(pNode) {
            while( pNode -> pNext ) {
                pNode = pNode -> pNext;
            }
            pNode -> pNext = pNewNode;
        }
        else {
            Head.pHead = pNewNode;
        }
    }//初始化四個玩家的struct
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
        }
    }
    return 0;
}
