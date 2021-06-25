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

// 绘画树
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

// 获取根节点左子树或者右子树节点的数量
static int getNodeNum(bTree *tree)
{
    if (NULL == tree)
    {
        return 0;
    }

    // 递归叶子节点的左子树，根节点和右子树
    return getNodeNum(tree->left) + 1 + getNodeNum(tree->right);
}

static bTree *maxLeftDepth(bTree *tree)
{
    if (NULL == tree->left)
    {
        return tree;
    }

    return maxLeftDepth(tree->left);
}

static bTree *maxRightDepth(bTree *tree)
{
    if (NULL == tree->right)
    {
        return tree;
    }

    return maxRightDepth(tree->right);
}

// 左旋
static int turnLeft(bTree **tree)
{
    bTree *root = *tree;    // 记录根节点
    *tree = (*tree)->right; // 根子树的右子树的根节点变为新的根节点
    root->right = NULL;     // 旧根节点断开右子树

    bTree *leftNode;
    leftNode = maxLeftDepth(*tree); // 找到新的根节点最深的左子树节点
    leftNode->left = root;

    return 0;
}

// 右旋
static int turnRight(bTree **tree)
{
    bTree *root = *tree;
    (*tree) = (*tree)->left;
    root->left = NULL;

    bTree *rightNode;
    rightNode = maxRightDepth(*tree); // 找到新的根节点最深的左子树节点
    rightNode->right = root;

    return 0;
}

// 平衡树
void treeBalance(bTree **tree)
{
    int sub = 0;
    if (NULL == *tree)
    {
        // 递归到叶子节点的左右子树
        return;
    }

    while (1)
    {
        // 根节点的左子树节点的个数和右子树节点的个数，差值为1，认为树平衡
        sub = getNodeNum((*tree)->left) - getNodeNum((*tree)->right);
        if (sub >= -1 && sub <= 1)
        {
            break;
        }
        // 左旋：当前节点的右子树作为根节点。左子树作为新根节点的左子树
        else if (sub < -1)
        {
            turnLeft(tree);
        }
        // 右旋：当前节点的左子树作为根节点。右子树作为新根节点的右子树
        else if (sub > 1)
        {
            turnRight(tree);
        }
    }

    // 根节点平衡好以后，平衡左右子树
    treeBalance(&(*tree)->left);

    treeBalance(&(*tree)->right);
}