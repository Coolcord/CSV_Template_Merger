#include "Error_Codes.h"

const static QString Error_Codes::Get_Error_Message(int error) {
    switch (error) {
    case SUCCESS:                           return "The new merged file was created successfully!";
    case UNABLE_TO_OPEN_ID_FILE:            return "Unable to open the ID file! Try closing any programs that might be using it.";
    case UNABLE_TO_READ_ID_FILE:            return "Unable to read the ID file! Try closing any programs that might be using it.";
    case UNABLE_TO_OPEN_TEMPLATE_FILE:      return "Unable to open the template file! Try closing any programs that might be using it.";
    case UNABLE_TO_READ_TEMPLATE_FILE:      return "Unable to read the template file! Try closing any programs that might be using it.";
    case UNABLE_TO_WRITE_OUTPUT_FILE:       return "Unable to write the output file!";
    case UNABLE_TO_CREATE_OUTPUT_FILE:      return "Unable to create the output file!";
    default:                                return QString();
    }
}
