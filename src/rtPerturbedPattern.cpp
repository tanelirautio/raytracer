#include "rtPerturbedPattern.hpp"
#include "FastNoiseLite.h"

#include <stdexcept>

namespace rt {

    PerturbedPattern::PerturbedPattern(const std::shared_ptr<Pattern>& sub_pattern, float perturbation_scale)
        : Pattern(Type::PERTURBED),
          m_sub_pattern(sub_pattern),
          m_noise(std::make_unique<FastNoiseLite>()),
          m_perturbation_scale(perturbation_scale)
    {
        if (!m_sub_pattern) {
            throw std::invalid_argument("PerturbedPattern requires a sub-pattern");
        }

        m_noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        m_noise->SetFrequency(10.f);
    }

    PerturbedPattern::~PerturbedPattern() = default;

    Point PerturbedPattern::perturb(const Point& p) const {
        float jitter_x = m_noise->GetNoise(p.x, p.y, p.z) * m_perturbation_scale;
        float jitter_y = m_noise->GetNoise(p.y, p.z, p.x) * m_perturbation_scale;
        float jitter_z = m_noise->GetNoise(p.z, p.x, p.y) * m_perturbation_scale;

        return Point(p.x + jitter_x, p.y + jitter_y, p.z + jitter_z);
    }

    Color PerturbedPattern::pattern_at(const Point& p) const {
        Point perturbed_point = perturb(p);
        Point sub_pattern_point = inverse(m_sub_pattern->transform()).value() * perturbed_point;

        return m_sub_pattern->pattern_at(sub_pattern_point);
    }

}
