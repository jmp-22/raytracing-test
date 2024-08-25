# include "raytracer.h"
# include "hittable.h"
# include "hittable_list.h"
# include "sphere.h"
# include "camera.h"


int main() {

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 1920;
    cam.samples_per_pixel = 200;

    cam.set_anti_aliasing(true);
    cam.set_focal_length(1);
    cam.max_depth = 50;

    cam.render(world);
       
}