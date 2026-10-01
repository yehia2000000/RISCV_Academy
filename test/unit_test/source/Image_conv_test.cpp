#include <tuple>
#include "gtest_lite.hpp"

#include "riscv_cv.hpp" 
#include "reference_cv.hpp"
#include "test_utils.hpp" 

//because  your function 
static void RandomInitializeRGB(Image<uint8_t, ImageType::RGB>& image,
                                RandomInt<uint8_t>& random)
{
    for (int y = 0; y < image.Height(); y++)
        for (int x = 0; x < image.Width(); x++)
            for (int c = 0; c < 3; c++)          // R, G, B
                image.SetPixel(x, y, random.get(), c);
}

class ImageConvTest : public ::testing::TestWithParam<std::tuple< int  , int >>
{
    
};
TEST_P(ImageConvTest, TEST_CASE_1)
{  
     const auto [width, height] = GetParam();
    
    Image<uint8_t, ImageType::RGB>  Input(width, height);
    Image<uint8_t, ImageType::GRAY> output_reference(width, height);
    Image<uint8_t, ImageType::GRAY> output_vectorized(width, height);

    RandomInt<uint8_t> random(0, 255);
    RandomInitializeRGB(Input,random);

    ref::Image_conv_fp(Input, output_reference);
    vec::image_conv_rvv(Input , output_vectorized);

    ExpectImagesEqual(output_reference, output_vectorized);

}

INSTANTIATE_TEST_SUITE_P(ImageSizes, ImageConvTest,
    ::testing::Combine(
        ::testing::Values(
            1, 7, 31,   // n < VL (when height == 1)
            32,         // exact one vector
            33, 47,     // one vector + tail
            64,         // multiple exact vectors
            65, 95),    // multiple vectors + tail
        ::testing::Values(
            1,          // single row
            13,         // odd height
            22))        // even height
);