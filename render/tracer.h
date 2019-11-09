//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_TRACER_H
#define COMPUTERGRAPHICS_TRACER_H

#include <random>
#include "../imaging/Image.h"
#include "Scene.h"

class tracer {
public:
    static Image ray_tracer(const Scene &scene, int paths_per_pixel);
private:
    static RGB ray_tracer(const Ray &ray, const Scene &scene);
};


#endif //COMPUTERGRAPHICS_TRACER_H