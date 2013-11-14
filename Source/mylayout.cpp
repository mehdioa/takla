#include "layout.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>
#include <QChar>

Layout::Layout(QString layoutFileName)
{
	QFile file(layoutFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Keyboard Layout Analyzer"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(layoutFileName)
							 .arg(file.errorString()));
		return;
	}
	QTextStream in(&file);
	name = in.readLine();
	alphabet = in.readLine();
	Key readingKey;
	while(!in.atEnd())
	{
		in >> readingKey.character;
		in >> readingKey.row;
		in >> readingKey.hand;
		in >> readingKey.finger;
		in >> readingKey.parallelMove;
		in >> readingKey.needsShift;
		keyboard.append(readingKey);
	}
}


void Layout::processWord(QString str)
{
	if (!consistsOfAlphabetOnly(str)) return;
	QChar previousChar = QChar::Null;
	foreach(QChar currentChar, str)
	{

	}
}

void Layout::procesText(QTextEdit *text)
{

}

bool Layout::consistsOfAlphabetOnly(QString str)
{
	foreach(QChar ch, str)
	{
		if (!alphabet.contains(ch)) return false;
	}
	return true;
}
