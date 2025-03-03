#include <Arduino.h>
#include <math.h>

class MotionController {
private:
    float Kp;  // Proportional gain for angle correction
    float Kd;  // Derivative gain for smooth transitions
    float speedReductionFactor; // Factor for reducing speed on sharp turns

    float prevAng;

public:
    MotionController(float kp = 1.0, float kd = 0.2, float speedFactor = 0.05)
        : Kp(kp), Kd(kd), speedReductionFactor(speedFactor), prevAng(90.0) {}

    float computeAdjustedAngle(int ang) {
        float deviationFromForward = ang - 90.0;
        float angleChange = ang - prevAng;

        float adjustedAngle;


        adjustedAngle = ang - (Kd * angleChange) - (Kp * deviationFromForward);


        prevAng = ang;
        return constrain(adjustedAngle, 0.0, 180.0); // Keep within bounds
    }

    float adjustSpeedForTurn(float spd, int ang) {
        float deviationFromForward = abs(ang - 90.0);
        spd *= expf(-deviationFromForward * speedReductionFactor);
        return spd;
    }

    struct AdjustedValues {
        int ang;
        float spd;
    };

    AdjustedValues getAdjustedValues(int ang, float spd) {
        int adjustedAngle = (int)computeAdjustedAngle(ang);
        float adjustedSpeed = adjustSpeedForTurn(spd, adjustedAngle);
        return {adjustedAngle, adjustedSpeed};
    }
};

