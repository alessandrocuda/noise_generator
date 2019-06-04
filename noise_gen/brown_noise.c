//compile gcc -o white_noise white_noise.c include/libportaudio.a -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio -lpthread
/**
 * Copyright (c) 2019 Alessandro Cudazzo
 *
 * white_noise is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `LICENCE` file for details.
 */
#include <signal.h>

#include "noise_controller/noise_controller.h"

#define VERSION 0.9.0
#define KEEP_RUNNING 1

int noise_type;

void 
killHandler(int dummy) {
	terminate_paudio();
	printf("\nBye Bye and thanks for all the fish.\n");
	exit(0);
}

int 
main(int argc, char const *argv[]){
	printf("Start white noise main process:\n");
	/* INIT */
 	signal(SIGINT, killHandler);

	PaStream *stream = NULL;
	PaStreamParameters outputParameters;

	init_noise_controller(&outputParameters,BROWN_NOISE_TYPE);
	printf("Hit ENTER to start/pause the whitenoise.\n");
	printf("Hit ctrl+c to stop the program.\n");

	while (KEEP_RUNNING)
	{
		getchar();
		startAudio(&stream, &outputParameters);
		/* Play white noise */
		getchar();
		stopAudio(&stream);
	}

    /* Terminate audio stream */

	return 0;
}
