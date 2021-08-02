#pragma once

#include<unordered_map>
#include<cstdint>
#include<string>

namespace csvm {
	const std::uint32_t file_header_magic = 0xDEADFACE;
	enum class opcode : std::uint8_t {
		SUBP = 0xf0,
		DATA = 0xf1,
		NONE = 0x00,
		PLBI = 0x01,
		PHBI = 0x02,
		PLBF = 0x03,
		PHBF = 0x04,
		PDAT = 0x05,
		PUSH = 0x06,
		COPY = 0x07,
		SPOP = 0x08,
		SADD = 0x10,
		IADD = 0x11,
		DADD = 0x12,
		SSUB = 0x13,
		ISUB = 0x14,
		DSUB = 0x15,
		SMUL = 0x16,
		IMUL = 0x17,
		DMUL = 0x18,
		SDIV = 0x19,
		IDIV = 0x1a,
		DDIV = 0x1b,
		NJMP = 0x20,
		CJMP = 0x21,
		CALL = 0x22,
		RETP = 0x23,
		FEOF = 0xff,
		ERROR = 0xfe,
	};

	inline opcode ui8_to_opcode(const std::uint8_t x)
	{
		switch (x) {
		case 0xf0:
			return opcode::SUBP;
		case 0xf1:
			return opcode::DATA;
		case 0x00:
			return opcode::NONE;
		case 0x01:
			return opcode::PLBI;
		case 0x02:
			return opcode::PHBI;
		case 0x03:
			return opcode::PLBF;
		case 0x04:
			return opcode::PHBF;
		case 0x05:
			return opcode::PDAT;
		case 0x06:
			return opcode::PUSH;
		case 0x07:
			return opcode::COPY;
        case 0x08:
            return opcode::SPOP;
		case 0x10:
			return opcode::SADD;
		case 0x11:
			return opcode::IADD;
		case 0x12:
			return opcode::DADD;
		case 0x13:
			return opcode::SSUB;
		case 0x14:
			return opcode::ISUB;
		case 0x15:
			return opcode::DSUB;
		case 0x16:
			return opcode::SMUL;
		case 0x17:
			return opcode::IMUL;
		case 0x18:
			return opcode::DMUL;
		case 0x19:
			return opcode::SDIV;
		case 0x1a:
			return opcode::IDIV;
		case 0x1b:
			return opcode::DDIV;
		case 0x20:
			return opcode::NJMP;
		case 0x21:
			return opcode::CJMP;
		case 0x22:
			return opcode::CALL;
		case 0x23:
			return opcode::RETP;
		case 0xff:
			return opcode::FEOF;
		default:
			return opcode::ERROR;
		}
	}

	std::string opcode_to_string(opcode x)
	{
		switch (x) {
		case opcode::PUSH :
			return "PUSH";
		case opcode::COPY :
			return "COPY";
		case opcode::DATA :
			return "DATA";
		case opcode::SUBP :
			return "SUBP";
		case opcode::NONE :
			return "NONE";
		case opcode::PLBI :
			return "PLBI";
		case opcode::PHBI :
			return "PHBI";
		case opcode::PLBF :
			return "PLBF";
		case opcode::PHBF :
			return "PHBF";
		case opcode::PDAT :
			return "PDAT";
		case opcode::SADD :
			return "SADD";
		case opcode::IADD :
			return "IADD";
		case opcode::DADD :
			return "DADD";
		case opcode::SSUB :
			return "SSUB";
		case opcode::ISUB :
			return "ISUB";
		case opcode::DSUB :
			return "DSUB";
		case opcode::SMUL :
			return "SMUL";
		case opcode::IMUL :
			return "IMUL";
		case opcode::DMUL :
			return "DMUL";
		case opcode::SDIV :
			return "SDIV";
		case opcode::IDIV :
			return "IDIV";
		case opcode::DDIV :
			return "DDIV";
		case opcode::NJMP :
			return "NJMP";
		case opcode::CJMP :
			return "CJMP";
		case opcode::CALL :
			return "CALL";
		case opcode::RETP :
			return "RETP";
		case opcode::FEOF :
			return "FEOF";
		default:
			return "ERROR";
		}
	}

	inline std::string ui8_to_string(std::uint8_t x){
	    return opcode_to_string(ui8_to_opcode(x));
	}

	std::unordered_map<std::string, csvm::opcode> s2o = {
		{"DATA", csvm::opcode::DATA},
		{"SUBP", csvm::opcode::SUBP},
		{"NONE", csvm::opcode::NONE},
		{"PLBI", csvm::opcode::PLBI},
		{"PHBI", csvm::opcode::PHBI},
		{"PHBF", csvm::opcode::PHBF},
		{"PHBF", csvm::opcode::PHBF},
		{"PDAT", csvm::opcode::PDAT},
		{"PUSH", csvm::opcode::PUSH},
		{"COPY", csvm::opcode::COPY},
		{"SADD", csvm::opcode::SADD},
		{"IADD", csvm::opcode::IADD},
		{"DADD", csvm::opcode::DADD},
		{"SSUB", csvm::opcode::SSUB},
		{"ISUB", csvm::opcode::ISUB},
		{"DSUB", csvm::opcode::DSUB},
		{"SMUL", csvm::opcode::SMUL},
		{"IMUL", csvm::opcode::IMUL},
		{"DMUL", csvm::opcode::DMUL},
		{"SDIV", csvm::opcode::SDIV},
		{"IDIV", csvm::opcode::IDIV},
		{"DDIV", csvm::opcode::DDIV},
		{"NJMP", csvm::opcode::NJMP},
		{"CJMP", csvm::opcode::CJMP},
		{"CALL", csvm::opcode::CALL},
		{"RETP", csvm::opcode::RETP},
		{"FEOF", csvm::opcode::FEOF}
	};

	csvm::opcode string_to_opcode(std::string x)
	{
		return s2o.at(x);
	}
}