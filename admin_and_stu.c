//
//  admin_and_stu.c
//  library system
//
//  Created by headreaper on 2019/2/3.
//  Copyright © 2019 headreaper. All rights reserved.
//
#include "admin_and_stu.h"
#include <string.h>
#include <stdlib.h>


accounts *makeAccount(long usernum,long booknum,char **Name, char **Book){
    usr **userlist = (usr **)malloc(sizeof(usr)*usernum);
    book **booklist = (book **)malloc(sizeof(book)*booknum);
    char seg[]="|";
    for (int i=0;i<usernum;i++){
        char *subname = strtok(Name[i], seg);
        int count=0;
        while(subname!=NULL){
            strcpy(userlist[count]->IDnumber, subname);
            subname = strtok(NULL, seg);
            strcpy(userlist[count]->name, subname);
            subname = strtok(NULL, seg);
            strcpy(userlist[count]->password, subname);
            subname = strtok(NULL, seg);
            strcpy(userlist[count]->num, subname);
            subname = strtok(NULL, seg);
            strcpy(userlist[count]->book1->name, subname);
            subname = strtok(NULL, seg);
            strcpy(userlist[count]->book2->name, subname);
            subname = strtok(NULL, seg);
            count++;
        }
    }
    for (int i=0;i<booknum;i++){
        char *subname = strtok(Book[i], seg);
        int count=0;
        while(subname!=NULL){
            strcpy(booklist[count]->name, subname);
            subname = strtok(NULL, seg);
            strcpy(booklist[count]->status, subname);
            subname = strtok(NULL, seg);
            count++;
        }
    }
    accounts *account;
    account->returnusr=userlist;
    account->returnbook=booklist;
    
    return account;
}
