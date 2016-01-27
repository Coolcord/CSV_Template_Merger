#ifndef TAG_MANAGER_H
#define TAG_MANAGER_H

#include "Tags.h"
#include <QMap>
#include <QVector>
#include <QString>

class CSV_Helper;

class Tag_Manager
{
public:
    Tag_Manager(CSV_Helper *csvHelper, QVector<int> *sourceIndexesInTemplate);
    ~Tag_Manager();
    QVector<QString> Read_Header_And_Get_Untagged_Elements(const QVector<QString> &idHeaderElements);
    QString Apply_Tag_To_Element(const QString &sourceHeader, const QString &idElement, const QString &element);
    bool Is_Header_Element_Tagged(const QString &element);

private:
    QString Randomize(const QString &rangeInIDFile, const QString &originalNumber);
    QString Randomize_By_Percentage_Range(const QString &rangeInIDFile, const QString &baseNumber);
    int Get_Number_Of_Decimal_Places_From_Number_Range(const QString &range);
    double Generate_Random_Double(double min, double max, int decimalPlaces);
    Tags::Tag Read_Tag(const QString &element);
    QString Strip_Tags(const QString &headerElement);

    CSV_Helper *csvHelper;
    QMap<QString, Tags::Tag> *taggedHeaders;
    QVector<int> *sourceIndexesInTemplate;
    QMap<QString, Tags::Tag> *supportedTags;
};

#endif // TAG_MANAGER_H
