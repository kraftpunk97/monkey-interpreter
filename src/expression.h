
//
// Created by kxg220013 on 12/14/2023.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

// This declaration is used by statement.h:
// (hence it being in front of the include)
typedef struct expression expr_t;

#include <stdbool.h>
#include "statement.h"
#include "token.h"

typedef enum {
    EXPRESSION_IDENTIFIER,
    EXPRESSION_NUMBER,
    EXPRESSION_BOOLEAN,
    EXPRESSION_PREFIX,
    EXPRESSION_INFIX,
    EXPRESSION_IF,
    EXPRESSION_FN_DEFN
} expr_type_t;

typedef struct {
    token_t token;
    char* value;
} identifier_t;

typedef struct {
    token_t token;
    int value;
} number_t;

typedef struct {
    token_t token;
    bool value;
} boolean_t;

typedef struct {
    token_t token; // operator of the prefix expr
    char* operator;
    expr_t* expr;
} prefix_t;

typedef struct {
    token_t token; // operator of the infix expr
    char* operator;
    expr_t* left_expr;
    expr_t* right_expr;
} infix_t;

typedef struct { 
    token_t token;
    expr_t* condition;
    stmt_t* consequence;
    stmt_t* alternative;
} if_t;

typedef struct {
    token_t token;
    expr_t* name;
    list parameters;
    stmt_t* body;
} fn_defn_t;

typedef struct {
    token_t token;
    list parameters;
    stmt_t* body;
} expr_fn_defn_t;

//     MACROS FOR ACCESSING THE EXPR UNION 
// ---------------------------------------------
// WARNING: 'e' must be of type 'expr_t* '
#define EXPR_IDENT(e)   ((e)->expr.identifier)
#define EXPR_NUMBER(e)  ((e)->expr.number)
#define EXPR_BOOLEAN(e) ((e)->expr.boolean)
#define EXPR_PREFIX(e)  ((e)->expr.prefix)
#define EXPR_INFIX(e)   ((e)->expr.infix)
#define EXPR_IF(e)      ((e)->expr.ifelse)
#define EXPR_FN_DEFN(e) ((e)->expr.fn_defn)

//     MACROS FOR CALLING EXPR METHODS
// --------------------------------------------
// WARNING: 'e' must be of type 'stmt_t* ' or 'expr_t* '
#ifndef METHOD_MACROS
#define METHOD_MACROS
    #define TOKEN_LITERAL(e) ((e)->token_literal(e))
    #define STRING(e)       ((e)->string(e))
    #define DESTROY(e)      ((e)->destroy(e));
#endif

struct expression {
    expr_type_t type;
    union {
        identifier_t identifier; 
        number_t number;
        boolean_t boolean;
        prefix_t prefix;
        infix_t infix;
        if_t ifelse; // Can't use 'if' keyword...
        fn_defn_t fn_defn;
    } expr;

    // ==== METHODS ====
    // this fn will always return a non-allocated literal of the expr's token
    char*   (*token_literal)    (expr_t* expr);
    // this fn will always return a heap-allocated string of the expr
    char*   (*string)           (expr_t* expr);
    // this fn will always destroy the expr completely.
    // (DOES NOT set expr to NULL)
    void    (*destroy)          (expr_t* expr);
};

expr_t*     expr_identifier_create          (token_t token);
char*       expr_identifier_token_literal   (expr_t* expr);
char*       expr_identifier_string          (expr_t* expr);
void        expr_identifier_destroy         (expr_t* expr);

expr_t*     expr_number_create              (token_t token, int value);
char*       expr_number_token_literal       (expr_t* expr);
char*       expr_number_string              (expr_t* expr);
void        expr_number_destroy             (expr_t* expr);

expr_t*     expr_boolean_create             (token_t token, bool value);
char*       expr_boolean_token_literal      (expr_t* expr);
char*       expr_boolean_string             (expr_t* expr);
void        expr_boolean_destroy            (expr_t* expr);

expr_t*     expr_prefix_create              (token_t token, char* op, expr_t* expr);
char*       expr_prefix_token_literal       (expr_t* expr);
char*       expr_prefix_string              (expr_t* expr);
void        expr_prefix_destroy             (expr_t* expr);

expr_t*     expr_infix_create               (token_t token, char* op, expr_t* lexpr, expr_t* rexpr);
char*       expr_infix_token_literal        (expr_t* expr);
char*       expr_infix_string               (expr_t* expr);
void        expr_infix_destroy              (expr_t* expr);

expr_t*     expr_if_create                  (token_t token, expr_t* cond, stmt_t* cons, stmt_t* alt);
char*       expr_if_token_literal           (expr_t* expr);
char*       expr_if_string                  (expr_t* expr);
void        expr_if_destroy                 (expr_t* expr);

expr_t*     expr_fn_defn_create             (token_t token, expr_t* name, list parameters, stmt_t* body);
char*       expr_fn_defn_token_literal      (expr_t* expr);
char*       expr_fn_defn_string             (expr_t* expr);
void        expr_fn_defn_destroy            (expr_t* expr);

void        expr_destroy                    (expr_t* expr);

#endif /* EXPRESSSION_H */
