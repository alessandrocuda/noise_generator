#include "controller.h"

static int paCallback( const void *inputBuffer,
			 void *outputBuffer, unsigned long framesPerBuffer,
			 const PaStreamCallbackTimeInfo* timeInfo,
			 PaStreamCallbackFlags statusFlags, void *userData ){

  struct randomValue *data = (struct randomValue*) userData;
  float *out = (float*) outputBuffer;
  float sample;
  int i;
  
  for (i = 0; i < framesPerBuffer; i++) {
    sample = data->white[data->next++];
    *out++ = sample; /* left */
    *out++ = sample; /* right */
    if (data->next >= TABLE_SIZE){
      data->next -= TABLE_SIZE;
      for (int i = 0; i < TABLE_SIZE; i++) {
		      data->white[i] = (randq64_double()*2.0 -1.0)/VOLUME;
	    }
    }
  }
  return paContinue;
}

void 
init_port_audio(PaStreamParameters *outputParameters)
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

}

void startAudio(PaStream **paStream, PaStreamParameters *outputParameters, struct randomValue *data)
{
    /* Open audio stream */
    PaError err = Pa_OpenStream( &*paStream, NULL /* no input */,
             outputParameters,
             SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag, 
             paCallback, data );

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