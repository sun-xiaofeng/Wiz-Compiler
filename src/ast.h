/* ast.h */

/*-----------------------------------------------------------------------
    Definitions for the abstract syntax trees generated for Iz programs.
    For use in the COMP90045 project 2014.
-----------------------------------------------------------------------*/

#ifndef AST_H
#define AST_H

#include "std.h"

typedef struct decl   Decl;
typedef struct decls  Decls;
typedef struct expr   Expr;
typedef struct stmts  Stmts;
typedef struct stmt   Stmt;
typedef struct prog   Program;
typedef struct proc   Proc;
typedef struct procs  Procs;
typedef struct arguments Arguments;
typedef struct argument Argument;
typedef struct procDef  ProcDef;
typedef int bool;

typedef enum {
    BINOP_ADD, BINOP_SUB, BINOP_MUL
} BinOp;

#define BINOP_NAMES "+", "-", "*"

extern const char *binopname[]; 

typedef enum {
    UNOP_MINUS
} UnOp;

#define UNOP_NAMES "-"

extern const char *unopname[];

typedef enum {
    BOOL_TYPE, INT_TYPE
} Type;

typedef union {
    int    int_val;
    BOOL   bool_val;
    float  float_val;
} Value;

typedef struct {
    Type   type;
    Value  val;
    char*  raw;
} Constant;

typedef enum {
    EXPR_ID, EXPR_CONST, EXPR_BINOP, EXPR_UNOP
} ExprKind;

struct expr {
    int       lineno;
    ExprKind  kind;
    char      *id;          /* for identifiers */
    Constant  constant;     /* for constant values */
    UnOp      unop;         /* for unary operators */
    BinOp     binop;        /* for binary operators */
    Expr      *e1;          /* for unary and binary operators */
    Expr      *e2;          /* for binary operators */
};

struct decl {
    int       lineno;
    char      *id;
    Type      type;
};

struct decls {
    Decl      *first;
    Decls     *rest;
};

typedef enum {
    STMT_ASSIGN, STMT_COND, STMT_READ, STMT_WHILE, STMT_WRITE
} StmtKind;

typedef struct {
    char      *asg_id;
    Expr      *asg_expr;
} Assign;

typedef struct {
    Expr      *cond;
    Stmts     *then_branch;
    Stmts     *else_branch;
} Cond;

typedef struct {
    Expr      *cond;
    Stmts     *body;
} While;

typedef union {
    Assign    assign;
    Stmts     *stmts;
    Cond      cond;
    char      *read;
    Expr      *write;
    While     loop;
} SInfo;

struct stmt {
    int       lineno;
    StmtKind  kind;
    SInfo     info;
};

struct stmts {
    Stmt      *first;
    Stmts     *rest;
};

struct prog {
    Procs   *procs;
};

struct proc {
    StmtKind   kind;
    ProcDef   *proc_def;
    Decls     *decls;
    Stmts     *body;
    char      *terminator;
};

struct procDef {
    char* start_marker;
    char* name;
    char* start_paran;
    Arguments *arguments;
    StmtKind kind;
    char* end_paran;
    
};

struct arguments {
    Argument *first;
    char *separator;
    Arguments *rest;
};

struct argument {
    Type type;
    char* id;
};

struct procs {
    Proc    *first;
    Procs   *rest;
};

#endif /* AST_H */
