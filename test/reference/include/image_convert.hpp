

#ifndef IN_MG_CONV_H_ 
#define IN_MG_CONV_H_

#pragma once
#include "types.hpp"

namespace ref {
bool  Image_conv (Image <uint8_t,ImageType::RGB> & Input , 
                 Image <uint8_t, ImageType::GRAY> & Output); 
}




#endif