
#include "image_conv_rvv.hpp"
#include <riscv_vector.h>

void vec::image_conv_rvv(Image <uint8_t,ImageType::RGB> & Input , Image <uint8_t, ImageType::GRAY> & Output)
{   int   n = Input.Getsize() ; 

    uint8_t * rgb = Input.GetPtr(0,0); 
    uint8_t * gray = Output.GetPtr(0,0); 
    for (size_t vl; n > 0; n -= vl ,  rgb += 3*vl ,  gray += vl) {
        vl = __riscv_vsetvl_e8m1(n);                                   
        vuint8m1x3_t px = __riscv_vlseg3e8_v_u8m1x3(rgb, vl);          
        vuint8m1_t r = __riscv_vget_v_u8m1x3_u8m1(px, 0);
        vuint8m1_t g = __riscv_vget_v_u8m1x3_u8m1(px, 1);
        vuint8m1_t b = __riscv_vget_v_u8m1x3_u8m1(px, 2);

        vuint16m2_t acc = __riscv_vwmulu_vx_u16m2(r, WRRV, vl);  
        acc = __riscv_vwmaccu_vx_u16m2(acc, WGRV, g, vl);
        acc = __riscv_vwmaccu_vx_u16m2(acc, WBRV, b, vl);
        vuint8m1_t y = __riscv_vnclipu_wx_u8m1(acc, 8, __RISCV_VXRM_RNU, vl); 
        __riscv_vse8_v_u8m1(gray, y, vl); 

    }
}