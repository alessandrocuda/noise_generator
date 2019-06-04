#include "noise_controller.h"
#include "../noise_model/noise_model.h"

#define SAMPLE_RATE 44100
#define TABLE_SIZE SAMPLE_RATE
#define FRAMES_PER_BUFFER 256


struct noise_struct {
  double noise[TABLE_SIZE];
  int next;
} data;

int noise_type = 0;

static float get_noise(int type){
  switch (type)
  {
  case WHITE_NOISE_TYPE:
    return get_wnoise();
    break;
  case BROWN_NOISE_TYPE:
    return get_bnoise();
    break;
  default:
    exit(EXIT_FAILURE);
    break;
  }
}


static int paCallback( const void *inputBuffer,
			 void *outputBuffer, unsigned long framesPerBuffer,
			 const PaStreamCallbackTimeInfo* timeInfo,
			 PaStreamCallbackFlags statusFlags, void *userData ){

  struct noise_struct *data = (struct noise_struct*) userData;
  float *out = (float*) outputBuffer;
  float sample;
  int i;
  
  for (i = 0; i < framesPerBuffer; i++) {
    sample = data->noise[data->next++];
    *out++ = sample; /* left */
    *out++ = sample; /* right */
    if (data->next >= TABLE_SIZE){
      data->next -= TABLE_SIZE;
      for (int i = 0; i < TABLE_SIZE; i++) {
		      data->noise[i] = get_noise(noise_type);
	    }
    }
  }
  return paContinue;
}

void 
init_noise_controller(PaStreamParameters *outputParameters, int noise)
{
  /* Initialize PortAudio */
  PaError err = Pa_Initialize();
  if( err != paNoError ) error(err);

  /* Set output stream parameters */
  outputParameters->device = Pa_GetDefaultOutputDevice();
  outputParameters->channelCount = 2;
  outputParameters->sampleFormat = paFloat32;
  outputParameters->suggestedLatency = 
    Pa_GetDeviceInfo( outputParameters->device )->defaultLowOutputLatency;
  outputParameters->hostApiSpecificStreamInfo = NULL;

  noise_type = noise;
  for (int i = 0; i < TABLE_SIZE; i++) {
		data.noise[i] = get_noise(noise_type);
	}
	/* Initialize user data */
	data.next = 0;

}

void startAudio(PaStream **paStream, PaStreamParameters *outputParameters)
{
    /* Open audio stream */
    PaError err = Pa_OpenStream( &*paStream, NULL /* no input */,
             outputParameters,
             SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag, 
             paCallback, &data );

    if (err != paNoError) error(err);
    /* Start audio stream */
    err = Pa_StartStream( *paStream );
    if (err != paNoError) error(err);
}

void stopAudio(PaStream **paStream ){
	/* Stop audio stream */

	  PaError err = Pa_StopStream( *paStream );
    if (err != paNoError) error(err);

    /* Close audio stream */
    err = Pa_CloseStream(*paStream);
    if (err != paNoError) error(err);

}

void terminate_paudio(){
  PaError err = Pa_Terminate();
  if (err != paNoError) error(err);
}

void error(PaError err){
	Pa_Terminate();
  	fprintf( stderr, "An error occured while using the portaudio stream\n" );
  	fprintf( stderr, "Error number: %d\n", err );
  	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
  	exit(0);
}