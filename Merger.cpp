#include "Merger.h"
#include "CSV_Helper.h"
#include "Error_Codes.h"
#include <QByteArray>
#include <QFileInfo>
#include <QMap>
#include <QMessageBox>
#include <assert.h>

Merger::Merger() {
    this->idFileLocation = QString();
    this->templateFileLocation = QString();
    this->outputFileLocation = QString();
    this->multiFileMode = true;
    this->csvHelper = new CSV_Helper();
}

Merger::Merger(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool multiFileMode) {
    this->idFileLocation = idFileLocation;
    this->templateFileLocation = templateFileLocation;
    this->outputFileLocation = outputFileLocation;
    this->multiFileMode = multiFileMode;
    this->csvHelper = new CSV_Helper();
}

int Merger::Merge() {
    //Check to see if all files are unique
    int duplicateCheckErrorCode = this->Check_For_Duplicate_Files();
    if (duplicateCheckErrorCode != Error_Codes::SUCCESS) return duplicateCheckErrorCode;

    //Open the ID file for reading
    QFile sourceFile(this->idFileLocation);
    if (!sourceFile.exists()) { //ID file does not exist
        return Error_Codes::UNABLE_TO_OPEN_ID_FILE;
    }
    if (!sourceFile.open(QFile::ReadOnly)) {
        return Error_Codes::UNABLE_TO_READ_ID_FILE;
    }

    //Open the Template file for reading
    QFile templateFile(this->templateFileLocation);
    if (!templateFile.exists()) { //template file does not exist
        sourceFile.close();
        return Error_Codes::UNABLE_TO_OPEN_TEMPLATE_FILE;
    }
    if (!templateFile.open(QFile::ReadOnly)) {
        sourceFile.close();
        return Error_Codes::UNABLE_TO_READ_TEMPLATE_FILE;
    }

    //Create a new file for output
    QFile outputFile(this->outputFileLocation);
    if (outputFile.exists()) {
        if (!outputFile.remove()) {
            return Error_Codes::UNABLE_TO_WRITE_OUTPUT_FILE;
        }
    }
    if (!outputFile.open(QFile::ReadWrite)) {
        sourceFile.close();
        templateFile.close();
        return Error_Codes::UNABLE_TO_CREATE_OUTPUT_FILE;
    }

    //Read the template headers and insert them into a hash for searching
    QString templateHeaderLine = templateFile.readLine();
    QVector<QString> templateHeaders = this->csvHelper->Get_CSV_Elements_From_Line_As_Vector(templateHeaderLine.toLower());
    QMap<QString, int> templateHeadersHash;
    for (int i = 0; i < templateHeaders.size(); ++i) {
        templateHeadersHash.insert(templateHeaders[i].toLower(), i);
    }

    //Read the source headers and determine their index in the template file
    QString sourceHeaderLine = sourceFile.readLine();
    QVector<QString> sourceHeaders = this->csvHelper->Get_CSV_Elements_From_Line_As_Vector(sourceHeaderLine.toLower());
    QVector<int> sourceIndexesInTemplate;
    QMap<int, int> sourceIndexesInTemplateHash;
    for (int i = 0; i < sourceHeaders.size(); ++i) {
        int index = -1;
        QMap<QString, int>::iterator element = templateHeadersHash.find(sourceHeaders[i].toLower());
        if (element != templateHeadersHash.end()) index = element.value();
        //Handle duplicates
        if (index != -1) {
            if (sourceIndexesInTemplateHash.contains(index)) {
                index = -1; //duplicates will just be prepended
            } else {
                sourceIndexesInTemplateHash.insert(i, index);
            }
        }
        sourceIndexesInTemplate.append(index);
    }
    assert(sourceHeaders.size() == sourceIndexesInTemplate.size());

    //Generate the header
    if (outputFile.write(QByteArray(this->Merge_Line(sourceIndexesInTemplate, sourceHeaders, sourceHeaderLine, templateHeaderLine, true).toUtf8().data())) == -1
            || outputFile.write(QByteArray(NEW_LINE.toUtf8().data())) == -1) {
        sourceFile.close();
        templateFile.close();
        outputFile.close();
        outputFile.remove();
        return Error_Codes::UNABLE_TO_CREATE_OUTPUT_FILE;
    }

    //Generate the body
    for (QString sourceLine = sourceFile.readLine(); !sourceFile.atEnd(); sourceLine = sourceFile.readLine()) {
        templateFile.reset(); //start at the beginning of the template file
        templateFile.readLine();
        for (QString templateLine = templateFile.readLine(); !templateFile.atEnd(); templateLine = templateFile.readLine()) {
            if (outputFile.write(QByteArray(this->Merge_Line(sourceIndexesInTemplate, sourceHeaders, sourceLine, templateLine, false).toUtf8().data())) == -1
                    || outputFile.write(QByteArray(NEW_LINE.toUtf8().data())) == -1) {
                sourceFile.close();
                templateFile.close();
                outputFile.close();
                outputFile.remove();
                return Error_Codes::UNABLE_TO_CREATE_OUTPUT_FILE;
            }
        }
    }

    //The merge was completed successfully
    sourceFile.close();
    templateFile.close();
    outputFile.close();

    //TODO: Add multi-file support
    return Error_Codes::SUCCESS;
}

void Merger::Set_ID_File_Location(const QString &idFileLocation) {
    this->idFileLocation = idFileLocation;
}

void Merger::Set_Template_File_Location(const QString &templateFileLocation) {
    this->templateFileLocation = templateFileLocation;
}

void Merger::Set_Output_File_Location(const QString &outputFileLocation) {
    this->outputFileLocation = outputFileLocation;
}

void Merger::Set_Multi_File_Mode(bool multiFileMode) {
    this->multiFileMode = multiFileMode;
}

QString Merger::Merge_Line(QVector<int> &sourceIndexesInTemplate, QVector<QString> &sourceHeaders, const QString sourceLine, const QString &templateLine, bool firstLine) {
    QString mergedLine = QString();
    QVector<QString> sourceElements = this->csvHelper->Get_CSV_Elements_From_Line_As_Vector(sourceLine);
    QVector<QString> templateElements = this->csvHelper->Get_CSV_Elements_From_Line_As_Vector(templateLine);

    //Add empty header elements to ensure that the source headers and elements match up
    while (firstLine && sourceHeaders.size() < sourceElements.size()) {
        sourceHeaders.append("");
    }

    //Update the template elements
    assert(sourceElements.size() == sourceIndexesInTemplate.size());
    for (int i = sourceElements.size()-1; i >= 0; --i) {
        //Insert at the beginning
        if (sourceIndexesInTemplate[i] == -1) {
            if (firstLine) { //fix the header
                templateElements.prepend(sourceHeaders[i]);
                //Fix the indexes before moving on
                for (int j = 0; j < sourceIndexesInTemplate.size(); ++j) {
                    if (sourceIndexesInTemplate[j] == -1) continue;
                    else ++sourceIndexesInTemplate[j];
                }
            } else { //add the element to the beginning of the line
                templateElements.prepend(sourceElements[i]);
            }
        } else { //replace the existing element
            //Add empty columns if necessary
            while (sourceIndexesInTemplate[i] > templateElements.size()-1) {
                templateElements.append("");
            }
            //Replace the data
            if (firstLine) {
                templateElements[sourceIndexesInTemplate[i]] = sourceHeaders[i];
            } else {
                templateElements[sourceIndexesInTemplate[i]] = sourceElements[i];
            }
        }
    }

    //Rebuild the line
    for (int i = 0; i < templateElements.size(); ++i) {
        if (i == templateElements.size()-1) { //last iteration
            mergedLine += templateElements[i];
        } else {
            mergedLine += templateElements[i] + ",";
        }
    }

    return mergedLine;
}

int Merger::Check_For_Duplicate_Files() {
    QFileInfo idFileInfo(this->idFileLocation);
    QFileInfo templateFileInfo(this->templateFileLocation);
    QFileInfo outputFileInfo(this->outputFileLocation);

    if (idFileInfo.filePath() == templateFileInfo.filePath()
            || idFileInfo.filePath() == outputFileInfo.filePath()) {
        return Error_Codes::ID_FILE_SAME;
    } else if (templateFileInfo.filePath() == outputFileInfo.filePath()) {
        return Error_Codes::TEMPLATE_FILE_SAME;
    }

    return Error_Codes::SUCCESS;
}
