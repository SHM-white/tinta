#pragma once

#include <algorithm>
#include <cmath>

// The page tracks finger displacement, never extrapolated release velocity.
// A fast swipe must not accidentally jump to the end of a long document.
namespace tinta_touch {
constexpr float kMaxStepPixels = 240.0f;

inline float applyPan(float scrollY, float fingerDeltaY, float contentHeight,
                      float viewportHeight) {
    if (!std::isfinite(scrollY) || !std::isfinite(fingerDeltaY) ||
        !std::isfinite(contentHeight) || !std::isfinite(viewportHeight)) {
        return std::max(0.0f, std::isfinite(scrollY) ? scrollY : 0.0f);
    }
    const float maxScroll = std::max(0.0f, contentHeight - viewportHeight);
    const float step = std::clamp(fingerDeltaY, -kMaxStepPixels, kMaxStepPixels);
    return std::clamp(scrollY - step, 0.0f, maxScroll);
}
}  // namespace tinta_touch
