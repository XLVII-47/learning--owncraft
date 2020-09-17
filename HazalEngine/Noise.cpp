

#include "Noise.h"
#include "glm.hpp"
#include "gtc/noise.hpp"

int Noise::maxHeight = 150;
float Noise::smooth = 0.01f;
int Noise::octaves = 4;
float Noise::persistance = 0.5f;

float Noise::Lerp(float a, float b, float t) {
	return (1.0 - t)*a + b * t;
}

float Noise::inverseLerp(float a, float b, float v) {
	return (v - a) / (b - a);
}

float Noise::reMap(float imin, float imax, float omin, float omax, float v) {
	return Lerp(omin, omax, inverseLerp(imin, imax, v));
}

int Noise::generateHeight(float x, float z) {
	float height = reMap(0, maxHeight, 0, 1, FBM(x*smooth, z*smooth, octaves, persistance));
	return (int)height;
}

float Noise::FBM(float x, float z, int oct, float pers) {
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0;
	for (int i = 0; i < oct; i++) {
		total += glm::perlin(glm::vec2(x*frequency, z*frequency))*amplitude ;
		maxValue += amplitude;
		amplitude *= pers;
		frequency *= 2;
	}

	return total ;
}

double Noise::findNoise1(int n)
{
	n += 123445454;
	n = (n << 13) ^ n;
	auto nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff; //what even?
	return 1.0 - ((double)nn / 1073741824.0); //what even? (part 2)
}

double Noise::findNoise2(double x, double z)
{
	return findNoise1(x + z * 57);
}


double Noise::noise(double x, double z)
{
	auto floorX = (double)((int)x); //This is kinda a cheap way to floor a double integer.
	auto floorZ = (double)((int)z);

	auto    s = 0.0,
		t = 0.0,
		u = 0.0,
		v = 0.0;//Integer declaration

	s = findNoise2(floorX, floorZ);
	t = findNoise2(floorX + 1, floorZ);
	u = findNoise2(floorX, floorZ + 1);//Get the surrounding values to calculate the transition.
	v = findNoise2(floorX + 1, floorZ + 1);

	auto rec1 = Lerp(s, t, x - floorX);//Interpolate between the values.
	auto rec2 = Lerp(u, v, x - floorX);//Here we use x-floorX, to get 1st dimension. Don't mind the x-floorX thingie, it's part of the cosine formula.
	auto rec3 = Lerp(rec1, rec2, z - floorZ);//Here we use y-floorZ, to get the 2nd dimension.
	return rec3;
}