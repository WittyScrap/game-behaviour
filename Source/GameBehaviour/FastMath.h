// Faster maths functions
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi

#include <tgmath.h>

namespace GFastMath
{
    /**
     * Calculates the arctangent of an angle in radians.
     * ~3.5 faster than STD function.
     * 
     * @param x The input value
     * @return The arctan of `x` in radians.
     */
    const __forceinline float __fastcall atan(float x)
    {
        return M_PI_4 * x - x * (fabs(x) - 1) * (0.2447 + 0.0663 * fabs(x));
    }
}