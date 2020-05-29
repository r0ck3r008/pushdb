#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"query.h"
#include"handler.h"

void init_loop(FILE *f)
{
	char *query=calloc(512, sizeof(char));
	while(1) {
		int begin=1;
		printf("[>] ");
		while(!feof(f)) {
			char c=getc(f);
			sprintf(query, "%s%c", query,
				(char)tolower((unsigned char)c));
			if(c=='\n' && !begin)
				printf("[.] ");
			else if(c==';')
				break;
			begin=0;
		}
		if(!feof(f)) {
			Query *q=query_init(query);
			if(!handler_dispatch(q))
				fprintf(stderr, "[-]Bad Query!\n");
			query_deinit(q);
		} else {
			printf("Exit!\n");
			break;
		}
		explicit_bzero(query, sizeof(char)*512);
	}
	free(query);
}

uint8_t main(uint8_t argc, int8_t **argv)
{
	if(argc!=2) {
		fprintf(stderr,
			"[-] Usage: bin/pushdb.out <ip_fname>{- or path}\n");
		_exit(-1);
	}
	FILE *f=NULL;
	if(!strcmp(argv[1], "-"))
		f=stdin;
	else
		f=fopen(argv[1], "r");
	if(f==NULL) {
		fprintf(stderr, "[-]Error in opening the file %s\n", argv[1]);
		_exit(-1);
	}
	init_loop(f);
}
