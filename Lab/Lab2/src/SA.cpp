#include "SA.hpp"
#include <string>
#include <string>
#include "info.hpp"
/*
符号表相关：
1. 调用未定义的函数, 使用未定义的变量 done
2. 重复定义函数, 同一个作用域内重复定义变量 done
类型检查相关：
1. 变量定义或赋值中左右表达式类型不匹配
2. 操作数类型不匹配或操作数类型与操作符不匹配, 如整型变量与数组变量相加减
3. return 语句的返回类型与函数定义的返回类型不匹配 done
4. 函数调用时实参与形参的数目(done)或类型不匹配; 特别的, 函数调用时数组对应维数不匹配
5. 对非数组型变量使用 "[...]" (数组访问) 操作符 done
6. 对普通变量使用 "(...)" (函数调用) 操作符, 也可以认为是调用未定义的函数 done
*/
// 检查一个vardef是不是定义了一个数组
void SemanticAnalyzer::enterNode(AST *node)
{
    std::string nodeType = node->get_node_type();
    if (nodeType == "Block")
    {
        if (env.enterFuncDef)
        {
            env.enterFuncDef = false;
            return;
        }
        this->enterBlock();
    }
    else if (nodeType == "FuncDef")
    {
        this->enterBlock();
        env.enterFuncDef = true;
    }
}
void SemanticAnalyzer::leaveNode(AST *node)
{
    std::string nodeType = node->get_node_type();
    if (nodeType == "Block")
    {
        this->leaveBlock();
    }
    if (nodeType == "FuncDef")
    {
        env.functionReturnType = ValType::NODEF;
    }
}
bool SemanticAnalyzer::registerVar(AST *cur, bool isParam = false)
{

    std::cout << "Register node " << cur->id << " " + cur->get_node_type() << std::endl;
    auto name = cur->children[1]->str_value;
    if (varHasDefindedInBlock(name))
    {
        errorInfo("[registerVar]:: duplicate declearation of " + name);
        return false;
    }
    Type varType;
    if (cur->get_node_type() == "FuncParam")
    {
        // int
        successInfo("int");
        varType = Type("var", "int");
    }
    else
    {
        // int arr
        successInfo("[registerVar]:: intarr");
        varType = Type("var", "intarray");
        varType.add_array_dimention(-1);
        if (cur->childNum() > 2)
        {
            for (auto dimNode : cur->children[2]->children)
            {
                varType.add_array_dimention(dimNode->int_value);
            }
        }
    }
    successInfo("[registerVar]:: insert " + name);
    insertVar(name, varType);
    successInfo("[registerVar]:: insertDone");
    if (isParam)
    {
        printVar("func", *env.curFuncType);
        env.curFuncType->add_func_arg(varType);
    }
    successInfo("[registerVar]::  done!");
    return true;
}
bool SemanticAnalyzer::registerFunc(AST *cur)
{
    if (cur->get_node_type() != "FuncDef")
    {
        errorInfo("[registerFunc]:: not a func def");
        return false;
    }
    AST *typeNode = cur->children[0];
    AST *identNode = cur->children[1];
    std::string name = identNode->str_value;
    if (funcHasDefinded(identNode->str_value))
    {
        // duplicate def
        errorInfo("[registerFunc]:: duplicate func defination");
        return false;
    }
    Type funcType;
    if (typeNode->get_node_type() == "BType")
    {
        funcType = Type("func", "int");
    }
    else if (typeNode->get_node_type() == "void")
    {
        funcType = Type("func", "void");
    }
    // deal with params
    if (cur->children.size() == 4)
    {
        // has params
        env.curFuncType = &funcType;
        AST *params = cur->children[2];
        for (auto child : params->children)
        {
            if (!registerVar(child, true))
            {
                return false;
            };
        }
        printVar(name, funcType);
    }
    else
    {
        // no params
    }
    insertFunc(name, funcType);
    env.functionReturnType = funcType.valType;
    successInfo(name + " func registered");
    return true;
    //
}
bool SemanticAnalyzer::check_type(AST *cur)
{
    int nodeID = cur->id;
    visitedID.push_back(nodeID);
    visitedNode.push_back(cur);
    // 应该是一个后序的遍历
    std::cout << cur->get_node_type() << std::endl;
    std::string nodeType = cur->get_node_type();

    enterNode(cur);
    // 把定义类的提前处理，提前检查出未定义类型的错误
    {

        if (nodeType == "VarDecl")
        {
            std::cout << "it is a VarDecl with children:" << cur->children.size() << std::endl;
            for (auto singleVarDef : cur->children)
            {
                if (singleVarDef == cur->children[0])
                {
                    std::cout << "Type Node: " + singleVarDef->get_node_type() << std::endl;
                    continue;
                }
                if (singleVarDef->get_node_type() == "VarDef")
                {
                    std::string varName = singleVarDef->children[0]->str_value;
                    std::cout << "varName: " << varName << std::endl;
                    if (varHasDefindedInBlock(varName))
                    {
                        // std::cout << "redefinition of " << varName << std::endl;
                        // return false;
                        errorInfo("redefinition of " + varName);
                        return false;
                    } // 检查是否有重复定义
                    // 获得类型
                    Type varType;
                    if (!isArray(singleVarDef))
                    {
                        // 插入变量
                        varType = Type("var", "int");
                    }
                    else
                    {
                        // 插入数组
                        varType = Type("var", "intarray");
                        for (auto dimention : singleVarDef->children[1]->children)
                        {
                            varType.add_array_dimention(dimention->int_value);
                        }
                    }
                    std::cout << "insert var" << std::endl;
                    insertVar(varName, varType);
                    std::cout << "print var" << std::endl;
                    printVar(varName, varType);
                }
                else
                {
                    std::cout << "Type Node: " + singleVarDef->get_node_type() << std::endl;
                }
            }
        }
        else if (nodeType == "FuncDef")
        {
            if (!registerFunc(cur))
            {
                return false;
            };
        }
        else if (nodeType == "Ident")
        {
            // 只检查有没有定义
            if (!varHasDefinded(cur->str_value) && !funcHasDefinded(cur->str_value))
            {
                errorInfo("undefined var or func " + cur->str_value);
                return false;
            }
        }
        else if (nodeType == "FunCall")
        {
            // 提前检查：函数是否定义，参数个数是否匹配
            auto funcName = cur->children[0]->str_value;
            // 1. check if function has been defined
            if (!funcHasDefinded(funcName))
            {
                errorInfo("func " + funcName + " not defined");
                return false;
            }
            // 2. check if function argument number is correct
            Type funcType = lookUpFunc(funcName);
            int funcArgCount = funcType.func_args_type.size();
            if (cur->children.size() == 1)
            {
                // call with no param
                if (funcArgCount != 0)
                {
                    errorInfo("func " + funcName + " expect " + std::to_string(funcArgCount) + " args but got 0");
                    return false;
                }
            }
            else
            {
                int callArgCount = cur->children[1]->children.size();
                if (funcArgCount != callArgCount)
                {
                    errorInfo("func " + funcName + " expect " + std::to_string(funcArgCount) + " args but got " + std::to_string(callArgCount));
                    return false;
                }
            }
            // todo: check if fuction parameters' type are correct
        }
        else if (nodeType == "Return")
        {
            // 只检查返回值类型是否匹配
            if (cur->children.size() == 0 && env.functionReturnType == ValType::INT)
            {
                errorInfo("return type mismatch expect int");
                return false;
            }
            else if (cur->children.size() == 1 && env.functionReturnType == ValType::VOID)
            {
                errorInfo("return type mismatch expect void");
                return false;
            }
            if (env.functionReturnType == ValType::NODEF)
            {
                errorInfo("this is super weird! return in a random crazy block?");
                return false;
            }
        }
        else if (nodeType == "LVal")
        {
            successInfo("LVal" + std::to_string(cur->id));
            if (cur->childNum() == 2)
            {
                // 一个使用数组方法的左值
                // 检查是否对于int变量采用了数组调用方法（反之无法在这里检查）
                std::string name = cur->children[0]->str_value;
                if (!varHasDefinded(name))
                {
                    // todo: seems needless?
                    errorInfo("undefined var " + name);
                    return false;
                }
                else
                {
                    Type varType = lookUpVar(name);
                    if (varType.valType != ValType::INTARRAY)
                    {
                        errorInfo("int var " + name + " is not an array");
                        return false;
                    }
                }
            }
        }
    }

    // 从下至上构建返回值表
    for (auto child : cur->children)
    {
        if (!check_type(child))
        {
            leaveNode(cur);
            return false;
        };
    }
    // 检查值的match与否
    if (nodeType == "IntConst")
    {
        cur->expType = Type("var", "int");
        cur->hasInstantValue = true;
        cur->instantValue = cur->int_value;
    }
    else if (nodeType == "Number")
    {
        cur->expType = Type("var", "int");
        cur->hasInstantValue = true;
        cur->instantValue = cur->children[0]->getInstantValue();
    }
    else if (nodeType == "Ident")
    {
        cur->expType = lookUpVar(cur->str_value);
    }
    else if (nodeType == "LVal")
    {
        std::string varName = cur->children[0]->str_value;
        Type rawVarType = lookUpVar(varName);
        if (cur->children.size() == 1)
        {
            cur->expType = rawVarType;
        }
        else
        {
            // todo: check array type
            auto arrayDimNode = cur->children[1];
            int arrayDim = arrayDimNode->children.size();
            int rawDim = rawVarType.array_dimentions.size();
            // 检查维度[]中的是不是都是int
            for (auto dimExp : arrayDimNode->children)
            {
                if(dimExp->expType.valType != ValType::INT){
                    errorInfo("array dimention should be int");
                    return false;
                }
            }
            if (rawDim < arrayDim)
            {
                errorInfo("array dimention mismatch, too many dimention");
                return false;
            }
            else if (rawDim == arrayDim)
            {
                cur->expType = Type("var", "int");
            }
            else
            {
                for (int i = 0; i < arrayDim; i++)
                {
                    rawVarType.array_dimentions.pop_front();
                }
                cur->expType = rawVarType;
            }
        }
    }
    else if (nodeType == "FunCall")
    {
        // 1. 设定自己的返回type
        // children[0] ident
        // children[1] args
        cur->expType = lookUpFunc(cur->children[0]->str_value);
        // 2. 检查参数类型是否匹配
        std::string funcName = cur->children[0]->str_value;
        Type funcType = lookUpFunc(funcName);

        // 2.1 检查参数个数
        int defParamNum = funcType.func_args_type.size();
        // 2.1.1 无参数函数检查
        if (cur->children.size() == 1)
        {
            if (defParamNum != 0)
            {
                errorInfo("FunCall arg number doe not match");
                return false;
            }
            else
            {
                return true;
            }
        }
        // 2.1.2 有参数函数检查
        AST *argNode = cur->children[1];
        if (argNode->childNum() != funcType.func_args_type.size())
        {
            errorInfo("FunCall arg number doe not match");
        }
        // 2.2 检查参数类型是否正确
        for (int i = 0; i < argNode->childNum(); i++)
        {
            Type defType = funcType.func_args_type[i];
            Type paramType = argNode->children[i]->expType;
            if (!defType.equalVal(paramType))
            {
                errorInfo("FunCall Check failed, different call type");
                return false;
            }
        }
    }
    else if (nodeType == "UnaryExp" || nodeType == "LOrExp" || nodeType == "LAndExp" || nodeType == "EqExp" || nodeType == "RelExp" || nodeType == "AddExp" || nodeType == "MulExp" || nodeType == "PrimaryExp" || nodeType == "Exp")
    {
        // these are made up of different types of exps
        if (cur->childNum() == 1)
        {
            cur->expType = cur->children[0]->expType;
        }
        else
        {
            Type firstType = cur->children[0]->expType;
            if (nodeType == "UnaryExp")
            {
                firstType = cur->children[1]->expType;
            }
            // 检查非void
            if (firstType.valType == ValType::VOID)
            {
                errorInfo("void type in " + nodeType);
                return false;
            }
            // 检查所有表达式的类型是否一致（只需要检查val相关的部分）
            for (auto expChild : cur->children)
            {
                if (expChild->get_node_type() == "basic AST")
                {
                    continue;
                }
                else
                {
                    if (!firstType.equalVal(expChild->expType))
                    {
                        errorInfo("ID: " + std::to_string(cur->id) + " type mismatch in " + nodeType);
                        return false;
                    }
                }
            }
            cur->expType = firstType;
        }
    }
    else if (nodeType == "Assign")
    {
        Type leftType = cur->children[0]->expType;
        if(leftType.valType == ValType::VOID){
            errorInfo("void type in assign");
            return false;
        }else if(leftType.valType == ValType::INTARRAY){
            errorInfo("array type in assign");
            return false;
        }
        Type rightType = cur->children[1]->expType;
        if (!leftType.equalVal(rightType))
        {
            errorInfo("type mismatch in assign");
            return false;
        }
    }
    else if (nodeType == "basic AST")
    {
        // 什么都不做
        // basic operators, has no influence over the instant value
        cur->hasInstantValue = true;
    }
    leaveNode(cur);

    return true;
}
bool SemanticAnalyzer::check_children_type(AST *cur)
{
    for (auto child : cur->children)
    {
        if (!check_type(child))
        {
            return false;
        };
    }
    return true;
}
