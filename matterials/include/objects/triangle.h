#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "objects/hittable.h"

class triangle : public hittable {
public:
    triangle(const point3& v0, const point3& v1, const point3& v2, shared_ptr<material> mat)
        : v0(v0), v1(v1), v2(v2), mat(mat) {}

    // Main hit function
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

        float t;

        // Check intersection with plane
        if (!intersect_plane(r, t))
            return false;

        // Check ray bounds
        if (!ray_t.surrounds(t))
            return false;

        // Calculate intersection point
        point3 p = r.at(t);

        // Check whether point is inside triangle
        if (!inside_triangle(p))
            return false;

        // Record successful hit
        rec.t = t;
        rec.p = p;
        rec.set_face_normal(r, get_normal());
        rec.mat = mat;

        return true;
    }

private:
    point3 v0;
    point3 v1;
    point3 v2;
    shared_ptr<material> mat;

    // Calculate unit normal
    vec3 get_normal() const {
        vec3 edge0 = v1 - v0;
        vec3 edge1 = v2 - v0;

        return unit_vector(cross(edge0, edge1));
    }

    // Calculate ray-plane intersection
    bool intersect_plane(const ray& r, float& t) const {
        vec3 normal = get_normal();

        float denom = dot(r.direction(), normal);

        // Ray parallel to plane
        if (fabs(denom) < 1e-8)
            return false;

        t = dot(v0 - r.origin(), normal) / denom;

        return true;
    }

    // Check whether point is inside triangle
    bool inside_triangle(const point3& p) const {

        // Edge v0 -> v1
        vec3 cp0 = cross(v1 - v0, p - v0);
        vec3 cp0_ref = cross(v1 - v0, v2 - v0);

        if (dot(cp0, cp0_ref) < 0)
            return false;

        // Edge v1 -> v2
        vec3 cp1 = cross(v2 - v1, p - v1);
        vec3 cp1_ref = cross(v2 - v1, v0 - v1);

        if (dot(cp1, cp1_ref) < 0)
            return false;

        // Edge v2 -> v0
        vec3 cp2 = cross(v0 - v2, p - v2);
        vec3 cp2_ref = cross(v0 - v2, v1 - v2);

        if (dot(cp2, cp2_ref) < 0)
            return false;

        return true;
    }
};

#endif