#include "Tag_Manager.h"
#include <assert.h>

Tag_Manager::Tag_Manager(CSV_Helper *csvHelper, QVector<int> *sourceIndexesInTemplate) {
    assert(csvHelper);
    assert(sourceIndexesInTemplate);
    this->csvHelper = csvHelper;
    this->taggedHeaders = new QMap<QString, Tags::Tag>();
    this->sourceIndexesInTemplate = sourceIndexesInTemplate;

    //Use a dictionary to keep track of supported tags
    //Use lower case for comparison
    this->supportedTags = new QMap<QString, Tags::Tag>();
    supportedTags->insert("randomize", Tags::RANDOMIZE);
    supportedTags->insert("randomizebypercentrange", Tags::RANDOMIZE_BY_PERCENT_RANGE);
    supportedTags->insert("randomizebpr", Tags::RANDOMIZE_BY_PERCENT_RANGE);
}

Tag_Manager::~Tag_Manager() {
    delete this->taggedHeaders;
    delete this->supportedTags;
    this->csvHelper = NULL;
    this->taggedHeaders = NULL;
    this->sourceIndexesInTemplate = NULL;
    this->supportedTags = NULL;
}

QVector<QString> Tag_Manager::Read_Header_And_Get_Untagged_Elements(const QVector<QString> &idHeaderElements) {
    QVector<QString> untaggedElements;
    this->taggedHeaders->clear();
    for (int i = 0; i < idHeaderElements.size(); ++i) {
        Tags::Tag tag = this->Read_Tag(idHeaderElements.at(i));
        if (tag == Tags::NONE) untaggedElements.append(idHeaderElements.at(i));
        else this->taggedHeaders->insert(idHeaderElements.at(i), tag);
    }
    return untaggedElements;
}

QString Tag_Manager::Apply_Tags_To_Line(QVector<QString> &line) {

}

QString Tag_Manager::Randomize(const QString &range) {

}

QString Tag_Manager::Randomize_By_Percentage_Range(const QString &range) {

}

Tags::Tag Tag_Manager::Read_Tag(const QString &element) {
    bool inTag = false;
    QString tag = "";

    //Scan for tags
    for (int i = 0; i < element.size(); ++i) {
        switch (element.at(i).toLatin1()) {
        default:
            tag += element.at(i);
            break;
        case '[':
            inTag = true;
            break;
        case ']':
            if (!inTag) break;
            inTag = false;
            tag = tag.toLower();
            QMap<QString, Tags::Tag>::iterator tagIter = this->supportedTags->find(tag);
            if (tagIter == this->supportedTags->end()) tag = "";
            else return tagIter.value();
            break;
        }
    }
    return Tags::NONE;
}

