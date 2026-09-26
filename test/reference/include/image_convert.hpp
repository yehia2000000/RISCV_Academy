

#ifndef IN_MG_CONV_H_ 
#define IN_MG_CONV_H_

#pragma once
#include "image.hpp"
#include "types.hpp"
#include <cstdint>
namespace ref {
bool  Image_conv (Image <uint8_t,ImageType::RGB> & Input , 
                 Image <uint8_t, ImageType::GRAY> & Output); 
}




#endif