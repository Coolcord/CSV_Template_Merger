#ifndef MERGER_H
#define MERGER_H

#include "Error_Codes.h"
#include <QWidget>
#include <QString>
#include <QFile>

class CSV_Helper;

class Merger {
public:
    Merger();
    Merger(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool multiFileMode);
    int Merge();
    void Set_ID_File_Location(const QString &idFileLocation);
    void Set_Template_File_Location(const QString &templateFileLocation);
    void Set_Output_File_Location(const QString &outputFileLocation);
    void Set_Multi_File_Mode(bool multiFileMode);

private:
    QString Merge_Line(QVector<int> &sourceIndexesInTemplate, QVector<QString> &sourceHeaders, const QString sourceLine, const QString &templateLine, bool firstLine);
    int Check_For_Duplicate_Files();

    QString idFileLocation;
    QString templateFileLocation;
    QString outputFileLocation;
    bool multiFileMode;
    CSV_Helper *csvHelper;
};

#endif // MERGER_H
