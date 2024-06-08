#include <cstdio>
#include "tree.hpp"
#include "ASTFactory.hpp"
extern int yydebug;
extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern AST *root;
FILE *input;
int main(int argc, char **argv)
{
    
    
    if(argc != 2)
    {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    printf("single file ");
    if(yyin == nullptr)
    {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }
    yydebug = 1;
    //yylex();
    
    yyparse();
    // printf("Parsed successfully\n");
    //重定向到输出
    std::string name = argv[1];
    std::string output = "output_" + name + ".md";
    output.replace(output.find("/"), 1, "_");
    output = "outputs/" + output;
    std::cout << output << std::endl;
    const char *output_file = output.c_str();
    freopen(output_file, "w", stdout);


    root->print_md(0,argv[1],"I am root");      
         
    fclose(yyin);

    return 0;
}
