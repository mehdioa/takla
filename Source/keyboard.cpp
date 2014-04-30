#include "keyboard.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextStream>
#include <QTextEdit>
#include <QMessageBox>
#include <cmath>

Keyboard::Keyboard(QString layoutFileName, KeyboardConstants *k_c):
	kc(k_c)
{

	QFile file(layoutFileName);
	if (!file.open(QFile::ReadOnly |  QFile::Text))
	{
		qDebug() << "The file "
					<< layoutFileName
					<<" can not be opened. Now Quiting.";
		return;
	}
	QTextStream in(&file);



	name = in.readLine();
	in.readLine();//Read of the short alphabet
	alphabet = in.readLine().remove(' ');//Read the complete alphabet
	alphabet.append(' ');//Appending space
	alphabet.append(QChar(0x000d));//Appending Return
	in.readLine();//Read of comment
	Key readingKey;
	foreach (QChar ch, alphabet) //Please double check here that the input file has enough entries
	{
		readingKey.character = ch;
		in >> readingKey.row;
		in >> readingKey.finger;
		in >> readingKey.parallelMove;
		in >> readingKey.needsShift;
		readingKey.distanceToHome = getDistanceToHome(readingKey.row, readingKey.parallelMove);
		keyboard.append(readingKey);
	}
}


double Keyboard::getDistanceToHome(const int row, const int parallelMove)
//Compute the distance to home without considering shift.
{
	double x, y = row*0.019;

	x = parallelMove*0.019 +kc->horizontalShift[row + 1];

	return sqrt(x*x + y*y);
}

void Keyboard::procesText(QTextEdit *text)
{
	Key previousKey = keyboard.at(alphabet.indexOf(' '));
	Key currentKey;
    QString simplifiedText = text->toPlainText();
	foreach (QChar ch, simplifiedText)
	{
		if (!alphabet.contains(ch))
		{
			if (ch != '\n') qDebug() << "The character " << ch << " is not in the layout " << name;
			previousKey = keyboard.at(alphabet.indexOf(' '));//Let start from space as the character is not in the alphabet
		} else
		{
			currentKey = keyboard.at(alphabet.indexOf(ch));
			computeDistances(&previousKey, &currentKey);
            if (currentKey.character != ' ' && !currentKey.needsShift) previousKey = currentKey;
		}
	}
    for(int i = 0; i < 13; ++i) sameHandHits[i] -= (inwardRollingHits[i] + outwardRollingHits[i]);

	changeToPercentage(distances);
	changeToPercentage(hits);
	changeToPercentage(outwardRollingHits);
	changeToPercentage(inwardRollingHits);
	changeToPercentage(sameFingerHits);
	changeToPercentage(rowJumps);
	changeToPercentage(handSymmetry);
    changeToPercentage(sameHandHits);
}

void Keyboard::changeToPercentage(double (&ar)[13])
{
	for (int i = 0; i < 4; ++i)
	{
		ar[10] += ar[i];//Left hand
		ar[11] += ar[9-i];//Right hand
	}

	ar[12] = ar[10]+ar[11];//Both hands
	if (ar[12] != 0)//Now we find percentages
	{
		for (int i = 0; i < 12; ++i)
		{
			ar[i] *= 100/ar[12];
		}
	}
}

void Keyboard::computeDistances(const Key *prevKey, const Key *curKey)
{
    //We use -1 and 1 for left hand and right hand
	int previousHand = 0;
	int currentHand = 0;

    previousHand = (prevKey->finger < 4) ? -1 : (prevKey->finger > 5);
    currentHand = (curKey->finger < 4) ? -1 : (curKey->finger > 5);


    ++hits[curKey->finger];//First we add the finger hit.

	if (currentHand == 0)//In this case we are dealing with a space
	{
//		distances[prevKey->finger] += prevKey->distanceToHome;//Move back the previous finger to home
		if (prevKey->needsShift) addShiftSpace(prevKey);//shift finger go back home
		return;
	}

    if (prevKey->needsShift + curKey->needsShift == 0)
    {
        if (previousHand*currentHand == -1) ++handSymmetry[curKey->finger];
        else if (previousHand*currentHand == 1)  ++sameHandHits[curKey->finger];
    }

	if (curKey->finger == prevKey->finger)
	{
        if (curKey->row != prevKey->row || curKey->parallelMove != prevKey->parallelMove) ++sameFingerHits[curKey->finger];
		distances[curKey->finger] += goToKey(prevKey, curKey);
        if (!prevKey->needsShift && curKey->needsShift) //The curkey needs shift but not the prevkey
        {
            addShiftSpace(curKey);
            ++hits[pinkyIndex(-currentHand)];//add the pinky hit to the other hand
        }
        if (prevKey->needsShift && !curKey->needsShift) addShiftSpace(prevKey);//The prevkey needs shift but not the curkey, so we release the shift and move back the prev hand pinky to home
		rowJumps[curKey->finger] += (abs(curKey->row - prevKey->row)>1);
		return;
	}

	distances[prevKey->finger] += prevKey->distanceToHome;//First let move the previous finger to home
	distances[curKey->finger] += curKey->distanceToHome;//Move the current key from home to key

	if (currentHand == previousHand)
	{
        rowJumps[curKey->finger] += (abs(curKey->row - prevKey->row)>1) &&
                (curKey->row != -1 || (curKey->finger != 3 && curKey->finger != 6)) &&//Jump on index fingers are not bad
                (prevKey->row != -1 || (prevKey->finger != 3 && prevKey->finger != 6));

        inwardRollingHits[curKey->finger] += (((prevKey->finger - curKey->finger) == currentHand) &&
                                              (curKey->row == prevKey->row) && !curKey->needsShift && !prevKey->needsShift);
        outwardRollingHits[curKey->finger] += (((curKey->finger - prevKey->finger) == currentHand) &&
                (curKey->row == prevKey->row) && !curKey->needsShift && !prevKey->needsShift);
        if (!prevKey->needsShift && curKey->needsShift) addShiftSpace(curKey);//The curkey needs shift but not the prevkey,
        if (prevKey->needsShift && !curKey->needsShift) addShiftSpace(prevKey);//The prevkey needs shift but not the curkey, so we release the shift and move back the curhand pinky to home
	} else
	{
		if (prevKey->needsShift) addShiftSpace(prevKey); //We need the hand that hold shift for prevkey.
		if (curKey->needsShift) addShiftSpace(curKey);
        if (curKey->needsShift && prevKey->row > 0)
        {
            ++rowJumps[pinkyIndex(previousHand)];
            sameFingerHits[pinkyIndex(previousHand)];
        }
        if (prevKey->needsShift && curKey->row > 0)
        {
            ++rowJumps[pinkyIndex(currentHand)];
            sameFingerHits[pinkyIndex(currentHand)];
        }
	}

}


double Keyboard::goToKey(const Key *fromKey, const Key *toKey)
{
	double x1, y1;//coordinates of the fromKey from corresponding finger home key in meter
	double x2, y2;//coordinates of the toKey from corresponding finger home key in meter

	y1 = fromKey->row*0.019;
	y2 = toKey->row*0.019;

	x1 = fromKey->parallelMove*0.019 + kc->horizontalShift[fromKey->row + 1];
	x2 = toKey->parallelMove*0.019 + kc->horizontalShift[toKey->row + 1];

	return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}


void Keyboard::addShiftSpace(const Key *key)
{
	if (key->finger < 4)
	{
		distances[9] += kc->rightShiftDistance;
		++hits[9];
	}
	else if (key->finger > 5)
	{
		distances[0] += kc->leftShiftDistance;
		++hits[0];
	}
}
