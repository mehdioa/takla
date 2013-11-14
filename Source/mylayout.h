#ifndef LAYOUT_H
#define LAYOUT_H
#include <QWidget>
#include <QList>
//#include <QChar>
//#include <QTextEdit>
//#include <QString>
//class QList;
class QChar;
class QTextEdit;
class QString;

enum Finger{Thumb = 0, Pinky = 1, Ring = 2, Middle = 3, Index = 4};
enum Row{Bottom = -1, Home = 0, Top = 1};
enum Hand{Left = -1, Right = 1};
struct Key{
	QChar character;
	int row;
	int hand;
	int finger;
	int parallelMove;
	int needsShift;
};

class Layout : public QWidget
{
	Q_OBJECT
private:
	int fingerHits [11];//fingerHits[0] is the total hits
	double fingerEfforts[11];//fingerEfforts[0] is the total effort.

	Row currentLeftHandRow;
	Row currentRightHandRow;
	Finger currenrLeftFinger;
	Finger currenrRightFinger;
	QList<Key> keyboard;
	QString name;
	QString alphabet;


	void processWord(QString str);
	bool consistsOfAlphabetOnly(QString str);

public:
	Layout(QString layoutFileName);
	void getName();
	void procesText(QTextEdit *text);
	double *getDistances(double *distanceWeights);
	double *getEfforts(double *effortWeights);
};

#endif // LAYOUT_H
