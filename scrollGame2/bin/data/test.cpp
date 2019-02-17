#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(){
    char rankingName[20][10];//名前は最大20文字
    int rankingScore[10];
    FILE *fp;
    fp=fopen("rankingData.txt","r+");
    if(fp==NULL){
        cout<<"no file"<<endl;
    }
    for(int i=0;i<10;i++){
        fscanf(fp,"%s %d",rankingName[i],&rankingScore[i]);
        cout<<"Name:"<<rankingName[i]<<" Score:"<<rankingScore[i]<<endl;
    }
}