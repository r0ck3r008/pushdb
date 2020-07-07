#ifndef FCACHE_H
#define FCACHE_H

#include"schema.h"
#include"page.h"

typedef struct
{
	// Total synced pages
	int tot_pgs;
	// Total pages, cached + uncached
	int npgs;
	// Total cached pages
	int cache_pgs;
	// Page cache list
	Page *pg_head, *pg_tail;
} FCache;

int fcache_getnpgs(FCache *, int);
int fcache_addpg(FCache *, Page *, int);
Page *fcache_getpg(FCache *, Schema *, int, int);
int fcache_writeback(FCache *, int);
int fcache_syncpg(FCache *, Page *, int);
void fcache_deinit(FCache *);

#endif
