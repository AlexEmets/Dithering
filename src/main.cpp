#include <boost/gil.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace boost::gil;

int up_round(int a, int b) {
    if(a%b == 0) return a/b;
    return a/b + 1;
}
int main() {

    try {
        std::ifstream imageStream("/home/oleksandr/Dithering/assets/original.jpg");

        rgb8_image_t img;
        read_image(imageStream, img, jpeg_tag{});

        const rgb8_view_t & mViewer = view(img);
        for (int y = 0; y < mViewer.height(); ++y)
        {
            rgb8_view_t::x_iterator trIt = mViewer.row_begin(y);
            for (int x = 0; x < mViewer.width(); ++x) {


                int a = 255;
                int r = get_color(trIt[x], red_t());
                int g = get_color(trIt[x], green_t());
                int b = get_color(trIt[x], blue_t());


                int avg = (r+g+b)/3;

                rgb8_pixel_t p ((a<<24) | (avg<<16) | (avg<<8) | avg);

                trIt[x] = p;

            }
        }
        write_view("/home/oleksandr/Dithering/outputs/output_original.jpeg", view(img), jpeg_tag{});
    }catch (std::exception& exc) {
        std::cout << exc.what();
    }

    return EXIT_FAILURE;
}

//g++ -Wall -Wextra -pedantic -pthread -o demo src/main.cpp -ljpeg