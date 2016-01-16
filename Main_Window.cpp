#include "Main_Window.h"
#include "ui_Main_Window.h"
#include "Merger_Thread.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

Main_Window::Main_Window(QWidget *parent) :
    QDialog(parent, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint),
    ui(new Ui::Main_Window) {
    this->ui->setupUi(this);
    this->Toggle_Generate_Button();
    this->mergerThread = new Merger_Thread(false, this);
}

Main_Window::~Main_Window() {
    delete this->ui;
    delete this->mergerThread;
    this->ui = NULL;
    this->mergerThread = NULL;
}

void Main_Window::on_btnGenerate_clicked() {
    this->ui->btnGenerate->setEnabled(false);
    this->ui->btnGenerate->setText("Generating...");
    this->mergerThread->Set_ID_File_Location(this->ui->leIDFileLocation->text());
    this->mergerThread->Set_Template_File_Location(this->ui->leTemplateFileLocation->text());
    this->mergerThread->Set_Output_File_Location(this->ui->leOutputFileLocation->text());
    this->mergerThread->start();
}

void Main_Window::on_btnIDFileLocation_clicked() {
    QString fileLocation = this->Get_Open_File_Location();
    if (this->Is_File_Used(fileLocation)) {
        QMessageBox::critical(this, "CSV Template Merger",
                              "The ID file should not be the same as the template or output files", "OK");
        return;
    }
    if (!fileLocation.isEmpty()) {
        this->ui->leIDFileLocation->setText(fileLocation);
        this->Toggle_Generate_Button();
    }
}

void Main_Window::on_btnTemplateFileLocation_clicked() {
    QString fileLocation = this->Get_Open_File_Location();
    if (this->Is_File_Used(fileLocation)) {
        QMessageBox::critical(this, "CSV Template Merger",
                              "The template file should not be the same as the ID or output files", "OK");
        return;
    }
    if (!fileLocation.isEmpty()) {
        this->ui->leTemplateFileLocation->setText(fileLocation);
        this->Toggle_Generate_Button();
    }
}

void Main_Window::on_btnOutputFileLocation_clicked() {
    QString fileLocation = this->Get_Save_File_Location();
    if (this->Is_File_Used(fileLocation)) {
        QMessageBox::critical(this, "CSV Template Merger",
                              "Don't overwrite the ID or template files!", "OK");
        return;
    }
    if (!fileLocation.isEmpty()) {
        this->ui->leOutputFileLocation->setText(fileLocation);
        this->Toggle_Generate_Button();
    }
}

QString Main_Window::Get_Open_File_Location() {
    QString fileLocation = QFileDialog::getOpenFileName(this, "Open a CSV File", QApplication::applicationDirPath(), "CSV files (*.csv);;All files (*.*)");
    if (fileLocation == NULL || fileLocation.isEmpty()) return QString();
    return fileLocation;
}

QString Main_Window::Get_Save_File_Location() {
    QString saveLocation = QFileDialog::getSaveFileName(this, "Save Location", QApplication::applicationDirPath(), "CSV files (*.csv);;All files (*.*)");
    if (saveLocation == NULL || saveLocation.isEmpty()) return QString();
    QFileInfo file(saveLocation);
    QDir dir = file.dir();
    if (file.isDir()) {
        QMessageBox::critical(this, "CSV Template Merger",
                              file.fileName() + " is a directory!", "OK");
        return QString();
    }
    if (!dir.exists()) {
        QMessageBox::critical(this, "CSV Template Merger",
                              file.fileName() + " does not exist!", "OK");
        return QString();
    }
    return saveLocation;
}

void Main_Window::Toggle_Generate_Button() {
    this->ui->btnGenerate->setEnabled(!this->ui->leIDFileLocation->text().isEmpty()
                                      && !this->ui->leTemplateFileLocation->text().isEmpty()
                                      && !this->ui->leOutputFileLocation->text().isEmpty());
}

bool Main_Window::Is_File_Used(const QString &filePath) {
    if (filePath.isEmpty()) return false;
    QFileInfo file(filePath);

    //Check the ID File
    if (!this->ui->leIDFileLocation->text().isEmpty()) {
        QFileInfo idFileInfo(this->ui->leIDFileLocation->text());
        if (file.filePath() == idFileInfo.filePath()) return true;
    }

    //Check the template file
    if (!this->ui->leTemplateFileLocation->text().isEmpty()) {
        QFileInfo templateFileInfo(this->ui->leTemplateFileLocation->text());
        if (file.filePath() == templateFileInfo.filePath()) return true;
    }

    //Check the output file
    if (!this->ui->leOutputFileLocation->text().isEmpty()) {
        QFileInfo outputFileInfo(this->ui->leOutputFileLocation->text());
        if (file.filePath() == outputFileInfo.filePath()) return true;
    }
    return false; //no matches found
}

void Main_Window::on_leIDFileLocation_textChanged() {
    this->Toggle_Generate_Button();
}

void Main_Window::on_leTemplateFileLocation_textChanged() {
    this->Toggle_Generate_Button();
}

void Main_Window::on_leOutputFileLocation_textChanged() {
    this->Toggle_Generate_Button();
}