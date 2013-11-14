#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include "keyboard.h"
#include <QDialog>
#include <QList>


namespace Ui {
class CompareDialog;
}

class CompareDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit CompareDialog(QTextEdit *text, QStringList *layoutsListPointer, bool isStandard,
						   bool isANSI,  QWidget *parent = 0);
	~CompareDialog();
	
private:
	Ui::CompareDialog *ui;
	QTextEdit *textEdit;

	QList<Keyboard> keyboardList;
	void evaluate (QString str);
};

#endif // COMPAREDIALOG_H
