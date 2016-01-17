#ifndef ERROR_CODES
#define ERROR_CODES

#include <QString>

namespace Error_Codes {
    enum Error_Code {
        SUCCESS = 0,
        UNABLE_TO_OPEN_ID_FILE = 1,
        UNABLE_TO_READ_ID_FILE = 2,
        UNABLE_TO_OPEN_TEMPLATE_FILE = 3,
        UNABLE_TO_READ_TEMPLATE_FILE = 4,
        UNABLE_TO_WRITE_OUTPUT_FILE = 5,
        UNABLE_TO_CREATE_OUTPUT_FILE = 6
    };

    const inline QString Get_Error_Message(int errorCode) {
        switch (errorCode) {
        case Error_Codes::SUCCESS:                           return "The new merged file was created successfully!";
        case Error_Codes::UNABLE_TO_OPEN_ID_FILE:            return "Unable to open the ID file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_READ_ID_FILE:            return "Unable to read the ID file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_OPEN_TEMPLATE_FILE:      return "Unable to open the template file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_READ_TEMPLATE_FILE:      return "Unable to read the template file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_WRITE_OUTPUT_FILE:       return "Unable to write the output file!";
        case Error_Codes::UNABLE_TO_CREATE_OUTPUT_FILE:      return "Unable to create the output file!";
        default:                                             return "An unknown error has occurred!";
        }
    }
}

#endif // ERROR_CODES

