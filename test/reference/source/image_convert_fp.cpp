#include "image_convert_fp.hpp"
#include <cstdint>
#include <cstddef>


bool ref::Image_conv_fp(Image<uint8_t, ImageType::RGB>&  Input,
                        Image<uint8_t, ImageType::GRAY>& Output)
{
    if (Input.GetPtr(0, 0) == nullptr)
        return false;

    const size_t size_image = Input.Getsize();   // pixel count
    constexpr uint32_t half_fp = 1u << (SH - 1);

    for (size_t i = 0; i < size_image; i++) {
        const uint32_t acc = WR * Input.GetPixel_index(3*i + 0)
                           + WG * Input.GetPixel_index(3*i + 1)
                           + WB * Input.GetPixel_index(3*i + 2);
        const uint8_t gray = (uint8_t)((acc + half_fp) >> SH);
        Output.SetPixel_index(i, gray);
    }
    return true;
}
