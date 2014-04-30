#ifndef PERCENTAGEWINDOW_H
#define PERCENTAGEWINDOW_H

#include <QDialog>
#include <QStringList>
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
	QStringList Bigramstrings;
	QStringList Trigramstrings;

	void setTotalCharacters();
	void setTotalBigrams();
	void setTotalTrigrams();
	void setModels();
	void subStrings(QStringList *string_list, QString str, int subStrNumber);


};

#endif // PERCENTAGEWINDOW_H
