#ifndef CSV_HELPER_H
#define CSV_HELPER_H

#include <QLinkedList>
#include <QString>
#include <QVector>

#ifdef Q_OS_WIN32
const static QString NEW_LINE = "\r\n";
#else
const static QString NEW_LINE = "\n";
#endif

class CSV_Helper
{
public:
    CSV_Helper() {}
    int Get_Number_Of_Columns(const QString &line);
    QString Get_Value_At_Index(int index, const QString &line);
    QVector<QString> Get_CSV_Elements_From_Line_As_Vector(const QString &line);
    QLinkedList<QString> Get_CSV_Elements_From_Line_As_Linked_List(const QString &line);
    int Get_Column_Index_By_Header(const QString &header, const QString &line);
};

#endif // CSV_HELPER_H
