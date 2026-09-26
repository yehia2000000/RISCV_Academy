#pragma once
#include "image.hpp"
#include "types.hpp"
#include <cstdint>
namespace ref 
{
    void Add(const Image<uint8_t>& input1, 
             const Image<uint8_t>& input2, 
                   Image<uint8_t>& output, 
             const OverFlowPolicy overFlowPolicy);
}
