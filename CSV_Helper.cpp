#include "CSV_Helper.h"
#include <assert.h>

int CSV_Helper::Get_Number_Of_Columns(const QString &line) {
    QVector<QString> elements = this->Get_CSV_Elements_From_Line_As_Vector(line);
    return elements.length();
}

QString CSV_Helper::Get_Value_At_Index(int index, const QString &line) {
    assert(index >= 0);
    QVector<QString> elements = this->Get_CSV_Elements_From_Line_As_Vector(line);
    assert(elements.length() <= index);
    return elements.at(index);
}

QVector<QString> CSV_Helper::Get_CSV_Elements_From_Line_As_Vector(const QString &line) {
    QVector<QString> elements;
    QString currentElement = QString();
    bool insideQuotes = false;
    bool lastWasComma = false;
    for (int i = 0; i < line.length(); ++i) {
        lastWasComma = false;
        switch (line[i].toLatin1()) {
        case '\r':
        case '\n':
            break;
        case '\"':
            insideQuotes = !insideQuotes;
            break;
        case ',':
            if (!insideQuotes) {
                elements.append(currentElement);
                currentElement = "";
                lastWasComma = true;
            }
            break;
        default:
            currentElement += line[i];
            break;
        }
    }
    if (lastWasComma || !currentElement.isEmpty()) elements.append(currentElement);

    return elements;
}

QLinkedList<QString> CSV_Helper::Get_CSV_Elements_From_Line_As_Linked_List(const QString &line) {
    QLinkedList<QString> elements;
    QString currentElement = QString();
    bool insideQuotes = false;
    bool lastWasComma = false;
    for (int i = 0; i < line.length(); ++i) {
        lastWasComma = false;
        if (line[i] == '\"') {
            insideQuotes = !insideQuotes;
        } else if (!insideQuotes && line[i] == ',') {
            elements.append(currentElement);
            currentElement = "";
            lastWasComma = true;
        } else {
            currentElement += line[i];
        }
    }
    if (lastWasComma || !currentElement.isEmpty()) elements.append(currentElement);

    return elements;
}

int CSV_Helper::Get_Column_Index_By_Header(const QString &header, const QString &line) {
    QVector<QString> elements = this->Get_CSV_Elements_From_Line_As_Vector(line);
    for (int i = 0; i < elements.length(); ++i) {
        if (elements.at(i).toLower() == header.toLower()) {
            return i;
        }
    }
    return -1;
}
