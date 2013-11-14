#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setOrganizationName("QtProject");
	app.setApplicationName("Keyboard Layout Analyzer");
	MainWindow mainWindow;
	mainWindow.show();
	mainWindow.setWindowTitle("Keyboard Layout Analyzer");
	mainWindow.setWindowIcon(QIcon("Images/kla.png"));

	return app.exec();
}
