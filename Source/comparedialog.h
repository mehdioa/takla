#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include "keyboard.h"
#include <QDialog>
#include <QList>

class KeyboardConstants;

namespace Ui {
class CompareDialog;
}

class CompareDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit CompareDialog(QTextEdit *text, QStringList *layoutsListPointer, KeyboardConstants k_c,  QWidget *parent = 0);
	~CompareDialog();

private:
	Ui::CompareDialog *ui;
	KeyboardConstants kc;

	QList<Keyboard *> keyboardList;
	void evaluate (QString str);
};

#endif // COMPAREDIALOG_H
