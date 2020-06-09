#include<ctype.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"query.h"
#include"handler.h"
#include"cargparse/cargparse.h"
#include"clogger/clogger.h"

Logger *logger;

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
	char query[512];
	fgets(query, sizeof(char)*512, f);
	Query *q=query_init(query);
	if(!handler_dispatch(q)) {
		logger_msg(logger, LOG_ERR, "Bad Query");
		goto exit;
	}

exit:
	query_deinit(q);
}

struct arg *manage_args(int argc, char **argv)
{

	struct arg *args=init_lib();

	add_argument(args, "-f", "--out_file", "outf",
			"The Log output file, - for stdout", 1);
	add_argument(args, "-i", "--in_file", "inf",
			"The Input file, - for stdin", 1);
	add_argument(args, "-v", "--verb", "verbosity",
			"The log output verbosity, 0, 1 or 2", 1);
	add_argument(args, "-s", "--single", "single",
			"One command execution mode, single mode", 0);

	if(argc<7 || argc>9) {
		show_help(args);
		_exit(-1);
	}

	parse_args(args, argc, argv);

	return args;
}

Logger *logger_setup(struct arg *args)
{
	char *path=find_arg_val(args, "outf");
	int lvl=strtol(find_arg_val(args, "verbosity"), NULL, 10);

	Logger *log=logger_init(path, (LOG_LVL)lvl);

	return log;
}

int main(int argc, char **argv)
{
	struct arg *args=manage_args(argc, argv);
	logger=logger_setup(args);
	int exec_type=strtol(find_arg_val(args, "single"), NULL, 10);
	FILE *inf=NULL;
	char *inf_path=find_arg_val(args, "inf");
	if(!strcmp("-", inf_path)) {
		inf=stdin;
	} else if((inf=fopen(inf_path, "r"))==NULL) {
		fprintf(stderr, "[-]Error in opening input file!\n");
		_exit(-1);
	}

	if(exec_type)
		single_mode(inf);
	else
		multi_mode(inf);

	logger_deinit(logger);
	clean(args);
}
