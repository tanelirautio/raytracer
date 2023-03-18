#include "rtPerlinPattern.hpp"
#include "rtUtil.hpp"
#include "rtDefs.hpp"
#include "rtUtil.hpp"
#include <array>
#include <random>

namespace rt {
    PerlinPattern::PerlinPattern(const Color& a, const Color& b, i32 octaves, f32 persistence)
        : Pattern(Type::PERLIN), m_a(a), m_b(b), m_octaves(octaves), m_persistence(persistence)
    {
    }

    Color PerlinPattern::pattern_at(const Point& p) const {
        f32 noise_value = perlin_noise(p);
        return m_a + (m_b - m_a) * noise_value;
    }

    f32 PerlinPattern::perlin_noise(const Point& p) const {
        f32 total = 0.0f;
        f32 frequency = 1.0f;
        f32 amplitude = 1.0f;
        f32 max_value = 0.0f;

        for (i32 i = 0; i < m_octaves; ++i) {
            total += amplitude * noise(p * frequency);
            max_value += amplitude;
            amplitude *= m_persistence;
            frequency *= 2.0f;
        }

        return total / max_value;
    }

    Vector PerlinPattern::random_unit_vector() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<f32> dist(-1.0, 1.0);

        Vector v;
        do {
            v = Vector(dist(gen), dist(gen), dist(gen));
        } while (std::powf(v.magnitude(), 2) >= 1);

        return v.normalize();
    }

    // 3D Perlin noise function
    float PerlinPattern::noise(const Vector& p) const {
        int xi = (int)floor(p.x);
        int yi = (int)floor(p.y);
        int zi = (int)floor(p.z);
        float xf = p.x - xi;
        float yf = p.y - yi;
        float zf = p.z - zi;

        // Generate random gradients for each lattice point
        Vector gradients[2][2][2];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    gradients[i][j][k] = Vector(random_unit_vector());
                }
            }
        }

        float u, v, w;
        float c[2][2][2];
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    Vector weight_v(xf - i, yf - j, zf - k);
                    c[i][j][k] = gradients[i][j][k].dot(weight_v);
                }
            }
        }

        u = fade(xf);
        v = fade(yf);
        w = fade(zf);
        float x1, x2, y1, y2;
        x1 = lerp(c[0][0][0], c[1][0][0], u);
        x2 = lerp(c[0][1][0], c[1][1][0], u);
        y1 = lerp(x1, x2, v);
        x1 = lerp(c[0][0][1], c[1][0][1], u);
        x2 = lerp(c[0][1][1], c[1][1][1], u);
        y2 = lerp(x1, x2, v);

        return lerp(y1, y2, w);
    }

    // Computes a dot product between a randomly chosen gradient vector and the input position(x, y, z).
    // The hash value is used to select a gradient vector from an array of precomputed vectors.
    // The implementation uses bit masking and conditional statements to choose the appropriate components of 
    // the gradient vector based on the hash value. 
    f32 PerlinPattern::grad(i32 hash, f32 x, f32 y, f32 z) const {
        i32 h = hash & 15;
        f32 u = h < 8 ? x : y;
        f32 v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    // Based on the common fade function used in Perlin noise generation, 
    // which maps a value t between 0 and 1 to a smooth curve that starts and ends at 0,
    // and has a slope of 1 at the midpoint (t=0.5).
    inline f32 PerlinPattern::fade(f32 t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }
}