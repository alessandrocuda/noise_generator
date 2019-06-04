#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for sleep() */
#include "include/portaudio.h"
#include <math.h>

#include "randq/randq.h"

#define WHITE_NOISE_TYPE 1
#define BROWN_NOISE_TYPE 2

/* callback function prototype */
void init_noise_controller(PaStreamParameters *outputParameters, int noise_type);
void terminate_paudio();
void startAudio(PaStream **stream, PaStreamParameters *outputParameters);
void stopAudio(PaStream **stream );
void error(PaError err);
