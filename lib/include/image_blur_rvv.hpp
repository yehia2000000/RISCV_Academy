#ifndef IN_BLUR_RVV_H_ 
#define IN_BLUR_RVV_H_

#pragma once
#include "image.hpp"
#include "types.hpp"
#include <cstdint>

namespace vec {
void blur_rvv(const Image<uint8_t, ImageType::GRAY>& Input,
                   Image<uint8_t, ImageType::GRAY>& Output, int k);
}

#endif