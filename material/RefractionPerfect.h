//
// Created by Sergio on 26/11/2019.
//

#ifndef COMPUTERGRAPHICS_REFRACTIONPERFECT_H
#define COMPUTERGRAPHICS_REFRACTIONPERFECT_H

#include <math.h>
#include <algorithm>
#include "Material.h"
#include "../geometry/Ray.h"


class RefractionPerfect : public Material{
private:
    RGB Kr;
public:
    RefractionPerfect(const RGB& color) : Kr(color){
        this->set_material(material_type::REFRACTION);
    }

    RGB get_emision() override {
        return RGB();
    }

    RGB get_BRDF(const Ray& in_ray, const Vector& normal, Ray& out_ray){
        return Kr;
    }

    RGB get_outgoing_ray(const Ray &in_ray, const Vector &collision_normal, const Vector &collision_point, Ray &out_ray,
                         float rr) override {
        return RGB();
    }

    RGB get_BRDF_next_event(const Ray& in_ray, const Vector& normal, const Ray& shadow_ray, const DotLight light,
                            const Vector& collision_point) const override{
        return RGB();
    }

    /**
     * If the ray is refracted, return true and v_out contain the refracted ray.
     * If the ray is not refracted(total internal reflection), return false and v_out contain the reflect ray.
     * For more info visit: https://en.wikipedia.org/wiki/Snell%27s_law
     * @param v_in incident ray NORMALIZED!
     * @param normal_surface normal at surface NORMALIZED!
     * @param n1 index of refraction from the extern material
     * @param n2 index of refraction from the internal material
     * @param v_out ray refracted or reflect
     * @return true if the ray is refracted, false if the ray is reflect
     */
    bool refracted_direction(const Vector& v_in, const Vector& normal_surface, float n1, float n2,
            Vector& v_out){
        float dt = Vector::dot(v_in, normal_surface);   // Angle between in and normal
        float n1_over_n2 = n1 / n2; // Proportion to n1 and n2
        float discriminant = 1.0f - n1_over_n2 * n1_over_n2 * (1 - dt * dt);
        if(discriminant > 0){
            // Return refracted ray
            v_out = n1_over_n2 * (v_in - normal_surface * dt) - normal_surface * sqrtf(discriminant);
            return true;
        }else{
            // Return reflected ray
            v_out = v_in - 2 * Vector::dot(v_in, normal_surface) * normal_surface;
            return false;
        }
    }
};


#endif //COMPUTERGRAPHICS_SPECULARPERFECT_H
