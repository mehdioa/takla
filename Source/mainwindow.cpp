#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "percentagewindow.h"
#include "comparedialog.h"
#include "keyboardconstants.h"
#include <QMainWindow>
#include <QSettings>
#include <QtEvents>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QList>



MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->addPushButton, SIGNAL(clicked()), this, SLOT(addLayout()));
	connect(ui->removePushButton, SIGNAL(clicked()), this, SLOT(removeLayout()));
	connect(ui->loadPushButton, SIGNAL(clicked()), this, SLOT(loadText()));
	connect(ui->analyzePushButton, SIGNAL(clicked()), this, SLOT(analyzeText()));
	connect(ui->comparePushButton, SIGNAL(clicked()), this, SLOT(compareLayouts()));

	readSettings();

	createStatusBar();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}





void MainWindow::readSettings()
{
	QSettings settings("QtProject", "Text And Keyboard Layout Analyzer");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

void MainWindow::writeSettings()
{
	QSettings settings("QtProject", "Text And Keyboard Layout Analyzer");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	writeSettings();
	event->accept();
}

void MainWindow::addLayout()
{
	QString fileName = QFileDialog::getOpenFileName(this,
													tr("Open Keyboard"),
													tr("Keyboard Files (*.klt)"));
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Text And Keyboard Layout Analyzer"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;

	}

	QTextStream in(&file);
	auto newItem = new QListWidgetItem(ui->layoutsListWidget);
	newItem->setText(in.readLine());
	file.close();
	newItem->setWhatsThis(fileName);
	ui->layoutsListWidget->addItem(newItem);
	statusBar()->showMessage(tr("Layout loaded"), 2000);
}

void MainWindow::removeLayout()
{
	delete ui->layoutsListWidget->currentItem();
	statusBar()->showMessage(tr("Layout removed"), 2000);

}

void MainWindow::loadText()
{
	QString fileName = QFileDialog::getOpenFileName(this);
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly |  QFile::Text))
	{
		QMessageBox::warning(this, tr("Text And Keyboard Layout Analyzer"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
	#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
	#endif
		ui->textEdit->clear();
		ui->textEdit->setPlainText(in.readAll());
	#ifndef QT_NO_CURSOR
		QApplication::restoreOverrideCursor();
	#endif
	file.close();
	statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::analyzeText()
{
	if (ui->textEdit->document()->isEmpty())
	{
		QMessageBox::warning(this, tr("Application"), tr("Please load a text file first"));
		return;
	}
	else if (!ui->layoutsListWidget->count())
	{
		QMessageBox::warning(this, tr("Application"), tr("Please load at least one layout"));
		return;
	}
	QFile file(ui->layoutsListWidget->item(0)->whatsThis());
	QTextStream in(&file);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Text And Keyboard Layout Analyzer"),
							 tr("Cannot read file %1:\n%2.")
							 .arg(ui->layoutsListWidget->item(0)->whatsThis())
							 .arg(file.errorString()));
		return;

	}
	in.readLine();

	QString characterSet = in.readLine().remove(" ");
	file.close();

	auto pw = new percentageWindow(characterSet, ui->textEdit, this);
	pw->setWindowTitle("Analyzing");
	pw->show();
	statusBar()->showMessage(tr("Text Analyzed"), 2000);

}

void MainWindow::compareLayouts()
{
	if (ui->textEdit->document()->isEmpty())
	{
		QMessageBox::warning(this, tr("Application"), tr("Please open a file first"));
		return;
	}
	else if (!ui->layoutsListWidget->count())
	{
		QMessageBox::warning(this, tr("Application"), tr("Please load at least one layout"));
		return;
	}

	QStringList layoutList;
	for (int i = 0; i < ui->layoutsListWidget->count(); ++i)
	{
		layoutList.append(ui->layoutsListWidget->item(i)->whatsThis());
	}

	KeyboardConstants kc( (KeyboardType) ui->standardRadioButton->isEnabled(), (KeyboardShape) ui->AnsiRadioButton->isEnabled());
	auto cw = new CompareDialog(ui->textEdit, &layoutList, kc, this);
	cw->setWindowTitle("Compares");
	cw->show();
	statusBar()->showMessage(tr("Layout compared"), 2000);

}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About KLA"),
			 tr("<b>Text And Keyboard Layout Analyzer<b> Based on Qt 4.8.4"));
}

