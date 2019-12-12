/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog3
    CS530, Fall 2016
*/
#include "file_parser.h"
#include "file_parse_exception.h"
#include "macroPP.h"
#include "macroPP_error_exception.h"
#include <iostream>
#include <ostream>
#include <algorithm>

using namespace std;

//int main(void){
int main(int argc, char **argv){
    if(argc != 2){
       cout << "Put the filename as the only argument." << endl;
       return 1;                       // 1 means an error, 0 means it worked
    }
    try{
        macroPP test(argv[1]);
        //macroPP test("program_2.txt");
        //macroPP test("macro_test.txt");
        //test.print_macros();
        test.write_se_file();
        cout << "MACRO PREPROCESSING COMPLETE... :D" << endl;
    }
    catch(macro_PP_exception e){
        cout << e.getMessage() << endl;
    return 0;
    }
//}
}
    macroPP::macroPP(string s){
        se_size = 0;
        num_of_macros = 0;
        found_invocation = false;
        get_macros(s);
        macro_separator();
    }
    macroPP::~macroPP(){}

    void macroPP::print_macros(){
        // print just macro defs
        /*for(int x = 0; x <= num_of_macros-1; x++){
            //cout << v_boundaries[x].start << endl;
            //cout << v_boundaries[x].endm << endl;
            begin_macro_def = v_boundaries[x].start;
            end_macro_def = v_boundaries[x].endm;
            for(int i = begin_macro_def-1; i < end_macro_def; i++){
                cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t' << v_contents[i].operand << endl;
            }
        }*/
        for(int i = 0; i < num_of_macros; i++){
            cout << v_tables[i].name << endl;
            for(int j = 0; j < v_tables[i].def_tab.size(); j++){
                cout << v_tables[i].def_tab[j].label << "\t";
                cout << v_tables[i].def_tab[j].opcode << "\t";
                cout << v_tables[i].def_tab[j].operand << "\t";
                cout << v_tables[i].def_tab[j].comment << endl;
            }
        }
    }

    void macroPP::macro_separator(){
        for(int x = 0; x <= num_of_macros-1; x++){
            begin_macro_def = v_boundaries[x].start -1;
            end_macro_def = v_boundaries[x].endm - 1;
            macros.name = v_contents[begin_macro_def].opcode;
            for(int i = begin_macro_def; i < end_macro_def; i++){
            //cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t' << v_contents[i].operand << endl;
            macros.def_tab.push_back(v_contents[i]);
            macros.inv_counter = 0;
            }
        v_tables.push_back(macros);
        macros.name = "";
        macros.def_tab.clear();
        }
    }

    void macroPP::write_se_file(){
        int begin_write_def = v_boundaries[0].start;
        int end_write_def = v_boundaries[num_of_macros-1].endm;
        int tmp = 0;
        ofstream output;
        string macroPPe_filename = macroPP_filename + "e";
        //string macroPPe_filename = "program_2_e.txt";
        //string macroPPe_filename = "macro_test_e.txt";
        output.open(macroPPe_filename.c_str());
        //if(output.is_open()){
        for(int i = 0;i < se_size; i++){
            found_invocation = false;
            if((i < begin_write_def-2) || (i > end_write_def)){
                    for(int j = 0; j < v_tables.size(); j++){
                        if(v_contents[i].opcode == v_tables[j].name){
                        v_tables[j].inv_counter++;
                        //cout << v_tables[j].inv_counter << endl;
                            process_parameters(v_contents[i].operand);
                            replace_macros(j);
                            for(int k = 0; k < v_tables[j].def_tab.size(); k++){
                                output << v_tables[j].def_tab[k].label << "\t";
                                output << v_tables[j].def_tab[k].opcode << "\t";
                                output << v_tables[j].def_tab[k].operand << endl;
                            }
                        output << "*   END OF MACRO EXPANSION" << endl;
                        found_invocation = true;
                        }
                    }if(!found_invocation && i<= v_contents.size()){
                        /*if(v_contents[i].label == "#minclude"){
                            tmp++;
                            file_parser parser(v_minclude[tmp]);
                            parser.read_file();
                            for(unsigned int i = 0; i < v_contents.size(); i++){
                                if(v_contents[i].label == "" && v_contents[i].opcode == "" && v_contents[i].operand == ""){
                                    output << v_contents[i].comment << endl;
                                } else {
                                output << v_contents[i].label << '\t' << v_contents[i].opcode << '\t';
                                output << v_contents[i].operand << '\t' << v_contents[i].comment <<'\t' << endl;
                                }
                            }
                        }*/
                        output << v_contents[i].label << "\t";
                        output << v_contents[i].opcode << "\t";
                        output << v_contents[i].operand << "\t";
                        output << v_contents[i].comment << endl;
                    }
            }
        }
        output.close();
    }

    void macroPP::replace_macros(int which_table){
    for(int l = 0; l < v_tables[which_table].def_tab.size(); l++){
        string s = v_tables[which_table].def_tab[l].operand;
        string s_label = v_tables[which_table].def_tab[l].label;
        string s_opcode = v_tables[which_table].def_tab[l].opcode;
        int where = s.find("\\");
        int where_label = s_label.find("\\");
        int where_opcode = s_opcode.find("\\");
        replace_parameter(s,where,which_table,l,"operand");
        replace_parameter(s_label,where_label,which_table,l,"label");
        replace_parameter(s_opcode,where_opcode,which_table,l,"opcode");
    }param_tab.clear();
    }

    void macroPP::replace_parameter(string s, int where, int which_table, int l, string column){
        string num_string;
        if(where != -1){
            num_string = s.substr(where+1,1);
            int num = atoi(num_string.c_str());
            if(where == 0){
                string right = s.substr(where+2);
                if(column == "label") v_tables[which_table].def_tab[l].label = param_tab[num-1] + right;
                else if (column == "opcode")v_tables[which_table].def_tab[l].opcode = param_tab[num-1] + right;
                else v_tables[which_table].def_tab[l].operand = param_tab[num-1] + right;
                //cout << "where = 0 and \\" << num << " has been replaced by: " << v_tables[which_table].def_tab[l].operand << endl;
            }else{
                if(s.substr(where+1,1) == "@"){
                    string left = s.substr(0,where-1);
                    //string right = s.substr(where+2);
                    stringstream convert;
                    convert << v_tables[which_table].inv_counter;
                    num_string = convert.str();
                    //cout << num_string << endl;
                    if(column == "label"){
                        string right = s.substr(where+2);
                        v_tables[which_table].def_tab[l].label = left + num_string + right;
                    }
                    else if (column == "opcode")v_tables[which_table].def_tab[l].opcode = left + num_string;
                    else v_tables[which_table].def_tab[l].operand = left + num_string;
                    //cout << "\@ has been replaced by: " << v_tables[which_table].def_tab[l].operand << endl;
                }else{
                    //cout << "where != 0" << endl;
                    string left = s.substr(0,where-1);
                    string right = s.substr(where+2);
                    if(column == "label")v_tables[which_table].def_tab[l].label = left + param_tab[num-1] + right;
                    else if (column == "opcode")v_tables[which_table].def_tab[l].opcode = left + param_tab[num-1] + right;
                    else v_tables[which_table].def_tab[l].operand = left + param_tab[num-1] + right;
                    //cout << "\\" << num << " has been replaced by: " << v_tables[which_table].def_tab[l].operand << endl;
                }
            }
        }
    }

    void macroPP::get_macros(string s){
    macro_boundaries macro_bound;
    macro_bound.start = 0;
    macro_bound.endm = 0;
    macroPP_filename = s;
    file_parser parser(macroPP_filename);
    parser.read_file();
    for(int i = 1; i <= parser.size(); i++){
            for(int j = 0; j < 4; j++){
                // case for #mincludes
                /*if(parser.get_token(i,j)== "#minclude"){
                   v_minclude.push_back(parser.get_token(i,j+1));
                }*/
                // begin macro definitions
                if (parser.get_token(i,j) == "macro"){
                    num_of_macros++;
                    //begin_macro_def = i;
                    macro_bound.start = i;
                    //cout << macro.start << endl;
                    //cout << macro.start << endl;
                    contents.opcode = parser.get_token(i,j-1);
                    contents.operand = parser.get_token(i,j);
                }
                // end macro definitions
                else if(parser.get_token(i,j) == "endm"){
                    //end_macro_def = i;
                    macro_bound.endm = i;
                    //cout << macro.endm << endl;
                    v_boundaries.push_back(macro_bound);
                }
                // macro defs
                else if(i >= macro_bound.start && i <= macro_bound.endm && j < 3) {
                    if(j == 0){
                        contents.label = parser.get_token(i,j);
                    }else if (j == 1){
                        contents.opcode = parser.get_token(i,j);
                    }else
                        contents.operand = parser.get_token(i,j);
                }else{
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
            }
            v_contents.push_back(contents);
            reset_data();
        }
    }

    void macroPP::process_parameters(string s){
        string delimiter = ",";
        string target = s;
        int last = target.find_first_not_of(delimiter,0);
        int first = target.find_first_of(delimiter, last);

        string parameter = target.substr(last, first-last);

        while(first != -1 || last != -1) {
            parameter = target.substr(last, first-last);
            //cout << token << endl;
            param_tab.push_back(parameter);
            last = target.find_first_not_of(delimiter,first);
            first = target.find_first_of(delimiter, last);
        }
    }

    void macroPP::reset_data() {
        se_size++;
        contents.label = "";
        contents.opcode = "";
        contents.operand = "";
    }


