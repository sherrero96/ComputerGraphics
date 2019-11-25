#ifndef COMPUTERGRAPHICS_EMITTER_H
#define COMPUTERGRAPHICS_EMITTER_H

#include "Material.h"
#include "../imaging/RGB.h"

/**
 * Represent an object that produce emission of light.
 */
class Emitter : public Material{
    RGB emitter_color;
public:
    Emitter(const RGB &rgb){emitter_color = rgb; set_material(material_type::EMITTER);}

    Emitter() {Emitter(RGB(0,0,0));}

    RGB get_emision(){ return emitter_color;}
    RGB get_BRDF(const Ray& in_ray, Ray& out_ray) override{return RGB();}
    RGB get_outgoing_ray(const Ray& in_ray, const Vector& collision_normal, const Vector& collision_point, Ray& out_ray, float rr) {
        return get_BRDF(in_ray,out_ray);
    }

};

#endif //COMPUTERGRAPHICS_EMITTER_H
