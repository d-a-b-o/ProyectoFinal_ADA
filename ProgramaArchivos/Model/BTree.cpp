#pragma once
#include "BTree.h"

using namespace std;

BTreeNode::BTreeNode(int _t, bool _leaf)
{
    t = _t;
    leaf = _leaf;
    n = 0;
    keys.resize(2 * t - 1);
    children.resize(2 * t);
}

void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!leaf)
            children[i]->traverse();

        cout << " " << keys[i];
    }

    if (!leaf)
        children[i]->traverse();
}

bool BTreeNode::search(int k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return true;

    if (leaf)
        return false;

    return children[i]->search(k);
}

void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;
    if (leaf)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n++;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);

    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf)
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n++;
}

void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    if (idx < n && keys[idx] == k)
    {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        /* Pendiente manejar mejor caso de dato no existente */ 
        if (leaf)
        {
            cout << "El dato " << k << " no existe en el arbol.\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (children[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
    return;
}

// Indice de la primera clave >= que k
int BTreeNode::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        idx++;

    return idx;
}

void BTreeNode::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; i++)
        keys[i - 1] = keys[i];
    n--;
    return;
}

void BTreeNode::removeFromNonLeaf(int idx)
{
    int k = keys[idx];

    if (children[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    else if (children[idx + 1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    else
    {
        merge(idx);
        children[idx]->remove(k);
    }
    return;
}

int BTreeNode::getPred(int idx)
{
    BTreeNode *cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int BTreeNode::getSucc(int idx)
{
    BTreeNode *cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx)
{
    if (idx != 0 && children[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && children[idx + 1]->n >= t)
        borrowFromNext(idx);
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
        for (int i = child->n; i >= 0; i--)
            child->children[i + 1] = child->children[i];

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::borrowFromNext(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys[(child->n)] = keys[idx];

    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i - 1] = sibling->children[i];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTreeNode::merge(int idx)
{
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf)
        for (int i = 0; i <= sibling->n; i++)
            child->children[i + t] = sibling->children[i];

    for (int i = idx + 1; i < n; i++)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; i++)
        children[i - 1] = children[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

BTree::BTree(int _t)
{
    root = nullptr;
    t = _t;
}

void BTree::traverse()
{
    if (root != nullptr)
    {
        root->traverse();
    }
}

bool BTree::search(int k)
{
    if (root == nullptr)
        return false;
    else
        return root->search(k);
}

void BTree::insert(int k)
{
    if (root == nullptr)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;

            s->children[i]->insertNonFull(k);
            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

void BTree::remove(int k)
{
    /* Pendiente manejar mejor caso arbol vacio */
    if (!root)
    {
        cout << "El arbol esta vacio\n";
        return;
    }

    root->remove(k);

    if (root->n == 0)
    {
        BTreeNode *temp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete temp;
    }
    return;
}