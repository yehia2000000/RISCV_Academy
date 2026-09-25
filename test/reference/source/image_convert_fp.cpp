#include "image_convert_fp.hpp"
#include <cstdint>
#include <cstddef>

namespace {
constexpr uint32_t SH = 8;   // Q8: WR+WG+WB == 256
}

bool ref::Image_conv_fp(Image<uint8_t, ImageType::RGB>&  Input,
                        Image<uint8_t, ImageType::GRAY>& Output)
{
    if (Input.GetPtr(0, 0) == nullptr)
        return false;

    const size_t size_image = Input.Getsize();   // pixel count

    for (size_t i = 0; i < size_image; i++) {
        const uint32_t acc = WR * Input.GetPixel_index(3*i + 0)
                           + WG * Input.GetPixel_index(3*i + 1)
                           + WB * Input.GetPixel_index(3*i + 2);
        const uint8_t gray = (uint8_t)((acc + (1u << (SH - 1))) >> SH);
        Output.SetPixel_index(i, gray);
    }
    return true;
}
