//
//  main.c
//  library system
//
//  Created by headreaper on 2019/2/3.
//  Copyright © 2019 headreaper. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin_and_stu.h"
#include "admin_and_stu(chain_1.2.h"
void PrintHead();
int TranslateChoice(int choice);
void AdminOp();
void UserOp();
Usrl *RegisterOp(Usrl *user);
void WrongChoice();
void WriteInBook(char *book);
void WriteInUser(char *user);
char * MakeBookWhole(Bookl *booklist,char *write);
char * MakeUserWhole(Usrl *userlist,char *write);
Usrl *UsrChain(FILE *origin);
Bookl *BookChain(FILE *origin);

extern Usrl *userlist;
extern Bookl *booklist;
int main(){
    PrintHead();
    FILE *fusr = fopen("user.txt", "r");
    if (fusr == NULL){
        userlist = NULL;
    }
    else
        userlist = UsrChain(fusr);
    FILE *fbook = fopen("book.txt", "r");
    if (fbook == NULL){
        booklist = NULL;
    }
    else
        booklist = BookChain(fbook);
    int choice=0;
    char *bookchar = NULL;
    char *userchar = NULL;
    scanf("%d",&choice);
    choice = TranslateChoice(choice);
    while (choice) {
        system("reset");
        switch (choice) {
            case 1:
                AdminOp(userlist);
                break;
            case 2:
                UserOp(userlist);
                break;
            case 3:
                userlist= RegisterOp(userlist);
                break;
            case 4:
                if (userlist!=NULL){
                    userchar = MakeUserWhole(userlist,userchar);
                    WriteInUser(userchar);
                }
                if (booklist!=NULL){
                    bookchar = MakeBookWhole(booklist, bookchar);
                    WriteInBook(bookchar);
                }
                while (userlist!=NULL) {
                    free(userlist);
                    userlist=userlist->nextusr;
                }
                while (booklist!=NULL) {
                    free(booklist);
                    booklist = booklist->nextbook;
                }
                return 0;
                break;
            case 5:
                WrongChoice();
                break;
            default:
                break;
        }
        PrintHead();
        scanf(" %d",&choice);
    }
    return  0;
}
