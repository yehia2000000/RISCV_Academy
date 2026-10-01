#include "image_convert.hpp"

bool  ref::Image_conv (Image <uint8_t,ImageType::RGB> & Input , 
                 Image <uint8_t, ImageType::GRAY> & Output){

bool LocalErrorState = true ; 
int size_image  =  Input.Getsize() ; 

if  (Input.GetPtr(0,0) != nullptr){
for (size_t i =0 ; i <size_image ; i++){
    const uint32_t acc = 0.299f * Input.GetPixel_index(3*i + 0)
                           + 0.587f * Input.GetPixel_index(3*i + 1)
                           + 0.114f * Input.GetPixel_index(3*i + 2);
    uint8_t Gray = (uint8_t)(acc + 0.5f);
    Output.SetPixel_index(i,Gray) ;
}
}
else {
LocalErrorState = false ; 
}

return LocalErrorState ; 

}

