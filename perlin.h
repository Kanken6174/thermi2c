#ifndef PERLIN_H
#define PERLIN_H

#include <QObject>
#include <math.h>
#include <QVector>

class Perlin
{
public:
    Perlin();
    float interpolate(float a, float b, float x) {
        float ft = x * 3.1415927;
        float f = (1 - cos(ft)) * 0.5;
        return a * (1 - f) + b * f;
    }
    float noise(int x, int y, float t, int seed) {
        int n = x + y * 57 + int(t) * 131 + seed;
        n = (n << 13) ^ n;
        return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    }

    float perlinNoise(float x, float y, float t, int seed) {
        int wholePartX = (int)x;
        float fractionalPartX = x - wholePartX;

        int wholePartY = (int)y;
        float fractionalPartY = y - wholePartY;

        float v1 = noise(wholePartX, wholePartY, t, seed);
        float v2 = noise(wholePartX + 1, wholePartY, t, seed);
        float v3 = noise(wholePartX, wholePartY + 1, t, seed);
        float v4 = noise(wholePartX + 1, wholePartY + 1, t, seed);

        float i1 = interpolate(v1, v2, fractionalPartX);
        float i2 = interpolate(v3, v4, fractionalPartX);

        return interpolate(i1, i2, fractionalPartY);
    }
    void fillWithPerlinNoise(QVector<float>& vector, int width, int height, int seed) {
        fprintf(stderr, "creating noise..\n");
        float t = 0.0f;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float noise = perlinNoise(x / (float)width, y / (float)height, t, seed);
                vector[(y * width + x)] = noise;
            }
            t += 0.01f; // flow speed variable
        }
    }
};

#endif // PERLIN_H
