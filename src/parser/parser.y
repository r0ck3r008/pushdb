%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<stdint.h>

	#include"parse_tree.h"

	int yylex();
	int yyparse();
	void yyerror(char *);

	// these data structures hold the result of the parsing
	struct TableList *tables=NULL; // the list of tables and aliases in the query
	struct AndList *boolean=NULL; // the predicate in the WHERE clause
	struct NameList *attsToSelect=NULL; // the set of attributes in the SELECT (NULL if no such atts)
	int queryType; // 1 for SELECT, 2 for CREATE, 3 for DROP, 4 for INSERT
	char *outputVar=NULL;
	char *tableName=NULL;
	char *fileToInsert=NULL;
	struct AttrList *attsToCreate=NULL;
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
}

%token <actualChars> _name
%token <actualChars> _float
%token <actualChars> _int
%token <actualChars> _string
%token _select /*_ due to collision with select function defined in stdlib */
%token from
%token where
%token as
%token and
%token or

%token create
%token _table
%token on
%token insert
%token drop
%token into
%token set
%token output

%type <myOrList> orlist
%type <myAndList> andlist
%type <myComparison> boolcomp
%type <myComparison> condition
%type <myTables> tables
%type <myBoolOperand> literal
%type <myNames> atts
%type <myAttrList> newatts

%start sql

%%

sql: _select whatiwant from tables
{
	tables = $4;
	queryType = 1;
}

| _select whatiwant from tables where andlist
{
	tables = $4;
	boolean = $6;
	queryType = 1;
}

| set output _name _select whatiwant from tables
{
	outputVar = $3;
	tables = $7;
	queryType = 1;
}

| set output _name _select whatiwant from tables where andlist
{
	outputVar = $3;
	tables = $7;
	boolean = $9;
	queryType = 1;
}

| set output _string _select whatiwant from tables where andlist
{
	outputVar=$3;
	tables = $7;
	boolean = $9;
	queryType = 1;
}

| create _table _name '(' newatts ')'
{
	tableName = $3;
	attsToCreate = $5;
	queryType = 2;
}

| insert _string into _name
{
	fileToInsert = $2;
	tableName = $4;
	queryType = 4;
}

| drop _table _name
{
	tableName = $3;
	queryType = 3;
}
;

newatts: _name _name
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

| _name _name',' newatts
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

whatiwant: atts
{
	attsToSelect = $1;
}

atts: _name
{
	$$ = (struct NameList *) malloc (sizeof (struct NameList));
	$$->name = $1;
	$$->next = NULL;
}

| atts ',' _name
{
	$$ = (struct NameList *) malloc (sizeof (struct NameList));
	$$->name = $3;
	$$->next = $1;
}
;

tables: _name as _name
{
	$$ = (struct TableList *) malloc (sizeof (struct TableList));
	$$->tableName = $1;
	$$->aliasAs = $3;
	$$->next = NULL;
}

| tables ',' _name as _name
{
	$$ = (struct TableList *) malloc (sizeof (struct TableList));
	$$->tableName = $3;
	$$->aliasAs = $5;
	$$->next = $1;
}
;

andlist: '(' orlist ')' and andlist
{
        // here we need to pre-pend the OrList to the AndList
        // first we allocate space for this node
        $$ = (struct AndList *) malloc (sizeof (struct AndList));

        // hang the OrList off of the left
        $$->left = $2;

        // hang the AndList off of the right
        $$->rightAnd = $5;

}

| '(' orlist ')'
{
        // just return the OrList!
        $$ = (struct AndList *) malloc (sizeof (struct AndList));
        $$->left = $2;
        $$->rightAnd = NULL;
}
;

orlist: condition or orlist
{
        // here we have to hang the condition off the left of the OrList
        $$ = (struct OrList *) malloc (sizeof (struct OrList));
        $$->left = $1;
        $$->rightOr = $3;
}

| condition
{
        // nothing to hang off of the right
        $$ = (struct OrList *) malloc (sizeof (struct OrList));
        $$->left = $1;
        $$->rightOr = NULL;
}
;

condition: literal boolcomp literal
{
        // in this case we have a simple literal/variable comparison
        $$ = $2;
        $$->left = $1;
        $$->right = $3;
}
;

boolcomp: '<'
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

literal : _string
{
        // construct and send up the operand containing the string
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = STRING;
        $$->value = $1;
}

| _float
{
        // construct and send up the operand containing the FP number
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = FLOAT;
        $$->value = $1;
}

| _int
{
        // construct and send up the operand containing the integer
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = INT;
        $$->value = $1;
}

| _name
{
        // construct and send up the operand containing the name
        $$ = (struct Operand *) malloc (sizeof (struct Operand));
        $$->code = NAME;
        $$->value = $1;
}
;

%%
