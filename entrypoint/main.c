#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"query.h"
#include"handler.h"

// void init_loop(FILE *f)
// {
// 	char *query=calloc(512, sizeof(char));
// 	while(1) {
// 		int begin=1;
// 		printf("[>] ");
// 		while(!feof(f)) {
// 			char c=getc(f);
// 			sprintf(query, "%s%c", query,
// 				(char)tolower((unsigned char)c));
// 			if(c=='\n' && !begin)
// 				printf("[.] ");
// 			else if(c==';')
// 				break;
// 			begin=0;
// 		}
// 		if(!feof(f)) {
// 			Query *q=query_init(query);
// 			if(!handler_dispatch(q))
// 				fprintf(stderr, "[-]Bad Query!\n");
// 			query_deinit(q);
// 		} else {
// 			printf("Exit!\n");
// 			break;
// 		}
// 		explicit_bzero(query, sizeof(char)*512);
// 	}
// 	free(query);
// }

// uint8_t main(uint8_t argc, int8_t **argv)
// {
// 	if(argc!=2) {
// 		fprintf(stderr,
// 			"[-] Usage: bin/pushdb.out <ip_fname>{- or path}\n");
// 		_exit(-1);
// 	}
// 	FILE *f=NULL;
// 	if(!strcmp(argv[1], "-"))
// 		f=stdin;
// 	else
// 		f=fopen(argv[1], "r");
// 	if(f==NULL) {
// 		fprintf(stderr, "[-]Error in opening the file %s\n", argv[1]);
// 		_exit(-1);
// 	}
// 	init_loop(f);
// }

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "schema.h"
#include "file.h"
#include <sys/types.h>
#include "record.h"
#include <inttypes.h>
Schema *prep_schema()
{
	int8_t *sch_name=strdup("test_name");
	int8_t *fname=strdup("dummy_fname");
	Schema *sch=schema_init(sch_name);
	schema_add_att(sch, "att1", 0, 0);
	schema_add_att(sch, "att2", 0, 1);
	schema_add_att(sch, "att3", 10, 2);

	free(sch_name);
	free(fname);

	return sch;
}
int main () {
    Schema *sch=prep_schema();
	int8_t *delimiter=strdup("|");
    int8_t *rec_str=strdup("1|1.010|Hello");
    Schema *sch2 = prep_schema();
    int8_t *rec_str2=strdup("1|1.010|World");
	Record *rec=record_ser(rec_str, delimiter, sch);
    Record *rec2=record_ser(rec_str2, delimiter, sch2);
	Page *try = createPage();
    Append(rec,sch,try);
	// printf("\n new number of records %d",try->numRecs);
	Append(rec2,sch2,try);
	// printf("\n new number of records %d",try->numRecs);
	//File *ftry = createFile();
	File *ftry=Open("/mnt/d/Naman_Group_Project/project/fs/akshit");
	// Append(rec,sch,try);
	addPage(try,0,ftry,sch);
}
