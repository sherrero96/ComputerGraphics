/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include "utils/IOppm.h"
#include "imaging/ToneMapper.h"
#include "render/Scene.h"
#include "render/tracer.h"
#include "utils/Prng.h"
#include "material/RefractionPerfect.h"

#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif

using namespace std;
void pruebas_prng();
int main(){
    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    const int PATHS_PER_PIXEL = 12;
    cout<<"Path tracer: "<<PATHS_PER_PIXEL<<" ppp."<<endl;
    Scene scene;
    scene.load_cornellBox();
    Image image = tracer::ray_tracer(scene, PATHS_PER_PIXEL);    // Create the image
    float max_pixel_value = image.getMaxValue();
    cout<<endl;

    if (max_pixel_value >= 65535) {
        ToneMapper::clamping(image, 65535);
    }
    cout<<"Saving HDR image..."<<endl;
    IOppm::store("../data/ray_tracer_hdr.ppm", image, 10000000);
    cout<<endl;

    cout<<"Tone Mapping image...";
    image.setMaxValue(max_pixel_value);
    //ToneMapper::equalAndClamp(image, 10);
    //ToneMapper::equalization(image);    // Tone mapping
    //ToneMapper::gamma(image, 0.8);
    ToneMapper::clampAndGamma(image, 1000, 0.15); // First clamp to light max value.
    //ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()),0.18, 0.75);
    cout<<"Done!"<<endl;

    cout<<"Saving (8-bit) image...";
    IOppm::store("../data/ray_tracer.ppm", image, 255);
    cout<<"Done!"<<endl;

    /*cout<<"Saving (10-bit) image..."<<endl; // Robert things
    IOppm::store("../data/ray_tracer_10bit.ppm", image, 1023);
    cout<<endl;*/


    /*cout<<"Saving (10-bit) image..."<<endl; // Robert things
    IOppm::store("../data/ray_tracer_10bit.ppm", image, 1023);
    cout<<endl;*/


    // To finish, obtain the timestamp
    finish_time = clock();
    double time = (double(finish_time - init_time) / CLOCKS_PER_SEC);
    if(time >= 60){ // More or equal to 1 minute
        if(time >= 3600){   // More or equal to 1 hour
            cout<<"Finish in: "<< time / 3600 <<" hours."<<endl;
        }else{
            cout<<"Finish in: "<< time / 60 <<" minutes."<<endl;
        }
    }else{
        cout<<"Finish in: "<<time<<" seconds."<<endl;
    }
}