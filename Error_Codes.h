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
        OUTPUT_FILE_SAME = 9,
        UNABLE_TO_CREATE_OUTPUT_FOLDER = 10,
        UNABLE_TO_READ_OUTPUT_FOLDER = 11,
        MULTIFILE_SUCCESS = 12,
        SYNTAX_ERROR_IN_ID_FILE = 13
    };

    const inline QString Get_Error_Message(int errorCode) {
        switch (errorCode) {
        case Error_Codes::SUCCESS:                           return "The new merged file was generated successfully!";
        case Error_Codes::UNABLE_TO_OPEN_ID_FILE:            return "Unable to open the ID file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_READ_ID_FILE:            return "Unable to read the ID file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_OPEN_TEMPLATE_FILE:      return "Unable to open the template file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_READ_TEMPLATE_FILE:      return "Unable to read the template file! Try closing any programs that might be using it.";
        case Error_Codes::UNABLE_TO_WRITE_OUTPUT_FILE:       return "Unable to write the output file!";
        case Error_Codes::UNABLE_TO_CREATE_OUTPUT_FILE:      return "Unable to create the output file!";
        case Error_Codes::ID_FILE_SAME:                      return "The ID file should not be the same as the template or output files";
        case Error_Codes::TEMPLATE_FILE_SAME:                return "The template file should not be the same as the ID or output files";
        case Error_Codes::OUTPUT_FILE_SAME:                  return "Don't overwrite the ID or template files!";
        case Error_Codes::UNABLE_TO_CREATE_OUTPUT_FOLDER:    return "Unable to create the output folder!";
        case Error_Codes::UNABLE_TO_READ_OUTPUT_FOLDER:      return "Unable to read the output folder!";
        case Error_Codes::MULTIFILE_SUCCESS:                 return "The new merged files were generated successfully!";
        case Error_Codes::SYNTAX_ERROR_IN_ID_FILE:           return "The ID file is not syntatically correct! Make sure that all of the tagged columns use the correct formatting!";
        default:                                             return "An unknown error has occurred!";
        }
    }
}

#endif // ERROR_CODES

