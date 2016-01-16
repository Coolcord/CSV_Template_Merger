#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include <QString>

class Merger_Thread;

namespace Ui {
class Main_Window;
}

class Main_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Main_Window(QWidget *parent = 0);
    ~Main_Window();

private slots:
    void on_btnGenerate_clicked();
    void on_btnIDFileLocation_clicked();
    void on_btnTemplateFileLocation_clicked();
    void on_btnOutputFileLocation_clicked();
    void on_leIDFileLocation_textChanged();
    void on_leTemplateFileLocation_textChanged();
    void on_leOutputFileLocation_textChanged();

private:
    QString Get_Open_File_Location();
    QString Get_Save_File_Location();
    void Toggle_Generate_Button();
    bool Is_File_Used(const QString &filePath);

    Ui::Main_Window *ui;
    Merger_Thread *mergerThread;
};

#endif // MAIN_WINDOW_H
