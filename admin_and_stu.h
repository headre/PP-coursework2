//
//  admin_and_stu.h
//  library system
//
//  Created by headreaper on 2019/2/3.
//  Copyright © 2019 headreaper. All rights reserved.
//

#ifndef admin_and_stu_h
#define admin_and_stu_h

#include <stdio.h>
typedef struct{
    char name[40];
    char status[1];
}book;
typedef struct{
    char IDnumber[10];
    char name[10];
    char password[8];
    char num[1];
    book *book1;
    book *book2;
}usr;
typedef struct{
    usr **returnusr;
    book **returnbook;
} accounts;
#endif /* admin_and_stu_h */
