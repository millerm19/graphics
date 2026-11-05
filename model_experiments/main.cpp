#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "obj_loader.h"
#include "sphere.h"
#include "triangle.h"

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    load_obj("models/plumbob.obj", world, point3(2, 0, -3));
    load_obj("models/plumbob.obj", world, point3(0, 1, -4), 0.5);
    load_obj("models/plumbob.obj", world, point3(-2, 0, -3), 1.5);

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 10;

    cam.render(world);
}