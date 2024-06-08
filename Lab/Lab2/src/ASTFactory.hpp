#ifndef AST_Factory
#define AST_Factory

#include <string>
#include <vector>
#include <iostream>
#include "tree.hpp"

class ASTFactory{
public:
    AST* makeNode(std::string type){
        return makeTypedNode(type);
    }
    AST* makeNode(std::string type, int value){
        auto newNode = makeTypedNode(type);
        newNode->int_value = value;
        return newNode;
    }
    AST* makeNode(std::string type, std::string value){
        auto newNode = makeTypedNode(type);
        newNode->str_value = value;
        return newNode;
    }
    AST* makeNode(std::string type, AST*child){
        auto newNode = makeTypedNode(type);
        newNode->add_one_child(child);
        return newNode;
    }
    template <typename... Args>
    AST* makeNode(std::string type, AST *child, Args... args) 
    {
        auto newNode = makeTypedNode(type);
        newNode->add_one_child(child);
        (..., newNode->add_one_child(args));
        return newNode;
    }

private:
    AST* makeTypedNode(std::string type) {
        if (type == "Program") {
            return new ASTProgramNode(type);
        } else if (type == "Ident"){
            return new ASTIdentNode(type);
        } else if (type == "CompUnit") {
            return new ASTCompUnitNode(type);
        } else if (type == "Decl") {
            return new ASTDeclNode(type);
        } else if (type == "BType") {
            return new ASTBTypeNode(type);
        } else if (type == "VarDecl") {
            return new ASTVarDeclNode(type);
        } else if (type == "VarDef") {
            return new ASTVarDefNode(type);
        } else if (type == "ArrayLengths") {
            return new ASTArrayLengthsNode(type);
        } else if (type == "InitVal") {
            return new ASTInitValNode(type);
        } else if (type == "InitVals") {
            return new ASTInitValsNode(type);
        } else if (type == "FuncDef") {
            return new ASTFuncDefNode(type);
        } else if (type == "FuncParams") {
            return new ASTFuncParamsNode(type);
        } else if (type == "FuncParam") {
            return new ASTFuncParamNode(type);
        } else if (type == "UnaryOp") {
            return new ASTUnaryOpNode(type);
        } else if (type == "Args") {
            return new ASTArgsNode(type);
        } else if (type == "MulExp") {
            return new ASTMulExpNode(type);
        } else if (type == "AddExp") {
            return new ASTAddExpNode(type);
        } else if (type == "RelExp") {
            return new ASTRelExpNode(type);
        } else if (type == "EqExp") {
            return new ASTEqExpNode(type);
        } else if (type == "LAndExp") {
            return new ASTLAndExpNode(type);
        } else if (type == "LOrExp") {
            return new ASTLOrExpNode(type);
        } else if (type == "Block") {
            return new ASTBlockNode(type);
        } else if (type == "BlockItem") {
            return new ASTBlockItemNode(type);
        } else if (type == "BlockItems") {
            return new ASTBlockItemsNode(type);
        } else if (type == "Stmt") {
            return new ASTStmtNode(type);
        } else if (type == "Exp") {
            return new ASTExpNode(type);
        } else if (type == "LVal") {
            return new ASTLValNode(type);
        } else if (type == "PrimaryExp") {
            return new ASTPrimaryExpNode(type);
        } else if (type == "Number") {
            return new ASTNumberNode(type);
        } else if (type == "UnaryExp") {
            return new ASTUnaryExpNode(type);
        } else if(type == "intconst"){
            return new ASTIntConstNode(type);
        } else if(type == "FunCall"){
            return new ASTFunCallNode(type);
        } else if(type == "Return"){
            return new ASTReturnNode(type);
        } else if(type == "Assign"){
            return new ASTAssignNode(type);
        }
        else {
            return new AST(type); // 默认情况，返回基类 AST 对象
        };
    }
};

#endif