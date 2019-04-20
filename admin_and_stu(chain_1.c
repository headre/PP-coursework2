//
//  admin_and_stu(chain_1.c
//  library system
//
//  Created by headreaper on 2019/4/19.
//  Copyright © 2019 headreaper. All rights reserved.
//

#include "admin_and_stu(chain_1.h"
#include <stdio.h>

struct account *MakeAccounts(struct usr *UsrList,struct book *BookList){
    struct account *accounts = NULL;
    accounts->returnbook=BookList;
    accounts->returnusr=UsrList;
    return accounts;
}
