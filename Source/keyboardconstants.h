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
	friend class Keyboard;

	KeyboardConstants(const KeyboardType &kt, const KeyboardShape &ks, const bool &hand);

private:
	KeyboardType _type;
	KeyboardShape _shape;
	bool isRightHanded;
	double rightShiftDistance;
	double leftShiftDistance;
	double horizontalShift [4];
	int (*KeySpec)[3];
	int LayouSize;


	int ISOspec[48][3] =
	{	//{Row,Finger,Move}
		{2,0,-1},
		{2,0,0},
		{2,1,0},
		{2,2,0},
		{2,3,0},
		{2,3,1},
		{2,6,-1},
		{2,6,0},
		{2,7,0},
		{2,8,0},
		{2,9,0},
		{2,9,1},
		{2,9,2},
		{1,0,0},
		{1,1,0},
		{1,2,0},
		{1,3,0},
		{1,3,1},
		{1,6,-1},
		{1,6,0},
		{1,7,0},
		{1,8,0},
		{1,9,0},
		{1,9,1},
		{1,9,2},
		{0,0,0},
		{0,1,0},
		{0,2,0},
		{0,3,0},
		{0,3,1},
		{0,6,-1},
		{0,6,0},
		{0,7,0},
		{0,8,0},
		{0,9,0},
		{0,9,1},
		{0,9,2},
		{-1,0,-1},
		{-1,0,0},
		{-1,1,0},
		{-1,2,0},
		{-1,3,0},
		{-1,3,1},
		{-1,6,-1},
		{-1,6,0},
		{-1,7,0},
		{-1,8,0},
		{-1,9,0}
	};

	int ANSIspec[47][3] =
	{	//{Row,Finger,Move}
		{2,0,-1},
		{2,0,0},
		{2,1,0},
		{2,2,0},
		{2,3,0},
		{2,3,1},
		{2,6,-1},
		{2,6,0},
		{2,7,0},
		{2,8,0},
		{2,9,0},
		{2,9,1},
		{2,9,2},
		{1,0,0},
		{1,1,0},
		{1,2,0},
		{1,3,0},
		{1,3,1},
		{1,6,-1},
		{1,6,0},
		{1,7,0},
		{1,8,0},
		{1,9,0},
		{1,9,1},
		{1,9,2},
		{1,9,3},
		{0,0,0},
		{0,1,0},
		{0,2,0},
		{0,3,0},
		{0,3,1},
		{0,6,-1},
		{0,6,0},
		{0,7,0},
		{0,8,0},
		{0,9,0},
		{0,9,1},
		{-1,0,0},
		{-1,1,0},
		{-1,2,0},
		{-1,3,0},
		{-1,3,1},
		{-1,6,-1},
		{-1,6,0},
		{-1,7,0},
		{-1,8,0},
		{-1,9,0}
	};
};

#endif // KEYBOARDCONSTANTS_H
