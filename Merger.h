#ifndef MERGER_H
#define MERGER_H

#include <QWidget>
#include <QString>
#include <QFile>

class CSV_Helper;

class Merger {
public:
    Merger(bool cli);
    Merger(bool cli, QWidget *parent);
    Merger(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool cli);
    Merger(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool cli, QWidget *parent);
    bool Merge();
    void Set_ID_File_Location(const QString &idFileLocation);
    void Set_Template_File_Location(const QString &templateFileLocation);
    void Set_Output_File_Location(const QString &outputFileLocation);

private:
    QString Merge_Line(QVector<int> &sourceIndexesInTemplate, const QString sourceLine, const QString &templateLine);
    void Show_Error_Message(const QString &message);

    QString idFileLocation;
    QString templateFileLocation;
    QString outputFileLocation;
    bool cli;
    QWidget *parent;
    CSV_Helper *csvHelper;
};

#endif // MERGER_H
