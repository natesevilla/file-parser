/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog3
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
    // determines boundaries of multiple macros
    struct macro_boundaries{
        int start;
        int endm;
    };
    struct macro_table{ // main macro table
        string name;
        vector<macro_def> def_tab;
        int inv_counter;
    };
    macro_def contents;
    macro_table macros;
    vector<macro_boundaries> v_boundaries;
    vector<macro_def> v_contents;
    vector<macro_table> v_tables; //holds structs of macros
    vector<string> param_tab;
    //vector<string> v_minclude;
    string macroPP_filename;
    bool found_invocation;
    void reset_data();
    void get_macros(string s);
    void macro_separator();
    void replace_macros(int which_table);
    void replace_parameter(string s, int where, int m_table, int def_table, string column);
    void process_parameters(string s);
    int begin_macro_def, end_macro_def, se_size, num_of_macros, inv_counter;
};

#endif // MACRO_PP_H

