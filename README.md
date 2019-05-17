# white_noise
White noise generation developed in C.

**repo empty, see why:**

To make a white noise it is necessary to be able to generate a sequence a pseudo-random numbers which are effectively distributed according to the standard uniform distribution.

**NOTE**:
First, and perhaps most important: be very, very suspicious of a 
system-supplied rand(). System-supplied rand()s are almost always 
linear congruential generators that will eventually repeat itself,
with a period.

That's why we need a better pseudo-random numbers generator. The white noise generator will use `randqd.c` a better way to generate a random number. It will use the "Quick and Dirty" Generators, described in "Numerical Recipes in C" Second Edition at page 284, relies on 32-bit arithmetic. 

Currently under development at repo: [randqd](https://github.com/alessandrocuda/randqd)



#BUILD

TBW