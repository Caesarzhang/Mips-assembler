#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include "Radix_covert.h"
#include "instruction_table.h"
#include "register_table.h"

typedef int ADDR;
typedef string BINARY_DATA;
typedef string LABEL;
vector<BINARY_DATA> memory;
string error_str;

class assembler {
private:
    const unsigned w_size = 4;
    vector<int> text_base_addr;
    vector<int> data_base_addr;
    int pc;
    int gp;
    int endvalue;
    map<LABEL, ADDR> labels;

public:
    assembler() {
        pc = 0;
        gp = 0;
    }

    void execute_parser(string filename) {
        memory.resize(50000);
        ifstream in1(filename);
        ifstream in2(filename);
        first_parser(in1);
        adjustMem();
        second_parser(in2);
    }

    void first_parser(ifstream &in) {
        bool datafield = false;
        while(!in.eof()) {
            bool isinst = true;
            string line;
            getline(in, line);
            if (line.length() == 0)
                continue;
            // Delete comments and ";"
            comments_remove(line);
            // Set the text_base_addr
            if (line.find("#baseAddre:") != string::npos ) {
                size_t pos = line.find("#baseAddre:");
                int curaddr = addr2int(line.substr(pos + 11));
                text_base_addr.push_back(curaddr);
                pc = curaddr;
                isinst = false;
                datafield = false;
            }
            // Set the data_base_addr
            if (line.find("#dataAddre:") != string::npos) {
                size_t pos = line.find("#dataAddre:");
                int curaddr = addr2int(line.substr(pos + 11));
                data_base_addr.push_back(curaddr);
                gp = curaddr;
                isinst = false;
                datafield = true;
            }
            // Recognize label
            if(datafield == false)
                label_insert(line, pc);
            else
                label_insert(line, data_base_addr[data_base_addr.size() - 1]);
            // check if it is data segment
            // Set the addresses of ".Byte"(8 bits) datum defined.
            if (line.find(".byte") != string::npos || line.find(".BYTE") != string::npos) {
                size_t pos = line.find(".byte") != string::npos ? line.find(".byte") : line.find(".BYTE");
                string datum = line.substr(pos + 5);
                string data_str;
                for (unsigned i = 0; i <= datum.length(); ++i) {
                    if (i == datum.length() && data_str.length() != 0) {
                        labels[data_str] = gp;
                        data_str.clear();
                        gp += 1;
                        break;
                    }
                    if (data_str.length() == 0 && !(isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_'))
                        continue;
                    else if (isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_') {
                        if (datum[i] == '_')
                            continue;
                        data_str.append(1, datum[i]);
                    }
                    else {
                        labels[data_str] = gp;
                        data_str.clear();
                        --i;
                        gp += 1;
                    }
                }
                isinst = false;
            }
            // Set the addresses of ".HALF"(16 bits) datum defined.
            if (line.find(".half") != string::npos || line.find(".HALF") != string::npos) {
                size_t pos = line.find(".half") != string::npos ? line.find(".half") : line.find(".HALF");
                string datum = line.substr(pos + 5);
                string data_str;
                for (unsigned i = 0; i <= datum.length(); ++i) {
                    if (i == datum.length() && data_str.length() != 0) {
                        labels[data_str] = gp;
                        data_str.clear();
                        gp += 2;
                        break;
                    }
                    if (data_str.length() == 0 && !(isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_'))
                        continue;
                    else if (isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_') {
                        if (datum[i] == '_')
                            continue;
                        data_str.append(1, datum[i]);
                    }
                    else {
                        labels[data_str] = gp;
                        data_str.clear();
                        --i;
                        gp += 2;
                    }
                }
                isinst = false;
            }
            // Set the addresses of ".WORD"(32 bits) datum defined.
            if (line.find(".word") != string::npos || line.find(".WORD") != string::npos) {
                size_t pos = line.find(".word") != string::npos ? line.find(".word") : line.find(".WORD");
                string datum = line.substr(pos + 5);
                string data_str;
                for (unsigned i = 0; i <= datum.length(); ++i) {
                    if (i == datum.length() && data_str.length() != 0) {
                        labels[data_str] = gp;
                        data_str.clear();
                        gp += 4;
                        break;
                    }
                    if (data_str.length() == 0 && !(isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_'))
                        continue;
                    else if (isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_') {
                        if (datum[i] == '_')
                            continue;
                        data_str.append(1, datum[i]);
                    }
                    else{
                        labels[data_str] = gp;
                        data_str.clear();
                        --i;
                        gp += 4;
                    }
                }
                isinst = false;
            }
            if (line.find("jalr") != string::npos || line.find("j") != string::npos
                || line.find("jr") != string::npos || line.find("beq") != string::npos
                || line.find("jr") != string::npos || line.find("beq") != string::npos
                || line.find("bltz") != string::npos || line.find("bgez") != string::npos
                || line.find("bne") != string::npos || line.find("blez") != string::npos
                || line.find("bgtz") != string::npos) {
                pc += 4;
            }
            // Set the addresses of ".EQU" const data defined.
            if (line.find(".equ") != string::npos || line.find(".EQU") != string::npos) {
                size_t pos = line.find(".equ") != string::npos ? line.find(".equ") : line.find(".EQU");
                string datum = line.substr(pos + 4);
                string data_str;
                for (unsigned i = 0; i < datum.length(); ++i) {
                    if (isalpha(datum[i]) || isdigit(datum[i]) || datum[i] == '_') {
                        if (datum[i] == '_')
                            continue;
                        data_str.append(1, datum[i]);
                    }
                }
                labels[data_str] = pc;
                isinst = false;
            }

            // END means the program is done.
            if (line.find(".end") != string::npos || line.find(".END") != string::npos)
                break;
            // current Address plus 1 word.
            if (line.find(";") != string::npos && isinst == true)
                pc += 4;
        }
        endvalue = gp > pc ? gp : pc;
        if (text_base_addr.size() == 0) {
            error_str.append("Error! No base address.\n");
        }
    }

    void second_parser(ifstream &in) {
        for (unsigned int i = 0; i < text_base_addr.size(); ++i) {
            string line, code, op, rs, rt, rd, shamt, imm;
            stringstream ss;
            pc = text_base_addr[i];
            getline(in, line);
            pc = text_base_addr[i];
            while (line.find(".end") == string::npos && !in.eof()) {
                comments_remove(line);
                label_remove(line);
                if (!isalpha(line[0])) {
                    getline(in, line);
                    continue;
                }
                else {
                    cout << line << endl;
                }
                for (unsigned int i = 0; i < line.length() && line[i] != ' ' && line[i] != ',' && line[i] != ';'; ++i)
                    op.append(1, line[i]);
                if (op.length() != 0 && instruction_table.find(op) == instruction_table.end()) {
                    error_str.append("Error! instruciton \'" + op + "\' not found\n");
                    return;
                }
                // 3 + 1 + 1 + 2 + 1 + 4 + 10 = 22 instructions included. (R - Type)
                if (instruction_table[op].size() == 6) {
                    int cnt = 0;
                    for (unsigned int i = 0; i < line.length() && line[i] != ';'; ++i) {
                        if (line[i] == '$') {
                            while (line[i] != ',' && line[i] != ' ' && line[i] != ';') {
                                switch (cnt) {
                                case 0: rd.append(1, line[i]); break;
                                case 1: rs.append(1, line[i]); break;
                                case 2: rt.append(1, line[i]); break;
                                }
                                i++;
                            }
                            cnt++;
                        }
                        else if (isdigit(line[i])) {
                            while (line[i] != ',' && line[i] != ' ' && line[i] != ';') {
                                shamt.append(1, line[i]);
                                i++;
                            }
                        }
                    }
                    // 3 instruction included
                    if (instruction_table[op][4] == "shamt") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + "00000"
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + unsignExt(str2bin(shamt), 5)
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch(int){
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }

                    // 1 instruction included
                    else if (instruction_table[op][1] == "4") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + "00100"
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 1 instruction included
                    else if (op == "jalr") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + "00000"
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                            pc += 4;
                            code.assign(32, '0');
                            cout << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }

                    }
                    // 2 instruction included
                    else if (instruction_table[op][1] == "0" && instruction_table[op][2] == "0"
                        && instruction_table[op][3] != "0" && instruction_table[op][4] == "0") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + "00000"
                                + " " + "00000"
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 1 instruction included
                    else if (instruction_table[op][1] == "0" && instruction_table[op][2] != "0"
                        && instruction_table[op][3] != "0" && instruction_table[op][4] == "0") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + "00000"
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 4 instruction included
                    else if (instruction_table[op][1] != "0" && instruction_table[op][2] != "0"
                        && instruction_table[op][3] == "0" && instruction_table[op][4] == "0") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + "00000"
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 10 instructions included
                    else if (instruction_table[op][4] == "0" && instruction_table[op][1] != "0"
                        && instruction_table[op][3] != "0" && instruction_table[op][2] != "0") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + unsignExt(int2bin(register_table[rt]), 5)
                                + " " + unsignExt(int2bin(register_table[rd]), 5)
                                + " " + "00000"
                                + " " + unsignExt(str2bin(instruction_table[op][5]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                }
                // 7 + 8 + 6 + 1 + 3 = 25 instructions included.
                else if (instruction_table[op].size() == 4) {
                    int cnt = 0;
                    for (unsigned int i = 0; i < line.length() && line[i] != ';'; ++i) {
                        if (line[i] == '$') {
                            while (line[i] != ',' && line[i] != ' ' && line[i] != ';' && line[i] != ')') {
                                switch (cnt) {
                                case 0: rt.append(1, line[i]); break;
                                case 1: rs.append(1, line[i]); break;
                                }
                                i++;
                            }
                            cnt++;
                        }
                        else if (line.substr(i).find("($") != string::npos && cnt == 1)
                            while (line[i] != '(') {
                                if (isdigit(line[i]))
                                    imm.append(1, line[i]);
                                i++;
                            }
                        else if ((isalpha(line[i]) || isdigit(line[i]) || line[i] == '-') && cnt > 0) {
                            while (line[i] != ',' && line[i] != ' ' && line[i] != ';') {
                                imm.append(1, line[i]);
                                i++;
                            }
                        }
                    }
                    //  7 ALU imm instruction included
                    if (instruction_table[op][3] == "imm" && instruction_table[op][1] == "rs") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + " " + unsignExt(int2bin(register_table[rs]), 5)
                                + " " + unsignExt(int2bin(register_table[rt]), 5)
                                + " " + signExt(str2bin(imm), 16);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    //	8 address-of instruction // lw $t5,14($zero);
                    else if (instruction_table[op][3] == "offset") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + unsignExt(int2bin(register_table[rs]), 5)
                                + unsignExt(int2bin(register_table[rt]), 5)
                                + unsignExt(str2bin(imm), 16);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 6 branch instruction beq $t2,$t5, start_A;
                    else if (instruction_table[op][3] == "label") {
                        try {
                            int rs_val;
                            if (labels.find(imm) != labels.end())
                                imm = int2bin((labels[imm] - (pc + 4)) >> 2);
                            else
                                imm = str2bin(imm);
                            if (instruction_table[op][2] != "rt")
                                rs_val = addr2int(instruction_table[op][2]);
                            else
                                rs_val = register_table[rs];
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + unsignExt(int2bin(register_table[rt]), 5)
                                + unsignExt(int2bin(rs_val), 5)
                                + signExt(imm, 16);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                            pc += 4;
                            memory[pc] = "00000000";
                            memory[pc + 1] = "00000000";
                            memory[pc + 2] = "00000000";
                            memory[pc + 3] = "00000000";
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // lui $t1, 0x02;
                    else if (op == "lui") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + "00000"
                                + unsignExt(int2bin(register_table[rt]), 5)
                                + signExt(str2bin(imm), 16);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }
                    }
                    // 3 R-Type
                    else if (instruction_table[op][2] == "0") {
                        try {
                            code = unsignExt(str2bin(instruction_table[op][0]), 6)
                                + unsignExt(int2bin(register_table[rt]), 5)
                                + "000000000000000"
                                + signExt(str2bin(instruction_table[op][3]), 6);
                            cout << pc << " " << code << endl;
                            getclean(code);
                            memory[pc] = code.substr(0, 8);
                            memory[pc + 1] = code.substr(8, 8);
                            memory[pc + 2] = code.substr(16, 8);
                            memory[pc + 3] = code.substr(24, 8);
                            if (op == "jr") {
                                pc += 4;
                                memory[pc] = "00000000";
                                memory[pc + 1] = "00000000";
                                memory[pc + 2] = "00000000";
                                memory[pc + 3] = "00000000";
                            }
                        }
                        catch (int) {
                            error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                            return;
                        }

                    }
                }
                // 2 instruction included
                else if (op == "j" || op == "jal") {
                    try {
                        string target;
                        string tmp = line.substr(op.length());
                        for (unsigned int i = 0; i < tmp.length(); ++i)
                            if ((isdigit(tmp[i]) || isalpha(tmp[i])) && tmp[i] != ' ' &&  tmp[i] != ';' && tmp[i] != ',')
                                target.append(1, tmp[i]);
                        if (labels.find(target) != labels.end())
                            target = int2bin((labels[target] << 4) >> 6);
                        else
                            target = str2bin(target);
                        code = unsignExt(str2bin(instruction_table[op][0]), 6)
                            + unsignExt(target, 26);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                        pc += 4;
                        getclean(code);
                        memory[pc] = "00000000";
                        memory[pc + 1] = "00000000";
                        memory[pc + 2] = "00000000";
                        memory[pc + 3] = "00000000";
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "eret") {
                    try {
                        code = unsignExt(str2bin(instruction_table[op][0]), 6)
                            + "1"
                            + unsignExt("0", 19)
                            + unsignExt(str2bin(instruction_table[op][3]), 6);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "syscall") {
                    try {
                        code = unsignExt(str2bin(instruction_table[op][0]), 6)
                            + unsignExt("0", 20)
                            + unsignExt(str2bin(instruction_table[op][2]), 6);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "break") {
                    try {
                        code = unsignExt(str2bin(instruction_table[op][0]), 6)
                            + unsignExt("0", 20)
                            + unsignExt(str2bin(instruction_table[op][2]), 6);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "la") {
                    try {
                        line = line.substr(2);
                        for (unsigned int i = 0; i < line.length() && line[i] != ';'; ++i) {
                            if (line[i] == '$') {
                                while (line[i] != ',' && line[i] != ' ' && line[i] != ';' && line[i] != ')') {
                                    rt.append(1, line[i]);
                                    i++;
                                }
                            }
                            else if ((isalpha(line[i]) || isdigit(line[i]) || line[i] == '_')) {
                                while (line[i] != ',' && line[i] != ' ' && line[i] != ';') {
                                    imm.append(1, line[i]);
                                    i++;
                                }
                            }
                        }
                        imm = signExt(int2bin(labels[imm] - pc), 32);
                        // lui rt, high(imm)
                        code = string("001111")
                            + " " + "00000"
                            + " " + unsignExt(int2bin(register_table[rt]), 5)
                            + " " + imm.substr(0, 16);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                        pc += 4;
                        code = string("001101")
                            + " " + unsignExt(int2bin(register_table[rt]), 5)
                            + " " + unsignExt(int2bin(register_table[rt]), 5)
                            + " " + imm.substr(16, 16);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "move") {
                    try {
                        int cnt = 0;
                        string rdest, rsrc;
                        for (unsigned int i = 0; i < line.length() && line[i] != ';'; ++i)
                            if (line[i] == '$') {
                                while (line[i] != ',' && line[i] != ' ' && line[i] != ';' && line[i] != ')') {
                                    if (cnt == 0) {
                                        rdest.append(1, line[i]);
                                        cnt += 0;
                                    }
                                    else
                                        rsrc.append(1, line[i]);
                                    i++;
                                }
                            }
                        code = string("000000")
                            + unsignExt(int2bin(register_table[rsrc]), 5)
                            + unsignExt(int2bin(register_table["$zero"]), 5)
                            + unsignExt(int2bin(register_table[rdest]), 5)
                            + "100000";
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                else if (op == "li") {
                    try {
                        line = line.substr(2);
                        for (unsigned int i = 0; i < line.length() && line[i] != ';'; ++i) {
                            if (line[i] == '$') {
                                while (line[i] != ',' && line[i] != ' ' && line[i] != ';' && line[i] != ')') {
                                    rt.append(1, line[i]);
                                    i++;
                                }
                            }
                            else if ((isalpha(line[i]) || isdigit(line[i]) || line[i] == '_')) {
                                while (line[i] != ',' && line[i] != ' ' && line[i] != ';') {
                                    imm.append(1, line[i]);
                                    i++;
                                }
                            }
                        }
                        if (labels.find(imm) != labels.end())
                            imm = signExt(int2bin(labels[imm] - pc), 32);
                        else
                            imm = signExt(str2bin(imm), 32);
                        // lui rt, high(imm)
                        code = string("001111")
                            + " " + "00000"
                            + " " + unsignExt(int2bin(register_table[rt]), 5)
                            + " " + imm.substr(0, 16);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                        pc += 4;
                        code = string("001101")
                            + " " + unsignExt(int2bin(register_table["$at"]), 5)
                            + " " + unsignExt(int2bin(register_table["$at"]), 5)
                            + " " + imm.substr(16, 16);
                        cout << pc << " " << code << endl;
                        getclean(code);
                        memory[pc] = code.substr(0, 8);
                        memory[pc + 1] = code.substr(8, 8);
                        memory[pc + 2] = code.substr(16, 8);
                        memory[pc + 3] = code.substr(24, 8);
                    }
                    catch (int) {
                        error_str.append("Error: In instruction \'" + op + "\' illegal statement");
                        return;
                    }
                }
                if (line.find(";"))
                    pc += 4;
                // clear the string stream
                code.clear();
                imm.clear();
                shamt.clear();
                op.clear();
                rs.clear();
                rt.clear();
                rd.clear();
                getline(in, line);
            }
        }
    }
    // Insert label into symbol table
    void label_insert(string &line, unsigned int pc) {
        string label;
        if (line.find(":") != string::npos) {
            for (unsigned i = 0; line[i] != ':'; ++i) {
                if (isalpha(line[i]) || isdigit(line[i]) || line[i] == '_')
                    label.append(1, line[i]);
            }
            labels[label] = pc;
        }
    }
    // Delete comments
    void comments_remove(string &line) {
        size_t p;
        p = line.find("//");
        if (p != string::npos)
            line.erase(p, line.length() - p);
    }

    void label_remove(string &line) {
        if (line.find(":") != string::npos)
            line.erase(0, line.find(":") + 1);
        for (unsigned int i = 0; i < line.length() && !isalpha(line[0]); ++i)
            if (line[i] == ' ')
                line.erase(i--, 1);

    }

    void adjustMem() {
        for (int i = 0; i < gp; ++i)
            memory[i] = unsignExt("0", 8);
        map<LABEL, ADDR>::iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if(iter->first.find("0x") != string::npos || iter->first.find("0X") != string::npos)
                if(iter->first.length() < 6)
                    memory[iter->second] = signExt(str2bin(iter->first), 8);
                else if(iter->first.length() < 10) {
                    memory[iter->second] = signExt(str2bin(iter->first), 16).substr(0, 8);
                    memory[iter->second + 1] = signExt(str2bin(iter->first), 16).substr(8, 8);
                }
                else{
                    string item = signExt(str2bin(iter->first), 32);
                    memory[iter->second] = item.substr(0, 8);
                    memory[iter->second + 1] = item.substr(8, 8);
                    memory[iter->second + 2] = item.substr(16, 8);
                    memory[iter->second + 3] = item.substr(24, 8);
                }
        }

    }

    int end() {
        return endvalue;
    }

    void outputCoe(ofstream &coe) {
        coe << "memory_initialization_radix = 16;" << endl <<
            "memory_initialization_vector =" << endl;
        for (int i = 0; i < end(); ++i) {
            coe << bin2hex(memory[i]);
            if ((i + 1) % 4 == 0) {
                if (i == end() - 1)
                    coe << ";";
                else
                    coe << ", ";
            }
            if ((i + 1) % 32 == 0)
                coe << endl;
        }
    }

    void outputBin(ofstream &bin) {
        for (int i = 0; i < end(); ++i) {
            bin << memory[i];
            if ((i + 1) % 4 == 0) {
                bin << endl;
            }
        }
    }
};

class disassembler {
private:
    vector<string> code;
    vector<string> inst;
    map<string, int> label_index;
    int cnt = 0;
    int zerocnt = 0;
    bool begin = false;

public:
    string execute(ifstream &in, ofstream &Asm, int flag) {
		try {
			if (flag == 1)
				open_bin(in);
			else
				open_coe(in);
		}
		catch (int) {
			if (flag == 1)
				return string("Open .bin failed");
			else
				return string("Open .coe failed");
		}

		try {
			inst_generate();
		}
		catch (int) {
			return string("Instruction generate failed.");
		}

		try {
			outputasm(Asm);
		}
		catch (int) {
			return string("Write into .asm failed.");
		}
		return string("ok");
    }

	void open_coe(ifstream &in) {
		string line;
		string tmp;
		while (!in.eof()) {
			getline(in, line);
			if (line.find("memory") != string::npos)
				continue;
			for (unsigned int i = 0; i < line.length(); ++i) {
				if (isdigit(line[i]) || isalpha(line[i]))
					while (isdigit(line[i]) || isalpha(line[i]))
						tmp.append(1, line[i++]);
				if (tmp.length() > 0) {
					code.push_back(unsignExt(str2bin(tmp.insert(0, "0x")), 32));
					tmp.clear();
				}
			}
		}
	}

    void open_bin(ifstream &in) {
        string line;
        while (!in.eof()) {
            getline(in, line);
            for(unsigned int i = 0; i < line.length(); ++i)
                if(line[i] != '0' && line[i] != '1')
                    line.erase(i, 1);
            if (line.length() > 0)
                code.push_back(line);
        }
    }

    void inst_generate() {
        stringstream ss;
        string tmp, op_str, label, imm, target;
        for (unsigned int i = 0; i <= code.size() - 1; ++i) {
            if (code[i] == unsignExt(string("0"), 32)) {
                zerocnt++;
                if (zerocnt > 10)
                    break;
                continue;
            }
            zerocnt = 0;
            if (code[i].substr(0, 6) == "010000" && code[i].substr(26, 6) == "011000")
                tmp.append("eret");
            else if (code[i].substr(0, 6) == "000000" && code[i].substr(26, 6) == "001101")
                tmp.append("break");
            else if (code[i].substr(0, 6) == "000000" && code[i].substr(26, 6) == "001100")
                tmp.append("syscall");
            else if (code[i].substr(0, 6) == "000000") {
                op_str = reverse_table[code[i].substr(0, 6) + "+" + code[i].substr(26, 6)];
                tmp.append(op_str + " ");
                if (instruction_table[op_str].size() == 6 && instruction_table[op_str][4] == "shamt") {
                    tmp.append(reverse_reg[code[i].substr(16, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    tmp.append(string("0x") + bin2hex(code[i].substr(21, 5)));
                }
                else if (op_str == "jalr") {
                    tmp.append(reverse_reg[code[i].substr(16, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(6, 5)]);
                }
                else if (op_str == "jr") {
                    tmp.append(reverse_reg[code[i].substr(6, 5)]);
                }
                else if (op_str == "div" || op_str == "divu" || op_str == "mult" || op_str == "multu") {
                    tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(11, 5)]);
                }
                else if (op_str == "mfhi" || op_str == "mflo") {
                    tmp.append(reverse_reg[code[i].substr(16, 5)] + ", ");
                }
                else if (op_str == "mthi" || op_str == "mtlp") {
                    tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                }
                else if (op_str == "mfc0") {
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(16, 5)]);
                }
                else if (op_str == "mtc0") {
                    tmp.append(reverse_reg[code[i].substr(16, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(11, 5)]);
                }
                else {
                    if (instruction_table[op_str][3] == "rd")
                        tmp.append(reverse_reg[code[i].substr(16, 5)] + ", ");
                    if (instruction_table[op_str][1] == "rs")
                        tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                    if (instruction_table[op_str][2] == "rt")
                        tmp.append(reverse_reg[code[i].substr(11, 5)]);
                }
            }
            else {
                string tmpcnt;
                ss << cnt;
                ss >> tmpcnt;
                op_str = reverse_table[code[i].substr(0, 6)];
                tmp.append(op_str + " ");
                if (op_str == "beq" || op_str == "bne") {
                    imm = code[i].substr(16, 16);
                    int addr = 1 + i + hex2int(bin2hex(imm));
                    tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    if (label_exist(addr) != "false") {
                        label = label_exist(addr);
                        tmp.append(label);
                    }
                    else {
                        label = string("label_") + tmpcnt;
                        cnt++;
                        tmp.append(label);
                        label_index[label] = addr;
                    }
                }
                else if (op_str == "bgez" || op_str == "bgtz" || op_str == "blez" || op_str == "bltz") {
                    imm = code[i].substr(16, 16);
                    int addr = 1 + i + hex2int(bin2hex(imm));
                    tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                    if (label_exist(addr) != "false") {
                        label = label_exist(addr);
                        tmp.append(label);
                    }
                    else {
                        label = string("label_") + tmpcnt;
                        tmp.append(label);
                        cnt++;
                        label_index[label] = addr;
                    }
                }
                else if (op_str == "j" || op_str == "jal") {
                    target = code[i].substr(6, 26);
                    int addr = hex2int(bin2hex(target));
                    if (label_exist(addr) != "false") {
                        label = label_exist(addr);
                        tmp.append(label);
                    }
                    else{
                        label = string("label_") + tmpcnt;
                        tmp.append(label);
                        cnt++;
                        label_index[label] = addr;
                    }
                }
                else if (op_str == "lui") {
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    tmp.append(string("0x") + bin2hex(code[i].substr(16, 16)));
                }
                else if (instruction_table[op_str].size() == 4 && instruction_table[op_str][3] == "imm") {
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    tmp.append(reverse_reg[code[i].substr(6, 5)] + ", ");
                    tmp.append(string("0x") + bin2hex(code[i].substr(16, 16)));
                }
                else if (instruction_table[op_str].size() == 4 && instruction_table[op_str][3] == "offset") {
                    string addr;
                    tmp.append(reverse_reg[code[i].substr(11, 5)] + ", ");
                    imm = code[i].substr(16, 16);
                    ss.clear();
                    ss << hex2int(bin2hex(imm));
                    ss >> addr;
                    tmp.append(addr);
                    tmp.append(string("(") + reverse_reg[code[i].substr(6, 5)] + ")");
                }
            }
            inst.push_back(tmp);
            ss.clear();
            tmp.clear();
        }
        label_insert();
    }

    string label_exist(int addr) {
        map<string, int>::iterator iter;
        for (iter = label_index.begin(); iter != label_index.end(); iter++)
            if (iter->second == addr)
                return iter->first;
        return string("false");
    }

    void label_insert() {
        map<string, int>::iterator iter;
		for (iter = label_index.begin(); iter != label_index.end(); iter++) {
			if (iter->second < inst.size()){
				inst[iter->second].insert(0, iter->first + ":\n    ");
			}
			else {
				cout << "Label index out of range!" << endl;
			}
		}
    }

    void outputasm(ofstream& ou) {
        string op;
        for (unsigned int i = 0; i < inst.size(); ++i) {
            if (inst[i] == unsignExt(string("0"), 32))
                continue;
            for (unsigned int j = 0; isalpha(inst[i][j]); ++j)
                op.append(1, inst[i][j]);
            if (inst[i].find("label") != string::npos && instruction_table.find(op) == instruction_table.end())
                ou << inst[i] << endl;
            else
                ou << "    " << inst[i] << endl;
            op.clear();
        }
    }
};


// int main() {
// 	assembler p;
// 	p.execute_parser(string("test.txt"));
// 	ofstream coe("ans.coe");
// 	ofstream bin("ans.bin");
// 	disassembler d;
// 	p.outputCoe(coe);
// 	p.outputBin(bin);
// 	ifstream in("ans.bin");
// 	ofstream Asm("ans.asm");
// 	d.open_bin(in);
// 	d.inst_generate();
// 	d.outputasm(Asm);
// 	return 0;
// }
