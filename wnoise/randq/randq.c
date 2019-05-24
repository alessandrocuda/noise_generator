#include <stdbool.h>

#include "randq.h"

/*
 * Copyright (c) 2019 Alessandro Cudazzo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

// Variable for "quick and dirt" PRNG
static uint32_t rqd_seed = 0UL;

// Variables for "64bit" PRNG
static bool is_seed_init = false;
static uint64_t default_rq64_seed = 1ULL;
static uint64_t u,v,w;


/**
 * Init the First Seed
 *
 * \start_seed      Started seed
 */
void srandqd(uint32_t start_seed)
{
    rqd_seed = start_seed;
}

/**
 * Return a random sample in the range [0, 2^32 - 1].
 * look in  "Numerical Recipes in C" Second Edition 
 * for the numbers explanation
 *
 * \return      Random number between [0, 2^32 - 1]
 */
uint32_t randqd_uint32()
{    
    rqd_seed = (uint32_t) (1664525UL * rqd_seed + 1013904223UL);
    return rqd_seed;
}

/**
 * Return a random number in the range [0, 1)
 *
 * \return      Random number between [0, 1)
 */
double randqd_double()
{
    return randqd_uint32() / (double) (1L << 32);
}

/**
 * Init the First Seed
 *
 * \start_seed      Started seed
 */
void srandq64(uint64_t start_seed)
{
    is_seed_init = true;
    v = 4101842887655102017LL;
    w = 1;
	u = start_seed ^ v; 
    randq64_uint64();
	v = u; 
    randq64_uint64();
	w = v; 
    randq64_uint64();
}

/**
 * Return a random sample in the range [0, 2^64 - 1].
 * look in  "Numerical Recipes in C" Third Edition 
 * for the numbers explanation
 *
 * \return      Random number between [0, 2^64 - 1]
 */
uint64_t randq64_uint64()
{    
    if (!is_seed_init){
        srandq64(default_rq64_seed);
    }
    
	u = u * 2862933555777941757LL + 7046029254386353087LL;
	v ^= v >> 17; 
    v ^= v << 31; 
    v ^= v >> 8;
	w = 4294957665U*(w & 0xffffffff) + (w >> 32);
	uint64_t x = u ^ (u << 21); 
    x ^= x >> 35; 
    x ^= x << 4;
	return (x + v) ^ w;
}

/**
 * Return a random sample in the range [0, 2^32 - 1].
 * look in  "Numerical Recipes in C" Third Edition 
 * for the numbers explanation
 *
 * \return      Random number between [0, 2^32 - 1]
 */
uint32_t randq64_uint32()
{    
    return (uint32_t) randq64_uint64();
}

/**
 * Return a random number in the range [0, 1)
 *
 * \return      Random number between [0, 1)
 */
double randq64_double()
{
    return 5.42101086242752217E-20 * randq64_uint64();
}

