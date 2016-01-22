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
        else this->taggedHeaders->insert(this->Trim_Tags(idHeaderElements.at(i)), tag);
    }
    return untaggedElements;
}

QString Tag_Manager::Apply_Tag_To_Element(const QString &sourceHeader, const QString &idElement, const QString &templateElement) {
    assert(this->Is_Header_Element_Tagged(templateElement));
    QMap<QString, Tags::Tag>::iterator tagIter = this->supportedTags->find(this->Trim_Tags(sourceHeader.toLower()));
    assert(tagIter != this->supportedTags->end());
    switch (tagIter.value()) {
    default:
    case Tags::NONE:                            assert(false);
    case Tags::RANDOMIZE:                       return this->Randomize(idElement, templateElement);
    case Tags::RANDOMIZE_BY_PERCENT_RANGE:      return this->Randomize_By_Percentage_Range(idElement, templateElement);
    }
    return QString();
}

bool Tag_Manager::Is_Header_Element_Tagged(const QString &element) {
    return this->taggedHeaders->contains(this->Trim_Tags(element.toLower()));
}

QString Tag_Manager::Randomize(const QString &rangeInIDFile, const QString &originalNumber) {
    QString range(rangeInIDFile);
    if (range.toLower() == "skip") return originalNumber;

    //Determine the min/max values
    double min = 0.0;
    double max = 0.0;
    if (range.isEmpty()) {
        max = 1000.00; //default value
    } else {
        QStringList ranges = range.split('-');
        if (ranges.size() != 2) return QString();

        //Parse out the numbers
        bool valid = false;
        min = ranges[0].toDouble(&valid);
        if (!valid) return QString();
        max = ranges[1].toDouble(&valid);
        if (!valid) return QString();
    }

    //TODO: There's a bug here. The decimal will currently ignore the min/max values
    return QString::number(min+(qrand()%(static_cast<int>(max-min+1))) + static_cast<double>((qrand()%100))/100.00);
}

QString Tag_Manager::Randomize_By_Percentage_Range(const QString &rangeInIDFile, const QString &baseNumber) {
    QString range(rangeInIDFile);
    if (range.toLower() == "skip") return baseNumber;

    //Determine the min/max values
    double min = 0.0;
    double max = 0.0;
    bool valid = false;
    if (range.isEmpty()) {
        //Set the default values
        min = 0.25;
        max = 200.00;
    } else {
        QStringList ranges = range.split('-');
        if (ranges.size() != 2) return QString();

        //Parse out the numbers
        range = range.replace("%", "");
        min = ranges[0].toDouble(&valid);
        if (!valid) return QString();
        max = ranges[1].toDouble(&valid);
        if (!valid) return QString();
    }

    //Parse the base number
    double baseNum = baseNumber.toDouble(&valid);
    if (!valid) return QString();

    //Update the min and max numbers based upon the range
    min = baseNum*(min/100.00);
    max = baseNum*(max/100.00);

    //TODO: There's a bug here. The decimal will currently ignore the min/max values
    return QString::number(min+(qrand()%(static_cast<int>(max-min+1))) + static_cast<double>((qrand()%100))/100.00);
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

QString Tag_Manager::Trim_Tags(const QString &element) {
    bool inTag = false;
    QString trimmed = "";
    for (int i = 0; i < element.size(); ++i) {
        if (inTag) {
            if (element.at(i) == ']') inTag = false;
        } else {
            if (element.at(i) == '[') inTag = true;
            else trimmed += element.at(i);
        }
    }
    return trimmed;
}

