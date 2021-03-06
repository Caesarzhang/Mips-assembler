#include <map>
#include <string>
using namespace std;

static std::map<string, unsigned int> register_table{
	{ "$zero", 0 },
	{ "$at", 1 },

	{ "$v0", 2 },
	{ "$v1", 3 },

	{ "$a0", 4 },
	{ "$a1", 5 },
	{ "$a2", 6 },
	{ "$a3", 7 },

	{ "$t0", 8 },
	{ "$t1", 9 },
	{ "$t2", 10 },
	{ "$t3", 11 },
	{ "$t4", 12 },
	{ "$t5", 13 },
	{ "$t6", 14 },
	{ "$t7", 15 },

	{ "$s0", 16 },
	{ "$s1", 17 },
	{ "$s2", 18 },
	{ "$s3", 19 },
	{ "$s4", 20 },
	{ "$s5", 21 },
	{ "$s6", 22 },
	{ "$s7", 23 },

	{ "$t8", 24 },
	{ "$t9", 25 },

	{ "$k0", 26 },
	{ "$k1", 27 },

	{ "$gp", 28 },
	{ "$sp", 29 },
	{ "$fp", 30 },
	{ "$ra", 31 }

};

static std::map<string, string> reverse_reg{
	{ "00000", "$zero"},
	{ "00001", "$at" },

	{ "00010", "$v0" },
	{ "00011", "$v1" },

	{ "00100", "$a0" },
	{ "00101", "$a1" },
	{ "00110", "$a2" },
	{ "00111", "$a3" },

	{ "01000", "$t0" },
	{ "01001", "$t1" },
	{ "01010", "$t2" },
	{ "01011", "$t3" },
	{ "01100", "$t4" },
	{ "01101", "$t5" },
	{ "01110", "$t6" },
	{ "01111", "$t7" },

	{ "10000", "$s0" },
	{ "10001", "$s1" },
	{ "10010", "$s2" },
	{ "10011", "$s3" },
	{ "10100", "$s4" },
	{ "10101", "$s5" },
	{ "10110", "$s6" },
	{ "10111", "$s7" },

	{ "11000", "$t8" },
	{ "11001", "$t9" },

	{ "11010", "$k0" },
	{ "11011", "$k1" },

	{ "11100", "$gp" },
	{ "11101", "$sp" },
	{ "11110", "$fp" },
	{ "11111", "$ra" }
};

