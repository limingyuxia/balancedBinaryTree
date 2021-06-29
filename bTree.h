#ifndef B_TREE__
#define B_TREE__

typedef struct BinaryTree
{
    struct BinaryTree *left;
    struct BinaryTree *right;
    int idx;
    void *data;
} bTree;

// 插入节点
int treeInsert(bTree **, void *, int, int);

// 查找节点
int treeSearch(bTree *, int, bTree **);

// 绘画树
void treeDraw(bTree *, int);

// 平衡树
void treeBalance(bTree **);

// 删除节点
int treeDelete(bTree **, int);

// 树的遍历
void treeTravel(bTree *);

// 树的按层遍历
int treeTravelLevel(bTree *, int);

#endif
