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
    QString Apply_Tags_To_Line(QVector<QString> &line);

private:
    QString Randomize(const QString &range);
    QString Randomize_By_Percentage_Range(const QString &range);
    Tags::Tag Read_Tag(const QString &element);

    CSV_Helper *csvHelper;
    QMap<QString, Tags::Tag> *taggedHeaders;
    QVector<int> *sourceIndexesInTemplate;
    QMap<QString, Tags::Tag> *supportedTags;
};

#endif // TAG_MANAGER_H
