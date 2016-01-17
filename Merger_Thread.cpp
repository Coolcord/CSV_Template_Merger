#include "Merger_Thread.h"
#include "Merger.h"

Merger_Thread::Merger_Thread() {
    this->merger = new Merger();
}

Merger_Thread::Merger_Thread(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool multiFileMode) {
    this->merger = new Merger(idFileLocation, templateFileLocation, outputFileLocation, multiFileMode);
}

Merger_Thread::~Merger_Thread() {
    delete this->merger;
    this->merger = NULL;
}

void Merger_Thread::Set_ID_File_Location(const QString &idFileLocation) {
    this->merger->Set_ID_File_Location(idFileLocation);
}

void Merger_Thread::Set_Template_File_Location(const QString &templateFileLocation) {
    this->merger->Set_Template_File_Location(templateFileLocation);
}

void Merger_Thread::Set_Output_File_Location(const QString &outputFileLocation) {
    this->merger->Set_Output_File_Location(outputFileLocation);
}

void Merger_Thread::Set_Multi_File_Mode(bool multiFileMode) {
    this->merger->Set_Multi_File_Mode(multiFileMode);
}

void Merger_Thread::run() {
    emit this->Merge_Completed(this->merger->Merge());
}


