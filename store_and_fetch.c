//
//  store_and_fetch.c
//  library system
//
//  Created by headreaper on 2019/2/3.
//  Copyright © 2019 headreaper. All rights reserved.
//

#include "store_and_fetch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int amount;
char **getList(FILE *origin,int number){
    int i=0;
    long n;
    char *source={""},seg[]="\n";
    while(!feof(origin)){
        source[i] = fgetc(origin);
        i++;
    }
    source[i++]='\0';
    i=0;
    n = strlen(source)/number+1;
    char * result[n];
    char *substr = strtok(source, seg);
    for (;i<n;i++){
        result[i] = (char *)malloc(number*sizeof(char));
    }
    i = 0;
    while(substr!=NULL){
        strcpy(result[i], substr);
        i++;
        substr = strtok(NULL, seg);
    }
    char **s = &result[0];
    return s;
};

long getNum(FILE *origin,int number){
    int i=0;
    long n;
    char *source={""};
    while(!feof(origin)){
        source[i] = fgetc(origin);
        i++;
    }
    source[i++]='\0';
    n = strlen(source)/number+1;
    return n;
}
