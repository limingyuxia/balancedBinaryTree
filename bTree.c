#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bTree.h"

// 插入节点
int treeInsert(bTree **tree, void *data, int idx, int dataSize)
{
    bTree *treeNode = NULL;

    // 叶子节点的左右节点
    if (NULL == *tree)
    {
        // 创建节点
        treeNode = malloc(sizeof(bTree));
        if (NULL == treeNode)
        {
            perror("malloc: ");
            return -1;
        }
        treeNode->data = malloc(dataSize);
        if (NULL == treeNode->data)
        {
            perror("malloc: ");
            return -1;
        }

        treeNode->left = NULL;
        treeNode->right = NULL;
        treeNode->idx = idx;
        if (NULL == memcpy(treeNode->data, data, dataSize))
        {
            perror("memcpy: ");
            return -2;
        }

        // 连接节点
        *tree = treeNode;

        return 0;
    }

    // 新节点的索引比根节点大，向根节点右子树走
    if (idx > (*tree)->idx)
    {
        return treeInsert(&(*tree)->right, data, idx, dataSize);
    }

    return treeInsert(&(*tree)->left, data, idx, dataSize);
}

// 查找节点
int treeSearch(bTree *tree, int idx, bTree **node)
{
    if (NULL == tree)
    {
        return -1;
    }

    // 索引比较
    if (tree->idx == idx)
    {
        *node = tree;
        return 0;
    }

    if (idx > tree->idx)
    {
        return treeSearch(tree->right, idx, node);
    }

    return treeSearch(tree->left, idx, node);
}

void treeDraw(bTree *tree, int level)
{
    int i;

    // 遍历到叶子节点的左右子树
    if (NULL == tree)
        return;

    // 树向左倒，先画右子树，再画根节点，在画左子树
    treeDraw(tree->right, level + 1);

    // 画节点之前，根据节点所在的层数，打印分割符
    for (i = 0; i < level; i++)
        printf("\t");

    //sleep(1);
    printf("%d\n\n", tree->idx);

    // 找到第一个要画的节点以后，还要找下一个，所以不return
    treeDraw(tree->left, level + 1);
}
