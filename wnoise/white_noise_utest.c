#include <stdio.h>
#include <stdint.h>
#include <math.h>

// CMOCKA INCLUDE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// RANDQD LIB
#include "randq/randq.h"

#define MAX_ITER 42000

static void
hello_message()
{
	fputs(" -------------------------------------------------\n", stdout);
	fputs("|              White_noise Unit Test              |\n",stdout);
	fputs(" -------------------------------------------------\n", stdout);
}

static void
randqd_double_interval(void **state)
{
    (void) state;
    uint32_t    start_seed = 589765974UL;
    uint32_t    pos = 0, neg = 0, zero = 0;

    srandqd(start_seed);

    for (size_t i = 0; i < MAX_ITER; ++i) {
        randqd_uint32();
        double rand_num = randqd_double()*2.0 -1.0;
        assert_true(rand_num >= -1 && rand_num < 1);

        if (rand_num < 0.){
            ++pos;
        } else if (rand_num >0.) {
            ++neg;
        } else {
            ++zero;
        }
    }
    assert_true(pos && neg);
    printf("[    -->     Check if randqd generate a uniform distribution of random number in range [-1,1)\n");
    printf("[    -->     positive: %d (%f%%) - negative: %d (%f%%) - zero: %d (%f%%).0\n",
            pos, (double) pos / MAX_ITER,
            neg, (double) neg / MAX_ITER,
            zero, (double) zero / MAX_ITER);

}


int
main(void)
{   
    hello_message();

    const struct CMUnitTest randqd_group[] = {
        cmocka_unit_test(randqd_double_interval),
    };

    return cmocka_run_group_tests(randqd_group, NULL, NULL);
}

