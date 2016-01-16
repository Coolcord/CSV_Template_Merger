#ifndef MERGER_THREAD_H
#define MERGER_THREAD_H

#include <QThread>

class Merger;

class Merger_Thread : public QThread {
    Q_OBJECT

public:
    Merger_Thread(bool cli);
    Merger_Thread(bool cli, QWidget *parent);
    Merger_Thread(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool cli);
    Merger_Thread(const QString &idFileLocation, const QString &templateFileLocation, const QString &outputFileLocation, bool cli, QWidget *parent);
    ~Merger_Thread();
    void Set_ID_File_Location(const QString &idFileLocation);
    void Set_Template_File_Location(const QString &templateFileLocation);
    void Set_Output_File_Location(const QString &outputFileLocation);

signals:
    void Error_Occurred(const QString &message);
    void Information_Sent(const QString &message);

private:
    void run();

    Merger *merger;
};

#endif // MERGER_THREAD_H
