#ifndef HITTABLE_H
#define HITTABLE_H

#include "RTWeekend.h"

class Material;

struct HitRecord
{
    Point3 point;
    Vector3 normal;
    shared_ptr<Material> mat_ptr;
    double t;

    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vector3& outward_normal)
    {
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const = 0;
};

#endif