#ifndef TYPE_HPP
#define TYPE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <deque>
enum class ValType
{
    INT,
    INTARRAY,
    VOID,
    NODEF
};
enum class IdentType
{
    VAR,
    FUNC,
    ERROR
};
class Type
{
    void errorInfo(std::string info)
    {
        std::cout << "\033[31m" << info << "\033[0m" << std::endl; // \033[31m 设置红色，\033[0m 重置颜色
    }
    void successInfo(std::string info)
    {
        std::cout << "\033[32m" << info << "\033[0m" << std::endl; // \033[32m 设置绿色，\033[0m 重置颜色
    }

public:
    ValType valType;
    IdentType identType;
    std::deque<int> array_dimentions;
    std::vector<Type> func_args_type;
    Type()
    {
        valType = ValType::VOID;
        identType = IdentType::VAR;
    }
    Type(std::string identType, std::string valType)
    {
        if (identType == "var")
        {
            this->identType = IdentType::VAR;
        }
        else if (identType == "func")
        {
            this->identType = IdentType::FUNC;
        }
        else
        {
            errorInfo("Invalid identType");
        }
        if (valType == "int")
        {
            this->valType = ValType::INT;
        }
        else if (valType == "intarray")
        {
            this->valType = ValType::INTARRAY;
        }
        else if (valType == "void")
        {
            this->valType = ValType::VOID;
        }
        else if (valType == "error")
        {
            this->valType = ValType::NODEF;
        }
        else
        {
            errorInfo("Invalid valType: " + valType);
        }
    }
    template <typename... Args> // function definition
    Type(std::string identType, std::string valType, Type funcParam, Args... args)
    {
        if (identType == "func")
        {
            this->identType = IdentType::FUNC;
            if (valType == "int")
            {
                this->valType = ValType::INT;
            }
            else if (valType == "void")
            {
                this->valType = ValType::VOID;
            }
            else
            {
                errorInfo("Invalid valType " + identType + "should be func");
                system("pause");
            }
            func_args_type.push_back(funcParam);
            (..., func_args_type.push_back(args));
        }
        else
        {
            errorInfo("Invalid identType " + identType + "should be func");
        }
    }
    template <typename... Args>
    Type(std::string identType, std::string valType, int dim, Args... args)
    {
        if (identType == "var")
        {
            this->identType = IdentType::VAR;
            if (valType == "intarray")
            {
                this->valType = ValType::INTARRAY;
                this->array_dimentions.push_back(dim);
                (..., array_dimentions.push_back(args));
            }
            else
            {
                errorInfo("Invalid valType " + valType + "should be intarray");
                system("pause");
            }
        }
        else
        {
            errorInfo("Invalid identType " + identType + "should be var");
        }
    }
    void add_array_dimention(int dimention)
    {

        if (valType != ValType::INTARRAY)
        {
            errorInfo("can not add dimention to non-array type");
            return;
        }
        array_dimentions.push_back(dimention);
    }
    void add_func_arg(Type arg_type)
    {
        if (arg_type.identType == IdentType::FUNC)
        {
            errorInfo("can not add function argument to function param");
            return;
        }
        func_args_type.push_back(arg_type);
    }
    bool is_func()
    {
        return identType == IdentType::FUNC;
    }
    bool is_var()
    {
        return identType == IdentType::VAR;
    }
    bool equalVal(Type other){
        if(valType!=other.valType){
            return false;
        }
        if(valType==ValType::INTARRAY){
            if(array_dimentions.size()!=other.array_dimentions.size()){
                return false;
            }
            for(int i=0;i<array_dimentions.size();i++){
                if(array_dimentions[i] == -1 || other.array_dimentions[i] == -1){
                    continue;
                }
                if(array_dimentions[i]!=other.array_dimentions[i]){
                    return false;
                }
            }
        }
        return true;
    }
};
#endif