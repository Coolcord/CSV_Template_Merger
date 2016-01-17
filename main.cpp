#include "Main_Window.h"
#include "Merger.h"
#include "Error_Codes.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (argc == 1) { //GUI mode
        Main_Window w;
        w.show();
        return a.exec();
    } else if (argc == 4) { //CLI mode
        Merger merger(argv[1], argv[2], argv[3]);

        //Perform the merge over command line
        qDebug() << "Generating...";
        int errorCode = merger.Merge();

        #ifdef Q_OS_WIN32
        if (errorCode == Error_Codes::SUCCESS) {
            QMessageBox::information(a.activeWindow(), "CSV Template Merger",
                                     Error_Codes::Get_Error_Message(errorCode).toUtf8().data(), "OK");
        } else {
            QMessageBox::critical(a.activeWindow(), "CSV Template Merger",
                                     Error_Codes::Get_Error_Message(errorCode).toUtf8().data(), "OK");
        }
        #else
        if (errorCode == Error_Codes::SUCCESS) {
            qDebug() << Error_Codes::Get_Error_Message(errorCode).toUtf8().data();
        } else {
            qCritical() << Error_Codes::Get_Error_Message(errorCode).toUtf8().data();
        }
        #endif
        return errorCode;
    }

    //Improper number of command line arguments
    #ifdef Q_OS_WIN32
    QMessageBox::information(a.activeWindow(), "CSV Template Merger",
                             QString(argv[0]) + " <ID_file> <template_file> <output_file>", "OK");
    #else
    qDebug() << argv[0] << " <ID_file> <template_file> <output_file>";
    #endif
    return 0;
}
