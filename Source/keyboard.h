#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <QString>
#include <QVector>
#include "keyboardconstants.h"

class QTextEdit;

struct Key{
	QChar character;
	int row;
	int finger;
	int parallelMove;//Minus to left, plus to right
	int needsShift;//0=doesn't need, 1 = needs
    double distanceToHome;//Distance without shift
};


class Keyboard
{

public:
	Keyboard(QString layoutFileName, KeyboardConstants *k_c);
	void procesText(QTextEdit *text);

	QString name;
    double inwardRollingHits [13] = {0.0};
    double outwardRollingHits [13] = {0.0};
    double sameFingerHits [13] = {0.0};
    double handSymmetry [13] = {0.0};
    double sameHandHits [13] = {0.0};
    double hits[13] = {0.0};
    double distances[13] = {0.0};
    double rowJumps[13] = {0.0};

private:
	QVector<Key> keyboard;
	QString alphabet;
	KeyboardConstants *kc;

	void computeDistances (const Key* prevKey, const Key* curKey);
	double goToKey (const Key* fromKey, const Key* toKey);
	double getDistanceToHome(const int row, const int parallelMove);
	void addShiftSpace(const Key* key);
	void changeToPercentage(double (&ar)[13]);
//	double rightShiftDistance = 0.034;//in standard keyboard
//	double leftShiftDistance = 0.021;//in standard and ANSI keyboard
//	double horizontalShift [4] = {0.009, 0.0, -0.004, -0.014};//Horizontal shift of the rows -1, 0, 1, 2 in standard keyboard

	int pinkyIndex (const int hand) {return (hand > 0) ? 9 : 0;}

};

#endif // KEYBOARD_H
