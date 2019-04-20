//
//  store_and_fetch(chain_1.c
//  library system
//
//  Created by headreaper on 2019/4/19.
//  Copyright © 2019 headreaper. All rights reserved.
//

#include "store_and_fetch(chain_1.h"
#include "admin_and_stu(chain_1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct usr *UsrChain(FILE *origin){
    int i=0;
    char *source={""},sege[]="\n",segi[]="|";
    while(!feof(origin)){
        source[i] = fgetc(origin);
        i++;
    }
    char *sentence = strtok(source, sege);
    struct usr *head = NULL;
    struct usr *pre=NULL,*current=NULL;
    while (sentence!=NULL) {
        char *substr = strtok(sentence, segi);
        if (head ==NULL){
            head = current;
        }
        else{
            pre->nextusr=current;
        }
        current->nextusr=NULL;
        strcpy(current->IDnum, substr);
        substr = strtok(sentence, segi);
        strcpy(current->name, substr);
        substr = strtok(sentence, segi);
        strcpy(current->password, substr);
        substr = strtok(sentence, segi);
        strcpy(current->num, substr);
        substr = strtok(sentence, segi);
        strcpy(current->book1->name, substr);
        substr = strtok(sentence, segi);
        strcpy(current->book2->name, substr);
        substr = strtok(sentence, segi);
        sentence = strtok(source, sege);
        pre = current;
    }
    return head;
}

struct book *BookChain(FILE *origin){
    int i=0;
    char *source={""},sege[]="\n",segi[]="|";
    while(!feof(origin)){
        source[i] = fgetc(origin);
        i++;
    }
    char *sentence = strtok(source, sege);
    struct book *head = NULL;
    struct book *pre=NULL,*current=NULL;
    while (sentence!=NULL) {
        char *substr = strtok(sentence, segi);
        if (head ==NULL){
            head = current;
        }
        else{
            pre->nextbook=current;
        }
        current->nextbook=NULL;
        strcpy(current->name, substr);
        substr = strtok(sentence, segi);
        strcpy(current->writer, substr);
        substr = strtok(sentence, segi);
        strcpy(current->status, substr);
        substr = strtok(sentence, segi);
        pre = current;
    }
    return head;
}
