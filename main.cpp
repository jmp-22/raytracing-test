# include "raytracer.h"
# include "hittable.h"
# include "hittable_list.h"
# include "material.h"
# include "sphere.h"
# include "camera.h"


int main() {

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_blue_plastic = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_red_plastic = make_shared<lambertian>(color(0.8, 0.1, 0.1));
    auto material_metal = make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_orange_metal = make_shared<metal>(color(0.8, 0.4, 0.1));

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_orange_metal));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, material_metal));
    world.add(make_shared<sphere>(point3(0,100.5,-1), 100, material_metal));

    camera cam;

    cam.aspect_ratio = 1.0 / 1.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 10;

    cam.set_anti_aliasing(true);
    cam.set_focal_length(1);
    cam.max_depth = 50;

    cam.render(world);
       
}