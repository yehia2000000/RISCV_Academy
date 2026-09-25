
#ifndef IN_MG_CONV_FP_H_ 
#define IN_MG_CONV_FP_H_

#pragma once
#include "types.hpp"

constexpr uint8_t WR = (uint8_t)(0.299f * 256) ; 
constexpr uint8_t WG = (uint8_t) (0.587f * 256);
constexpr uint8_t WB =  (uint8_t)(0.114f *256) ;



namespace ref {
bool  Image_conv_fp (Image <uint8_t,ImageType::RGB> & Input , 
                 Image <uint8_t, ImageType::GRAY> & Output); 
}




#endif