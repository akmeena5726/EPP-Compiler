/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "../include/exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    type = "";
    id = "";
    // num = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    type = t;
    if (t == "VAL")
        num = v;
    if (t == "VAR")
        id = to_string(v);
}

ExprTreeNode::~ExprTreeNode()
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
    // delete this;
}