#include <map>
#include <vector>
#include <string>
using namespace std;

static std::map<string, vector<string>> instruction_table{
	{"sll", vector<string>{ "0x00", "rs", "rt", "rd", "shamt", "0x00"}}, //*#
	{"srl", vector<string>{ "0x00", "rs", "rt", "rd", "shamt", "0x02"}}, //*#
	{"sra", vector<string>{ "0x00", "rs", "rt", "rd", "shamt", "0x03"}}, //*#
	{"jalr", vector<string>{ "0x00", "rs", "0", "rd", "0", "0x09"}},		//*#
	{"add", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x20"}},		//*#
	{"addu", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x21"}},	//*#
	{"sub", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x22"}},		//*#
	{"subu", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x23"}},	//*#
	{"and", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x24"}},		//*#
	{"or", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x25"}},		//*#
	{"xor", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x26"}},		//*#
	{"nor", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x27"}},		//*#
	{"slt", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x2a"}},		//*#
	{"sltu", vector<string>{ "0x00", "rs", "rt", "rd", "0", "0x2b"}},	//*#

	{"mfhi", vector<string>{ "0x00", "0", "0", "rd", "0", "0x10"}},		//*#
	{"mflo", vector<string>{ "0x00", "0", "0", "rd", "0", "0x12"}},		//*#
	{"mfc0", vector<string>{ "0x10", "0", "rt", "rd", "0", "0x00"}},		//*#
	{"div", vector<string>{ "0x00", "rs", "rt", "0", "0", "0x1a"}},		//*#
	{"divu", vector<string>{ "0x00", "rs", "rt", "0", "0", "0x1b"}},		//*#
	{"mult", vector<string>{ "0x00", "rs", "rt", "0", "0", "0x18"}},		//*#
	{"multu", vector<string>{ "0x00", "rs", "rt", "0", "0", "0x19"}},	//*#
	{"mtc0", vector<string>{ "0x10", "4", "rt", "rd", "0", "0x00"}},		//*#

	{"jr", vector<string>{ "0x00", "rs", "0", "0x08"}},			//*#
	{"mthi", vector<string>{ "0x00", "rs", "0", "0x11"}},		//*#
	{"mtlo", vector<string>{ "0x00", "rs", "0", "0x13"}},		//*#

	{"bltz", vector<string>{ "0x01", "rs", "0", "label"}},		//*#
	{"bgez", vector<string>{ "0x01", "rs", "1", "label"}},		//*#
	{"beq", vector<string>{ "0x04", "rs", "rt", "label"}},		//*#
	{"bne", vector<string>{ "0x05", "rs", "rt", "label"}},		//*#
	{"blez", vector<string>{ "0x06", "rs", "0", "label"}},		//*#
	{"bgtz", vector<string>{ "0x07", "rs", "0", "label"}},		//*#

	{"addi", vector<string>{ "0x08", "rs", "rt", "imm"}},			//*#
	{"addiu", vector<string>{ "0x09", "rs", "rt", "imm"}},		//*#
	{"slti", vector<string>{ "0x0a", "rs", "rt", "imm"}},		//*#
	{"sltiu", vector<string>{ "0x0b", "rs", "rt", "imm"}},		//*#
	{"andi", vector<string>{ "0x0c", "rs", "rt", "imm"}},		//*#
	{"ori", vector<string>{ "0x0d", "rs", "rt", "imm"}},			//*#
	{"xori", vector<string>{ "0x0e", "rs", "rt", "imm"}},		//*#
	{"lui", vector<string>{ "0x0f", "0", "rt", "imm"}},			//*#

	{"lb", vector<string>{ "0x20", "rs", "rt", "offset"}},		//*#
	{"lh", vector<string>{ "0x21", "rs", "rt", "offset"}},		//*#
	{"lw", vector<string>{ "0x23", "rs", "rt", "offset"}},		//*#
	{"lbu", vector<string>{ "0x24", "rs", "rt", "offset"}},		//*#
	{"lhu", vector<string>{ "0x25", "rs", "rt", "offset"}},		//*#
	{"sb", vector<string>{ "0x28", "rs", "rt", "offset"}},		//*#
	{"sh", vector<string>{ "0x29", "rs", "rt", "offset"}},		//*#
	{"sw", vector<string>{ "0x2b", "rs", "rt", "offset"}},		//*#
	{"j", vector<string>{ "0x02", "imm"}},						//*#
	{"jal", vector<string>{ "0x03", "imm"}},						//*#

	{"eret", vector<string>{ "0x10", "1", "0", "0x18"}},			//*
	{"syscall", vector<string>{ "0x00", "0", "0x0c"}},			//*
	{"break", vector<string>{ "0x00", "code", "0x0d"}},			//*

};




static std::map<string, string> reverse_table{
	{ "000000+000000", "sll" },
	{ "000000+000010", "srl" },
	{ "000000+000011", "sra" },
	{ "000000+001001", "jalr" },
	{ "000000+100000", "add" },
	{ "000000+100001", "addu" },
	{ "000000+100010", "sub" },
	{ "000000+100011", "subu" },
	{ "000000+100100", "and" },
	{ "000000+100101", "or" },
	{ "000000+100110", "xor" },
	{ "000000+100111", "nor" },
	{ "000000+101010", "slt" },
	{ "000000+101011", "sltu" },
	{ "000000+010000", "mfhi" },
	{ "000000+010010", "mflo" },
	{ "000000+011010", "div" },
	{ "000000+011011", "divu" },
	{ "010000+0", "mfc0" },
	{ "000000+011000", "mult" },
	{ "000000+011001", "multu" },
	{ "010000+4", "mtc0" },

	{ "000000+001000", "jr" },
	{ "000000+010001", "mthi" },
	{ "000000+010011", "mtlo" },

	{ "000100", "beq" },
	{ "000001", "bgez" },
	{ "000111", "bgtz" },
	{ "000110", "blez" },
	{ "000001", "bltz" },
	{ "000101", "bne" },

	{ "001000", "addi" },
	{ "001001", "addiu" },
	{ "001010", "slti" },
	{ "001011", "sltiu" },
	{ "001100", "andi" },
	{ "001101", "ori" },
	{ "001110", "xori" },
	{ "001111", "lui" },

	{ "100000", "lb" },
	{ "100100", "lbu" },
	{ "100001", "lh" },
	{ "100101", "lhu" },
	{ "100011", "lw" },
	{ "101000", "sb" },
	{ "101001", "sh" },
	{ "101011", "sw" },
	{ "000010", "j" },
	{ "000011", "jal" },

	{ "000000+001101", "break" },
	{ "010000", "eret" },
	{ "000000+001100", "syscall" },
};
