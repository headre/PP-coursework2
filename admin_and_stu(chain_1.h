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
    char *name;
    char *status;
    char *writer;
    struct book *nextbook;
};
struct usr{
    char *IDnum;
    char *name;
    char *password;
    struct book *book1;
    struct book *book2;
    char *num;
    struct usr *nextusr;
};
struct account{
    struct usr *returnusr;
    struct book *returnbook;
};
#endif /* admin_and_stu_chain_1_h */
