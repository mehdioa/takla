#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void addLayout();
	void removeLayout();
	void loadText();
	void analyzeText();
	void compareLayouts();
	void about();

private:
	Ui::MainWindow *ui;
	QString efforts;

	void createSettings();
	void readSettings();
	void writeSettings();
	void createStatusBar();

};

#endif // MAINWINDOW_H
