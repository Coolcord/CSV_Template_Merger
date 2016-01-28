#include "Tag_Manager.h"
#include <assert.h>

Tag_Manager::Tag_Manager(CSV_Helper *csvHelper) {
    assert(csvHelper);
    this->Initialize(csvHelper, NULL);
}

Tag_Manager::Tag_Manager(CSV_Helper *csvHelper, QVector<int> *sourceIndexesInTemplate) {
    assert(csvHelper);
    assert(sourceIndexesInTemplate);
    this->Initialize(csvHelper, sourceIndexesInTemplate);
}

void Tag_Manager::Initialize(CSV_Helper *csvHelper, QVector<int> *sourceIndexesInTemplate) {
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

void Tag_Manager::Set_Source_Indexes_In_Template(QVector<int> *sourceIndexesInTemplate) {
    assert(sourceIndexesInTemplate);
    this->sourceIndexesInTemplate = sourceIndexesInTemplate;
}

QVector<QString> Tag_Manager::Read_Header_And_Get_Untagged_Elements(const QVector<QString> &idHeaderElements) {
    QVector<QString> untaggedElements;
    this->taggedHeaders->clear();
    for (int i = 0; i < idHeaderElements.size(); ++i) {
        Tags::Tag tag = this->Read_Tag(idHeaderElements.at(i));
        if (tag == Tags::NONE) untaggedElements.append(idHeaderElements.at(i));
        else this->taggedHeaders->insert(this->Strip_Tags(idHeaderElements.at(i)), tag);
    }
    return untaggedElements;
}

QString Tag_Manager::Apply_Tag_To_Element(const QString &sourceHeader, const QString &idElement, const QString &templateElement) {
    assert(this->Is_Header_Element_Tagged(sourceHeader));
    QMap<QString, Tags::Tag>::iterator tagIter = this->taggedHeaders->find(this->Strip_Tags(sourceHeader.toLower()));
    assert(tagIter != this->taggedHeaders->end());
    switch (tagIter.value()) {
    default:
    case Tags::NONE:                            assert(false);
    case Tags::RANDOMIZE:                       return this->Randomize(idElement, templateElement);
    case Tags::RANDOMIZE_BY_PERCENT_RANGE:      return this->Randomize_By_Percentage_Range(idElement, templateElement);
    }
    return QString();
}

bool Tag_Manager::Is_Header_Element_Tagged(const QString &element) {
    return this->taggedHeaders->contains(this->Strip_Tags(element.toLower()));
}

QString Tag_Manager::Randomize(const QString &rangeInIDFile, const QString &originalNumber) {
    QString range(rangeInIDFile);
    if (range.toLower() == "skip") return originalNumber;

    //Determine the min/max values
    double min = 0.0;
    double max = 0.0;
    int decimalPlaces = 2;
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

        decimalPlaces = this->Get_Number_Of_Decimal_Places_From_Number_Range(range);
    }
    return this->Generate_Random_Double(min, max, decimalPlaces);
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
        range = range.replace("%", "");
        QStringList ranges = range.split('-');
        if (ranges.size() != 2) return QString();

        //Parse out the numbers
        min = ranges[0].toDouble(&valid);
        if (!valid) return QString();
        max = ranges[1].toDouble(&valid);
        if (!valid) return QString();
    }

    //Parse the base number
    double baseNum = baseNumber.toDouble(&valid);
    if (!valid) return QString();

    //Get the number of decimal places to use from the base number
    int decimalPlaces = 0;
    QStringList baseNumberSplit = baseNumber.split(".");
    if (baseNumberSplit.size() > 1) {
        decimalPlaces = baseNumberSplit.at(1).size();
    }

    //Update the min and max numbers based upon the range
    min = baseNum*(min/100.00);
    max = baseNum*(max/100.00);
    return this->Generate_Random_Double(min, max, decimalPlaces);
}

int Tag_Manager::Get_Number_Of_Decimal_Places_From_Number_Range(const QString &range) {
    QStringList ranges = range.split('-');
    if (ranges.size() == 1) return 0;

    //Parse each number string
    int decimalPlaces = 0;
    QStringList decimal = ranges.at(0).split(".");
    if (decimal.size() != 1) {
        decimalPlaces = decimal.at(1).size();
    }
    decimal = ranges.at(1).split(".");
    if (decimal.size() != 1) {
        if (decimal.at(1).size() > decimalPlaces) {
            decimalPlaces = decimal.at(1).size();
        }
    }
    return decimalPlaces;
}

QString Tag_Manager::Generate_Random_Double(double min, double max, int decimalPlaces) {
    double value = (((double)rand() * (max-min)) / (double)RAND_MAX+min);
    QString valueString = QString::number(value);
    QStringList valueStringSplit = valueString.split(".");
    QString valueDecimal = "";
    if (valueStringSplit.size() > 1) valueDecimal = valueStringSplit.at(1);

    //Add padding if necessary
    while (valueDecimal.size() < decimalPlaces) {
        valueDecimal += "0";
    }

    //Trim down to the remaining decimal places
    valueString = valueStringSplit.at(0);
    if (decimalPlaces > 0) valueString += ".";
    for (int i = 0; i < decimalPlaces; ++i) {
        valueString += valueDecimal.at(i);
    }

    return valueString;
}

Tags::Tag Tag_Manager::Read_Tag(const QString &element) {
    bool inTag = false;
    QString tag = "";

    //Scan for tags
    for (int i = 0; i < element.size(); ++i) {
        switch (element.at(i).toLatin1()) {
        default:
            if (inTag) tag += element.at(i);
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

QString Tag_Manager::Strip_Tags(const QString &headerElement) {
    bool inTag = false;
    QString strippedElement = "";

    //Scan for tags
    for (int i = 0; i < headerElement.size(); ++i) {
        switch (headerElement.at(i).toLatin1()) {
        default:
            if (!inTag) strippedElement += headerElement.at(i);
            break;
        case '[':
            inTag = true;
            break;
        case ']':
            inTag = false;
            break;
        }
    }
    return strippedElement;
}

