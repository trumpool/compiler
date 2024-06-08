lab2/add.sy
```mermaid
graph TD
  0[CompUnit
ExtraInfo: CompUnit
 ID: 0
]
  0---1
  1[FuncDef
ExtraInfo: FuncDef
 ID: 1
]
  1---2
  2[BType
ExtraInfo: BType
 ID: 2
]
  2---3
  3[int 
ExtraInfo: basic AST
 ID: 3
]
  1---4
  4[Ident main
ExtraInfo: Ident
 ID: 4
]
  1---5
  5[Block
ExtraInfo: Block
 ID: 5
]
  5---6
  6[BlockItems
ExtraInfo: BlockItems
 ID: 6
]
  6---7
  7[BlockItem
ExtraInfo: BlockItem
 ID: 7
]
  7---8
  8[Decl
ExtraInfo: Decl
 ID: 8
]
  8---9
  9[VarDecl
ExtraInfo: VarDecl
 ID: 9
]
  9---10
  10[BType
ExtraInfo: BType
 ID: 10
]
  10---11
  11[int 
ExtraInfo: basic AST
 ID: 11
]
  9---12
  12[VarDef
ExtraInfo: VarDef
 ID: 12
]
  12---13
  13[Ident a
ExtraInfo: Ident
 ID: 13
]
  9---14
  14[VarDef
ExtraInfo: VarDef
 ID: 14
]
  14---15
  15[Ident b
ExtraInfo: Ident
 ID: 15
]
  6---16
  16[BlockItem
ExtraInfo: BlockItem
 ID: 16
]
  16---17
  17[Assign
ExtraInfo: Assign
 ID: 17
]
  17---18
  18[LVal
ExtraInfo: LVal
 ID: 18
]
  18---19
  19[Ident a
ExtraInfo: Ident
 ID: 19
]
  17---20
  20[LOrExp
ExtraInfo: LOrExp
 ID: 20
]
  20---21
  21[LAndExp
ExtraInfo: LAndExp
 ID: 21
]
  21---22
  22[EqExp
ExtraInfo: EqExp
 ID: 22
]
  22---23
  23[RelExp
ExtraInfo: RelExp
 ID: 23
]
  23---24
  24[AddExp
ExtraInfo: AddExp
 ID: 24
]
  24---25
  25[MulExp
ExtraInfo: MulExp
 ID: 25
]
  25---26
  26[UnaryExp
ExtraInfo: UnaryExp
 ID: 26
]
  26---27
  27[PrimaryExp
ExtraInfo: PrimaryExp
 ID: 27
]
  27---28
  28[Number
ExtraInfo: Number
 ID: 28
]
  28---29
  29[intconst 10
ExtraInfo: IntConst
 ID: 29
]
  6---30
  30[BlockItem
ExtraInfo: BlockItem
 ID: 30
]
  30---31
  31[Assign
ExtraInfo: Assign
 ID: 31
]
  31---32
  32[LVal
ExtraInfo: LVal
 ID: 32
]
  32---33
  33[Ident b
ExtraInfo: Ident
 ID: 33
]
  31---34
  34[LOrExp
ExtraInfo: LOrExp
 ID: 34
]
  34---35
  35[LAndExp
ExtraInfo: LAndExp
 ID: 35
]
  35---36
  36[EqExp
ExtraInfo: EqExp
 ID: 36
]
  36---37
  37[RelExp
ExtraInfo: RelExp
 ID: 37
]
  37---38
  38[AddExp
ExtraInfo: AddExp
 ID: 38
]
  38---39
  39[MulExp
ExtraInfo: MulExp
 ID: 39
]
  39---40
  40[UnaryExp
ExtraInfo: UnaryExp
 ID: 40
]
  40---41
  41[sub 
ExtraInfo: basic AST
 ID: 41
]
  40---42
  42[UnaryExp
ExtraInfo: UnaryExp
 ID: 42
]
  42---43
  43[PrimaryExp
ExtraInfo: PrimaryExp
 ID: 43
]
  43---44
  44[Number
ExtraInfo: Number
 ID: 44
]
  44---45
  45[intconst 1
ExtraInfo: IntConst
 ID: 45
]
  6---46
  46[BlockItem
ExtraInfo: BlockItem
 ID: 46
]
  46---47
  47[Exp
ExtraInfo: Exp
 ID: 47
]
  47---48
  48[LOrExp
ExtraInfo: LOrExp
 ID: 48
]
  48---49
  49[LAndExp
ExtraInfo: LAndExp
 ID: 49
]
  49---50
  50[EqExp
ExtraInfo: EqExp
 ID: 50
]
  50---51
  51[RelExp
ExtraInfo: RelExp
 ID: 51
]
  51---52
  52[AddExp
ExtraInfo: AddExp
 ID: 52
]
  52---53
  53[MulExp
ExtraInfo: MulExp
 ID: 53
]
  53---54
  54[FunCall
ExtraInfo: FunCall
 ID: 54
]
  54---55
  55[Ident putint
ExtraInfo: Ident
 ID: 55
]
  54---56
  56[Args
ExtraInfo: Args
 ID: 56
]
  56---57
  57[LOrExp
ExtraInfo: LOrExp
 ID: 57
]
  57---58
  58[LAndExp
ExtraInfo: LAndExp
 ID: 58
]
  58---59
  59[EqExp
ExtraInfo: EqExp
 ID: 59
]
  59---60
  60[RelExp
ExtraInfo: RelExp
 ID: 60
]
  60---61
  61[AddExp
ExtraInfo: AddExp
 ID: 61
]
  61---62
  62[AddExp
ExtraInfo: AddExp
 ID: 62
]
  62---63
  63[MulExp
ExtraInfo: MulExp
 ID: 63
]
  63---64
  64[UnaryExp
ExtraInfo: UnaryExp
 ID: 64
]
  64---65
  65[PrimaryExp
ExtraInfo: PrimaryExp
 ID: 65
]
  65---66
  66[LVal
ExtraInfo: LVal
 ID: 66
]
  66---67
  67[Ident a
ExtraInfo: Ident
 ID: 67
]
  61---68
  68[MulExp
ExtraInfo: MulExp
 ID: 68
]
  68---69
  69[UnaryExp
ExtraInfo: UnaryExp
 ID: 69
]
  69---70
  70[PrimaryExp
ExtraInfo: PrimaryExp
 ID: 70
]
  70---71
  71[LVal
ExtraInfo: LVal
 ID: 71
]
  71---72
  72[Ident b
ExtraInfo: Ident
 ID: 72
]
  6---73
  73[BlockItem
ExtraInfo: BlockItem
 ID: 73
]
  73---74
  74[Return
ExtraInfo: Return
 ID: 74
]
  74---75
  75[LOrExp
ExtraInfo: LOrExp
 ID: 75
]
  75---76
  76[LAndExp
ExtraInfo: LAndExp
 ID: 76
]
  76---77
  77[EqExp
ExtraInfo: EqExp
 ID: 77
]
  77---78
  78[RelExp
ExtraInfo: RelExp
 ID: 78
]
  78---79
  79[AddExp
ExtraInfo: AddExp
 ID: 79
]
  79---80
  80[MulExp
ExtraInfo: MulExp
 ID: 80
]
  80---81
  81[UnaryExp
ExtraInfo: UnaryExp
 ID: 81
]
  81---82
  82[PrimaryExp
ExtraInfo: PrimaryExp
 ID: 82
]
  82---83
  83[Number
ExtraInfo: Number
 ID: 83
]
  83---84
  84[intconst 0
ExtraInfo: IntConst
 ID: 84
]
```
