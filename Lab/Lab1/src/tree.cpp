#include "tree.hpp"
#include "ASTFactory.hpp"
#include <string>
AST *root;
ASTFactory F;
int totalNodeCount = 0;
void AST::print_md(int depth, std::string fileName, std::string extraInfo = "")
{
    if (!depth)
    {
        std::cout << fileName << std::endl;
        std::cout << "```mermaid" << std::endl;
        std::cout << "graph TD" << std::endl;
        id = 0;
    }
    std::cout<< "  " << id << "((" << type  ;
    if (children.size() == 0)
    {
        if (type == "intconst")
        {
            std::cout << " " << int_value;
        }
        else
        {
            std::cout << " " << str_value;
        }
    }

    {
        /* code */
        std::cout<<std::endl<<"ExtraInfo: "<<get_node_type();
    }
    
    std::cout << "))" << std::endl;
    for (auto child : children)
    {
        child->id = ++totalNodeCount;
        std::cout<< "  " << this->id << "---" << child->id << std::endl;
        child->print_md(depth + 1,fileName);
    }
    if (!depth)
    {
        std::cout << "```" << std::endl;
    }
}