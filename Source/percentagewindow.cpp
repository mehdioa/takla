#include "percentagewindow.h"
#include "ui_percentagewindow.h"
#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QStringList>
#include <QStandardItemModel>

percentageWindow::percentageWindow(QString characters, QTextEdit *text, QWidget *parent) :
	QDialog(parent), ui(new Ui::percentageWindow),
    characterSet(characters), textEdit(text->toPlainText().remove(' '))
{
    ui->setupUi(this);
	alphabetSize = characterSet.length();
	setTotalCharacters();
	setTotalBigrams();

	setModels();
	foreach (QChar ch, characterSet)
	{
		ui->baseBigramsComboBox->addItem(ch);
	}

    connect(ui->baseBigramsShowPushButton, SIGNAL(clicked()), this, SLOT(showBaseBigrams()));
	connect(ui->trigramsShowPushButton, SIGNAL(clicked()), this, SLOT(showTrigrams()));
}

percentageWindow::~percentageWindow()
{
    delete ui;
}

void percentageWindow::setTotalCharacters()
{
	totalCharacters = 0;
	for (int i = 0; i < alphabetSize; ++i)
	{
		totalCharacters += textEdit.count(characterSet[i], Qt::CaseInsensitive);
	}

}

void percentageWindow::setTotalBigrams()
{
	totalBigrams= 0;
	auto Bigramstrings = new QStringList;
	Bigramstrings = subStrings(characterSet, 2);
	for (int i = 0; i < alphabetSize*alphabetSize; ++i)
	{
		totalBigrams += textEdit.count((QString) Bigramstrings->at(i), Qt::CaseInsensitive);
	}
}

void percentageWindow::setTotalTrigrams()
{
	totalTrigrams= 0;
	auto trigramstrings = new QStringList;
	trigramstrings = subStrings(characterSet, 3);
	for (int i = 0; i < alphabetSize*alphabetSize*alphabetSize; ++i)
	{
		totalTrigrams += textEdit.count((QString) trigramstrings->at(i), Qt::CaseInsensitive);
	}

}


void percentageWindow::setModels()
{
	auto charModel = new QStandardItemModel(alphabetSize, 2, this);
	charModel->setHeaderData(0, Qt::Horizontal, tr("Character"));
	charModel->setHeaderData(1, Qt::Horizontal, tr("Percentage"));

	for (int row = 0; row < alphabetSize; ++row)
	{
		charModel->setData(charModel->index(row, 0, QModelIndex()), (QString) characterSet[row]);
		charModel->setData(charModel->index(row, 1, QModelIndex()),
						   (double) textEdit.count(characterSet[row], Qt::CaseSensitive)/totalCharacters*100);
	}

	int bigramNumber = alphabetSize*alphabetSize;
	auto bigramModel = new QStandardItemModel(bigramNumber,2,this);
	bigramModel->setHeaderData(0, Qt::Horizontal, tr("Bigram"));
	bigramModel->setHeaderData(1, Qt::Horizontal, tr("Percentage"));
	auto Bigramstrings = new QStringList;
	Bigramstrings = subStrings(characterSet, 2);
	for (int row =0; row < bigramNumber; ++row)
	{
		bigramModel->setData(bigramModel->index(row, 0, QModelIndex()), (QString)Bigramstrings->at(row));
		bigramModel->setData(bigramModel->index(row, 1, QModelIndex()),
                              (double) textEdit.count((QString)Bigramstrings->at(row))/textEdit.length()*100);
	}




	charModel->sort(1, Qt::DescendingOrder);
	bigramModel->sort(1, Qt::DescendingOrder);
	ui->charTableView->setModel(charModel);
	ui->bigramsTableView->setModel(bigramModel);
}

void percentageWindow::showBaseBigrams()
{
    auto basebigramModel = new QStandardItemModel((1+ui->oderedRadioButton->isChecked())*alphabetSize, 2, this);
	basebigramModel->setHeaderData(0, Qt::Horizontal, tr("Composition"));
	basebigramModel->setHeaderData(1, Qt::Horizontal, tr("Percentage"));

	for (int i = 0; i < alphabetSize; ++i)
	{
		basebigramModel->setData(basebigramModel->index(i, 0, QModelIndex()),
						   (QString) ui->baseBigramsComboBox->currentText()+characterSet[i]);
		basebigramModel->setData(basebigramModel->index(i, 1, QModelIndex()),
                           (((double) textEdit.count((QString) ui->baseBigramsComboBox->currentText()+characterSet[i], Qt::CaseInsensitive)) +
                                 ui->unorderedRadioButton->isChecked()*(ui->baseBigramsComboBox->currentIndex() != i)*
                            ((double) textEdit.count((QString) characterSet[i]+ui->baseBigramsComboBox->currentText(),
                                                     Qt::CaseInsensitive)))/textEdit.length()*100);
        if (ui->oderedRadioButton->isChecked())
        {
            basebigramModel->setData(basebigramModel->index(alphabetSize+i, 0, QModelIndex()),
                               (QString) characterSet[i]+ui->baseBigramsComboBox->currentText());
            basebigramModel->setData(basebigramModel->index(alphabetSize+i, 1, QModelIndex()),
                               ui->oderedRadioButton->isChecked()*((double) textEdit.count((QString) characterSet[i]+ui->baseBigramsComboBox->currentText(),
                                                                      Qt::CaseInsensitive))/textEdit.length()*100);
        }
    }
    basebigramModel->removeRow(ui->baseBigramsComboBox->currentIndex());
    basebigramModel->sort(1, Qt::DescendingOrder);
	ui->baseBigramsTableView->setModel(basebigramModel);
}

void percentageWindow::showTrigrams()
{
	setTotalTrigrams();

	int trigramNumber = alphabetSize*alphabetSize*alphabetSize;
	auto trigramModel = new QStandardItemModel(trigramNumber,2,this);
	trigramModel->setHeaderData(0, Qt::Horizontal, tr("Trigram"));
	trigramModel->setHeaderData(1, Qt::Horizontal, tr("Percentage"));
	auto trigramstrings = new QStringList;
	trigramstrings = subStrings(characterSet, 3);
	for (int row =0; row < trigramNumber; ++row)
	{
		trigramModel->setData(trigramModel->index(row, 0, QModelIndex()), (QString)trigramstrings->at(row));
		trigramModel->setData(trigramModel->index(row, 1, QModelIndex()),
                               (double) textEdit.count((QString)trigramstrings->at(row))/textEdit.length()*100);
	}
	trigramModel->sort(1, Qt::DescendingOrder);
	ui->trigramsTableView->setModel(trigramModel);
}

QStringList *percentageWindow::subStrings(QString str, int subStrNumber)
{
	int baseNumber = str.length();
	int totalNumber = str.length();
	for (int pow = 1; pow < subStrNumber; ++pow)
	{
		totalNumber *= baseNumber;
	}
	auto answer = new QStringList;
	QString subStr;
	int tempNumber;
	for (int i = 0; i < totalNumber; ++i)
	{
		subStr = "";
		tempNumber = i;
		for(int j = 0; j < subStrNumber; ++j)
		{
			subStr.append(str[tempNumber%baseNumber]);
			tempNumber /= baseNumber;
		}
		answer->append(subStr);
	}
	return answer;
}
