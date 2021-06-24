#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <time.h>

#include "bTree.h"

#define NAMESIZE 128

struct Data
{
    unsigned char drugCode;  // 药码
    char drugName[NAMESIZE]; // 药名
};

static int print(struct Data *treeData)
{
    printf("drugCode: %hhu drugName: %s\n",
           treeData->drugCode, treeData->drugName);

    return 0;
}

int main()
{
    int idxArr[] = {1, 2, 3, 7, 6, 5, 9, 8, 4};
    int i;
    struct Data drugData;
    bTree *treeRoot = NULL; // 指针初始化为NULL，防止指向一块未知的空间

    for (i = 0; i < sizeof(idxArr) / sizeof(*idxArr); i++)
    {
        uuid_generate(&drugData.drugCode);
        snprintf(drugData.drugName, NAMESIZE, "drug_%ld", time(NULL) - idxArr[i]);

        treeInsert(&treeRoot, &drugData, idxArr[i], sizeof(struct Data));
    }

    int idx = 6;
    bTree *treeNode = NULL;
    treeSearch(treeRoot, idx, &treeNode);
    if (NULL != treeNode)
    {
        struct Data *drugNode = treeNode->data;
        print(drugNode);
    }

    // 根节点从左边第0个字符开始打印
    treeDraw(treeRoot, 0);

    return 0;
}
