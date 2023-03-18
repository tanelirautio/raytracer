#ifndef __RT_PERLIN_PATTERN_HPP__
#define __RT_PERLIN_PATTERN_HPP__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"
#include "rtPattern.hpp"

namespace rt {
    class Shape;
    class Matrix;
    class PerlinPattern : public Pattern {
    public:
        PerlinPattern(const Color& a, const Color& b,
            i32 octaves = 4, f32 persistence = 0.5f);
        Color a() const { return m_a; }
        Color b() const { return m_b; }
        
        i32 octaves() const { return m_octaves; }
        f32 persistence() const { return m_persistence; }

        Color pattern_at(const Point& p) const final override;
    private:
        f32 perlin_noise(const Point& p) const;
        f32 grad(i32 hash, f32 x, f32 y, f32 z) const;
        inline f32 fade(f32 t) const;
        float noise(const Vector& p) const;
        Vector random_unit_vector() const;

        Color m_a;
        Color m_b;
        i32 m_octaves;
        f32 m_persistence;
    };
}

#endif
