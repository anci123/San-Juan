#pragma once
int cardHeap[106];

int32_t initList( head *Head ) {
    if( Head == NULL ) {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    Head -> pHead = NULL;

    return 0;
}
void cardRander() {
    int number = 0;
    int random = time(0);
    int r = 0;
    int repeat = 1;
    memset(cardHeap, 0x00, sizeof(cardHeap));
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
            r/=2;
            r+=26;
        }
        cardHeap[i]=r;
    }
}
void addCard(card *pHead,int id){
    if( pHead == NULL ) printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
    card *pNewNode = calloc( 1, sizeof( card ) );
    pNewNode -> id = id;
    pNewNode -> pNext = NULL;
    card *pNode = pHead;

    while( pNode -> pNext ) {
        pNode = pNode -> pNext;
    }
    pNode -> pNext = pNewNode;
}