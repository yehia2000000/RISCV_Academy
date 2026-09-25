#include <tuple>
#include "gtest_lite.hpp"

#include "riscv_cv.hpp" 
#include "reference_cv.hpp"
#include "test_utils.hpp" 


class ImageConvTest : public ::testing::TestWithParam< const char *>
{
    
};
TEST_P(ImageConvTest, TEST_CASE_1)
{  
     const char * path_test  = GetParam();
    
    Image <uint8_t, ImageType::RGB> Input; 
    Input.Read(path_test);
    Image <uint8_t, ImageType::GRAY> Output_sc (Input.GetWidth(),Input.GetHeight())  ;
    Image <uint8_t, ImageType::GRAY> Output_vec (Input.GetWidth(),Input.GetHeight())  ;

    ref::Image_conv_fp(Input, Output_sc);
    vec::image_conv_rvv(Input , Output_vec);

    ExpectImagesEqual(Output_sc, Output_vec);

}

INSTANTIATE_TEST_SUITE_P(ImageSizesAndKernels, ImageConvTest,
    ::testing::Values(
        "sample_640×426.ppm"
    )
);