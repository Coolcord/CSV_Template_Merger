#ifndef MERGER_H
#define MERGER_H

#include "Error_Codes.h"
#include <QWidget>
#include <QString>
#include <QFile>

class CSV_Helper;

class Merger {
public:
    Merger(bool cli);
    Merger(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool cli);
    int Merge();
    void Set_ID_File_Location(const QString &idFileLocation);
    void Set_Template_File_Location(const QString &templateFileLocation);
    void Set_Output_File_Location(const QString &outputFileLocation);

private:
    QString Merge_Line(QVector<int> &sourceIndexesInTemplate, QVector<QString> &sourceHeaders, const QString sourceLine, const QString &templateLine, bool firstLine);

    QString idFileLocation;
    QString templateFileLocation;
    QString outputFileLocation;
    bool cli;
    CSV_Helper *csvHelper;
};

#endif // MERGER_H
