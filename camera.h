#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer.h"

#include "hittable.h"

class camera {
    public:
        // Public camera parameters

        double aspect_ratio = 1.0;
        int image_width = 100;

        void set_focal_length(double f) {
            focal_length = f;
        }

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    
                    auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
                    auto ray_direction = pixel_center - center;

                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);

                    //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
                }
    }

    std::clog << "\rDone.                    \n";
        }
    
    private:
        // Private camera parameters

        int image_height;   // render image height
        point3 center;      // camera center
        point3 pixel00_loc; // Location of pixel 0,0
        vec3 pixel_delta_u; // Offset of pixel to the right
        vec3 pixel_delta_v; // Offset of pixel down
        double focal_length = 1.0;

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 0);

            // Viewport dimensions
            //focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the horizontal and vertical vectors for the camera
            auto viewport_u = vec3(viewport_width, 0, 0); // goes from left to right across the top of the viewport
            auto viewport_v = vec3(0, -viewport_height, 0); // goes from top to bottom down the side of the viewport

            // calculate the horizontal and vertical delta vectors from pixel to pixel

            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // calculate the upper left corner of the viewport

            auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;

            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u/2 + pixel_delta_v/2);
        }

        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1, 1, 1));
            }
            
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);

            // blend between 2 values: "blendedValue = (1−𝑎)⋅startValue+𝑎 ⋅ endValue"
            return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.2, 0.6, 0.7);
        }
};

#endif