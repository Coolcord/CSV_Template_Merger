#include "Main_Window.h"
#include "Merger.h"
#include <QApplication>
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
        if (merger.Merge()) return 0;
        else return 1;
    }

    //Improper number of command line arguments
    std::cout << argv[0] << " <ID file> <template file> <output file>" << std::endl;
    return 0;
}
