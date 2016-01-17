#ifndef MERGER_THREAD_H
#define MERGER_THREAD_H

#include "Error_Codes.h"
#include <QThread>

class Merger;

class Merger_Thread : public QThread {
    Q_OBJECT

public:
    Merger_Thread();
    Merger_Thread(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation);
    ~Merger_Thread();
    void Set_ID_File_Location(const QString &idFileLocation);
    void Set_Template_File_Location(const QString &templateFileLocation);
    void Set_Output_File_Location(const QString &outputFileLocation);

signals:
    void Merge_Completed(int errorCode);

private:
    void run();

    Merger *merger;
};

#endif // MERGER_THREAD_H
