%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<stdint.h>

	#include"parse_tree.h"

	uint8_t yylex();
	int yyparse();
	void yyerror(int8_t *);

	// these data structures hold the result of the parsing
	struct TableList *tables; // the list of tables and aliases in the query
	struct AndList *boolean; // the predicate in the WHERE clause
	struct NameList *attsToSelect; // the set of attributes in the SELECT (NULL if no such atts)
	int queryType; // 1 for SELECT, 2 for CREATE, 3 for DROP, 4 for INSERT
	char *outputVar;
	char *tableName;
	char *fileToInsert;
	struct AttrList *attsToCreate;
%}

// this stores all of the types returned by production rules
%union {
	struct TableList *myTables;
	struct ComparisonOp *myComparison;
	struct Operand *myBoolOperand;
	struct OrList *myOrList;
	struct AndList *myAndList;
	struct NameList *myNames;
	struct AttrList *myAttrList;
	char *actualChars;
	char whichOne;
};

%token <actualChars> Name
%token <actualChars> Float
%token <actualChars> Int
%token <actualChars> String
%token SELECT
%token FROM
%token WHERE
%token AS
%token AND
%token OR

%token CREATE
%token TABLE
%token ON
%token INSERT
%token DROP
%token INTO
%token SET
%token OUTPUT
%token EXIT

%type <myOrList> OrList
%type <myAndList> AndList
%type <myComparison> BoolComp
%type <myComparison> Condition
%type <myTables> Tables
%type <myBoolOperand> Literal
%type <myNames> Atts
%type <myAttrList> NewAtts

%start SQL

%%

SQL: SELECT WhatIWant FROM Tables WHERE AndList
{
	tables = $4;
	boolean = $6;
	queryType = 1;
}

| SET OUTPUT Name SELECT WhatIWant FROM Tables WHERE AndList
{
	outputVar = $3;
	tables = $7;
	boolean = $9;
	queryType = 1;
}

| SET OUTPUT String SELECT WhatIWant FROM Tables WHERE AndList
{
	outputVar=$3;
	tables = $7;
	boolean = $9;
	queryType = 1;
}

| CREATE TABLE Name '(' NewAtts ')'
{
	tableName = $3;
	attsToCreate = $5;
	queryType = 2;
}

| INSERT String INTO Name
{
	fileToInsert = $2;
	tableName = $4;
	queryType = 4;
}

| DROP TABLE Name
{
	tableName = $3;
	queryType = 3;
}

| EXIT
{
	queryType = 6;
}
;

NewAtts: Name Name
{
	$$ = (struct AttrList *) malloc (sizeof (struct AttrList));
	$$->name = $1;
	if (strcmp ($2, "Int") == 0)
		$$->type = 0;
	else if (strcmp ($2, "Float") == 0)
		$$->type = 1;
	else if (strcmp ($2, "String") == 0)
		$$->type = 2;
	$$->next = NULL;
}

| Name Name',' NewAtts
{
	$$ = (struct AttrList *) malloc (sizeof (struct AttrList));
	$$->name = $1;
	if(strcmp($2, "Int") == 0)
		$$->type = 0;
	else if(strcmp($2, "Float") == 0)
		$$->type = 1;
	else if(strcmp($2, "String") == 0)
		$$->type = 2;
	$$->next = $4;
}
;

WhatIWant: Atts
{
	attsToSelect = $1;
}

Atts: Name
{
	$$ = (struct NameList *) malloc (sizeof (struct NameList));
	$$->name = $1;
	$$->next = NULL;
}

| Atts ',' Name
{
	$$ = (struct NameList *) malloc (sizeof (struct NameList));
	$$->name = $3;
	$$->next = $1;
}
;

Tables: Name AS Name
{
	$$ = (struct TableList *) malloc (sizeof (struct TableList));
	$$->tableName = $1;
	$$->aliasAs = $3;
	$$->next = NULL;
}

| Tables ',' Name AS Name
{
	$$ = (struct TableList *) malloc (sizeof (struct TableList));
	$$->tableName = $3;
	$$->aliasAs = $5;
	$$->next = $1;
}
;

AndList: '(' OrList ')' AND AndList
{
        // here we need to pre-pend the OrList to the AndList
        // first we allocate space for this node
        $$ = (struct AndList *) malloc (sizeof (struct AndList));

        // hang the OrList off of the left
        $$->left = $2;

        // hang the AndList off of the right
        $$->rightAnd = $5;

}

| '(' OrList ')'
{
        // just return the OrList!
        $$ = (struct AndList *) malloc (sizeof (struct AndList));
        $$->left = $2;
        $$->rightAnd = NULL;
}
;

OrList: Condition OR OrList
{
        // here we have to hang the condition off the left of the OrList
        $$ = (struct OrList *) malloc (sizeof (struct OrList));
        $$->left = $1;
        $$->rightOr = $3;
}

| Condition
{
        // nothing to hang off of the right
        $$ = (struct OrList *) malloc (sizeof (struct OrList));
        $$->left = $1;
        $$->rightOr = NULL;
}
;

Condition: Literal BoolComp Literal
{
        // in this case we have a simple literal/variable comparison
        $$ = $2;
        $$->left = $1;
        $$->right = $3;
}
;

BoolComp: '<'
{
        // construct and send up the comparison
        $$ = (struct ComparisonOp *) malloc (sizeof (struct ComparisonOp));
        $$->code = LESS_THAN;
}

| '>'
{
        // construct and send up the comparison
        $$ = (struct ComparisonOp *) malloc (sizeof (struct ComparisonOp));
        $$->code = GREATER_THAN;
}

| '='
{
        // construct and send up the comparison
        $$ = (struct ComparisonOp *) malloc (sizeof (struct ComparisonOp));
        $$->code = EQUALS;
}
;

Literal : String
{
        // construct and send up the operand containing the string
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = STRING;
        $$->value = $1;
}

| Float
{
        // construct and send up the operand containing the FP number
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = DOUBLE;
        $$->value = $1;
}

| Int
{
        // construct and send up the operand containing the integer
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = INT;
        $$->value = $1;
}

| Name
{
        // construct and send up the operand containing the name
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = NAME;
        $$->value = $1;
}
;

%%
