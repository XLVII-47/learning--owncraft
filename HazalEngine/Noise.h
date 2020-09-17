#pragma once


class Noise {
public:
	static int maxHeight;
	static float smooth;
	static int octaves;
	static float persistance;

	static float Lerp(float a, float b, float t);
	static float inverseLerp(float a, float b, float v);
	static float reMap(float imin, float imax, float omin, float omax, float v);

	static int generateHeight(float x, float z);
	static float FBM(float x, float z, int oct, float pers);

	static double findNoise1(int n);
	static double findNoise2(double x, double z);
	static double noise(double x, double z);
};