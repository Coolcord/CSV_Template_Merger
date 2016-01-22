#include "Main_Window.h"
#include "Merger.h"
#include "Error_Codes.h"
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QTime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qsrand((uint)QTime::currentTime().msec());

    if (argc == 1) { //GUI mode
        Main_Window w;
        w.show();
        return a.exec();
    } else if (argc == 4 || argc == 5) { //CLI mode
        bool noMessages = false;
        if (argc == 5) {
            QString noMessagesString = QString(argv[4]).toLower();
            if (noMessagesString == "--nomessages" || noMessagesString == "-nomessages") noMessages = true;
        }

        QString outputPath = QString(argv[3]);
        QFileInfo outputLocation(outputPath);
        Merger merger(argv[1], argv[2], argv[3], (outputLocation.exists() && outputLocation.isDir()));

        //Perform the merge over command line
        qDebug() << "Generating...";
        int errorCode = merger.Merge();

        #ifdef Q_OS_WIN32
        if (!noMessages) {
            if (errorCode == Error_Codes::SUCCESS || errorCode == Error_Codes::MULTIFILE_SUCCESS) {
                QMessageBox::information(a.activeWindow(), "CSV Template Merger",
                                         Error_Codes::Get_Error_Message(errorCode).toUtf8().data(), "OK");
            } else {
                QMessageBox::critical(a.activeWindow(), "CSV Template Merger",
                                         Error_Codes::Get_Error_Message(errorCode).toUtf8().data(), "OK");
            }
        }
        #else
        if (errorCode == Error_Codes::SUCCESS || errorCode == Error_Codes::MULTIFILE_SUCCESS) {
            qDebug() << Error_Codes::Get_Error_Message(errorCode).toUtf8().data();
        } else {
            qCritical() << Error_Codes::Get_Error_Message(errorCode).toUtf8().data();
        }
        #endif

        if (errorCode == Error_Codes::MULTIFILE_SUCCESS) errorCode = Error_Codes::SUCCESS;
        return errorCode;
    }

    //Improper number of command line arguments
    #ifdef Q_OS_WIN32
    QMessageBox::information(a.activeWindow(), "CSV Template Merger",
                             QString(argv[0]) + " <ID_file> <template_file> <output_location> [--nomessages]", "OK");
    #else
    qDebug() << argv[0] << " <ID_file> <template_file> <output_location> [--nomessages]";
    #endif
    return 0;
}
