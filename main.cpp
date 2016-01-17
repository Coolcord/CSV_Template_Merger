#include "Main_Window.h"
#include "Merger.h"
#include "Error_Codes.h"
#include <QApplication>
#include <QString>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc == 1) { //GUI mode
        QApplication a(argc, argv);
        Main_Window w;
        w.show();
        return a.exec();
    } else if (argc == 4) { //CLI mode
        QApplication a(argc, argv);
        Merger merger(argv[1], argv[2], argv[3], true);

        //Perform the merge over command line
        std::cout << "Generating..." << std::endl;
        int errorCode = merger.Merge();
        if (errorCode == Error_Codes::SUCCESS) {
            std::cout << Error_Codes::Get_Error_Message(errorCode).toUtf8().data() << std::endl;
        } else {
            std::cerr << Error_Codes::Get_Error_Message(errorCode).toUtf8().data() << std::endl;
        }
        return errorCode;
    }

    //Improper number of command line arguments
    std::cout << argv[0] << " <ID file> <template file> <output file>" << std::endl;
    return 0;
}
