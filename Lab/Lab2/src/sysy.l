%option noinput
%option nounput
%option noyywrap

%{
#include "tree.hpp"
#include "SA.hpp"
#include "sysy.tab.hh"
#include <iostream>
#include "ASTFactory.hpp"
extern ASTFactory F;
%}

digit [0-9]
blank [ \t\r\n]
alpha [a-zA-Z_]



%%

"/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"			{ printf("comment\n"); /*注释*/}
"//"[^\r\n]*      { printf("comment\n"); /* ignore */ }


"int"           { yylval.node = F.makeNode("int"); return INT; }
"void"          { yylval.node = F.makeNode("void"); return VOID; }
"if"            { yylval.node = F.makeNode("if"); return IF; }
"else"          { yylval.node = F.makeNode("else"); return ELSE; }
"while"         { yylval.node = F.makeNode("while"); return WHILE; }
"return"        { yylval.node = F.makeNode("return"); return RETURN; }
"break"         { yylval.node = F.makeNode("break"); return BREAK; }
"continue"      { yylval.node = F.makeNode("continue"); return CONTINUE; }
"const"         { yylval.node = F.makeNode("const"); return CONST; }

"+"             { yylval.node = F.makeNode("add"); return ADD; }
"-"             { yylval.node = F.makeNode("sub"); return SUB; }
"*"             { yylval.node = F.makeNode("mul"); return MUL; }
"/"             { yylval.node = F.makeNode("div"); return DIV; }
"%"             { yylval.node = F.makeNode("mod"); return MOD; }
"="             { yylval.node = F.makeNode("assign"); return ASSIGN; }
"=="            { yylval.node = F.makeNode("eq"); return EQ; }
"!="            { yylval.node = F.makeNode("ne"); return NE; }
"<"             { yylval.node = F.makeNode("lt"); return LT; }
"<="            { yylval.node = F.makeNode("le"); return LE; }
">"             { yylval.node = F.makeNode("gt"); return GT; }
">="            { yylval.node = F.makeNode("ge"); return GE; }
"&&"            { yylval.node = F.makeNode("and"); return AND; }
"||"            { yylval.node = F.makeNode("or"); return OR; }
"!"             { yylval.node = F.makeNode("not"); return NOT; }
";"             { yylval.node = F.makeNode("semi"); return SEMI; }
","             { yylval.node = F.makeNode("comma"); return COMMA; }
"("             { yylval.node = F.makeNode("lparen"); return LPAREN; }
")"             { yylval.node = F.makeNode("rparen"); return RPAREN; }
"["             { yylval.node = F.makeNode("lbracket"); return LBRACKET; }
"]"             { yylval.node = F.makeNode("rbracket"); return RBRACKET; }
"{"             { yylval.node = F.makeNode("lbrace"); return LBRACE; }
"}"             { yylval.node = F.makeNode("rbrace"); return RBRACE; }

{alpha}({alpha}|{digit})* { yylval.node = F.makeNode("Ident", yytext); return IDENT; }

[0-9]           { int k; sscanf(yytext, "%d", &k); yylval.node = F.makeNode("intconst", k); return INTCONST; }
[1-9]{digit}*   { int k; sscanf(yytext, "%d", &k); yylval.node = F.makeNode("intconst", k); return INTCONST; }

{blank}         {}
.               { printf("unrecognized character\n"); return 0; }

%%


