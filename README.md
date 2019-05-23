# white_noise
White noise generation developed in C.

Whitenoise by definition contains all frequencies at a constant amplitude. 
To generate a white noise it is necessary to be able to generate a sequence a pseudo-random numbers in the range from [-1.0 .. 1.0) which are effectively distributed according to the standard uniform distribution.

**NOTE**:
First, and perhaps most important: be very, very suspicious of a 
system-supplied rand(). System-supplied rand()s are almost always 
linear congruential generators that will eventually repeat itself,
with a period.

That's why we need a better pseudo-random numbers generator. The white noise generator will use `randq.c` a better way to generate a random number. We will use the "Quick and Dirty" Generators, described in "Numerical Recipes in C" Second Edition at page 284, relies on 32-bit arithmetic and developed in `randq.c` through the following functions: `srandqd`, `randqd_uint32` and `randq_double`;



## BUILD

TBW

## Support

Reach out to me at one of the following places!

- Website at <a href="https://alessandrocudazzo.it" target="_blank">Alessandro Cudazzo</a>.
- Twitter at <a href="http://twitter.com/alessandrocuda" target="_blank">`@alessandrocuda`</a>

## License
[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. 

- **[MIT license](LICENSE)**
- Copyright 2019 © <a href="https://alessandrocudazzo.it" target="_blank">Alessandro Cudazzo</a>.