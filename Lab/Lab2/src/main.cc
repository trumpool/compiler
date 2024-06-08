#include <cstdio>
#include "tree.hpp"
#include "ASTFactory.hpp"
#include "SA.hpp"
extern int yydebug;
extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern AST *root;
FILE *input;
SemanticAnalyzer SA;
int main(int argc, char **argv)
{
    // return 0;
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
    
    yyparse();
    
    std::string name = argv[1];
    std::string output = "output_" + name + ".md";
    output.replace(output.find("/"), 1, "_");
    output = "outputs/" + output;
    std::cout << output << std::endl;
    const char *output_file = output.c_str();

    auto outfp = freopen(output_file, "w", stdout);

    
    root->print_md(0,argv[1],"I am root");      
    
    if(yyin) fclose(yyin);
    if(outfp) fclose(outfp);
    
    freopen("/dev/tty", "a", stdout);
    // 再次打印到标准输出
    
    std::cout << "End of parsing" << std::endl;

    
    bool SAres = SA.check_type(root);
    std::cout << output << std::endl;
    if(SAres){
        std::cout << "Semantic Analysis passed" << std::endl;
        return 0;
    }else{
        std::cout << "Semantic Analysis failed" << std::endl;
        return 1;
    }
}
