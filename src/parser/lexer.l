%{

#include<stdio.h>
#include<string.h>
#include<stdint.h>

#include"y.tab.h"
#include"parse_tree.h"

uint8_t lineno=0;
void yyerror(int8_t *);
YY_BUFFER_STATE yy_scan_string(const char *);
void yy_delete_buffer();

%}

%%

"SELECT"		return(SELECT);
"FROM"			return(FROM);
"WHERE"			return(WHERE);
"AND"			return(AND);
"OR"			return(OR);
"AS"			return(AS);
"DROP"			return(DROP);
"CREATE"		return(CREATE);
"TABLE"			return(TABLE);
"ON"			return(ON);
"INSERT"		return(INSERT);
"INTO"			return(INTO);
"SET"			return(SET);
"OUTPUT"		return(OUTPUT);
"EXIT"			return(EXIT);
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
				return(Int);
			}
-?[0-9]+\.[0-9]*	{
				yylval.actualChars = strdup(yytext);
				return(Float);
			}
[A-Za-z][A-Za-z0-9_-]*	{
				yylval.actualChars = strdup(yytext);
				return(Name);
			}
[A-Za-z][A-Za-z0-9_-]*\.[A-Za-z][A-Za-z0-9_-]*	{
							yylval.actualChars = strdup(yytext);
							return(Name);
						}
\'[^'\n]*\'		{
				/* take care of ' in a string */
				if (yytext[yyleng - 2] == '\\') {
					yymore();
				} else {
					yylval.actualChars = strdup(yytext + 1);
					yylval.actualChars[strlen(yylval.actualChars) - 1] = 0;
					return(String);
				}
			}
\n			lineno++;
[ \t]             	;
.                 	yyerror("LEX_ERROR: invalid character");
%%

void yyerror(int8_t *s)
{
	printf("%d: %s at %s\n", lineno, s, yytext);
}

int yywrap(void)
{
	return 1;
}
