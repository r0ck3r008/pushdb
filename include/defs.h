#ifndef DEFS_H
#define DEFS_H

// Max Page size 4096KB
#define PAGE_SIZE  4194304
// Per relation, max pages to cache
#define N_CACHE_PAGES 8

typedef enum DataType
{
	Int, Float, String
} DataType;

#endif
