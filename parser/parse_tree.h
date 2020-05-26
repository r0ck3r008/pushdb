#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include<stdint.h>

// these are the types of operands that can appear in a CNF expression
#define FLOAT 1
#define INT 2
#define NAME 3
#define STRING 4
#define LESS_THAN 5
#define GREATER_THAN 6
#define EQUALS 7

/* To be used in aggregate queries
 *
// used in computational (funcional) expressions
typedef struct FuncOperand
{
	// this tells us the type of the operand: FLOAT, INT, STRING...
	uint8_t code;
	// this is the actual operand
	int8_t *value;
} FuncOperand;

typedef struct FuncOperator
{
	// this tells us which operator to use: '+', '-', ...
	uint8_t code;
	// these are the operators on the left and on the right
	struct FuncOperator *leftOperator;
	struct FuncOperand *leftOperand;
	struct FuncOperator *right;
} FuncOperator;
*
*/

typedef struct TableList
{
	// this is the original table name
	int8_t *tableName;
	// this is the value it is aliased to
	int8_t *aliasAs;
	// and this the next alias
	struct TableList *next;
} TableList;

typedef struct NameList
{
	// this is the name
	int8_t *name;
	// and this is the next name in the list
	struct NameList *next;
} NameList;

// used in boolean expressions... there's no reason to have both this
// and FuncOperand, but both are here for legacy reasons!!
typedef struct Operand
{
	// this tells us the type of the operand: FLOAT, INT, STRING...
	int code;
	// this is the actual operand
	int8_t *value;
} Operand;

typedef struct ComparisonOp
{
	// this corresponds to one of the codes describing what type
	// of literal value we have in this nodes: LESS_THAN, EQUALS...
	int code;
	// these are the operands on the left and on the right
	struct Operand *left;
	struct Operand *right;
} ComparisonOp;

typedef struct OrList
{
	// this is the comparison to the left of the OR
	struct ComparisonOp *left;
	// this is the OrList to the right of the OR; again,
	// this might be NULL if the right is a simple comparison
	struct OrList *rightOr;
} OrList;

typedef struct AndList
{
	// this is the disjunction to the left of the AND
	struct OrList *left;
	// assuming atomic operations per AndList->left
	uint8_t is_join;
	// this is the AndList to the right of the AND
	// note that this can be NULL if the right is a disjunction
	struct AndList *rightAnd;
} AndList;

// Used in DDL Commands
typedef struct AttrList
{
	int8_t *name;
	uint8_t type;
	uint16_t len;
	struct AttrList *next;

} AttrList;

#endif
