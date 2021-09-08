#include"image_processing.h"
void colorToGreyScale(const std::string& inputFileName, const std::string& outputFileName) {
        rgb8_image_t img;
        read_image(inputFileName, img, jpeg_tag{});

        const rgb8_view_t & mViewer = view(img);
        for (int y = 0; y < mViewer.height(); ++y) {
            rgb8_view_t::x_iterator trIt = mViewer.row_begin(y);
            for (int x = 0; x < mViewer.width(); ++x) {

                int r = get_color(trIt[x], red_t());
                int g = get_color(trIt[x], green_t());
                int b = get_color(trIt[x], blue_t());

                int avg = (r+g+b)/3;

                trIt[x] = static_cast<rgb8_pixel_t>(avg);
            }
        }
        write_view(outputFileName, view(img), jpeg_tag{});
}