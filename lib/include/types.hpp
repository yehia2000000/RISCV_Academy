#pragma once


enum class OverFlowPolicy
{
    SATURATE,
    WRAP,
};

enum class FilterSize {

    KernelSize3x3 = 3 , 
    KernelSize5x5 = 5 ,
    KernelSize7x7 = 7 ,
    KernelSize9x9 = 9 ,
    KernelSize11x11 = 11 ,
};


enum class BorderType {
    NO_BORDER,
    REPLICATE, 
    CONSTANT , 
    MIRROR 
};
