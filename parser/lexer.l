%{

#include<stdio.h>
#include<string.h>
#include<stdint.h>

#include"y.tab.h"
#include"parse_tree.h"

int lineno=0;
void yyerror(char *);
YY_BUFFER_STATE yy_scan_string(const char *);
void yy_delete_buffer();

%}

%%

"select"		return(_select);
"from"			return(from);
"where"			return(where);
"and"			return(and);
"or"			return(or);
"as"			return(as);
"drop"			return(drop);
"create"		return(create);
"table"			return(_table);
"on"			return(on);
"insert"		return(insert);
"into"			return(into);
"set"			return(set);
"output"		return(output);
"("			return('(');
"<"			return('<');
">"			return('>');
"="			return('=');
")"    	        	return(')');
"+"    	        	return('+');
"-"    	        	return('-');
"/"    	        	return('/');
"*"    	        	return('*');
","    	        	return(',');
-?[0-9]+		{
				yylval.actualChars = strdup(yytext);
				return(_int);
			}
-?[0-9]+\.[0-9]*	{
				yylval.actualChars = strdup(yytext);
				return(_float);
			}
[A-Za-z][A-Za-z0-9_-]*	{
				yylval.actualChars = strdup(yytext);
				return(_name);
			}
[A-Za-z][A-Za-z0-9_-]*\.[A-Za-z][A-Za-z0-9_-]*	{
							yylval.actualChars = strdup(yytext);
							return(_name);
						}
\'[^'\n]*\'		{
				/* take care of ' in a string */
				if (yytext[yyleng - 2] == '\\') {
					yymore();
				} else {
					yylval.actualChars = strdup(yytext + 1);
					yylval.actualChars[strlen(yylval.actualChars) - 1] = 0;
					return(_string);
				}
			}
";"			;
\n			lineno++;
[ \t]             	;
.                 	yyerror("LEX_ERROR: invalid character");
%%

void yyerror(char *s)
{
	printf("%d: %s at %s\n", lineno, s, yytext);
}

int yywrap(void)
{
	return 1;
}
