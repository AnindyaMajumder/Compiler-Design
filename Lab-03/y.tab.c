/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "syntax_analyzer.y"


#include "symbol_table.h"

#define YYSTYPE symbol_info*

extern FILE *yyin;
int yyparse(void);
int yylex(void);
extern YYSTYPE yylval;

// create your symbol table here.
// You can store the pointer to your symbol table in a global variable
// or you can create an object

symbol_table *st;

int lines = 1;
int error_count = 0;

// Track lines with errors to avoid counting multiple errors on same line
set<int> lines_with_errors;

ofstream outlog;
ofstream errout;

// you may declare other necessary variables here to store necessary info
// such as current variable type, variable list, function name, return type, function parameter types, parameters names etc.
string current_type;
string data_type;
int array_size;
vector<string> param_names;
vector<string> param_types;
string current_func_return_type;

// Helper function to report semantic errors
void semantic_error(int line, string message) {
    // Only increment error count if this is the first error on this line
    if(lines_with_errors.find(line) == lines_with_errors.end()) {
        lines_with_errors.insert(line);
    }
    errout << "Error at line no: " << line << " : " << message << endl;
    outlog << "Error at line no: " << line << " : " << message << endl;
}

// Helper function to type check
bool type_compatible(string type1, string type2) {
    if (type1 == type2) return true;
    if (type1 == "float" && type2 == "int") return true;
    
    return false;
}

// Helper functions for processing variable declarations
vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

void process_variable(const string& var, const string& type) {
    size_t open_bracket = var.find('[');
    size_t close_bracket = var.find(']');

    if (open_bracket != string::npos && close_bracket != string::npos && close_bracket > open_bracket + 1) {
        // Array variable
        string array_name = var.substr(0, open_bracket);
        int array_size = stoi(var.substr(open_bracket + 1, close_bracket - open_bracket - 1));

        // Check if variable is already declared in current scope
        symbol_info* existing = st->lookup(array_name);
        if (existing != NULL) {
            semantic_error(lines, "Multiple declaration of variable " + array_name);
            return;
        }

        symbol_info* new_symbol = new symbol_info(array_name, "ID", "Array");
        new_symbol->set_array_size(array_size);
        new_symbol->set_data_type(type);
        st->insert(new_symbol);
    } else {
        // Normal variable
        // Check if variable is already declared in current scope
        symbol_info* existing = st->lookup(var);
        if (existing != NULL) {
            semantic_error(lines, "Multiple declaration of variable " + var);
            return;
        }

        symbol_info* new_symbol = new symbol_info(var, "ID", "Variable");
        new_symbol->set_data_type(type);
        st->insert(new_symbol);
    }
}

void yyerror(char *s)
{
	outlog<<"At line "<<lines<<" "<<s<<endl<<endl;

    // you may need to reinitialize variables if you find an error
    param_names.clear();
    param_types.clear();
}


/* Line 371 of yacc.c  */
#line 179 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     DO = 262,
     BREAK = 263,
     INT = 264,
     CHAR = 265,
     FLOAT = 266,
     DOUBLE = 267,
     VOID = 268,
     RETURN = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     CONTINUE = 273,
     PRINTLN = 274,
     ADDOP = 275,
     MULOP = 276,
     INCOP = 277,
     DECOP = 278,
     RELOP = 279,
     ASSIGNOP = 280,
     LOGICOP = 281,
     NOT = 282,
     LPAREN = 283,
     RPAREN = 284,
     LCURL = 285,
     RCURL = 286,
     LTHIRD = 287,
     RTHIRD = 288,
     COMMA = 289,
     SEMICOLON = 290,
     CONST_INT = 291,
     CONST_FLOAT = 292,
     ID = 293,
     LOWER_THAN_ELSE = 294
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define PRINTLN 274
#define ADDOP 275
#define MULOP 276
#define INCOP 277
#define DECOP 278
#define RELOP 279
#define ASSIGNOP 280
#define LOGICOP 281
#define NOT 282
#define LPAREN 283
#define RPAREN 284
#define LCURL 285
#define RCURL 286
#define LTHIRD 287
#define RTHIRD 288
#define COMMA 289
#define SEMICOLON 290
#define CONST_INT 291
#define CONST_FLOAT 292
#define ID 293
#define LOWER_THAN_ELSE 294



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 323 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   175

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    15,    23,
      24,    31,    36,    40,    43,    45,    49,    52,    56,    58,
      60,    62,    66,    73,    80,    82,    87,    92,    94,    97,
      99,   101,   103,   105,   113,   119,   127,   133,   139,   143,
     145,   148,   150,   155,   157,   161,   163,   167,   169,   173,
     175,   179,   181,   185,   188,   191,   193,   195,   200,   204,
     206,   208,   211,   214,   216,   217,   221
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    42,    43,    -1,    43,    -1,
      49,    -1,    44,    -1,    -1,    50,    38,    28,    47,    29,
      45,    48,    -1,    -1,    50,    38,    28,    29,    46,    48,
      -1,    47,    34,    50,    38,    -1,    47,    34,    50,    -1,
      50,    38,    -1,    50,    -1,    30,    52,    31,    -1,    30,
      31,    -1,    50,    51,    35,    -1,     9,    -1,    11,    -1,
      13,    -1,    51,    34,    38,    -1,    51,    34,    38,    32,
      36,    33,    -1,    51,    34,    38,    32,    37,    33,    -1,
      38,    -1,    38,    32,    36,    33,    -1,    38,    32,    37,
      33,    -1,    53,    -1,    52,    53,    -1,    49,    -1,    44,
      -1,    54,    -1,    48,    -1,     5,    28,    54,    54,    56,
      29,    53,    -1,     3,    28,    56,    29,    53,    -1,     3,
      28,    56,    29,    53,     4,    53,    -1,     6,    28,    56,
      29,    53,    -1,    19,    28,    38,    29,    35,    -1,    14,
      56,    35,    -1,    35,    -1,    56,    35,    -1,    38,    -1,
      38,    32,    56,    33,    -1,    57,    -1,    55,    25,    57,
      -1,    58,    -1,    58,    26,    58,    -1,    59,    -1,    59,
      24,    59,    -1,    60,    -1,    59,    20,    60,    -1,    61,
      -1,    60,    21,    61,    -1,    20,    61,    -1,    27,    61,
      -1,    62,    -1,    55,    -1,    38,    28,    63,    29,    -1,
      28,    56,    29,    -1,    36,    -1,    37,    -1,    55,    22,
      -1,    55,    23,    -1,    64,    -1,    -1,    64,    34,    57,
      -1,    57,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   130,   137,   146,   153,   163,   162,   226,
     225,   261,   284,   298,   310,   324,   337,   352,   379,   386,
     393,   402,   410,   420,   432,   440,   448,   461,   468,   477,
     484,   492,   499,   506,   513,   520,   527,   534,   547,   564,
     571,   580,   603,   640,   648,   697,   705,   717,   725,   737,
     745,   761,   769,   817,   824,   831,   840,   848,   901,   909,
     917,   925,   933,   943,   951,   959,   966
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "PRINTLN", "ADDOP", "MULOP", "INCOP",
  "DECOP", "RELOP", "ASSIGNOP", "LOGICOP", "NOT", "LPAREN", "RPAREN",
  "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "CONST_INT",
  "CONST_FLOAT", "ID", "LOWER_THAN_ELSE", "$accept", "start", "program",
  "unit", "func_definition", "$@1", "$@2", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    45,    44,    46,
      44,    47,    47,    47,    47,    48,    48,    49,    50,    50,
      50,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     7,     0,
       6,     4,     3,     2,     1,     3,     2,     3,     1,     1,
       1,     3,     6,     6,     1,     4,     4,     1,     2,     1,
       1,     1,     1,     7,     5,     7,     5,     5,     3,     1,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    18,    19,    20,     0,     2,     4,     6,     5,     0,
       1,     3,    24,     0,     0,     0,     0,    17,     9,     0,
      14,     0,     0,    21,     0,     7,     0,    13,    25,    26,
       0,     0,    10,     0,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    39,    59,    60,    41,
      30,    32,    29,     0,    27,    31,    56,     0,    43,    45,
      47,    49,    51,    55,     8,    11,    22,    23,     0,     0,
       0,     0,     0,    56,    53,    54,     0,    64,     0,    15,
      28,    61,    62,     0,    40,     0,     0,     0,     0,     0,
       0,     0,    38,     0,    58,    66,     0,    63,     0,    44,
      46,    50,    48,    52,     0,     0,     0,     0,    57,     0,
      42,    34,     0,    36,    37,    65,     0,     0,    35,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    50,    33,    24,    19,    51,    52,
       9,    13,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    96,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -71
static const yytype_int16 yypact[] =
{
      41,   -71,   -71,   -71,    23,    41,   -71,   -71,   -71,     0,
     -71,   -71,     5,    27,     1,    44,    11,   -71,   -71,   -14,
      51,    55,    57,    45,    61,   -71,    41,   -71,   -71,   -71,
      46,    65,   -71,    61,    56,    66,    72,    69,    70,    80,
      20,    81,    20,    20,    20,   -71,   -71,   -71,   -71,    32,
     -71,   -71,   -71,   101,   -71,   -71,    50,    76,   -71,    87,
      39,    95,   -71,   -71,   -71,   -71,   -71,   -71,    20,    -9,
      20,    82,    84,    64,   -71,   -71,    89,    20,    20,   -71,
     -71,   -71,   -71,    20,   -71,    20,    20,    20,    20,    90,
      -9,    94,   -71,    96,   -71,   -71,    97,    93,    91,   -71,
     -71,    95,   110,   -71,   137,    20,   137,    98,   -71,    20,
     -71,   130,   106,   -71,   -71,   -71,   137,   137,   -71,   -71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   136,    17,   -71,   -71,   -71,    -8,    31,
      -5,   -71,   -71,   -51,   -66,   -42,   -36,   -70,    59,    58,
      63,   -37,   -71,   -71,   -71
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      73,    73,    80,    90,    71,    74,    75,    95,    76,    20,
       1,    42,     2,    99,     3,    25,    32,     7,    43,    44,
      26,    34,     7,    10,   105,    64,    46,    47,    48,    49,
      18,     8,    89,    14,    91,    73,     8,    15,    12,   115,
      42,    73,    98,    73,    73,    73,    73,    43,    44,    23,
       1,   103,     2,   111,     3,   113,    47,    48,    49,    86,
      77,    16,    17,    87,    78,   118,   119,    73,    37,   112,
      38,    39,    81,    82,     1,    83,     2,    30,     3,    40,
      21,    22,    35,    36,    41,    42,    81,    82,    28,    27,
      29,    31,    43,    44,    65,    31,    45,    68,    69,    66,
      46,    47,    48,    49,    37,    67,    38,    39,    70,    72,
       1,    84,     2,    85,     3,    40,    88,    92,    94,   104,
      41,    42,    93,   106,   110,   107,   108,   109,    43,    44,
      86,    31,    79,   114,   116,   117,    46,    47,    48,    49,
      37,    11,    38,    39,   100,   102,     1,     0,     2,   101,
       3,    40,     0,     0,     0,     0,    41,    42,     0,     0,
       0,     0,     0,     0,    43,    44,     0,    31,     0,     0,
       0,     0,    46,    47,    48,    49
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      42,    43,    53,    69,    40,    42,    43,    77,    44,    14,
       9,    20,    11,    83,    13,    29,    24,     0,    27,    28,
      34,    26,     5,     0,    90,    33,    35,    36,    37,    38,
      29,     0,    68,    28,    70,    77,     5,    32,    38,   109,
      20,    83,    78,    85,    86,    87,    88,    27,    28,    38,
       9,    88,    11,   104,    13,   106,    36,    37,    38,    20,
      28,    34,    35,    24,    32,   116,   117,   109,     3,   105,
       5,     6,    22,    23,     9,    25,    11,    32,    13,    14,
      36,    37,    36,    37,    19,    20,    22,    23,    33,    38,
      33,    30,    27,    28,    38,    30,    31,    28,    28,    33,
      35,    36,    37,    38,     3,    33,     5,     6,    28,    28,
       9,    35,    11,    26,    13,    14,    21,    35,    29,    29,
      19,    20,    38,    29,    33,    29,    29,    34,    27,    28,
      20,    30,    31,    35,     4,    29,    35,    36,    37,    38,
       3,     5,     5,     6,    85,    87,     9,    -1,    11,    86,
      13,    14,    -1,    -1,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    -1,    30,    -1,    -1,
      -1,    -1,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    13,    41,    42,    43,    44,    49,    50,
       0,    43,    38,    51,    28,    32,    34,    35,    29,    47,
      50,    36,    37,    38,    46,    29,    34,    38,    33,    33,
      32,    30,    48,    45,    50,    36,    37,     3,     5,     6,
      14,    19,    20,    27,    28,    31,    35,    36,    37,    38,
      44,    48,    49,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    48,    38,    33,    33,    28,    28,
      28,    56,    28,    55,    61,    61,    56,    28,    32,    31,
      53,    22,    23,    25,    35,    26,    20,    24,    21,    56,
      54,    56,    35,    38,    29,    57,    63,    64,    56,    57,
      58,    60,    59,    61,    29,    54,    29,    29,    29,    34,
      33,    53,    56,    53,    35,    57,     4,    29,    53,    53
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 120 "syntax_analyzer.y"
    {
		outlog<<"At line no: "<<lines<<" start : program "<<endl<<endl;
		outlog<<"Symbol Table"<<endl<<endl;
		
		// Print your whole symbol table here
		st->print_all_scopes(outlog);
		outlog<<endl<<endl;
	}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 131 "syntax_analyzer.y"
    {
		outlog<<"At line no: "<<lines<<" program : program unit "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->get_name()+"\n"+(yyvsp[(2) - (2)])->get_name()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+"\n"+(yyvsp[(2) - (2)])->get_name(),"program");
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 138 "syntax_analyzer.y"
    {
		outlog<<"At line no: "<<lines<<" program : unit "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"program");
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 147 "syntax_analyzer.y"
    {
		outlog<<"At line no: "<<lines<<" unit : var_declaration "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"unit");
	 }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 154 "syntax_analyzer.y"
    {
		outlog<<"At line no: "<<lines<<" unit : func_definition "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"unit");
	 }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 163 "syntax_analyzer.y"
    {
			// Create the function definition in symbol table
			symbol_info* func = new symbol_info((yyvsp[(2) - (5)])->get_name(), "ID", "Function");
			func->set_data_type((yyvsp[(1) - (5)])->get_name());
			
			// Get the parameter information from parameter_list
			vector<string> param_types = (yyvsp[(4) - (5)])->get_param_types();
			vector<string> param_names = (yyvsp[(4) - (5)])->get_param_names();
			
			func->set_param_types(param_types);
			func->set_param_names(param_names);
			
			// Check if the function is already declared in the current scope
			// Use the getter method instead of direct access
			symbol_info* existing_func = st->get_current_scope()->lookup((yyvsp[(2) - (5)])->get_name());
			if(existing_func != NULL && existing_func->get_symbol_type() == "Function") {
				semantic_error(lines, "Redefinition of function: " + (yyvsp[(2) - (5)])->get_name());
			} else {
				st->insert(func);
			}
			
			// Create a new scope for function body
			st->enter_scope();
			outlog << "Entered new scope with ID: " << st->get_current_scope_id() << endl;
			
			// Add parameters to the new scope
			for(size_t i = 0; i < param_types.size(); i++) {
				string param_name = param_names[i];
				if(param_name.empty()) continue; // Skip unnamed parameters
				
				// Check for duplicate parameter names within the parameter list only
				bool duplicate = false;
				for(size_t j = 0; j < i; j++) {
					if(param_names[j] == param_name) {
						semantic_error(lines, "Multiple declaration of variable " + param_name + " in parameter list");
						duplicate = true;
						break;
					}
				}
				
				if(!duplicate) {
					// Add the parameter to the symbol table
					symbol_info* param = new symbol_info(param_name, "ID", "Variable");
					param->set_data_type(param_types[i]);
					st->insert(param);
				}
			}

			// Store the current function's return type for later validation
			if((yyvsp[(1) - (5)])->get_name() == "void") {
				current_func_return_type = "void";
			} else {
				current_func_return_type = (yyvsp[(1) - (5)])->get_name();
			}
		}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 219 "syntax_analyzer.y"
    {	
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (7)])->get_name()<<" "<<(yyvsp[(2) - (7)])->get_name()<<"("+(yyvsp[(4) - (7)])->get_name()+")\n"<<(yyvsp[(7) - (7)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (7)])->get_name()+" "+(yyvsp[(2) - (7)])->get_name()+"("+(yyvsp[(4) - (7)])->get_name()+")\n"+(yyvsp[(7) - (7)])->get_name(),"func_def");
		}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 226 "syntax_analyzer.y"
    {
			// Create the function in symbol table
			symbol_info* func = new symbol_info((yyvsp[(2) - (4)])->get_name(), "ID", "Function");
			func->set_data_type((yyvsp[(1) - (4)])->get_name());
			func->set_param_types(vector<string>());
			func->set_param_names(vector<string>());
			
			// Check if the function is already declared in the current scope
			symbol_info* existing_func = st->lookup((yyvsp[(2) - (4)])->get_name());
			if(existing_func != NULL && existing_func->get_symbol_type() == "Function") {
				semantic_error(lines, "Redefinition of function: " + (yyvsp[(2) - (4)])->get_name());
			} else {
				st->insert(func);
			}
			
			// Create a new scope for function body
			st->enter_scope();
			outlog << "Entered new scope with ID: " << st->get_current_scope_id() << endl;

			// Store the current function's return type for later validation
			if((yyvsp[(1) - (4)])->get_name() == "void") {
				current_func_return_type = "void";
			} else {
				current_func_return_type = (yyvsp[(1) - (4)])->get_name();
			}
		}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 253 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (6)])->get_name()<<" "<<(yyvsp[(2) - (6)])->get_name()<<"()\n"<<(yyvsp[(6) - (6)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name()+" "+(yyvsp[(2) - (6)])->get_name()+"()\n"+(yyvsp[(6) - (6)])->get_name(),"func_def");
		}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 262 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" parameter_list : parameter_list COMMA type_specifier ID "<<endl<<endl;
 		  	outlog<<(yyvsp[(1) - (4)])->get_name()<<","<<(yyvsp[(3) - (4)])->get_name()<<" "<<(yyvsp[(4) - (4)])->get_name()<<endl<<endl;
					
			(yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name()+","+(yyvsp[(3) - (4)])->get_name()+" "+(yyvsp[(4) - (4)])->get_name(),"param_list");
			
			// Check for duplicate parameter names within THIS parameter list only (not across entire scope)
			bool duplicate = false;
			vector<string> param_names = (yyvsp[(1) - (4)])->get_param_names();
			for(const auto& param_name : param_names) {
				if(param_name == (yyvsp[(4) - (4)])->get_name()) {
					semantic_error(lines, "Multiple declaration of variable " + (yyvsp[(4) - (4)])->get_name() + " in parameter list");
					duplicate = true;
					break;
				}
			}
			
            // store the necessary information about the function parameters
			(yyval)->set_param_types((yyvsp[(1) - (4)])->get_param_types());
			(yyval)->set_param_names((yyvsp[(1) - (4)])->get_param_names());
			(yyval)->add_parameter((yyvsp[(3) - (4)])->get_name(), (yyvsp[(4) - (4)])->get_name());
		}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 285 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" parameter_list : parameter_list COMMA type_specifier "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<","<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+","+(yyvsp[(3) - (3)])->get_name(),"param_list");
			
            // store the necessary information about the function parameters
            // They will be needed when you want to enter the function into the symbol table

			(yyval)->set_param_types((yyvsp[(1) - (3)])->get_param_types());
			(yyval)->set_param_names((yyvsp[(1) - (3)])->get_param_names());
			(yyval)->add_parameter((yyvsp[(3) - (3)])->get_name(), "");
		}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 299 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" parameter_list : type_specifier ID "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->get_name()<<" "<<(yyvsp[(2) - (2)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+" "+(yyvsp[(2) - (2)])->get_name(),"param_list");
			
            // store the necessary information about the function parameters
            // They will be needed when you want to enter the function into the symbol table

			(yyval)->add_parameter((yyvsp[(1) - (2)])->get_name(), (yyvsp[(2) - (2)])->get_name());
		}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 311 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" parameter_list : type_specifier "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"param_list");
			
            // store the necessary information about the function parameters
            // They will be needed when you want to enter the function into the symbol table
			
			(yyval)->add_parameter((yyvsp[(1) - (1)])->get_name(), "");
		}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 325 "syntax_analyzer.y"
    {
			outlog << "At line no: " << lines << " compound_statement : LCURL statements RCURL " << endl << endl;
			outlog << "{\n" << (yyvsp[(2) - (3)])->get_name() << "\n}" << endl << endl;

			(yyval) = new symbol_info("{\n" + (yyvsp[(2) - (3)])->get_name() + "\n}", "comp_stmnt");

			// Print the ID of the scope being removed
			outlog << "Exiting scope with ID: " << st->get_current_scope_id() << endl;
			outlog << "Current state of the symbol table before exiting scope:" << endl;
			st->print_all_scopes(outlog);
			st->exit_scope();
		}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 338 "syntax_analyzer.y"
    {
			outlog << "At line no: " << lines << " compound_statement : LCURL RCURL " << endl << endl;
			outlog << "{\n}" << endl << endl;

			(yyval) = new symbol_info("{\n}", "comp_stmnt");

			// Print the ID of the scope being removed
			outlog << "Exiting scope with ID: " << st->get_current_scope_id() << endl;
			outlog << "Current state of the symbol table before exiting scope:" << endl;
			st->print_all_scopes(outlog);
			st->exit_scope();
		}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 353 "syntax_analyzer.y"
    {
    outlog << "At line no: " << lines << " var_declaration : type_specifier declaration_list SEMICOLON " << endl << endl;
    outlog << (yyvsp[(1) - (3)])->get_name() << " " << (yyvsp[(2) - (3)])->get_name() << ";" << endl << endl;

    (yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name() + " " + (yyvsp[(2) - (3)])->get_name() + ";", "var_dec");

    data_type = (yyvsp[(1) - (3)])->get_name();
    
    // Check if variable type is void
    if (data_type == "void") {
        semantic_error(lines, "variable type can not be void");
    }
    
    string decl_list = (yyvsp[(2) - (3)])->get_name();
    size_t start = 0, end;

    while ((end = decl_list.find(',', start)) != string::npos) {
        string var = decl_list.substr(start, end - start);
        process_variable(var, data_type);
        start = end + 1;
    }
    // Process the last variable (or the only one if no commas)
    process_variable(decl_list.substr(start), data_type);
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 380 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : INT "<<endl<<endl;
			outlog<<"int"<<endl<<endl;
			
			(yyval) = new symbol_info("int","type");
	    }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 387 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : FLOAT "<<endl<<endl;
			outlog<<"float"<<endl<<endl;
			
			(yyval) = new symbol_info("float","type");
	    }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 394 "syntax_analyzer.y"
    {
			outlog<<"At line no: "<<lines<<" type_specifier : VOID "<<endl<<endl;
			outlog<<"void"<<endl<<endl;
			
			(yyval) = new symbol_info("void","type");
	    }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 403 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
 		  	outlog<<(yyvsp[(1) - (3)])->get_name()+","<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;

            // you may need to store the variable names to insert them in symbol table here or later
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+","+(yyvsp[(3) - (3)])->get_name(),"declaration_list");
 		  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 411 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
 		  	outlog<<(yyvsp[(1) - (6)])->get_name()+","<<(yyvsp[(3) - (6)])->get_name()<<"["<<(yyvsp[(5) - (6)])->get_name()<<"]"<<endl<<endl;
			
			current_type = "array";
			array_size = stoi((yyvsp[(5) - (6)])->get_name()); // Convert string to int
            // Store array name and size
			(yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name()+","+(yyvsp[(3) - (6)])->get_name()+"["+ (yyvsp[(5) - (6)])->get_name()+"]","declaration_list");
 		  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 421 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD "<<endl<<endl;
 		  	outlog<<(yyvsp[(1) - (6)])->get_name()+","<<(yyvsp[(3) - (6)])->get_name()<<"["<<(yyvsp[(5) - (6)])->get_name()<<"]"<<endl<<endl;
			
            // Report error for float array size
            semantic_error(lines, "Array size must be an integer, not float");
			
			current_type = "array";
			array_size = 0; // Invalid array size
			(yyval) = new symbol_info((yyvsp[(1) - (6)])->get_name()+","+(yyvsp[(3) - (6)])->get_name()+"["+ (yyvsp[(5) - (6)])->get_name()+"]","declaration_list");
 		  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 433 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;

            // you may need to store the variable names to insert them in symbol table here or later
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"declaration_list");
 		  }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 441 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
			outlog<<(yyvsp[(1) - (4)])->get_name()<<"["<<(yyvsp[(3) - (4)])->get_name()<<"]"<<endl<<endl;

            // Store array name and size
			(yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name()+"["+ (yyvsp[(3) - (4)])->get_name()+"]","declaration_list");
 		  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 449 "syntax_analyzer.y"
    {
 		  	outlog<<"At line no: "<<lines<<" declaration_list : ID LTHIRD CONST_FLOAT RTHIRD "<<endl<<endl;
			outlog<<(yyvsp[(1) - (4)])->get_name()<<"["<<(yyvsp[(3) - (4)])->get_name()<<"]"<<endl<<endl;

            // Report error for float array size
            semantic_error(lines, "Array size must be an integer, not float");
			
			(yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name()+"["+ (yyvsp[(3) - (4)])->get_name()+"]","declaration_list");
 		  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 462 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statements : statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"stmnts");
	   }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 469 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statements : statements statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->get_name()<<"\n"<<(yyvsp[(2) - (2)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+"\n"+(yyvsp[(2) - (2)])->get_name(),"stmnts");
	   }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 478 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : var_declaration "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"stmnt");
	  }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 485 "syntax_analyzer.y"
    {
	  		outlog<<"At line no: "<<lines<<" statement : func_definition "<<endl<<endl;
            outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;

            (yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"stmnt");
	  		
	  }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 493 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : expression_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"stmnt");
	  }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 500 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : compound_statement "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"stmnt");
	  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 507 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
			outlog<<"for("<<(yyvsp[(3) - (7)])->get_name()<<(yyvsp[(4) - (7)])->get_name()<<(yyvsp[(5) - (7)])->get_name()<<")\n"<<(yyvsp[(7) - (7)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info("for("+(yyvsp[(3) - (7)])->get_name()+(yyvsp[(4) - (7)])->get_name()+(yyvsp[(5) - (7)])->get_name()+")\n"+(yyvsp[(7) - (7)])->get_name(),"stmnt");
	  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 514 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"if("<<(yyvsp[(3) - (5)])->get_name()<<")\n"<<(yyvsp[(5) - (5)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info("if("+(yyvsp[(3) - (5)])->get_name()+")\n"+(yyvsp[(5) - (5)])->get_name(),"stmnt");
	  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 521 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
			outlog<<"if("<<(yyvsp[(3) - (7)])->get_name()<<")\n"<<(yyvsp[(5) - (7)])->get_name()<<"\nelse\n"<<(yyvsp[(7) - (7)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info("if("+(yyvsp[(3) - (7)])->get_name()+")\n"+(yyvsp[(5) - (7)])->get_name()+"\nelse\n"+(yyvsp[(7) - (7)])->get_name(),"stmnt");
	  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 528 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
			outlog<<"while("<<(yyvsp[(3) - (5)])->get_name()<<")\n"<<(yyvsp[(5) - (5)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info("while("+(yyvsp[(3) - (5)])->get_name()+")\n"+(yyvsp[(5) - (5)])->get_name(),"stmnt");
	  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 535 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
			outlog<<"printf("<<(yyvsp[(3) - (5)])->get_name()<<");"<<endl<<endl; 
			
			// Check if the variable exists
			symbol_info* var = st->lookup((yyvsp[(3) - (5)])->get_name());
			if(var == NULL) {
				semantic_error(lines, "Undeclared variable " + (yyvsp[(3) - (5)])->get_name());
			}
			
			(yyval) = new symbol_info("printf("+(yyvsp[(3) - (5)])->get_name()+");","stmnt");
	  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 548 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
			outlog<<"return "<<(yyvsp[(2) - (3)])->get_name()<<";"<<endl<<endl;
			
			(yyval) = new symbol_info("return "+(yyvsp[(2) - (3)])->get_name()+";","stmnt");
			
			// Check if return type is compatible with function return type
			if (current_func_return_type == "void" && (yyvsp[(2) - (3)])->get_name() != "") {
				semantic_error(lines, "Void function cannot return a value");
			}
			else if (current_func_return_type == "int" && (yyvsp[(2) - (3)])->get_data_type() == "float") {
				semantic_error(lines, "Error: Possible loss of precision when returning float from an int function");
			}
	  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 565 "syntax_analyzer.y"
    {
				outlog<<"At line no: "<<lines<<" expression_statement : SEMICOLON "<<endl<<endl;
				outlog<<";"<<endl<<endl;
				
				(yyval) = new symbol_info(";","expr_stmt");
	        }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 572 "syntax_analyzer.y"
    {
				outlog<<"At line no: "<<lines<<" expression_statement : expression SEMICOLON "<<endl<<endl;
				outlog<<(yyvsp[(1) - (2)])->get_name()<<";"<<endl<<endl;
				
				(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+";","expr_stmt");
	        }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 581 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" variable : ID "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"varbl");
		
		// Check if the variable is declared - in ANY scope (includes global scope)
		symbol_info* var = st->lookup((yyvsp[(1) - (1)])->get_name());
		if(var == NULL) {
			semantic_error(lines, "Undeclared variable " + (yyvsp[(1) - (1)])->get_name());
			(yyval)->set_data_type("error");
		} else {
			// Successfully found variable, set its type information
			(yyval)->set_data_type(var->get_data_type());
			(yyval)->set_symbol_type(var->get_symbol_type());
			
			// Check if it's an array being used without index
			if(var->is_array()) {
				semantic_error(lines, "variable is of array type : " + (yyvsp[(1) - (1)])->get_name());
			}
		}
	 }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 604 "syntax_analyzer.y"
    {
	 	outlog<<"At line no: "<<lines<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
		outlog<<(yyvsp[(1) - (4)])->get_name()<<"["<<(yyvsp[(3) - (4)])->get_name()<<"]"<<endl<<endl;
		
		(yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name()+"["+(yyvsp[(3) - (4)])->get_name()+"]","varbl");
		
		// Check if the array is declared
		symbol_info* var = st->lookup((yyvsp[(1) - (4)])->get_name());
		if(var == NULL) {
			semantic_error(lines, "Undeclared variable " + (yyvsp[(1) - (4)])->get_name());
			(yyval)->set_data_type("error");
		} else {
			// Check if it's actually an array
			if(!var->is_array()) {
				semantic_error(lines, "variable is not of array type : " + (yyvsp[(1) - (4)])->get_name());
				(yyval)->set_data_type(var->get_data_type());
			} else {
				(yyval)->set_data_type(var->get_data_type());
				(yyval)->set_symbol_type("Array");
				
				// Check if index is integer
				if((yyvsp[(3) - (4)])->get_data_type() != "int") {
					semantic_error(lines, "array index is not of integer type : " + (yyvsp[(1) - (4)])->get_name());
					(yyval)->set_data_type("error"); // Mark as error to prevent further operations
				}
				
				// Check if the index is a float literal by looking for a decimal point
				if((yyvsp[(3) - (4)])->get_name().find('.') != string::npos) {
				    semantic_error(lines, "array index is not an integer : " + (yyvsp[(1) - (4)])->get_name());
				    (yyval)->set_data_type("error"); // Mark as error to prevent further operations
				}
			}
		}
	 }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 641 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" expression : logic_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"expr");
			(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 649 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<"="<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;

			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+"="+(yyvsp[(3) - (3)])->get_name(),"expr");
			
			// Check if types are compatible
			if((yyvsp[(1) - (3)])->get_data_type() != "error" && (yyvsp[(3) - (3)])->get_data_type() != "error") {
				// Get types for assignment validation
				string var_type = (yyvsp[(1) - (3)])->get_data_type();
				string expr_type = (yyvsp[(3) - (3)])->get_data_type();
				string expr_val = (yyvsp[(3) - (3)])->get_name();
				
				// Check if the expression is a void function call
				if(expr_type == "void") {
					semantic_error(lines, "Void function used in expression");
					(yyval)->set_data_type("error");
				}
				// Integer variable assigned float value - treat exactly as per expected output
				else if(var_type == "int" && (expr_type == "float" || expr_val.find('.') != string::npos)) {
					// Make sure to use exactly the same format as in error2.txt
					semantic_error(lines, "Warning: Assignment of float value into variable of integer type");
					// Still mark the line as having an error 
					if(lines_with_errors.find(lines) == lines_with_errors.end()) {
						lines_with_errors.insert(lines);
					}
					
					(yyval)->set_data_type(var_type);
				}
				// Handle empty (null) expression values
				else if(expr_type == "") {
					(yyval)->set_data_type(var_type);
				}
				
				// Regular type compatibility check for other cases
				else if(!type_compatible(var_type, expr_type)) {
					semantic_error(lines, "Type mismatch in assignment. " + var_type + " variable cannot be assigned " + expr_type + " value");
					(yyval)->set_data_type(var_type); 
				} 
				else {
					(yyval)->set_data_type(var_type);
				}
			} else {
				(yyval)->set_data_type("error");
			}
	   }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 698 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"lgc_expr");
			(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	     }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 706 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<(yyvsp[(2) - (3)])->get_name()<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+(yyvsp[(2) - (3)])->get_name()+(yyvsp[(3) - (3)])->get_name(),"lgc_expr");
			
			// Result of logical operation should always be int
			(yyval)->set_data_type("int");
	     }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 718 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"rel_expr");
			(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	    }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 726 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<(yyvsp[(2) - (3)])->get_name()<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+(yyvsp[(2) - (3)])->get_name()+(yyvsp[(3) - (3)])->get_name(),"rel_expr");
			
			// Result of relational operation should always be int
			(yyval)->set_data_type("int");
	    }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 738 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" simple_expression : term "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"simp_expr");
			(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	      }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 746 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<(yyvsp[(2) - (3)])->get_name()<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+(yyvsp[(2) - (3)])->get_name()+(yyvsp[(3) - (3)])->get_name(),"simp_expr");
			
			// Type check for ADDOP
			if((yyvsp[(1) - (3)])->get_data_type() == "float" || (yyvsp[(3) - (3)])->get_data_type() == "float") {
				(yyval)->set_data_type("float");
			} else {
				(yyval)->set_data_type("int");
			}
	      }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 762 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" term : unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"term");
			(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	 }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 770 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" term : term MULOP unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (3)])->get_name()<<(yyvsp[(2) - (3)])->get_name()<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+(yyvsp[(2) - (3)])->get_name()+(yyvsp[(3) - (3)])->get_name(),"term");
			
			// Type checks for multiplication, division, and modulus
			string op = (yyvsp[(2) - (3)])->get_name();
			
			// Both operands should be integers for modulus
			if(op == "%") {
				if((yyvsp[(1) - (3)])->get_data_type() != "int" || (yyvsp[(3) - (3)])->get_data_type() != "int") {
					semantic_error(lines, "Modulus operator on non integer type");
					(yyval)->set_data_type("error");
				} else {
					(yyval)->set_data_type("int");
				}
				if((yyvsp[(3) - (3)])->get_name() == "0") {
					semantic_error(lines, "Modulus by 0 ");
					(yyval)->set_data_type("error");
				}
			} 
			// Check for division by zero (for constants)
			else if(op == "/" || op == "%") {
				if((yyvsp[(3) - (3)])->get_name() == "0") {
					semantic_error(lines, "Division by zero");
					(yyval)->set_data_type("error");
				} 
				else {
					if(op == "/" && ((yyvsp[(1) - (3)])->get_data_type() == "float" || (yyvsp[(3) - (3)])->get_data_type() == "float")) {
						(yyval)->set_data_type("float");
					} else {
						(yyval)->set_data_type("int");
					}
				}
			}
			// For multiplication
			else {
				if((yyvsp[(1) - (3)])->get_data_type() == "float" || (yyvsp[(3) - (3)])->get_data_type() == "float") {
					(yyval)->set_data_type("float");
				} else {
					(yyval)->set_data_type("int");
				}
			}
	 }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 818 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
			outlog<<(yyvsp[(1) - (2)])->get_name()<<(yyvsp[(2) - (2)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+(yyvsp[(2) - (2)])->get_name(),"un_expr");
	     }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 825 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : NOT unary_expression "<<endl<<endl;
			outlog<<"!"<<(yyvsp[(2) - (2)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info("!"+(yyvsp[(2) - (2)])->get_name(),"un_expr");
	     }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 832 "syntax_analyzer.y"
    {
	    	outlog<<"At line no: "<<lines<<" unary_expression : factor "<<endl<<endl;
			outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"un_expr");
	     }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 841 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"fctr");
		(yyval)->set_data_type((yyvsp[(1) - (1)])->get_data_type());
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 849 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
		outlog<<(yyvsp[(1) - (4)])->get_name()<<"("<<(yyvsp[(3) - (4)])->get_name()<<")"<<endl<<endl;

		(yyval) = new symbol_info((yyvsp[(1) - (4)])->get_name()+"("+(yyvsp[(3) - (4)])->get_name()+")","fctr");
		
		// Check if the function exists
		symbol_info* func = st->lookup((yyvsp[(1) - (4)])->get_name());
		if(func == NULL) {
			semantic_error(lines, "Undeclared function: " + (yyvsp[(1) - (4)])->get_name());
			(yyval)->set_data_type("error");
		} else {
			// Check if it's actually a function
			if(!func->is_function()) {
				semantic_error(lines, (yyvsp[(1) - (4)])->get_name() + " is not a function");
				(yyval)->set_data_type("error");
			} else {
				// Check if it's a void function used in an expression
				if(func->get_data_type() == "void") {
					semantic_error(lines, "operation on void type");
					(yyval)->set_data_type("error");
				} else {
					(yyval)->set_data_type(func->get_data_type());
				}
				
				// Parse arguments
				vector<string> arg_types;
				string args = (yyvsp[(3) - (4)])->get_name();
				if(!args.empty()) {
					size_t start = 0, end;
					while((end = args.find(',', start)) != string::npos) {
						arg_types.push_back("int"); // track actual types
						start = end + 1;
					}
					arg_types.push_back("int"); 
				}
				
				// Check number of arguments
				vector<string> param_types = func->get_param_types();
				if(arg_types.size() != param_types.size()) {
					semantic_error(lines, "Inconsistencies in number of arguments in function call: " + (yyvsp[(1) - (4)])->get_name());
				}
				
				// Check argument types (simplified)
				for(size_t i = 0; i < min(arg_types.size(), param_types.size()); i++) {
					if(param_types[i] == "int" && arg_types[i] != "int") {
						semantic_error(lines, "argument " + to_string(i+1) + " type mismatch in function call: " + (yyvsp[(1) - (4)])->get_name());
					}
				}
			}
		}
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 902 "syntax_analyzer.y"
    {
	   	outlog<<"At line no: "<<lines<<" factor : LPAREN expression RPAREN "<<endl<<endl;
		outlog<<"("<<(yyvsp[(2) - (3)])->get_name()<<")"<<endl<<endl;
		
		(yyval) = new symbol_info("("+(yyvsp[(2) - (3)])->get_name()+")","fctr");
		(yyval)->set_data_type((yyvsp[(2) - (3)])->get_data_type());
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 910 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : CONST_INT "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"fctr");
		(yyval)->set_data_type("int");
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 918 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : CONST_FLOAT "<<endl<<endl;
		outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
			
		(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"fctr");
		(yyval)->set_data_type("float");
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 926 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable INCOP "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->get_name()<<"++"<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+"++","fctr");
			(yyval)->set_data_type((yyvsp[(1) - (2)])->get_data_type());
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 934 "syntax_analyzer.y"
    {
	    outlog<<"At line no: "<<lines<<" factor : variable DECOP "<<endl<<endl;
		outlog<<(yyvsp[(1) - (2)])->get_name()<<"--"<<endl<<endl;
			
			(yyval) = new symbol_info((yyvsp[(1) - (2)])->get_name()+"--","fctr");
			(yyval)->set_data_type((yyvsp[(1) - (2)])->get_data_type());
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 944 "syntax_analyzer.y"
    {
					outlog<<"At line no: "<<lines<<" argument_list : arguments "<<endl<<endl;
					outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
						
					(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"arg_list");
			  }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 951 "syntax_analyzer.y"
    {
					outlog<<"At line no: "<<lines<<" argument_list :  "<<endl<<endl;
					outlog<<""<<endl<<endl;
						
					(yyval) = new symbol_info("","arg_list");
			  }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 960 "syntax_analyzer.y"
    {
				outlog<<"At line no: "<<lines<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
				outlog<<(yyvsp[(1) - (3)])->get_name()<<","<<(yyvsp[(3) - (3)])->get_name()<<endl<<endl;
						
				(yyval) = new symbol_info((yyvsp[(1) - (3)])->get_name()+","+(yyvsp[(3) - (3)])->get_name(),"arg");
		  }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 967 "syntax_analyzer.y"
    {
				outlog<<"At line no: "<<lines<<" arguments : logic_expression "<<endl<<endl;
				outlog<<(yyvsp[(1) - (1)])->get_name()<<endl<<endl;
						
				(yyval) = new symbol_info((yyvsp[(1) - (1)])->get_name(),"arg");
	      }
    break;


/* Line 1792 of yacc.c  */
#line 2703 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 976 "syntax_analyzer.y"


int main(int argc, char *argv[])
{
	if(argc != 2) 
	{
		cout<<"Please provide input file name"<<endl;
		return 0;
	}
	yyin = fopen(argv[1], "r");
	
	// Extract student ID from filename and create output file names
	string inputfile = argv[1];
	
	outlog.open("log.txt", ios::trunc);
	errout.open("error.txt", ios::trunc);
	
	if(yyin == NULL)
	{
		cout<<"Couldn't open input file"<<endl;
		return 0;
	}
	// Enter the global or the first scope here
	st = new symbol_table(10);
	st->enter_scope();
	outlog << "Entered new scope with ID: " << st->get_current_scope_id() << endl;

	yyparse();
	
	// Reset error count based on unique lines with errors
	error_count = lines_with_errors.size();

	outlog<<endl<<"Total lines: "<<lines<<endl;
	outlog<<"Total error lines: "<<error_count<<endl;

	// Add error count to error file too
	errout<<endl<<"Total error lines: "<<error_count<<endl;
	
	outlog.close();
	errout.close();
	
	fclose(yyin);
	
	return 0;
}