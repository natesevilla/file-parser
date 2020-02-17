/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog1
    CS530, Fall 2016
*/
#include "file_parser.h"
#include "file_parse_exception.h"
#include "macroPP.h"
#include "macroPP_error_exception.h"
#include <iostream>
#include <ostream>

using namespace std;

int main(int argc, char **argv){
    if(argc != 2){
       cout << "Put the filename as the only argument." << endl;
       return 1;                       // 1 means an error, 0 means it worked
    }
    try{
        macroPP test(argv[1]);
        test.print_macros();
        test.write_se_file();
    }
    catch(macro_PP_exception e){
        cout << e.getMessage() << endl;
    return 0;
    }
}
    macroPP::macroPP(string s){
        macroPP_filename = s;
        file_parser parser(macroPP_filename);
        parser.read_file();
        for(int i = 1; i <= parser.size(); i++){
            for(int j = 0; j < 4; j++){
                // begin macro definitions
                if (parser.get_token(i,j) == "macro"){
                    begin_macro_def = i;
                    contents.opcode = parser.get_token(i,j-1);
                    contents.operand = parser.get_token(i,j);
                }
                // end macro definitions
                if(parser.get_token(i,j) == "endm")
                    end_macro_def = i;
                // iterates until endm
                if(i >= begin_macro_def && i <= end_macro_def && j < 3) {
                    if(j == 0){
                        contents.label = parser.get_token(i,j);
                    }else if (j == 1){
                        contents.opcode = parser.get_token(i,j);
                    }else
                        contents.operand = parser.get_token(i,j);
                }
                if(j == 0){
                    contents.label = parser.get_token(i,j);
                }else if (j == 1){
                    contents.opcode = parser.get_token(i,j);
                }else if (j == 2){
                    contents.operand = parser.get_token(i,j);
                }else{
                    contents.comment = parser.get_token(i,j);
                }
            }
            v_contents.push_back(contents);
            reset_data();
            se_size++;
        }
    }
    macroPP::~macroPP(){}

    void macroPP::print_macros(){
        // print just macro defs
        for(int i = begin_macro_def-1; i < end_macro_def; i++){
            cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t' << v_contents[i].operand << endl;
        }
        /*
        // print whole source file
        for(int i = 1; i < se_size; i++){
            cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t' << v_contents[i].operand << v_contents[i].comment << endl;
        }*/
    }

    void macroPP::write_se_file(){
        ofstream output;
        string macroPPe_filename = macroPP_filename + "e";
        output.open(macroPPe_filename);
        if(output.is_open())
        /*for(int i = 0; i < se_size; i++){
            if(i < begin_macro_def-1 || i >= end_macro_def){
                cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t' << v_contents[i].operand << '\t' < v_contents[i].comment << endl;
            }
        }*/
        for(int i = 0; i < se_size; i++){
            if(i < begin_macro_def-1 || i >= end_macro_def){
                output << v_contents[i].label + "\t";
                output << v_contents[i].opcode + "\t";
                output << v_contents[i].operand + "\t";
                output << v_contents[i].comment << endl;
            }
        }
        output.close();
    }

    void macroPP::reset_data() {
        contents.label = "";
        contents.opcode = "";
        contents.operand = "";
    }

