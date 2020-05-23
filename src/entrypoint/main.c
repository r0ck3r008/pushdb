#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"db/query.h"

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
}
