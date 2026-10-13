#include <riscv_vector.h>
#include <cstdint>
#include <cstddef>
#include "image_blur_rvv.hpp"

namespace {

constexpr int div_shift(uint32_t n)
{
    int k = 0;
    while (((1ull << (17 + k)) + n - 1) / n <= 0xFFFF) ++k;
    return k;
}

constexpr uint16_t div_mult(uint32_t n)
{
    return static_cast<uint16_t>(((1ull << (16 + div_shift(n))) + n - 1) / n);
}


template <int K>
inline vuint16m2_t row_sum(const uint8_t* p, size_t vl)
{
    vuint16m2_t s = __riscv_vwaddu_vv_u16m2(__riscv_vle8_v_u8m1(p, vl),__riscv_vle8_v_u8m1(p + 1, vl), vl);
    for (int i = 2; i < K; ++i)
        s = __riscv_vwaddu_wv_u16m2(s, __riscv_vle8_v_u8m1(p + i, vl), vl);
    return s;
}

template <int K>
void blur_box_rvv(const Image<uint8_t, ImageType::GRAY>& Input,
                  Image<uint8_t, ImageType::GRAY>& Output)
{
    constexpr uint32_t N = K * K;
    constexpr uint16_t M  = div_mult(N);
    constexpr int      SH = div_shift(N);

    constexpr size_t kMaxVL = 256;            
    static uint16_t ring[K * kMaxVL];          

    const int W  = Output.Width();
    const int H  = Output.Height();
    const int SS = Input.Width();

    const uint8_t* src = Input.GetPtr(0, 0);
    uint8_t*       dst = Output.GetPtr(0, 0);

    for (int x = 0; x < W; )
    {
        const size_t rem = W - x;
        const size_t vl  = __riscv_vsetvl_e8m1(rem < kMaxVL ? rem : kMaxVL);

     
        vuint16m2_t s = __riscv_vmv_v_x_u16m2(0, vl);
        for (int r = 0; r < K - 1; ++r)
        {
            vuint16m2_t rs = row_sum<K>(src + r * SS + x, vl);
            __riscv_vse16_v_u16m2(ring + r * kMaxVL, rs, vl);
            s = __riscv_vadd_vv_u16m2(s, rs, vl);
        }

        int slot = K - 1;                    
        for (int y = 0; y < H; ++y)
        {
          
            vuint16m2_t rn = row_sum<K>(src + (y + K - 1) * SS + x, vl);
            __riscv_vse16_v_u16m2(ring + slot * kMaxVL, rn, vl);
            s = __riscv_vadd_vv_u16m2(s, rn, vl);

            vuint16m2_t q = __riscv_vmulhu_vx_u16m2(s, M, vl);
            q = __riscv_vsrl_vx_u16m2(q, SH, vl);
            __riscv_vse8_v_u8m1(dst + y * W + x, __riscv_vncvt_x_x_w_u8m1(q, vl), vl);

            slot = (slot + 1 == K) ? 0 : slot + 1;
            s = __riscv_vsub_vv_u16m2(s, __riscv_vle16_v_u16m2(ring + slot * kMaxVL, vl), vl);
        }
        x += vl;
    }
}

} // namespace

void vec::blur_rvv(const Image<uint8_t, ImageType::GRAY>& Input,
                   Image<uint8_t, ImageType::GRAY>& Output, int k)
{
    switch (k)
    {
        case 3:  blur_box_rvv<3>(Input, Output);  break;
        case 5:  blur_box_rvv<5>(Input, Output);  break;
        case 7:  blur_box_rvv<7>(Input, Output);  break;
        case 9:  blur_box_rvv<9>(Input, Output);  break;
        case 11: blur_box_rvv<11>(Input, Output); break;
        default: assert(false && "unsupported kernel size");
    }
}