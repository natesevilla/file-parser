/*  Jessica Dabu, Nathan Sevilla, Tony Peterson
    cssc0634
    Team Arizona
    prog3
    CS530, Fall 2016
*/
#include "file_parser.h"
#include "file_parse_exception.h"
#include <iostream>

using namespace std;
    // constructor
    file_parser::file_parser(string s){
        filename = s;
        number_of_lines = 0;
        delimiters = " \t\n";
        is_comment = false;
    }
    // destructor
    file_parser::~file_parser(){}

    void file_parser::read_file(){
            ifstream input;
            input.open(filename.c_str(), ios::in);
            if(!input)throw file_parse_exception("Could not open file");
            while(!input.eof()){
                reset_data();
                getline(input, line);
                number_of_lines++;
                //cout << number_of_lines << endl;
                vector<string> v;   // holds tokens for each line
                if(line != ""){
                //cout << number_of_lines << endl;
                stringstream current_line(line);

                while(!current_line.eof()){     //iterates through current line
                    getline(current_line,target);
		    target = process_tabs(target);
                    target = process_comments(target);
                    if(is_comment == true){
                        string token = target.substr(0);
                        //cout << token << endl;
                        //v.push_back(token);
                        contents.comment = token;
                    }
                    else{
                        target = process_quotes(target);

                        int last = target.find_first_not_of(delimiters,0);
                        int first = target.find_first_of(delimiters, last);

                        string token = target.substr(last, first-last);

                        int index = 0;
                        while(first != -1 || last != -1) {

                        token = target.substr(last, first-last);
                        int where = token.find("*");
                        if(where != -1) {
                            token = token.substr(0,where) + tmp[index++] + token.substr(where+1);
                        }
                        //cout << token << endl;
                        v.push_back(token);
                        last = target.find_first_not_of(delimiters,first);
                        first = target.find_first_of(delimiters, last);
                        }
                //return 0;   // from riggins algorithm

                if(v.size() >= 5){
                    string s = static_cast<ostringstream*>(&(ostringstream() << number_of_lines))->str();
                    throw file_parse_exception("Too many tokens in row " + s);
                }
                if(v.size() == 4){
                    contents.label = v[0];
                    contents.opcode = v[1];
                    contents.operand = v[2];
                    contents.comment = v[3];
                }
                else if(v.size() == 3){
                    contents.label = v[0];
                    contents.opcode = v[1];
                    contents.operand = v[2];
                }
                else if(v.size() == 2){
                    int where = v[0].find("#");
                    if(where != -1){
                        contents.label = v[0];
                        contents.opcode = v[1];
                    }
                    else {
                    contents.opcode = v[0];
                    contents.operand = v[1];
                    }
                }
                else if(v.size() == 1){
                    int where = v[0].find(":");
                    if (where != -1)
                        contents.label = v[0];
                    else
                        contents.opcode = v[0];
                }
                    }
                v.clear();

                }
    }// ends non-empty string block

                v_contents.push_back(contents);
            }
            input.close();
        }
    string file_parser::get_token(unsigned int row, unsigned int column){
        if(row >= 1 && row <= number_of_lines && 0 <= column && column <= 3){
            if(column == 0)
                return v_contents[row-1].label;
            else if(column == 1)
                return v_contents[row-1].opcode;
            else if(column == 2)
                return v_contents[row-1].operand;
            else if(column == 3)
                return v_contents[row-1].comment;
        }        // for valid inputs
        else throw file_parse_exception("ERROR: Row or column input doesnt exist");
    }

    void file_parser::print_file(){
        for(unsigned int i = 0; i < v_contents.size(); i++){
            if(v_contents[i].label == "" && v_contents[i].opcode == "" && v_contents[i].operand == ""){
            cout << v_contents[i].comment << endl;
            } else {
            cout << v_contents[i].label << '\t' << v_contents[i].opcode << '\t';
            cout << v_contents[i].operand << '\t' << v_contents[i].comment <<'\t' << endl;
            }
        }
    }

    int file_parser::size(){
        return number_of_lines;
    }

    string file_parser::process_tabs(string s){
    	if(s == "\t") {
		s = "*";
	}
	return s;
    }

    string file_parser::process_comments(string s) {
        is_comment = false;
        int where = s.find("*");
    if(where == 0){
        is_comment = true;
        //cout << s << endl;
        return s;
    }
    if (where != -1){
        string comment = s.substr(where);
        s = s.substr(0,where-1);
        contents.comment = comment;
        //cout << "Storing the comment " << comment << endl;
    }
    return s;
    }

    string file_parser::process_quotes(string s) {
        int where = s.find("\'");

        while(where != -1) {
            //int start = where;
            string one = s.substr(0,where);
            string two = s.substr(where+1);

            where = two.find("\'");

            if(where == -1) {
                cout << "ERROR" << endl;
                exit(1);
            }

            string quoted = "\'" + two.substr(0, where+1);
            two = two.substr(where+1);

            s = one + "*" + two;
            tmp.push_back(quoted);
            where = s.find("\'");
        }
        return s;
    }

    void file_parser::reset_data() {
        contents.label = "";
        contents.opcode = "";
        contents.operand = "";
        contents.comment = "";
    }


