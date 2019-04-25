//
//  admin_and_stu(chain_1.h
//  library system
//
//  Created by headreaper on 2019/4/19.
//  Copyright © 2019 headreaper. All rights reserved.
//

#ifndef admin_and_stu_chain_1_h
#define admin_and_stu_chain_1_h

#include <stdio.h>
struct book{
    int ID;
    char name[30];
    char status[4];
    char writer[20];
};
typedef struct book Book;
typedef struct bookl{
    Book BookItem;
    struct bookl *nextbook;
}Bookl;
typedef Bookl *BookList;
struct usr{
    char IDnum[11];
    char name[30];
    char password[20];
    struct book book1;
    struct book book2;
    char num[2];
};
typedef  struct usr Usr;
typedef struct usrl{
    Usr UsrItem;
    struct usrl *nextusr;
}Usrl;
typedef Usrl *UsrList;
#endif /* admin_and_stu_chain_1_h */
