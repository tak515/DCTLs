#ifndef __ACES_LMT_H_INCLUDED__
#define __ACES_LMT_H_INCLUDED__

// Combined LMT support files

#include "ACES_functions.h"
#include "ACES_Utilities_Color.h"
#include "ACES_Transform_Common.h"
#include "ACES_Tonescales.h"
#include "ACES_RRT_Common.h"
#include "ACES_LMT_Common.h"


__DEVICE__ inline float3 overlay_f3( float3 a, float3 b)
{
const float LUMA_CUT = lin_to_ACEScct( 0.5f); 

float luma = 0.2126f * a.x + 0.7152f * a.y + 0.0722f * a.z;

float3 out;
if (luma < LUMA_CUT) {
out.x = 2.0f * a.x * b.x;
out.y = 2.0f * a.y * b.y;
out.z = 2.0f * a.z * b.z;
} else {
out.x = 1.0f - (2.0f * (1.0f - a.x) * (1.0f - b.x));
out.y = 1.0f - (2.0f * (1.0f - a.y) * (1.0f - b.y));
out.z = 1.0f - (2.0f * (1.0f - a.z) * (1.0f - b.z));
}

return out;
}

__DEVICE__ inline float3 LMT_Bleach_Bypass( float3 aces)
{
aces = ACEScct_to_ACES(aces);

float3 a, b, blend;
a = sat_adjust( aces, 0.9f);
a = mult_f_f3( 2.0f, a);
					  
b = sat_adjust( aces, 0.0f);
b = gamma_adjust_linear( b, 1.2f);

a = ACES_to_ACEScct( a);
b = ACES_to_ACEScct( b);

blend = overlay_f3( a, b);

return blend;
}

#endif