/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// Write your code below this line

EPPCompiler::EPPCompiler()
{
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0; i < mem_limit; i++)
    {
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    for (vector<string> expression : code)
    {
        targ.parse(expression);
        if (expression[0] == "RET")
            continue;
        if (expression[0] == "DEL")
            mem_loc.push_back(targ.last_deleted);
        else
        {
            if (targ.symtable->search(expression[0]) == -1)
            {
                int mem = mem_loc.back();
                mem_loc.pop_back();
                targ.symtable->assign_address(expression[0], mem);
            }
        }
        vector<string> commands = generate_targ_commands();
        write_to_file(commands);
    }
}

void createCode(ExprTreeNode *root, vector<string> &result, SymbolTable *store)
{
    if (root == NULL)
        return;

    createCode(root->right, result, store);
    createCode(root->left, result, store);
    string command;
    if (root->type == "VAR")
        command = "PUSH mem[" + to_string(store->search(root->id)) + "]";
    else if (root->type == "VAL")
        command = "PUSH " + to_string(root->num);
    else
        command = root->type;
    result.push_back(command);
}

vector<string> EPPCompiler::generate_targ_commands()
{
    ExprTreeNode *last = targ.expr_trees.back();
    vector<string> result;
    string command;
    if (last->left->type == "DEL")
    {
        command = "DEL = mem[" + to_string(targ.last_deleted) + "]";
    }
    else
    {
        createCode(last->right, result, targ.symtable);
        if (last->left->type == "RET")
            command = "RET = POP";
        else
            command = "mem[" + to_string(targ.symtable->search(last->left->id)) + "] = POP";
    }
    result.push_back(command);
    return result;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream file;
    file.open(output_file, ios::app);
    for (string command : commands)
    {
        file << command << endl;
    }
    file.close();
}

EPPCompiler::~EPPCompiler()
{
    // delete targ.symtable;
    // for (ExprTreeNode *node : targ.expr_trees)
    // {
    //     delete node;
    // }
}