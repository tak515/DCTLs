#ifndef __IDT_SONY_SLOG3_SGAMUT3_H_INCLUDED__
#define __IDT_SONY_SLOG3_SGAMUT3_H_INCLUDED__

//------------------------------------------------------------------------------------
//  S-Gamut 3 To ACES(Primaries0) matrix
//------------------------------------------------------------------------------------
__CONSTANT__ mat3 matrixCoef =
{
	{  0.7529825954f,  0.0217076974f, -0.0094160528f },
	{  0.1433702162f,  1.0153188355f,  0.0033704179f },
	{  0.1036471884f, -0.0370265329f,  1.0060456349f }
};

//------------------------------------------------------------------------------------
//  S-Log 3 to linear
//------------------------------------------------------------------------------------
__DEVICE__ inline float SLog3_to_linear( float SLog )
{
	float out;

	if (SLog >= 171.2102946929f / 1023.0f)
	{
		out = _powf(10.0f, (SLog * 1023.0f - 420.0f) / 261.5f) * (0.18f + 0.01f) - 0.01f;
	}
	else
	{
		out = (SLog * 1023.0f - 95.0f) * 0.01125000f / (171.2102946929f - 95.0f);
	}

	return out;
}

//------------------------------------------------------------------------------------
//  main
//------------------------------------------------------------------------------------
__DEVICE__ inline float3 IDT_Sony_SLog3_SGamut3( float3 SLog3)
{
	
	float3 linear;
	linear.x = SLog3_to_linear( SLog3.x );
	linear.y = SLog3_to_linear( SLog3.y );
	linear.z = SLog3_to_linear( SLog3.z );

	float3 aces = mult_f3_f33( linear, matrixCoef );

	return aces;
}

#endif
