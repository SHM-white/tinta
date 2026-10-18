#include "touch_pan.h"
#include <cmath>
#include <iostream>
#include <limits>

static int failures = 0;
static void check(bool good, const char* what) {
    if (!good) {
        std::cerr << "FAIL: " << what << "\n";
        ++failures;
    }
}

int main() {
    using tinta_touch::applyPan;
    check(applyPan(500.0f, -75.0f, 5000.0f, 800.0f) == 575.0f,
          "upward finger motion scrolls down by actual displacement");
    check(applyPan(500.0f, 75.0f, 5000.0f, 800.0f) == 425.0f,
          "downward finger motion scrolls up");
    check(applyPan(50.0f, 120.0f, 5000.0f, 800.0f) == 0.0f,
          "top boundary clamps");
    check(applyPan(4150.0f, -250.0f, 5000.0f, 800.0f) == 4200.0f,
          "bottom boundary clamps");
    check(applyPan(500.0f, -100000.0f, 50000.0f, 800.0f) == 740.0f,
          "one anomalous gesture sample cannot jump to EOF");
    check(applyPan(0.0f, -100.0f, 500.0f, 800.0f) == 0.0f,
          "short documents cannot pan");
    float pos = 2500.0f;
    for (int i = 0; i < 10; ++i) pos = applyPan(pos, -12.0f, 20000.0f, 800.0f);
    check(pos == 2620.0f, "ten small gesture events accumulate only 120 pixels");
    check(std::isfinite(applyPan(1.0f,
              std::numeric_limits<float>::quiet_NaN(), 5000.0f, 800.0f)),
          "non-finite sample does not poison scroll position");
    if (failures) std::cerr << failures << " touch-pan tests failed\n";
    return failures ? 1 : 0;
}
