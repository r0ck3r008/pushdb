#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

#include"query.h"
#include"handler.h"
#include"cargparse2/cargparse2.h"
#include"clogger/clogger.h"

Logger *logger;
char *tmp_prefix="tmp/";

void multi_mode(FILE *f)
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
				logger_msg(logger, LOG_ERR, "Bad Query!");
			query_deinit(q);
		} else {
			printf("Exit!\n");
			break;
		}
		explicit_bzero(query, sizeof(char)*512);
	}
	free(query);
}

void single_mode(FILE *f)
{
	char query[512], buf[64];
	while(fgets(buf, sizeof(char)*64, f)!=NULL)
		strncat(query, buf, sizeof(char)*64);

	Query *q=query_init(query);
	if(q==NULL)
		_exit(-1);
	if(!handler_dispatch(q)) {
		logger_msg(logger, LOG_ERR, "Bad Query");
		goto exit;
	}

exit:
	query_deinit(q);
}

ArgParse *handle_args(int argc , char **argv)
{
	ArgParse *args=argparse_init();
	char *def_file="-";
	int def_verb=2;
	add_argument(args, "-i", "--ifile",
		"The input file name", "ifile", StrType, 0, def_file);
	add_argument(args, "-o", "--ofile",
		"The outptut file name", "ofile", StrType, 0, def_file);
	add_argument(args, "-v", "--verb",
		"Output verbosity, 0, 1, 2", "verb", IntType, 0, &def_verb);
	add_argument(args, "-s", "--single",
		"Single command execution mode", "single", NoneType, 0, NULL);

	parse_args(args, argc, argv);

	return args;
}

Logger *logger_args(ArgParse *args)
{
	Logger *log=logger_init(argparse_get_char(args, "ofile"),
				(LOG_LVL)argparse_get_int(args, "verb"));

	return log;
}

int main(int argc, char **argv)
{
	ArgParse *args=handle_args(argc, argv);
	logger=logger_args(args);

	FILE *ifile=NULL;
	char *ifile_path=argparse_get_char(args, "ifile");
	if(!strcmp(ifile_path, "-")) {
		ifile=stdin;
	} else {
		if((ifile=fopen(ifile_path, "r"))==NULL) {
			fprintf(stderr, "[-]Error in opening file: %s: %s\n",
				ifile_path, strerror(errno));
			_exit(-1);
		}
	}

	if(argparse_get_int(args, "single"))
		single_mode(ifile);
	else
		multi_mode(ifile);

	clean(args);
	logger_deinit(logger);
}
