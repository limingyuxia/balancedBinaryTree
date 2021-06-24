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
    int idxArr[] = {1, 9, 4, 56, 34, 24, 76, 10};
    int i;
    struct Data drugData;
    bTree *treeRoot;

    for (i = 0; i < sizeof(idxArr) / sizeof(*idxArr); i++)
    {
        uuid_generate(&drugData.drugCode);
        snprintf(drugData.drugName, NAMESIZE, "drug_%ld", time(NULL) - idxArr[i]);

        treeInsert(&treeRoot, &drugData, idxArr[i], sizeof(struct Data));
    }

    int idx = 24;
    bTree *treeNode;
    treeSearch(treeRoot, idx, &treeNode);
    if (NULL != treeNode)
    {
        struct Data *drugNode = treeNode->data;
        print(drugNode);
    }

    return 0;
}
