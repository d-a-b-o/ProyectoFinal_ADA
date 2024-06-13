#pragma once
#include <vector>

using namespace std;

class BTreeNode
{
private:
    int t, n;
    bool leaf;
    vector<int> keys;
    vector<BTreeNode *> children;

public:
    BTreeNode(int _t, bool _leaf);
    void traverse();
    bool search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    void remove(int k);
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    friend class BTree;
};

class BTree
{
private:
    BTreeNode *root;
    int t;

public:
    BTree(int _t);
    
    void traverse();

    bool search(int k);
    void insert(int k);
    void remove(int k);
};