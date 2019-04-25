//
//  store_and_fetch.c
//  library system
//
//  Created by headreaper on 2019/2/3.
//  Copyright © 2019 headreaper. All rights reserved.
//

#include "store_and_fetch.h"
#include "admin_and_stu(chain_1.2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//conversion between different types of data
char * TransIntToStr(char *str,int i)
{
    sprintf(str, "%d", i);
    return str;
}
int TransStrToInt(const char* str)
{
    int temp = 0;
    const char* p = str;
    if(str == NULL) return 0;
    if(*str == '-' || *str == '+')
    {
        str ++;
    }
    while( *str != 0)
    {
        if( *str < '0' || *str > '9')
        {
            break;
        }
        temp = temp*10 +(*str -'0');
        str ++;
    }
    if(*p == '-')
    {
        temp = -temp;
    }
    return temp;
}
//add new book
Bookl *AddBook(Book book, Bookl *pbook){
    Bookl *pnew;
    Bookl *scan = pbook;
    pnew = (Bookl *)malloc(sizeof(Bookl));
    pnew->BookItem = book;
    pnew->nextbook= NULL;
    if(scan ==NULL){
        pnew->BookItem.ID=0;
        pbook = pnew;
    }
    else{
        while(scan->nextbook!=NULL){
            scan=scan->nextbook;
        }
        scan->nextbook = pnew;
        pnew->BookItem.ID = scan->BookItem.ID+1;
    }
    return pbook;
}
//remove book
Bookl *RemoveBook(Bookl *bookremove,Bookl *booklist){
    Bookl *scan;
    scan = booklist;
    printf("%s is to be removed\n",bookremove->BookItem.name);
    while (scan!=NULL) {
        if(scan->nextbook == bookremove){
            if(bookremove==booklist){
                booklist = booklist->nextbook;
            }
            else{
                scan->nextbook = scan->nextbook->nextbook;
            }
            free(scan->nextbook);
            break;
        }
        scan = scan->nextbook;
    }
    return booklist;
}
//add user
Usrl *AddUsr(Usr user, Usrl *pusr){
    Usrl *pnew = (Usrl *)malloc(sizeof(Usrl));
    Usrl *scan = pusr;
    pnew->UsrItem = user;
    pnew->nextusr = NULL;
    if(scan ==NULL){
        pusr = pnew;
    }
    else{
        while(scan->nextusr!=NULL){
            scan=scan->nextusr;
        }
        scan->nextusr = pnew;
    }
    printf("%s\n",pusr->UsrItem.name);
    return pusr;
}
void PrintBook(Bookl *pbook){
    Bookl *head = pbook;
    while (head!=NULL) {
        printf("%d. %s writer: %s, where: %s\n",head->BookItem.ID,head->BookItem.name,head->BookItem.writer,head->BookItem.status);
        head = head->nextbook;
    }
}
//print basic menu
void PrintHead(){
    printf("***************************************\n\nWelcome to the library system(beta 1.0)\n\n***************************************\n\nNow please check the service you want(press the number and enter it):\n1.Log in as the administrator\n2.Log in as the user\n3.register for an user account\n4.exit\n");
}
//determine whether the book is what we want
int FindBook(char *enter,char *onebook){
    char *str1 = NULL,*str2 = NULL;
    str1 = enter;
    str2 = onebook;
    int result = 0,count0=0,count1=0,i=0,j=0,sign = 0;
    char post[strlen(str2)];
    for (int i =0;i<strlen(str2);i++){
        post[i]='_';
    }
    if(strlen(str1)>strlen(str2)){
        return result;
    }
    else{
        while (i<strlen(str1)) {
            while (j<strlen(str2)){
                if(str1[i]==str2[j]){
                    for (int m=0;m<strlen(post);m++){
                        if(str1[i]!=post[m]){
                            count1++;
                            post[count0] = str2[j];
                            sign = 1;
                            j++;
                            break;
                        }
                    }
                }
                else{
                    j++;
                }
                if(sign){
                    break;
                }
            }
            sign=0;
            if(count0==count1){
                return result;
            }
            else{
                count0=count1;
            }
            i++;
        }
    }
    if(count1 ==strlen(str1)){
        result=1;
    }
    return result;
}
//A translation of unreasonable choice
int TranslateChoice(int choice){
    if (choice<=0||choice>4)
        choice=5;
    return choice;
}
//initialize the user data(set the admin)
void Initialize(){
    Usrl *head = (Usrl *)malloc(sizeof(Usrl));
    char *ID = (char *)malloc(sizeof(char)*11);
    printf("Please enter your ID\n");
    scanf(" %s",ID);
    strcpy(head->UsrItem.IDnum, ID);
    char *name = (char *)malloc(sizeof(char)*30);
    printf("Please enter your name(plese use '_' to replace space)\n");
    scanf(" %s",name);
    strcpy(head->UsrItem.name,name);
    char *password = (char *)malloc(sizeof(char)*20);
    printf("Please enter your password\n");
    scanf(" %s",password);
    strcpy(head->UsrItem.password,password);
    head->UsrItem.book1.ID = -1;
    head->UsrItem.book2.ID = -1;
    strcpy(head->UsrItem.num, "0");
    head->nextusr=NULL;
    userlist = head;
}
//check the admin account information
int AdminCheck(char *enter,int choice){
    switch (choice) {
        case 1:
            if(strcmp(enter, userlist->UsrItem.IDnum)){
                    printf("Account doesn't exist, please try again\n");
                }
            else{
                    choice=2;
                }
            break;
        case 2:
            if(userlist==NULL){
                printf("No data, please initialize the data first\n");
            }
            else if(strcmp(enter, userlist->UsrItem.password)){
                printf("Passward is not right, please try again\n");
            }
            else{
                printf("Log in successfully!\n");
                choice=0;
            }
            break;
        default:
            break;
    }
    return choice;
    
};
//check the user information to log in
Usrl *UserCheck(char *enter,int *choice,Usrl *head){
    int LocalChoice=0;
    switch (*choice) {
        case 1:
            printf("checking account....\n");
            if(head==NULL){
                printf("No data, please use administrator mode to initialize the data\n");
            }
            else{
                while((head)!=NULL){
                    if(strcmp(enter,head->UsrItem.IDnum)){
                        (head)=(head)->nextusr;
                    }
                    else{
                        *choice=2;
                        break;
                    }
                }
                if(*choice==1){
                    printf("Account doesn't exist, please try again or register one\nPress 1 to register, press 2 to exit\n");
                    scanf("%d",&LocalChoice);
                    if(LocalChoice==1){
                        RegisterOp(userlist);
                    }
                    else{
                        break;
                    }
                }
            }
            break;
        case 2:
            if(head==NULL){
                printf("No data, please initialize the data first\n");
            }
            else if(strcmp(enter, (head)->UsrItem.password)){
                printf("Passward is not right, please try again\n");
            }
            else{
                printf("Log in successfully!\n");
                *choice=0;
            }
            break;
            
            break;
        default:
            break;
    }
    return head;
};
//admin operation：
void AdminOp(){
    int choice=1;
    char *Adaccount = (char *)malloc(sizeof(char)*11),*Adpassword = (char *)malloc(sizeof(char)*20);
    int localchoice;
    if(userlist==NULL){
        printf("There is no data, do you want to initialize the data?\nPress 1 to initialize, press 2 to exit\n");
        scanf("%d",&localchoice);
        if (localchoice==1){
            Initialize();
            printf("Initilization finished!\nPlease reopen this part\n");
        }
        else if (localchoice==2) {
            return;
        }
    }
    printf("Please enter the adiministrator account:\n");
    scanf(" %s",Adaccount);
    choice = AdminCheck(Adaccount,choice);
    while (choice==2) {
        printf("Please enter the administrator password:\n");
        scanf(" %s",Adpassword);
        choice = AdminCheck(Adpassword,choice);
    }
    if(!choice){
        int littlechoice = 0;
        printf("Now admin, what do you want to do:\n1. see the book list\n2. add and delete books\n3. see the user list\n4. exit\n");
        scanf("%d",&littlechoice);
        int l1choice=0,l2choice=0;
        while (1) {
        switch (littlechoice) {
            case 1:
                if(booklist == NULL){
                    printf("There is no book, do you want to add one?\n1. yew\n2. no, next time\n");
                    scanf("%d",&l1choice);
                    if (l1choice==1){
                        l1choice = 0;
                        while(!l1choice){
                            Book new;
                            char * name = (char *)malloc(sizeof(char)*30);
                            char * writer = (char *)malloc(sizeof(char)*20);
                            printf("Please enter the book name:\n");
                            scanf(" %s",name);
                            strcpy(new.name, name);
                            printf("Please enter the book writer:\n");
                            scanf(" %s",writer);
                            strcpy(new.writer, writer);
                            strcpy(new.status, "in");
                            new.ID = -1;
                            booklist = AddBook(new, booklist);
                            printf("free test\n");
                            free(name);
                            free(writer);
                            printf("do you want to continue adding?\n1.yes\n2.no\n");
                            scanf("%d",&l1choice);
                            l1choice--;
                        }
                        break;
                    }
                }
                Bookl *pbook = booklist;
                PrintBook(pbook);
                break;
            case 2:
                while(!l2choice){
                    printf("Do you want to add or remove book:\n1.add\n2.remove\n3.exit\n");
                    scanf("%d",&l2choice);
                    switch (l2choice) {
                        case 1:{
                            Book new;
                            char * name = (char *)malloc(sizeof(char)*30);
                            char * writer = (char *)malloc(sizeof(char)*20);
                            printf("Please enter the book name:\n");
                            scanf(" %s",name);
                            strcpy(new.name, name);
                            printf("Please enter the book writer:\n");
                            scanf(" %s",writer);
                            strcpy(new.writer, writer);
                            strcpy(new.status, "in");
                            new.ID = -1;
                            booklist = AddBook(new, booklist);}
                            break;
                        case 2:{
                            int id=-1;
                            char *enter = (char *)malloc(sizeof(char));
                            printf("Here are the books' datas:\n");
                            PrintBook(booklist);
                            printf("If you want to remove any book, just enter its id(you can exit '#' to exit\n");
                            scanf("%s",enter);
                            if(!strcmp(enter, "#")){
                                break;
                            }
                            while (1) {
                                Bookl *pbook = booklist;
                                id = TransStrToInt(enter);
                                while (pbook!=NULL) {
                                    if(pbook->BookItem.ID==id){
                                        booklist = RemoveBook(pbook, booklist);
                                        break;
                                    }
                                    pbook=pbook->nextbook;
                                }
                                printf("Book removed. If you want to keep removing ,just enter the id; if not, enter '#' to exit\n");
                                scanf(" %s",enter);
                                if(!strcmp(enter, "#")){
                                    break;
                                }
                                id = TransStrToInt(enter);
                            }
                            free(enter);
                        }
                        case 3:{
                            l2choice=1;
                            break;
                        }
                        default:
                            break;
                    }
                    
                }
                break;
            case 3:{
                    Usrl *head = userlist;
                    int i = 1;
                    while (head!=NULL) {
                        printf("%d.%s\n",i,head->UsrItem.name);
                        i++;
                        head = head->nextusr;
                    }
                }
                    break;
            case 4:
                    return;
                    break;
            default:
                    return;
                break;
                }
            printf("Now admin, what do you want to do:\n1. see the book list\n2. add and delete books\n3. see the user list\n4. exit\n");
            scanf("%d",&littlechoice);
        }
    }
    Adaccount=NULL;
    free(Adaccount);
    Adpassword=NULL;
    free(Adpassword);
};
//user operation:
void UserOp(){
    int choice = 1;
    Usrl *head = userlist;
    char *Usaccount= (char *)malloc(sizeof(char)*11),*Uspassword=(char *)malloc(sizeof(char)*20);
    printf("Please enter your account name:\n");
    scanf(" %s",Usaccount);
    head = UserCheck(Usaccount, &choice,head);
    while(choice == 2){
        printf("Please enter your password:\n");
        scanf(" %s",Uspassword);
        head = UserCheck(Uspassword,&choice,head);
    }
    if(!choice){
        system("reset");
        int littlechoice = 0;
        char *name = head->UsrItem.name;
        printf("Now dear %s, what do you want to do:\n1. see the book list\n2. search and borrow books\n3. see what i have borrowed\n4.exit\n",name);
        scanf("%d",&littlechoice);
        int l1choice=0,l2choice=0;
        while (1) {
            switch (littlechoice) {
                case 1:
                    if(booklist == NULL){
                        printf("There is no book, please contact with the admin to add books\n");
                    }
                    else{
                        Bookl *pbook = booklist;
                        while (pbook!=NULL) {
                            printf("%d. %s\n",pbook->BookItem.ID,pbook->BookItem.name);
                            pbook = pbook->nextbook;
                        }
                    }
                    break;
                case 2:
                    while(1){
                        int sign = 0;
                        char *enter = (char *)malloc(sizeof(char)*50);
                        printf("What books do you want(you can enter both book name and writer name , if you want to exit, press '#' and enter):\n");
                        scanf(" %s",enter);
                        if(!strcmp(enter, "#")){
                            break;
                        }
                        Bookl *pbook = booklist;
                        while (pbook!=NULL) {
                            char *source = (char *)malloc(sizeof(char)*50);
                            strcpy(source, pbook->BookItem.name);
                            strcat(source, pbook->BookItem.writer);
                            if(FindBook(enter, source)){
                                printf("Book found, it's %d, %s, written by %s,still %s\n",pbook->BookItem.ID,pbook->BookItem.name,pbook->BookItem.writer,pbook->BookItem.status);
                                sign = 1;
                                if(!strcmp("in", pbook->BookItem.status)){
                                    printf("Do you want to borrow it?\n1.yes\n2.no\n3.exit searching\n");
                                    scanf("%d",&l1choice);
                                    if(l1choice==3){
                                        break;
                                    }
                                    if(!(l1choice-1)){
                                        if(head->UsrItem.book1.ID==-1||head->UsrItem.book2.ID==-1){
                                            strcpy(pbook->BookItem.status, "out");
                                            if(head->UsrItem.book1.ID==-1){
                                                head->UsrItem.book1.ID = pbook->BookItem.ID;
                                            }
                                            else{
                                                head->UsrItem.book2.ID = pbook->BookItem.ID;
                                            }
                                        }
                                        else{
                                            printf("Sorry you can not borrow over two books, please return any one first\n");
                                        }
                                    }
                                }
                                else{
                                    printf("However, you can not borrow it yet\nDo you want to continue searching or exit:\n1.continue\n2.exit\n");
                                    scanf("%d",&l1choice);
                                    if(!(l1choice-1)){
                                    }
                                    else{
                                        free(enter);
                                        break;
                                    }
                                }
                            }
                            pbook = pbook->nextbook;
                            free(source);
                            source=NULL;
                        }
                        if(!sign){
                            printf("Sorry, there is no such book\n");
                        }
                        printf("searching work finished\n");
                    }
                    system("reset");
                    break;
                case 3:{
                    Bookl *pbook = booklist;
                    if(head->UsrItem.book1.ID==-1&&head->UsrItem.book2.ID==-1){
                        printf("You haven't borrowed any book yet\n");
                    }
                    else{
                        int id,id2=-1,sign=0,sign2=0;
                            char *name,*name2,*writer,*writer2;
                            id = head->UsrItem.book1.ID;
                            id2 = head->UsrItem.book2.ID;
                            while(pbook!=NULL){
                                if(pbook->BookItem.ID==id){
                                    name = pbook->BookItem.name;
                                    writer = pbook->BookItem.writer;
                                    sign=1;
                                }
                                else if(pbook->BookItem.ID==id2){
                                    name2 = pbook->BookItem.name;
                                    writer2 = pbook->BookItem.writer;
                                    sign2=1;
                                }
                                if(sign&&sign2){
                                    break;
                                }
                                pbook=pbook->nextbook;
                            }
                            printf("The number of books you borrowed is %d\n",sign2+sign);
                            if(sign+sign2==2){
                                printf("They are %s, written by %sand %s, written by %s\n",name,writer,name2,writer2);
                            }
                            else{
                                if(sign2==1){
                                    name = name2;
                                    writer = writer2;
                                }
                                printf("The book is %s, written by %s\n",name,writer);
                            }
                            printf("What else do you want to do:\n1.return book\n2.exit\n");
                            scanf("%d",&l2choice);
                        pbook = booklist;
                        while (!(l2choice-1)) {
                            int cid=-1;
                            char *enter = (char *)malloc(sizeof(char));
                            id = head->UsrItem.book1.ID;
                            id2 = head->UsrItem.book2.ID;
                            if(id==-1&&id2==-1){
                                l2choice=2;
                            }
                            else{
                                if(id!=-1){
                                    printf("%s's id is %d\n",name,id);
                                }
                                if(id2!=-1){
                                    printf("%s's id is %d\n",name2,id2);
                                }
                                printf("which book do you want to return,enter the id,press '#' to exit:\n");
                                scanf(" %s",enter);
                                if(!strcmp(enter, "#")){
                                    break;
                                }
                                else{
                                    cid = TransStrToInt(enter);
                                }
                                while (pbook!=NULL) {
                                    if(pbook->BookItem.ID==cid){
                                        strcpy(pbook->BookItem.status, "in");
                                        if(id==cid){
                                            head->UsrItem.book1.ID=-1;
                                        }
                                        else{
                                            head->UsrItem.book2.ID=-1;
                                        }
                                        break;
                                    }
                                    pbook = pbook->nextbook;
                                }
                            }
                            free(enter);
                            enter = NULL;
                        }
                        
                    }
                    }
                    break;
                case 4:
                    system("reset");
                    return;
                    break;
                default:
                    return;
                    break;
            }
            printf("Now dear %s, what do you want to do:\n1. see the book list\n2. search and borrow books\n3. see what i have borrowed\n4.exit\n",name);
            scanf("%d",&littlechoice);
        }
        
    }
    Uspassword=NULL;
    free(Usaccount);
    Usaccount=NULL;
    free(Usaccount);
};
//registeration operation
Usrl * RegisterOp(Usrl *user){
    if(user==NULL){
        user = (Usrl *)malloc(sizeof(Usrl));
    }
    Usr UserAdd;
    Usrl *head = NULL;
    char *IDname, *name =(char *)malloc(sizeof(char)*30),*password = (char *)malloc(sizeof(char)*20);
    int sign=0;
    head = user;
    while (1) {
        IDname = (char *)malloc(sizeof(char)*11);
        printf("Please enter your IDname:\n");
        scanf(" %s",IDname);
        while (user!=NULL) {
            if(!strcmp(user->UsrItem.IDnum, IDname)){
                printf("head has %s\n",user->UsrItem.name);
                sign= 1;
                break;
            }
            user = user->nextusr;
        }
        printf("checking your IDname....\n");
        if(sign){
            printf("This IDname has existed, please try another\n");
        }
        else{
            strcpy(UserAdd.IDnum, IDname);
            break;
        }
    }
    printf("Please enter your name:\n");
    scanf(" %s",name);
    strcpy(UserAdd.name, name);
    printf("Please enter your password(less than 20 letters):\n");
    scanf(" %s",password);
    while (strlen(password)>21) {
        printf("Password too long, please retry\n");
        password = (char *)malloc(sizeof(char)*20);
        scanf(" %s",password);
    }
    strcpy(UserAdd.password, password);
    UserAdd.book1.ID = -1;
    UserAdd.book2.ID = -1;
    strcpy(UserAdd.num, "2");
    head = AddUsr(UserAdd, head);
    return head;
}
//it will alert user when unreasonable choice is given
void WrongChoice(){
    printf("Please enter correct command and try again\n");
};
//build a linked list of book
Bookl *BookChain(FILE *origin){
    int i=0;
    char *source = (char *)malloc(sizeof(char)),seg[]="\n|";
    while(1){
        char c = getc(origin);
        if (feof(origin)){
            break;
        }
        source[i] = c;
        i++;
        source = (char *)realloc(source, sizeof(char)*(i+1));
    }
    char *substr = strtok(source, seg);
    Bookl *head = NULL;
    Bookl *pre=NULL,*current;
    i = 0;
    while(substr!=NULL){
        current = (Bookl *)malloc(sizeof(Bookl));
        if (head ==NULL){
            head = current;
        }
        else{
            pre->nextbook=current;
        }
        current->nextbook=NULL;
        current->BookItem.ID = i;
        strcpy(current->BookItem.name, substr);
        substr = strtok(NULL, seg);
        strcpy(current->BookItem.writer, substr);
        substr = strtok(NULL, seg);
        strcpy(current->BookItem.status, substr);
        substr = strtok(NULL, seg);
        pre = current;
        i++;
    }
    return head;
}
//build a linked list of user
Usrl *UsrChain(FILE *origin){
    int i=0;
    char *source=(char *)malloc(sizeof(char)),seg[]="\n|";
    while(1){
        char c = getc(origin);
        if (feof(origin)){
            break;
        }
        source[i] = c;
        i++;
        source = (char *)realloc(source, sizeof(char)*(i+1));
    }
    char *substr = strtok(source, seg);
    Usrl *head = NULL;
    Usrl *pre=NULL,*current;
    while(substr!=NULL){
        current = (Usrl *)malloc(sizeof(Usrl));
        if (head ==NULL){
            head = current;
        }
        else{
            pre->nextusr=current;
        }
        current->nextusr=NULL;
        strcpy(current->UsrItem.IDnum, substr);
        substr = strtok(NULL, seg);
        strcpy(current->UsrItem.name, substr);
        substr = strtok(NULL, seg);
        strcpy(current->UsrItem.password, substr);
        substr = strtok(NULL, seg);
        current->UsrItem.book1.ID = TransStrToInt(substr);
        substr = strtok(NULL, seg);
        current->UsrItem.book2.ID = TransStrToInt(substr);
        substr = strtok(NULL, seg);
        strcpy(current->UsrItem.num, substr);
        substr = strtok(NULL, seg);
        pre = current;
    }
    return head;
}

//build a string of book, each book has one
char * MakeBookChar(char * char1,char *char2,char * char3){
    char *result = (char *)malloc(sizeof(char)*54);
    memset(result, 0, sizeof(result));
    char seg[] = "|";
    char *enter = "\n";
    strcat(result, char1);
    strcat(result, seg);
    strcat(result, char2);
    strcat(result, seg);
    strcat(result, char3);
    strcat(result, enter);
    return result;
}
//build a string of user, each user has one
char * MakeUserChar(char * char1,char *char2,char * char3,int ID1,int ID2,char *char4){
    char *result  = (char *)malloc(sizeof(char)*63);
    memset(result, 0,sizeof(result));
    char seg[] = "|";
    char *enter = "\n";
    char id1[6], id2[6];
    TransIntToStr(id1, ID1);
    TransIntToStr(id2, ID2);
    strcat(result, char1);
    strcat(result, seg);
    strcat(result, char2);
    strcat(result, seg);
    strcat(result, char3);
    strcat(result, seg);
    strcat(result, id1);
    strcat(result, seg);
    strcat(result, id2);
    strcat(result, seg);
    strcat(result, char4);
    strcat(result, enter);
    return result;
}
//split joint the book strings as a whole
char * MakeBookWhole(Bookl *booklist,char *write){
    write = (char *)malloc(sizeof(char)*54);
    int i=1;
    while(booklist!=NULL){
        char *name = booklist->BookItem.name;
        char *writer = booklist->BookItem.writer;
        char *status = booklist->BookItem.status;
        strcat(write, MakeBookChar(name, writer, status));
        write = (char *)realloc(write, sizeof(char)*(i+1)*54);
        booklist = booklist->nextbook;
        i++;
    }
    return write;
}
//split joint the user strings as a whole
char * MakeUserWhole(Usrl *userlist,char *write){
    write = (char *)malloc(sizeof(char)*54);
    memset(write, 0, sizeof(write));
    int i=1;
    while(userlist!=NULL){
        char *IDname = userlist->UsrItem.IDnum;
        char *name = userlist->UsrItem.name;
        char *password = userlist->UsrItem.password;
        int ID1 = userlist->UsrItem.book1.ID;
        int ID2 = userlist->UsrItem.book2.ID;
        char *num = userlist->UsrItem.num;
        strcat(write, MakeUserChar(IDname, name, password,ID1,ID2,num));
        write = (char *)realloc(write, sizeof(char)*(i+1)*63);
        userlist = userlist->nextusr;
        i++;
    }
    return write;
}
//write book files
void WriteInBook(char * book){
    FILE *fbook = fopen("book.txt", "w");
    fprintf(fbook, "%s",book);
    
    free(book);
    fclose(fbook);
}
//write user files
void WriteInUser(char *user){
    FILE *fuser = fopen("user.txt", "w");
    fprintf(fuser, "%s",user);
    free(user);
    fclose(fuser);
}
