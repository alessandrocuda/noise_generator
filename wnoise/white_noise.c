//compile gcc -o white_noise white_noise.c include/libportaudio.a -framework CoreServices -framework CoreFoundation -framework AudioUnit -framework AudioToolbox -framework CoreAudio -lpthread
#include <signal.h>

#include "controller.h"

#define VERSION 0.8.0
#define KEEP_RUNNING 1

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

	struct randomValue data;

	/* Generate table random values */
	for (int i = 0; i < TABLE_SIZE; i++) {
		data.white[i] = (randq64_double()*2.0 -1.0)/VOLUME;
	}
	/* Initialize user data */
	data.next = 0;
	init_port_audio(&outputParameters);
	printf("Hit ENTER to start/pause the whitenoise.\n");
	printf("Hit ctrl+c to stop the program.\n");

	while (KEEP_RUNNING)
	{
		getchar();
		startAudio(&stream, &outputParameters, &data);
		/* Play white noise */
		getchar();
		stopAudio(&stream);
	}

    /* Terminate audio stream */

	return 0;
}
