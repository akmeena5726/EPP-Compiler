/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "../include/symnode.h"

// Write your code below this line

SymNode::SymNode()
{
    key = "";
    height = 0;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
}

void update(SymNode *node)
{
    if (node == NULL)
        return;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;

    node->height = max(leftHeight, rightHeight) + 1;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *temp = this->right;    
    if (temp->left != NULL)
    {
        this->right = temp->left;
        temp->left->par = this;
    }
    else 
    {
        this->right = NULL;
    }
    if (this->par != NULL)
    {
        if (this->par->left == this)
            this->par->left = temp;
        else
            this->par->right = temp;
    }
    temp->par = this->par;
    this->par = temp;
    temp->left = this;
    update(this);
    update(temp);
    return temp;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *temp = this->left;
    if (temp->right != NULL)
    {
        this->left = temp->right;
        temp->right->par = this;
    }
    else 
    {
        this->left = NULL;
    }
    if (this->par != NULL)
    {
        if (this->par->left == this)
            this->par->left = temp;
        else
            this->par->right = temp;
    }
    temp->par = this->par;
    this->par = temp;
    temp->right = this;
    update(this);
    update(temp);
    return temp;
}

SymNode *SymNode::LeftRightRotation()
{
    this->right = this->right->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    this->left = this->left->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode::~SymNode()
{
    // if (left != NULL)
    // {
    //     // delete left;
    //     left = NULL;
    // }
    // if (right != NULL)
    // {
    //     // delete right;
    //     right = NULL;
    // }
    // if (par != NULL)
    // {
    //     if (par->left == this)
    //         par->left = NULL;
    //     else if (par->right == this)
    //         par->right = NULL;
    // }
    // delete this;
}