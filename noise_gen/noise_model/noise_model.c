#include "noise_model.h"
/*
 * white noise
 */
#define VOLUME_WN 300

/*
 * Brown Noise
 */
#define VOLUME_BN 30
#define LPF_Beta  0.025
float RawData;
float SmoothData = 0;

float 
get_wnoise(){
    return (randq64_double()*2.0 -1.0)/VOLUME_WN;
}

float 
get_bnoise(){
    RawData = (randq64_double()*2.0 -1.0)/VOLUME_BN;
	SmoothData = SmoothData - (LPF_Beta * (SmoothData - RawData)); // RC Filter
    return SmoothData;
}