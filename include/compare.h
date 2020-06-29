#ifndef COMPARE_H
#define COMPARE_H

#include"record.h"
#include"cnf.h"

// Returns -1, 1 if rejected or accepted respectively
int compare_l(Cnf *, Record *);
// Returns -1, 0, 1 if left is less than, equal to or greater than right,
// respectively
int compare_lr(Cnf *, Record *, Record *);

#endif
