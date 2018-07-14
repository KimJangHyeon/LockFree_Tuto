#include <stdbool.h>
#include "lockfree.h"
bool
compare_and_swap(int* lock, int oldval, int newval) {
	__sync_val_compare_and_swap(lock, oldval, newval);
}

int
test_and_set(int* lock, int newval) {
	__sync_lock_test_and_set(lock, newval);
}
