#include "keyboardconstants.h"

KeyboardConstants::KeyboardConstants(const KeyboardType &kt, const KeyboardShape &ks):
	_type(kt),
	_shape(ks)
{
	if (_type != KeyboardType::ANSI) {
		leftShiftDistance = 0.038;
	} else {
		leftShiftDistance = 0.021;
	}

	if (_shape == KeyboardShape::STANDARD) {
		rightShiftDistance = 0.034;
		leftShiftDistance = 0.021;
		horizontalShift[0] = 0.009;
		horizontalShift[1] = 0.0;
		horizontalShift[2] = -0.004;
		horizontalShift[3] = -0.014;

	} else {
		rightShiftDistance = 0.027;
		leftShiftDistance = 0.027;
		horizontalShift[0] = 0.0;
		horizontalShift[1] = 0.0;
		horizontalShift[2] = 0.0;
		horizontalShift[3] = 0.0;
	}
}
