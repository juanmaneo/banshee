#include "runtime.h"

int main(uint32_t core_id, uint32_t core_num) {
    volatile uint32_t *x = (void *)&l1_alloc_base;
    if (core_id == 0) {
        *x = 0;
    }
    for (uint32_t i = 0; i < core_num; i++) {
        pulp_barrier();
        if (i == core_id) {
            *x += 1;
        }
    }
    pulp_barrier();
    return core_id == 0 ? core_num -= *x : 0;
}
