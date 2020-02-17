/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog1
    CS530, Fall 2016
*/

#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "macroPP.h"
#include "macroPP_error_exception.h"

using namespace std;

class file_parser {
    public:
        // ctor, filename is the parameter.  A driver program will read
        // the filename from the command line, and pass the filename to
        // the file_parser constructor.  Filenames must not be hard-coded.
        file_parser(string);

        // dtor
        ~file_parser();

        // reads the source file, storing the information is some
        // auxiliary data structure you define in the private section.
        // Throws a file_parse_exception if an error occurs.
        // if the source code file fails to conform to the above
        // specification, this is an error condition.
        void read_file();

        // returns the token found at (row, column).  Rows and columns
        // are zero based.  Returns the empty string "" if there is no
        // token at that location. column refers to the four fields
        // identified above.
        string get_token(unsigned int, unsigned int);

        // prints the source code file to stdout.  Should not repeat
        // the exact formatting of the original, but uses tabs to align
        // similar tokens in a column. The fields should match the
        // order of token fields given above (label/opcode/operands/comments)
        void print_file();

        // returns the number of lines in the source code file
        int size();

    private:
        int number_of_lines;
        string filename;
        //string token;
        string comment;
        string line;
        string target;
        string delimiters = " \t\n";
        bool is_comment = false;
        struct parse_line{
            string label;
            string opcode;
            string operand;
            string comment;
        };
        parse_line contents;
        vector<parse_line> v_contents;
        vector<string> tmp;
        //string remove_spaces(string str);
        void reset_data();
        string process_comments(string s);
        string process_quotes(string s);

};

#endif

