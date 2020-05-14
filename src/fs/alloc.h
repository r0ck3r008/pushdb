#ifndef FS_ALLOC_H
#define FS_ALLOC_H

#include<stdint.h>

#include"record.h"

Record *fs_record_alloc();
int8_t *fs_char_alloc(int8_t *, uint16_t);

#endif
