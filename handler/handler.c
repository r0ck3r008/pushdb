#include"ddl.h"
#include"handler.h"

int handler_dispatch(Query *q)
{
	switch(q->qtype) {
	case 0:
		break;
	case 1:
		if(!ddl_create(q))
			return 0;
		break;
	case 2:
		if(!ddl_insert(q))
			return 0;
		break;
	case 3:
		if(!ddl_drop(q))
			return 0;
		break;
	default:
		return 0;
	}

	return 1;
}
