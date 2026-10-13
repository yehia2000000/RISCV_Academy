#include "gtest_lite.hpp"

#include <cstdio>
#include <tuple>

#include "riscv_cv.hpp"
#include "reference_cv.hpp"
#include "test_utils.hpp"
#include "image_blur_rvv.hpp"

namespace {

const char* BorderName(BorderType b)
{
    switch (b) {
        case BorderType::NO_BORDER: return "NO_BORDER";
        case BorderType::CONSTANT:  return "CONSTANT";
        case BorderType::REPLICATE: return "REPLICATE";
        case BorderType::MIRROR:    return "MIRROR";
    }
    return "UNKNOWN";
}

constexpr uint8_t kConstVal = 128; 

} // namespace

class BlurTest : public ::testing::TestWithParam<std::tuple<int, int, int, BorderType>>
{
};

TEST_P(BlurTest, VectorizedMatchesReference)
{
    const auto [width, height, ksize, border] = GetParam();

    // print the test parameters
    printf("[ %-7s %16d ]\n", "width:",  width);
    printf("[ %-7s %16d ]\n", "height:", height);
    printf("[ %-7s %16d ]\n", "ksize:",  ksize);
    printf("[ %-7s %16s ]\n", "border:", BorderName(border));

    const int  pad        = ksize / 2;
    const bool valid_only = (border == BorderType::NO_BORDER);

    // NO_BORDER needs the whole kernel inside the image to produce any output.
    if (valid_only && (width < ksize || height < ksize)) {
        printf("[ %-7s %16s ]\n", "skip:", "image < kernel");
        return;
    }

    const int outW = valid_only ? width  - 2 * pad : width;
    const int outH = valid_only ? height - 2 * pad : height;

    Image<uint8_t, ImageType::GRAY> input(width, height);

    Image<uint8_t, ImageType::GRAY> output_reference(outW, outH);
    Image<uint8_t, ImageType::GRAY> output_vectorized(outW, outH);

    RandomInt<uint8_t> random(0, 255);
    random.ImageRandomInitialize(input);

    ref::Blur(input, output_reference, ksize, border, kConstVal);

    if (valid_only) {
        vec::blur_rvv(input, output_vectorized, ksize);
    } else {
        Image<uint8_t, ImageType::GRAY> padded(width + 2 * pad, height + 2 * pad);
        input.MakeBorder(padded, pad, border, kConstVal);
        vec::blur_rvv(padded, output_vectorized, ksize);
    }

    ExpectImagesEqual(output_reference, output_vectorized);
}

// VL = VLEN/SEW = 128/8 = 16 elements per vector; loop is over the output width.
// "tail" = remainder elements after full vector chunks (outW % VL != 0).
// With a border mode outW == width, so the widths below map directly to tail cases.
// With NO_BORDER outW == width - ksize + 1, which shifts them to other tail cases.
INSTANTIATE_TEST_SUITE_P(ImageSizesKernelsBorders, BlurTest,
    ::testing::Combine(
        ::testing::Values(
            7,          // single partial vector (width < VL)
            32,         // multiple exact vectors (strip loop runs twice, no tail)
            33),        // multiple vectors + tail of 1 element (vl = 1)
        ::testing::Values(
            1,          // single row (border modes only; exercises MIRROR len == 1)
            22),        // height > 2 * max ksize, so the ring buffer wraps several times
        ::testing::Values(
            3, 5, 7, 9, 11),
        ::testing::Values(
            BorderType::NO_BORDER, BorderType::CONSTANT,
            BorderType::REPLICATE, BorderType::MIRROR))
    );