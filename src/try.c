#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "db/schema.h"
#include "fs/file.h"
#include <sys/types.h>
#include "fs/record.h"
Schema *prep_schema()
{
	int8_t *sch_name=strdup("test_name");
	int8_t *fname=strdup("dummy_fname");
	Schema *sch=schema_init(sch_name, fname);
	schema_add_att(sch, "att1", 0, 0);
	schema_add_att(sch, "att2", 0, 1);
	schema_add_att(sch, "att3", 10, 2);

	free(sch_name);
	free(fname);

	return sch;
}
void main () {
    Schema *sch=prep_schema();
	int8_t *delimiter=strdup("|");
    int8_t *rec_str=strdup("1|1.010|Hello");
    Schema *sch2 = prep_schema();
    int8_t *rec_str2=strdup("1|1.010|World");
	Record *rec=record_ser(rec_str, delimiter, sch);
    Record *rec2=record_ser(rec_str2, delimiter, sch2);
    Page *try;
    createPage(try);
    Append(rec,sch,try);
}