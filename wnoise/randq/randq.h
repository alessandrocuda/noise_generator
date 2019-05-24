/**
 * Copyright (c) 2019 Alessandro Cudazzo
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `LICENCE` file for details.
 */

#ifndef RANDQD_H
#define RANDQD_H

#include <stdint.h>

#define RANDQD_VERSION "2.0"


/*
*********************************************************************
*             A better way to generate a random number              *
*********************************************************************
*
*   PRNG (Pseudo-Random Number Generators):
*   First, and perhaps most important: be very, very suspicious of a 
*   system-supplied rand(). System-supplied rand()s are almost always 
*   linear congruential generators that will eventually repeat itself,
*   with a period.
*   So, never use the built-in generators in the C and C++ languages, 
*   especially rand  and srand. These have no standard implementation 
*   and are often badly flawed.
*   
*   This Library provides two  better way to generate a random number:
*       -   The "suspenders-and-belt,full-body-armor, never-any-doubt"
*           generator  laying on 64bit and respect all the constraints
*           defined in "Numerical Recipes" Third Edition at page 342.
*           The period of the generator is 3.138*10^57.
*           Function are: srandq64, randq64_uint64, randq64_uint32,
*                         and randq64_double;
*
*       -   the "Quick and Dirty" Generators laying on 32bit defined in
*           "Numerical Recipes in C" Second Edition. Use it only in very
*           special cases, where speed is critical and if you don’t need
*           a period longer than 2^32.
*           Function are: srandqd, randqd_uint32 and randq_double;
*
*/

/**
 * Init the First Seed for randqd
 *
 * \start_seed      Started seed
 */
void srandqd(uint32_t start_seed);

/**
 * Returns a random value within the range [0, 2^32 - 1]
 *
 * \return      Random number between [0, 2^32 - 1]
 */
uint32_t randqd_uint32();

/**
 * Returns a random value within the range [0, 1)
 *
 * \return      Random double number between [0, 1)
 */
double randqd_double();

/**
 * Init the First Seed for randq64
 *
 * \start_seed      Started seed
 */
void srandq64(uint64_t start_seed);

/**
 * Returns a random value within the range [0, 2^64 - 1]
 *
 * \return      Random number between [0, 2^64 - 1]
 */
uint64_t randq64_uint64();

/**
 * Returns a random value within the range [0, 2^32 - 1]
 *
 * \return      Random number between [0, 2^32 - 1]
 */
uint32_t randq64_uint32();

/**
 * Returns a random value within the range [0, 1)
 *
 * \return      Random double number between [0, 1)
 */
double randq64_double();

#endif
