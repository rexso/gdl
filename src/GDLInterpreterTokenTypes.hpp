#ifndef INC_GDLInterpreterTokenTypes_hpp_
#define INC_GDLInterpreterTokenTypes_hpp_

/* $ANTLR 2.7.6 (20071205): "gdlc.i.g" -> "GDLInterpreterTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API GDLInterpreterTokenTypes {
#endif
	enum {
		EOF_ = 1,
		ALL = 4,
		ASSIGN = 5,
		ASSIGN_INPLACE = 6,
		ASSIGN_REPLACE = 7,
		ASSIGN_ARRAYEXPR_MFCALL = 8,
		ARRAYDEF = 9,
		ARRAYDEF_CONST = 10,
		ARRAYIX = 11,
		ARRAYIX_ALL = 12,
		ARRAYIX_ORANGE = 13,
		ARRAYIX_RANGE = 14,
		ARRAYIX_ORANGE_S = 15,
		ARRAYIX_RANGE_S = 16,
		ARRAYEXPR = 17,
		ARRAYEXPR_FN = 18,
		ARRAYEXPR_MFCALL = 19,
		BLOCK = 20,
		BREAK = 21,
		CSBLOCK = 22,
		CONTINUE = 23,
		COMMONDECL = 24,
		COMMONDEF = 25,
		CONSTANT = 26,
		DEREF = 27,
		ELSEBLK = 28,
		EXPR = 29,
		FOR = 30,
		FOR_STEP = 31,
		FOREACH = 32,
		FCALL = 33,
		FCALL_LIB = 34,
		FCALL_LIB_RETNEW = 35,
		IF_ELSE = 36,
		KEYDECL = 37,
		KEYDEF = 38,
		KEYDEF_REF = 39,
		KEYDEF_REF_CHECK = 40,
		KEYDEF_REF_EXPR = 41,
		LABEL = 42,
		MPCALL = 43,
		MPCALL_PARENT = 44,
		MFCALL = 45,
		MFCALL_LIB = 46,
		MFCALL_LIB_RETNEW = 47,
		MFCALL_PARENT = 48,
		MFCALL_PARENT_LIB = 49,
		MFCALL_PARENT_LIB_RETNEW = 50,
		NOP = 51,
		NSTRUC = 52,
		NSTRUC_REF = 53,
		ON_IOERROR_NULL = 54,
		PCALL = 55,
		PCALL_LIB = 56,
		PARADECL = 57,
		PARAEXPR = 58,
		POSTDEC = 59,
		POSTINC = 60,
		DECSTATEMENT = 61,
		INCSTATEMENT = 62,
		REF = 63,
		REF_CHECK = 64,
		REF_EXPR = 65,
		RETURN = 66,
		RETF = 67,
		RETP = 68,
		STRUC = 69,
		SYSVAR = 70,
		UMINUS = 71,
		VAR = 72,
		VARPTR = 73,
		IDENTIFIER = 74,
		AND_OP = 75,
		BEGIN = 76,
		CASE = 77,
		COMMON = 78,
		COMPILE_OPT = 79,
		DO = 80,
		ELSE = 81,
		END = 82,
		ENDCASE = 83,
		ENDELSE = 84,
		ENDFOR = 85,
		ENDFOREACH = 86,
		ENDIF = 87,
		ENDREP = 88,
		ENDSWITCH = 89,
		ENDWHILE = 90,
		EQ_OP = 91,
		FORWARD = 92,
		FUNCTION = 93,
		GE_OP = 94,
		GOTO = 95,
		GT_OP = 96,
		IF = 97,
		INHERITS = 98,
		LE_OP = 99,
		LT_OP = 100,
		MOD_OP = 101,
		NE_OP = 102,
		NOT_OP = 103,
		OF = 104,
		ON_IOERROR = 105,
		OR_OP = 106,
		PRO = 107,
		REPEAT = 108,
		SWITCH = 109,
		THEN = 110,
		UNTIL = 111,
		WHILE = 112,
		XOR_OP = 113,
		METHOD = 114,
		COMMA = 115,
		COLON = 116,
		END_U = 117,
		EQUAL = 118,
		DEC = 119,
		INC = 120,
		AND_OP_EQ = 121,
		ASTERIX_EQ = 122,
		EQ_OP_EQ = 123,
		GE_OP_EQ = 124,
		GTMARK_EQ = 125,
		GT_OP_EQ = 126,
		LE_OP_EQ = 127,
		LTMARK_EQ = 128,
		LT_OP_EQ = 129,
		MATRIX_OP1_EQ = 130,
		MATRIX_OP2_EQ = 131,
		MINUS_EQ = 132,
		MOD_OP_EQ = 133,
		NE_OP_EQ = 134,
		OR_OP_EQ = 135,
		PLUS_EQ = 136,
		POW_EQ = 137,
		SLASH_EQ = 138,
		XOR_OP_EQ = 139,
		MEMBER = 140,
		LBRACE = 141,
		RBRACE = 142,
		SLASH = 143,
		LSQUARE = 144,
		RSQUARE = 145,
		SYSVARNAME = 146,
		EXCLAMATION = 147,
		LCURLY = 148,
		RCURLY = 149,
		CONSTANT_HEX_BYTE = 150,
		CONSTANT_HEX_LONG = 151,
		CONSTANT_HEX_LONG64 = 152,
		CONSTANT_HEX_INT = 153,
		CONSTANT_HEX_I = 154,
		CONSTANT_HEX_ULONG = 155,
		CONSTANT_HEX_ULONG64 = 156,
		CONSTANT_HEX_UI = 157,
		CONSTANT_HEX_UINT = 158,
		CONSTANT_BYTE = 159,
		CONSTANT_LONG = 160,
		CONSTANT_LONG64 = 161,
		CONSTANT_INT = 162,
		CONSTANT_I = 163,
		CONSTANT_ULONG = 164,
		CONSTANT_ULONG64 = 165,
		CONSTANT_UI = 166,
		CONSTANT_UINT = 167,
		CONSTANT_OCT_BYTE = 168,
		CONSTANT_OCT_LONG = 169,
		CONSTANT_OCT_LONG64 = 170,
		CONSTANT_OCT_INT = 171,
		CONSTANT_OCT_I = 172,
		CONSTANT_OCT_ULONG = 173,
		CONSTANT_OCT_ULONG64 = 174,
		CONSTANT_OCT_UI = 175,
		CONSTANT_OCT_UINT = 176,
		CONSTANT_FLOAT = 177,
		CONSTANT_DOUBLE = 178,
		CONSTANT_BIN_BYTE = 179,
		CONSTANT_BIN_LONG = 180,
		CONSTANT_BIN_LONG64 = 181,
		CONSTANT_BIN_INT = 182,
		CONSTANT_BIN_I = 183,
		CONSTANT_BIN_ULONG = 184,
		CONSTANT_BIN_ULONG64 = 185,
		CONSTANT_BIN_UI = 186,
		CONSTANT_BIN_UINT = 187,
		ASTERIX = 188,
		DOT = 189,
		STRING_LITERAL = 190,
		POW = 191,
		MATRIX_OP1 = 192,
		MATRIX_OP2 = 193,
		PLUS = 194,
		MINUS = 195,
		LTMARK = 196,
		GTMARK = 197,
		LOG_NEG = 198,
		LOG_AND = 199,
		LOG_OR = 200,
		QUESTION = 201,
		STRING = 202,
		INCLUDE = 203,
		EOL = 204,
		W = 205,
		D = 206,
		L = 207,
		H = 208,
		O = 209,
		B = 210,
		EXP = 211,
		DBL_E = 212,
		DBL = 213,
		CONSTANT_OR_STRING_LITERAL = 214,
		COMMENT = 215,
		END_MARKER = 216,
		WHITESPACE = 217,
		SKIP_LINES = 218,
		CONT_STATEMENT = 219,
		END_OF_LINE = 220,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_GDLInterpreterTokenTypes_hpp_*/
