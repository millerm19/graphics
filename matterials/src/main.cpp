
#include "core/rtweekend.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION


#include "core/camera.h"
#include "objects/hittable_list.h"
#include "helper/obj_loader.h"
#include "objects/sphere.h"

#include "outputting/window.h"

int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.4, 0.4, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.2);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.8);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    //world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_right));

    load_obj("assets/models/plumbob.obj", world, material_left, point3(2, 0, -3));
    load_obj("assets/models/plumbob.obj", world, material_right, point3(-2, 0, -3), 1.5);

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 2;
    cam.max_depth = 16;
    
    cam.vfov = 90;
    cam.lookfrom = point3(-2,2,1);
    cam.lookat   = point3(0,0,-1);
    cam.vup      = vec3(0,1,0);

    //pixel_buffer buffer = cam.render(world);
    //buffer.save_to_image("render.png");

    window win(cam, world);

    if(!win.initialize()) {
        return 1;
    }

    win.run();

    return 0;
}