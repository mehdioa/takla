#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setOrganizationName("QtProject");
	app.setApplicationName("Text And Keyboard Layout Analyzer");
	MainWindow mainWindow;
	mainWindow.show();
	mainWindow.setWindowTitle("Text And Keyboard Layout Analyzer");
	mainWindow.setWindowIcon(QIcon("://images/Images/tkla.png"));

	return app.exec();
}
