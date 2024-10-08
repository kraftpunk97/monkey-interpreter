//
// Created by kxg220013 on 12/13/2023.
//

#ifndef AST_H
#define AST_H


#include "linked_list/linked_list.h"
#include "token.h"

typedef struct {
    list statements;
} program_t;

program_t*  ast_program_create      ();
void        ast_program_destroy     (program_t* program);
char*       ast_program_string      (program_t* program);

#endif /* AST_H */
