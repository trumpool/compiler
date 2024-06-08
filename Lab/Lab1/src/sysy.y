%{
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "tree.hpp"
#include "ASTFactory.hpp"
#define YYDEBUG 1
void yyerror(const char *s);
extern int yylex(void);
extern AST *root;
extern ASTFactory F;
%}

%union{
    AST *node;
    int qq;
}


%start Program
%token <node> ADD "+"
%token <node> SUB "-"
%token <node> MUL "*"
%token <node> DIV "/"
%token <node> MOD "%"
%token <node> ASSIGN "="
%token <node> EQ "=="
%token <node> NE "!="
%token <node> LT "<"
%token <node> LE "<="
%token <node> GT ">"
%token <node> GE ">="
%token <node> AND "&&"
%token <node> OR "||"
%token <node> NOT "!"
%token <node> INC "++"
%token <node> DEC "--"
%token <node> SEMI ";"
%token <node> COMMA ","
%token <node> LPAREN "("
%token <node> RPAREN ")"
%token <node> LBRACKET "["
%token <node> RBRACKET "]"
%token <node> LBRACE "{"
%token <node> RBRACE "}"
%token <node> INT "int"
%token <node> VOID "void"
%token <node> IF "if"
%token <node> ELSE "else"
%token <node> WHILE "while"
%token <node> RETURN "return"
%token <node> BREAK "break"
%token <node> CONTINUE "continue"
%token <node> CONST "const"
%token <node> IDENT
%token <node> INTCONST

%type <node> Program CompUnit Decl BType VarDecl VarDef ArrayLengths InitVal InitVals FuncDef FuncParams FuncParam UnaryOp Args MulExp AddExp RelExp EqExp LAndExp LOrExp Block BlockItem BlockItems Stmt Exp LVal PrimaryExp Number UnaryExp 
// helper, not actual node
%type <node> Lval_Arrays IntTypeDecl VoidTypeDecl VarDefs 


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

Program : CompUnit {root = $1;}
    ;

CompUnit : Decl {$$ = F.makeNode("CompUnit", $1);}
    | FuncDef   {$$ = F.makeNode("CompUnit", $1);}
    | CompUnit Decl      {$$ = $$->add_children($2);}
    | CompUnit FuncDef    {$$ = $$->add_children($2);}
    ;

BType : INT             {$$ = F.makeNode("BType", $1);}
    ;

Decl : VarDecl      {$$ = F.makeNode("Decl", $1);}
    ;

IntTypeDecl : BType IDENT  {$$ = F.makeNode("IntTypeDecl", $1, $2);}
    ;

VoidTypeDecl : VOID IDENT   {$$ = F.makeNode("VoidTypeDecl", $1, $2);}
// int a;
// int a = 2;
// int a[10];
VarDecl : IntTypeDecl VarDefs ";"              {$$ = F.makeNode("VarDecl"); $$->absorb($1); $$->absorb($2);}
    | IntTypeDecl ArrayLengths VarDefs ";"     {$$ = F.makeNode("VarDecl"); $$->add_children(F.makeNode("VarDef", $1->children[0],  $1->children[1], $2)); $$->absorb($3);}
    | IntTypeDecl "=" InitVal VarDefs ";"      {$$ = F.makeNode("VarDecl"); $$->add_children(F.makeNode("VarDef", $1->children[0], $1->children[1], $2, $3)); $$->absorb($4);}
    ;

VarDefs : %empty               {$$ = F.makeNode("EmptyVarDefs");/*shall be absorbed*/}
    | "," VarDef           {$$ = F.makeNode("VarDefs", $2);}
    | VarDefs "," VarDef       {$$ = $$->add_children($3);}

VarDef : IDENT                  {$$ = F.makeNode("VarDef", $1);}
    | IDENT ArrayLengths        {$$ = F.makeNode("VarDef", $1, $2);}
    | IDENT "=" InitVal         {$$ = F.makeNode("VarDef", $1, $2, $3);}
    | IDENT ArrayLengths "=" InitVal   {$$ = F.makeNode("VarDef", $1, $2, $3, $4);}
    ;

ArrayLengths : "[" INTCONST "]" {$$ = F.makeNode("ArrayLengths", $2);}
    | ArrayLengths "[" INTCONST "]"  {$$ = $$->add_children($3);}
    ;

InitVal : "{"  "}"              {$$ = F.makeNode("InitVal");}
    | "{" InitVals "}"          {$$ = F.makeNode("InitVal", $2);}
    | Exp                       {$$ = F.makeNode("InitVal", $1);}
    ;

InitVals : InitVal              {$$ = F.makeNode("InitVals", $1);} 
    | InitVals "," InitVal      {$$ = $$->add_children($3);}
    ;

FuncDef : IntTypeDecl "(" FuncParams ")" Block     {$$ = F.makeNode("FuncDef"); $$->absorb($1); $$->add_children($3,$5);}
    | IntTypeDecl "(" ")" Block                    {$$ = F.makeNode("FuncDef"); $$->absorb($1); $$->add_children($4);}
    | VoidTypeDecl "(" FuncParams ")" Block         {$$ = F.makeNode("FuncDef"); $$->absorb($1); $$->add_children($3,$5);}
    | VoidTypeDecl "(" ")" Block                    {$$ = F.makeNode("FuncDef"); $$->absorb($1); $$->add_children($4);}
    ;


FuncParams : FuncParam          {$$ = F.makeNode("FuncParams", $1);}
    | FuncParams "," FuncParam  {$$ = $$->add_children($3);}
    ;

FuncParam : IntTypeDecl         
    | IntTypeDecl "[" "]"       {$$ = F.makeNode("FuncParam_Array", $1, $2);}
    | IntTypeDecl "[" "]" ArrayLengths  {$$ = F.makeNode("FuncParam_Array", $1, $2, $4);}
    ;

Block : "{" "}"                         {$$ = F.makeNode("Block");}
    | "{" BlockItems "}"                {$$ = F.makeNode("Block", $2);}
    ;

BlockItems : BlockItem                  {$$ = F.makeNode("BlockItems", $1);}
    | BlockItems BlockItem              {$$ = $$->add_children($2);}
    ;

BlockItem : Stmt                        {$$ = F.makeNode("BlockItem", $1);}
    | Decl                              {$$ = F.makeNode("BlockItem", $1);}
    ;

Stmt : LVal "=" Exp ";"                 {$$ = F.makeNode("Assign", $1, $3);}
    | Exp ";"                           {$$ = F.makeNode("Exp", $1);}
    | ";"                               {$$ = F.makeNode("Exp");}
    | Block                             {$$ = F.makeNode("Stmt", $1);}
    | "if" "(" Exp ")" Stmt %prec LOWER_THAN_ELSE  {$$ = F.makeNode("If", $3, $5);}
    | "if" "(" Exp ")" Stmt "else" Stmt            {$$ = F.makeNode("IfElse", $3, $5, $7);}
    | "while" "(" Exp ")" Stmt             {$$ = F.makeNode("While", $3, $5);}
    | "return" Exp ";"                      {$$ = F.makeNode("Return", $2);}
    | "return" ";"                          {$$ = F.makeNode("Return");}
    ;

Exp : LOrExp                         
    ;

LVal : IDENT                {$$ = F.makeNode("LVal", $1);}
    | IDENT Lval_Arrays     {$$ = F.makeNode("LVal", $1, $2);}
    ;

Lval_Arrays : "[" Exp "]"    {$$ = F.makeNode("Lval_Arrays", $2);}
    | Lval_Arrays "[" Exp "]"   {$$ = $$->add_children($3);}

PrimaryExp : "(" Exp ")"        {$$ = F.makeNode("PrimaryExp", $2);}
    | LVal                      {$$ = F.makeNode("PrimaryExp", $1);}
    | Number                    {$$ = F.makeNode("PrimaryExp", $1);}
    ;

Number : INTCONST               {$$ = F.makeNode("Number", $1);}
    ;

UnaryExp : PrimaryExp           {$$ = F.makeNode("UnaryExp", $1);}
    | IDENT "(" ")"             {$$ = F.makeNode("FunCall", $1);}
    | IDENT "(" Args ")"        {$$ = F.makeNode("FunCall", $1, $3);}
    | UnaryOp UnaryExp          {$$ = F.makeNode("UnaryExp", $1, $2);}
    ;

UnaryOp : "+"                   
    | "-"                       
    | "!"                       
    | "++" 
    | "--" 
    ;

Args : Exp              {$$ = F.makeNode("Args", $1);}
    | Args "," Exp      {$$ = $$->add_children($3);}
    ;

MulExp : UnaryExp           {$$ = F.makeNode("MulExp", $1);}
    | MulExp "*" UnaryExp   {$$ = F.makeNode("MulExp", $1, $3);}
    | MulExp "/" UnaryExp   {$$ = F.makeNode("MulExp", $1, $3);}
    | MulExp "%" UnaryExp   {$$ = F.makeNode("MulExp", $1, $3);}
    ;

AddExp : MulExp             {$$ = F.makeNode("AddExp", $1);}
    | AddExp "+" MulExp     {$$ = F.makeNode("AddExp", $1, $3);}
    | AddExp "-" MulExp     {$$ = F.makeNode("AddExp", $1, $3);}
    ;

RelExp : AddExp             {$$ = F.makeNode("RelExp", $1);}
    | RelExp "<" AddExp     {$$ = F.makeNode("RelExp", $1, $3);}
    | RelExp "<=" AddExp    {$$ = F.makeNode("RelExp", $1, $3);}
    | RelExp ">" AddExp     {$$ = F.makeNode("RelExp", $1, $3);}
    | RelExp ">=" AddExp    {$$ = F.makeNode("RelExp", $1, $3);}
    ;

EqExp : RelExp              {$$ = F.makeNode("EqExp", $1);}
    | EqExp "==" RelExp     {$$ = F.makeNode("EqExp", $1, $3);}
    | EqExp "!=" RelExp     {$$ = F.makeNode("EqExp", $1, $3);}
    ;

LAndExp : EqExp             {$$ = F.makeNode("LAndExp", $1);}
    | LAndExp "&&" EqExp    {$$ = F.makeNode("LAndExp", $1, $3);}
    ;

LOrExp : LAndExp            {$$ = F.makeNode("LOrExp", $1);}
    | LOrExp "||" LAndExp   {$$ = F.makeNode("LOrExp", $1, $3);}
    ;

%%

void yyerror(const char *s) {
    printf("error occured: %s\n", s);
}
