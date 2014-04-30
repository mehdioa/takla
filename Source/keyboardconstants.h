#ifndef KEYBOARDCONSTANTS_H
#define KEYBOARDCONSTANTS_H

enum class KeyboardType{
	ISO,
	ANSI
};

enum class KeyboardShape{
	STANDARD,
	MATRIX
};

class KeyboardConstants
{
public:
	KeyboardConstants(const KeyboardType &kt, const KeyboardShape &ks);

	double rightShiftDistance;
	double leftShiftDistance;
	double horizontalShift [4];


private:
	KeyboardType _type;
	KeyboardShape _shape;

};

#endif // KEYBOARDCONSTANTS_H
