
#ifndef IN_MG_CONV_FP_H_ 
#define IN_MG_CONV_FP_H_

#pragma once
#include "types.hpp"

constexpr float r_coeff = 0.299f;
constexpr float g_coeff = 0.587f;
constexpr float b_coeff = 0.114f;

constexpr int SH = 8;
constexpr int mult_factor = 1 << SH;
    
constexpr uint8_t WR = (uint8_t)(r_coeff * mult_factor ) ; 
constexpr uint8_t WG = (uint8_t) (g_coeff * mult_factor );
constexpr uint8_t WB =  (uint8_t)(b_coeff *mult_factor ) ;



namespace ref {
bool  Image_conv_fp (Image <uint8_t,ImageType::RGB> & Input , 
                 Image <uint8_t, ImageType::GRAY> & Output); 
}




#endif