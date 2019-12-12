/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog3
    CS530, Fall 2016
*/

#ifndef FILE_PARSE_EXCEPTION_H
#define FILE_PARSE_EXCEPTION_H
#include <string>

using namespace std;

class file_parse_exception {

public:
    file_parse_exception(string s) {    // us a string streamer to write throw file_parse_exception("Bad token in line" + line_number);
        message = s;
        }

    file_parse_exception() {
        message = "An error has occurred";
        }

    string getMessage() {
        return message;
    }

private:
    string message;
};
#endif


