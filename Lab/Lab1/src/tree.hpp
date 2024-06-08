#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <vector>
#include <iostream>
class AST
{
public:
    std::string type;
    int int_value;
    std::string str_value;
    std::vector<AST *> children;
    int id;
    int childID;
    std::string get_type() { return type; }
    virtual std::string get_node_type(){return "basic AST";}
    void print_md(int depth, std::string fileName, std::string extraInfo);
    
    AST() {}
    AST(std::string type) : type(type) {}
    AST(std::string type, int int_value) : type(type), int_value(int_value) {}
    AST(std::string type, std::string str_value) : type(type), str_value(str_value) {}

    AST(std::string type, AST *child) : type(type)
    {
        add_one_child(child);
    }
    

    template <typename... Args>
    AST *add_children(AST *child, Args... args)
    {
        add_one_child(child);
        (..., add_one_child(args));
        return this;
    }
    void add_one_child(AST *child){
        child->childID = children.size();
        children.push_back(child);
    }

    void absorb(AST *other)
    {
        for (auto child : other->children)
        {
            add_one_child(child);
        }
    }

    

};

class ASTProgramNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Program"; }
};

class ASTCompUnitNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "CompUnit"; }
};

class ASTDeclNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Decl"; }
};

class ASTBTypeNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "BType"; }
};

class ASTVarDeclNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "VarDecl"; }
};

class ASTVarDefNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "VarDef"; }
};

class ASTArrayLengthsNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "ArrayLengths"; }
};

class ASTInitValNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "InitVal"; }
};

class ASTInitValsNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "InitVals"; }
};

class ASTFuncDefNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "FuncDef"; }
};

class ASTFuncParamsNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "FuncParams"; }
};

class ASTFuncParamNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "FuncParam"; }
};

class ASTUnaryOpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "UnaryOp"; }
};

class ASTArgsNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Args"; }
};

class ASTMulExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "MulExp"; }
};

class ASTAddExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "AddExp"; }
};

class ASTRelExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "RelExp"; }
};

class ASTEqExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "EqExp"; }
};

class ASTLAndExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "LAndExp"; }
};

class ASTLOrExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "LOrExp"; }
};

class ASTBlockNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Block"; }
};

class ASTBlockItemNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "BlockItem"; }
};

class ASTBlockItemsNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "BlockItems"; }
};

class ASTStmtNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Stmt"; }
};

class ASTExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Exp"; }
};

class ASTLValNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "LVal"; }
};

class ASTPrimaryExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "PrimaryExp"; }
};

class ASTNumberNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Number"; }
};

class ASTUnaryExpNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "UnaryExp"; }
};

class ASTIdentNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "Ident"; }
};

class ASTIntConstNode : public AST {
    using AST::AST;
    std::string get_node_type() override { return "IntConst"; }
};
#endif