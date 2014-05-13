#include "keyboardconstants.h"

KeyboardConstants::KeyboardConstants(const KeyboardType &kt, const KeyboardShape &ks, const bool &hand):
	_type(kt),
	_shape(ks),
	isRightHanded(hand)
{
	if (_type == KeyboardType::ISO) {
		leftShiftDistance = 2*0.019;
		KeySpec = ISOspec;
		LayouSize = 48;
	} else {
		leftShiftDistance = 0.021;
		KeySpec = ANSIspec;
		LayouSize = 47;
	}

	if (_shape == KeyboardShape::STANDARD) {
		rightShiftDistance = 0.034;
		leftShiftDistance = 0.021;
		horizontalShift[0] = 0.009;
		horizontalShift[1] = 0.0;
		horizontalShift[2] = -0.004;
		horizontalShift[3] = -0.014;

	} else {
		rightShiftDistance = 0.038;
		leftShiftDistance = 0.019;
		horizontalShift[0] = 0.0;
		horizontalShift[1] = 0.0;
		horizontalShift[2] = 0.0;
		horizontalShift[3] = 0.0;
	}
}
