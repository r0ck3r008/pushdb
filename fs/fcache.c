#include<stdio.h>
#include<string.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#include"fcache.h"
#include"defs.h"
#include"clogger/clogger.h"

extern Logger *logger;

int fcache_getnpgs(FCache *fcache, int fd)
{
	struct stat buf;
	if(fstat(fd, &buf)<0) {
		logger_msg(logger, LOG_ERR,
			"FCACHE: Fstat: %s", strerror(errno));
		_exit(-1);
	}

	fcache->tot_pgs=(int)(buf.st_size/PAGE_SIZE);

	return fcache->tot_pgs;
}

