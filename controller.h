#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for sleep() */
#include "include/portaudio.h"
#include <math.h>

#include "randq/randq.h"

#define VOLUME 300
#define SAMPLE_RATE 44100
#define TABLE_SIZE SAMPLE_RATE
#define FRAMES_PER_BUFFER 256

struct randomValue {
  double white[TABLE_SIZE];
  int next;
} TestData;

/* callback function prototype */
void init_port_audio(PaStreamParameters *outputParameters);
void terminate_paudio();
void startAudio(PaStream **stream, PaStreamParameters *outputParameters, struct randomValue *data);
void stopAudio(PaStream **stream );
void error(PaError err);
