#include "comparedialog.h"
#include "ui_comparedialog.h"
#include <QDebug>
#include <QTextEdit>
#include <QListWidget>
#include <QStandardItemModel>

CompareDialog::CompareDialog(QTextEdit *text, QStringList *layoutsListPointer, KeyboardConstants k_c, QWidget *parent):
	QDialog(parent),
	ui(new Ui::CompareDialog), textEdit(text),
	kc(k_c)
{
	ui->setupUi(this);

	for (int i = 0; i < layoutsListPointer->size(); ++i )
	{
		Keyboard kb(layoutsListPointer->at(i), &kc);
		kb.procesText(text);
		keyboardList.append(kb);
	}
    auto fingerDistanceModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto fingerHitsModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto outwardRollingModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto inwardRollingModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto sameFingerModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto rowJumpsModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto handSymmetryModel = new QStandardItemModel(13, layoutsListPointer->size(), this);
    auto sameHandModel = new QStandardItemModel(13, layoutsListPointer->size(), this);

	QList<QStandardItemModel*> models;
	models.append(fingerHitsModel);
	models.append(fingerDistanceModel);
	models.append(outwardRollingModel);
	models.append(inwardRollingModel);
	models.append(sameFingerModel);
	models.append(rowJumpsModel);
	models.append(handSymmetryModel);
    models.append(sameHandModel);

	for (int kbIndex = 0; kbIndex < keyboardList.size(); ++kbIndex)
	{
        for (int finger = 0; finger < 13; ++finger)
		{
			fingerDistanceModel->setData(fingerDistanceModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).distances[finger]);
			fingerHitsModel->setData(fingerHitsModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).hits[finger]);
			sameFingerModel->setData(sameFingerModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).sameFingerHits[finger]);
			inwardRollingModel->setData(inwardRollingModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).inwardRollingHits[finger]);
			outwardRollingModel->setData(outwardRollingModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).outwardRollingHits[finger]);
			rowJumpsModel->setData(rowJumpsModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).rowJumps[finger]);
			handSymmetryModel->setData(handSymmetryModel->index(finger, kbIndex, QModelIndex()),
										 (double) keyboardList.at(kbIndex).handSymmetry[finger]);
            sameHandModel->setData(sameHandModel->index(finger, kbIndex, QModelIndex()),
                                         (double) keyboardList.at(kbIndex).sameHandHits[finger]);

		}
	}

	QStringList fingerNames = {"Left Pinky", "Left Ring", "Left Middle", "left Index", "Left Thumb",
							   "Right Thumb", "Right Index", "Right Middle", "Right Ring", "Right Pinky",
                               "Left Hand", "Right Hand", "Total"};

	QStringList layoutNames;
	for (int kbIndex = 0; kbIndex < keyboardList.size(); ++kbIndex)
	{
		layoutNames << (QString) keyboardList.at(kbIndex).name;
	}

	foreach (auto qsim, models)
	{
		qsim->setVerticalHeaderLabels(fingerNames);
		qsim->setHorizontalHeaderLabels(layoutNames);
		qsim->removeRows(4,2);
	}

	ui->fingerDistanceTableView->setModel(fingerDistanceModel);
	ui->fingerHitsTableView->setModel(fingerHitsModel);
	ui->outwardRollingTableView->setModel(outwardRollingModel);
	ui->inwardRollingTableView->setModel(inwardRollingModel);
	ui->sameFingerTableView->setModel(sameFingerModel);
	ui->rowJumpTableView->setModel(rowJumpsModel);
	ui->handSymmetryTableView->setModel(handSymmetryModel);
    ui->sameHandTableView->setModel(sameHandModel);
}

CompareDialog::~CompareDialog()
{
	delete ui;
	delete textEdit;
}
