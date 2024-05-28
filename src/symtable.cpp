/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "../include/symtable.h"
// Write your code below this line

SymbolTable::SymbolTable()
{
    root = NULL;
    size = 0;
}

int balanceFactor(SymNode *node)
{
    return (node->right ? node->right->height : -1) - (node->left ? node->left->height : -1);
}

void updateHeight(SymNode *node)
{
    if (node == NULL)
        return;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;
    node->height = max(leftHeight, rightHeight) + 1;
}

void balanceTree(SymNode *node, SymNode *&root_node, bool isDelete = false)
{
    if (isDelete == false)
        node = node->par;
    if (node == NULL)
        return;
    while (node != NULL)
    {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf == 2)
        {
            if (balanceFactor(node->right) == 1)
            {
                node = node->LeftLeftRotation();
            }
            else
            {
                node = node->LeftRightRotation();
            }
        }
        else if (bf == -2)
        {
            if (balanceFactor(node->left) == -1)
            {
                node = node->RightRightRotation();
            }
            else
            {
                node = node->RightLeftRotation();
            }
        }
        if (node->par == NULL)
            break;
        node = node->par;
    }
    root_node = node;
}

void insertHelper(SymNode *&node, string k, SymNode *&root, SymNode *parent = NULL)
{
    if (node == NULL)
    {
        node = new SymNode(k);
        node->par = parent;
        balanceTree(node, root);
        return;
    }
    else if (node->key > k)
    {
        insertHelper(node->left, k, root, node);
    }
    else
    {
        insertHelper(node->right, k, root, node);
    }
}

void SymbolTable::insert(string k)
{
    insertHelper(root, k, root);
    size++;
}

SymNode *findMinVal(SymNode *root)
{
    if (root == NULL)
        return root;
    while (root->left != NULL)
        root = root->left;
    return root;
}

SymNode *removeHelper(SymNode *node, string k, SymNode *&root)
{
    if (node == NULL)
        return node;
    else if (node->key > k)
        node->left = removeHelper(node->left, k, root);
    else if (node->key < k)
        node->right = removeHelper(node->right, k, root);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }
        if (node->left == NULL || node->right == NULL)
        {
            SymNode *temp = node->left ? node->left : node->right;
            temp->par = node->par;
            if (node->par)
            {
                if (node->par->left == node)
                    node->par->left = temp;
                else if (node->par->right == node)
                    node->par->right = temp;
            }
            // delete node;
            return temp;
        }
        SymNode *temp = findMinVal(node->right);
        node->key = temp->key;
        node->right = removeHelper(node->right, temp->key, root);
        // return node;
    }
    balanceTree(node, root);
    return node;
}

void SymbolTable::remove(string k)
{
    SymNode *res = removeHelper(root, k, root);
    if (res)
    {
        // balanceTree(res, root);
        size--;
    }
}

int searchHelper(SymNode *node, string k)
{
    if (node == NULL)
        return -2;
    else if (node->key > k)
        return searchHelper(node->left, k);
    else if (node->key < k)
        return searchHelper(node->right, k);
    else
        return node->address;
}

int SymbolTable::search(string k)
{
    return searchHelper(root, k);
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *node = root;
    while (node != NULL)
    {
        if (node->key > k)
            node = node->left;
        else if (node->key < k)
            node = node->right;
        else
        {
            node->address = idx;
            break;
        }
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void deleteSymNode(SymNode *node)
{
    if (node == NULL)
        return;
    deleteSymNode(node->left);
    deleteSymNode(node->right);
    if (node->par != NULL)
    {
        if (node->par->left == node)
        {
            node->par->left = NULL;
        }
        else if (node->par->right == node)
        {
            node->par->right = NULL;
        }
    }
    delete node;
}

SymbolTable::~SymbolTable()
{
    deleteSymNode(root);
}