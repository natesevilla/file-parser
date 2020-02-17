/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog1
    CS530, Fall 2016
*/

#ifndef MACRO_PP_EXCEPTION_H
#define MACRO_PP_EXCEPTION_H
#include <string>

using namespace std;

class macro_PP_exception {

public:
    macro_PP_exception(string s) {    // us a string streamer to write throw file_parse_exception("Bad token in line" + line_number);
        message = s;
        }

    macro_PP_exception() {
        message = "An error has occurred";
        }

    string getMessage() {
        return message;
    }

private:
    string message;
};
#endif


