#ifndef SA_HPP
#define SA_HPP
#include "tree.hpp"
#include "Type.hpp"
#include <string>
#include <vector>
#include <tuple>
#include <map>

class Env
{
public:
    ValType functionReturnType = ValType::NODEF;
    ValType blockReturnType;
    Type *curFuncType;
    bool enterFuncDef = false;
};
class SemanticAnalyzer
{
    std::vector<AST *> visitedNode;
    std::vector<int> visitedID;
    bool isArray(AST *cur)
    // for VarDef and FuncParam node only!!!!
    {
        if (cur->get_node_type() == "VarDef")
        {
            if(cur->children.size() > 1){
                return (cur->children[1]->get_node_type().find("Array") != std::string::npos);
            };
            return false;
        }
        else
        {
            errorInfo("not an array!");
            return false;
        }
    }
    void printVar(std::string name, Type type)
    {
        std::cout << "name: " << name << " type: ";
        if (type.valType == ValType::INT)
        {
            std::cout << "int";
        }
        else if (type.valType == ValType::INTARRAY)
        {
            std::cout << "intarray";
            for (auto dimention : type.array_dimentions)
            {
                std::cout << "[" << dimention << "]";
            }
        }
        else
        {
            std::cout << "error";
        }
        std::cout << std::endl;
    }
    void errorInfo(std::string info)
    {
        std::cout << "\033[31m" << info << "\033[0m" << std::endl; // \033[31m 设置红色，\033[0m 重置颜色
    }
    void successInfo(std::string info)
    {
        std::cout << "\033[32m" << info << "\033[0m" << std::endl; // \033[32m 设置绿色，\033[0m 重置颜色
    }
    void prepare_sysfunc()
    {
        func_table["getint"] = Type("func", "int");
        func_table["getch"] = Type("func", "int");
        func_table["getarray"] = Type("func", "int", Type("var", "intarray"));
        func_table["putint"] = Type("func", "void", Type("var", "int"));
        func_table["putch"] = Type("func", "void", Type("var", "int"));
        func_table["putarray"] = Type("func", "void", Type("var", "int"), Type("var", "intarray"));
    }

public:
    Env env;
    bool check_type(AST *cur);
    bool check_children_type(AST *cur);
    typedef std::map<std::string, Type> SymbolTable;
    std::vector<SymbolTable> var_table;
    SymbolTable func_table;
    SemanticAnalyzer()
    {
        prepare_sysfunc();
        var_table.push_back(SymbolTable());
    }
    bool contains(std::string name)
    {
        if (var_table.back().find(name) != var_table.back().end())
        {
            return true;
        }
        if (func_table.find(name) != func_table.end())
        {
            return true;
        }
        return false;
    }
    bool varHasDefindedInBlock(std::string name){
        if (var_table.back().find(name) != var_table.back().end())
        {
            return true;
        }
        return false;
    };
    bool varHasDefinded(std::string name){
        for (auto it = var_table.rbegin(); it != var_table.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return true;
            }
        }
        return false;
    };
    bool funcHasDefinded(std::string name){
        if (func_table.find(name) != func_table.end())
        {
            return true;
        }
        return false;
    };
    Type lookUpVar(std::string name)
    {
        Type res = Type("var", "error");
        for (auto it = var_table.rbegin(); it != var_table.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                res = (*it)[name];
            }
        }
            return res;
    }
    Type lookUpFunc(std::string name)
    {
        if (func_table.find(name) != func_table.end())
        {
            return func_table[name];
        }
        return Type("func", "error");
    }
    void insertVar(std::string name, Type type)
    {
        if (var_table.empty())
        {
            std::cout << "empty table" << std::endl;
        }
        var_table.back()[name] = type;
    }
    void insertFunc(std::string name, Type type)
    {
        func_table[name] = type;
    }
    void enterBlock()
    {
        var_table.push_back(SymbolTable());
    }
    void leaveBlock()
    {
        var_table.pop_back();
    }
    void enterNode(AST *node);
    void leaveNode(AST *node);
    bool registerFunc(AST *node);
    bool registerVar(AST *node, bool isParam);
    // todo: finish these
    // bool childrenHasSameType(AST *cur);
    bool canHaveInstantValue(AST *cur){
        if(cur->get_node_type() == "Ident"){
            return false;
        }
        for(auto child: cur->children){
            if(!child->hasInstantValue){
                return false;
            }
        }
        return true;
    }
};

#endif