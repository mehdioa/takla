#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
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


class Keyboard : public QObject
{
	Q_OBJECT
public:
	explicit Keyboard(QString layoutFileName, KeyboardConstants *k_c, QObject *parent=0);
	void procesText(QTextEdit *text);

	QString name;
	bool deleteMe;
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
	static const double keysDistance;

	void computeDistances (Key* prevKey, Key* curKey);
	double goToKey (Key* fromKey, Key* toKey);
	double getDistanceToHome(const int row, const int parallelMove);
	void addShiftSpace(Key* key);
	void changeToPercentage(double *ar);

	int pinkyIndex (const int &hand) const {return (hand > 0) ? 9 : 0;}

};

#endif // KEYBOARD_H
