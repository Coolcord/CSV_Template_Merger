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
        UNABLE_TO_CREATE_OUTPUT_FILE = 6,
        ID_FILE_SAME = 7,
        TEMPLATE_FILE_SAME = 8,
        OUTPUT_FILE_SAME = 9
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
        case Error_Codes::ID_FILE_SAME:                      return "The ID file should not be the same as the template or output files";
        case Error_Codes::TEMPLATE_FILE_SAME:                return "The template file should not be the same as the ID or output files";
        case Error_Codes::OUTPUT_FILE_SAME:                  return "Don't overwrite the ID or template files!";
        default:                                             return "An unknown error has occurred!";
        }
    }
}

#endif // ERROR_CODES

