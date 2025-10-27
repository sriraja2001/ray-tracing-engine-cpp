#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

using namespace std;

// Function to determine whether ray r hits a sphere defined by its center and radius
bool hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc = center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), oc);
    double c = dot(oc, oc) - (radius * radius);
    double discrim = (b*b) - (4*a*c); 
    return (discrim >= 0);
}

// Function to return the color intecepted by ray r
color ray_color(const ray &r) {
    if(hit_sphere(point3(0, 0, -1), 0.5, r)) return color(1, 0, 0);

    vec3 unit_direction = unit_vector(r.direction());
    // a is the intensity of blue in the pixel; the below equation rescales the y coordinate that ranges from -1 to 1, to 0 to 1 
    auto a = 0.5*(unit_direction.y() + 1.0); 
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // Image dimension config 
    // The ideal aspect ratio - the original might be different from it when the height and the width are rounded to integers
    double aspect_ratio = 16.0/9.0;     
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // Camera Config
    vec3 camera_center = vec3(0, 0, 0);
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = (static_cast<double>(image_width) / image_height) * viewport_height;

    // Init vectors to aid viewport traversal
    // vu & vv vectors point to limits of the viewport and help with the traversal - especially along y direction since the scanning direction is inverted 
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate pixel-to-pixel distance, the distance in 3D world in the viewport that corresponds to one pixel while rendering
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper-left pixel/corner of the viewport.
    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
    vec3 pixel00_loc = viewport_upper_left + (pixel_delta_u / 2) + (pixel_delta_v) / 2; // Center of pixel 00

    // Rendering the image
    ofstream outputFile("image.ppm");  // Save in current directory

    outputFile << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        clog << "\rScanlines remaining: " << image_height - i << " " << flush;
        for (int j = 0; j < image_width; j++) {
            vec3 pixel_center = pixel00_loc + (pixel_delta_u * j) + (pixel_delta_v * i);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            const color pixelColor = ray_color(r);
            write_color(outputFile, pixelColor);
        }
    }

    clog << "\rFile rendered successfully\n" << flush;
    outputFile.close();

    return 0;
}
