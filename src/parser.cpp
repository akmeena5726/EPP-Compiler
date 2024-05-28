/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your expression below this line

Parser::Parser()
{
    symtable = new SymbolTable();
    last_deleted = -1;
}

class Stack
{
private:
    vector<ExprTreeNode *> stack;

public:
    Stack()
    {
        stack = vector<ExprTreeNode *>();
    }
    ~Stack()
    {
        stack.clear();
    }
    void push(ExprTreeNode *node)
    {
        stack.push_back(node);
    }
    ExprTreeNode *pop()
    {
        ExprTreeNode *node = stack.back();
        stack.pop_back();
        return node;
    }

    ExprTreeNode *top()
    {
        return stack.back();
    }

    bool empty()
    {
        return stack.empty();
    }
};

string typeFinder(string t)
{
    if (t == "+")
        return "ADD";
    else if (t == "-")
        return "SUB";
    else if (t == "*")
        return "MUL";
    else if (t == "/")
        return "DIV";
    else if (t == ":=")
        return "ASSIGN";
    else if (t == "del")
        return "DEL";
    else if (t == "ret")
        return "RET";
    else if (t[0] - '0' < 10 && t[0] - '0' >= 0)
        return "VAL";
    else if (t[0] == '-' && t.length() > 1 && t[1] - '0' >= 0 && t[1] - '0' < 10)
        return "VAL";
    else
        return "VAR";
}

const string LEFT_PAREN = "(";
const string RIGHT_PAREN = ")";

void Parser::parse(vector<string> expression)
{
    ExprTreeNode *root = new ExprTreeNode();

    if (typeFinder(expression[0]) == "DEL")
    {
        root->type = typeFinder(expression[0]);
        root->left = new ExprTreeNode();
        root->left->type = "DEL";
        root->right = new ExprTreeNode();
        root->right->type = "VAR";
        root->right->id = expression[2];

        expr_trees.push_back(root);
        last_deleted = symtable->search(expression[2]);
        symtable->remove(expression[2]);
    }

    else
    {
        root->type = typeFinder(expression[1]);
        root->left = new ExprTreeNode();
        root->left->type = typeFinder(expression[0]);
        if (root->left->type == "VAR")
        {
            root->left->id = expression[0];
            if (symtable->search(expression[0]) == -2)
            {
                symtable->insert(expression[0]);
            }
        }
        root->right = new ExprTreeNode();

        ExprTreeNode *curr = root->right;
        expr_trees.push_back(root);
        Stack stack;
        stack.push(root);
        for (size_t i = 2; i < expression.size(); i++)
        {
            if (expression[i] == LEFT_PAREN)
            {
                ExprTreeNode *newNode = new ExprTreeNode();
                curr->left = newNode;
                stack.push(curr);
                curr = curr->left;
            }
            else if (expression[i] == RIGHT_PAREN)
            {
                curr = stack.pop();
            }
            else if (typeFinder(expression[i]) == "VAL")
            {
                curr->type = "VAL";
                curr->num = stoi(expression[i]);
                curr = stack.pop();
            }
            else if (typeFinder(expression[i]) == "VAR")
            {
                curr->type = "VAR";
                curr->id = expression[i];
                curr = stack.pop();
            }
            else
            {
                curr->type = typeFinder(expression[i]);
                curr->right = new ExprTreeNode();
                stack.push(curr);
                curr = curr->right;
            }
        }
    }
}

Parser::~Parser()
{
    // for (size_t i = 0; i < expr_trees.size(); i++)
    // {
    //     delete expr_trees[i];
    // }
    // delete symtable;
}