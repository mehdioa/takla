#ifndef PERCENTAGEWINDOW_H
#define PERCENTAGEWINDOW_H

#include <QDialog>
class QTextEdit;

namespace Ui {
class percentageWindow;
}

class percentageWindow : public QDialog
{
	Q_OBJECT

public:
	explicit percentageWindow(QString characters, QTextEdit *text, QWidget *parent = 0);
	~percentageWindow();

private slots:
    void showBaseBigrams();
	void showTrigrams();

private:
	Ui::percentageWindow *ui;
	QString characterSet;
	QString textEdit;
	int totalCharacters;
	int totalBigrams;
	int totalTrigrams;
	int alphabetSize;

	void setTotalCharacters();
	void setTotalBigrams();
	void setTotalTrigrams();
	void setModels();
	QStringList *subStrings(QString str, int subStrNumber);


};

#endif // PERCENTAGEWINDOW_H
