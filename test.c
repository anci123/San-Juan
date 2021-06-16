#include<stdio.h>
int main(){
    int j[10]={0};
    for(int i=0;i<5;++i){
        scanf("%d",&j[i]);
        ++j[i];
    }
    return 0;
}
