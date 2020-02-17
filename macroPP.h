/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog1
    CS530, Fall 2016
*/

#ifndef MACRO_PP_H
#define MACRO_PP_H

using namespace std;

class macroPP{
public:
    macroPP(string);
    ~macroPP();
    void print_macros();
    void write_se_file();
private:
    struct macro_def{
            string label;
            string opcode;
            string operand;
            string comment;
        };
    macro_def contents;
    vector<macro_def> v_contents;
    string macroPP_filename;
    void reset_data();
    int begin_macro_def, end_macro_def, se_size;
};

#endif // MACRO_PP_H
