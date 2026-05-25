#ifndef __RT_PERTURBED_PATTERN_HPP__
#define __RT_PERTURBED_PATTERN_HPP__

#include "rtPattern.hpp"
#include "rtTuple.hpp"

class FastNoiseLite;

namespace rt {


    class PerturbedPattern : public Pattern {
    public:
        PerturbedPattern(const std::shared_ptr<Pattern>& sub_pattern, float perturbation_scale = 0.2f);
        ~PerturbedPattern() override;

        Color pattern_at(const Point& p) const final override;

    private:
        std::shared_ptr<Pattern> m_sub_pattern;
        std::unique_ptr<FastNoiseLite> m_noise;
        float m_perturbation_scale = 0.0f;

        Point perturb(const Point& p) const;
    };
}

#endif
