# noise_generator
Noise generator developed in C, allow to play in backgroun White and Brown noise.

 - ## White Noise

    Whitenoise by definition contains all frequencies at a constant amplitude. To generate a white noise it is necessary to be able to generate a sequence a pseudo-random numbers in the range from [-1.0 .. 1.0) which are effectively distributed according to the standard uniform distribution.

    **NOTE**:
    First, and perhaps most important: be very, very suspicious of a 
    system-supplied rand(). System-supplied rand()s are almost always 
    linear congruential generators that will eventually repeat itself,
    with a period.

    That's why we need a better pseudo-random numbers generator. The white noise generator will use `randq.c` a better way to generate a random number. We will use the "Quick and Dirty" Generators, described in "Numerical Recipes in C" Second Edition at page 284, relies on 32-bit arithmetic and developed in `randq.c` through the following functions: `srandqd`, `randqd_uint32` and `randq_double`;

 - ## Brown Noise

    White noise + <a href="https://en.wikipedia.org/wiki/Low-pass_filter#Simple_infinite_impulse_response_filter" target="_blank">digital low-pass filter</a> 

    **Digital Low-pass filter:**

    assume that samples of the input and output are taken at evenly spaced points in time separated by Delta_T time. Let the samples of v_in **(the white noise)** be represented by the sequence (x_1,  x_2, ..., x_n), and let v_out **(brown noise)** be represented by the sequence (y_1, y_2, ..., y_n), which correspond to the same points in time.

    ![ RC ](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e0/1st_Order_Lowpass_Filter_RC.svg/250px-1st_Order_Lowpass_Filter_RC.svg.png)

    ![ low-pass filter](https://wikimedia.org/api/rest_v1/media/math/render/svg/eba443fdddb03e497b347d8684c39b22f5624e34)

    >therefore, to obtain the brown noise sequence it is sufficient to apply this equation to the white noise sequence.

## Stack
- [randq.c](https://github.com/alessandrocuda/randq): a better pseudo-random numbers generator
- [Portaudio](http://www.portaudio.com/): audio I/O library

## System requirements
### Linux Ubuntu/Debian
[//]: # (sudo apt-get install libjack-dev)

```bash
# Requirements for white_noise_utest
sudo apt-get install libcmocka-dev 

# Requirements for portaudio
sudo apt-get install libasound-dev

# Downlod and install portaudo lib
git clone https://git.assembla.com/portaudio.git
cd portaudio
./configure && make
sudo make install
```
### MacOS with Homebrew
```bash
brew install cmocka
brew install portaudio
```

## BUILD
```bash
git clone https://github.com/alessandrocuda/noise_generator
cd noise_generator
make
```
### Run
```bash
# Player
./white_noise           #run white_noise player
./brown_noise           #run brown_noise player

# unit_test
./white_noise_utest     #run unit test for white_noise
```

## TODO
- [x] add Brown Noise
- [ ] add Pink Noise
- [ ] make a noises player with parameter to select the noise


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
