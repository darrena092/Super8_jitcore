#pragma once

#include <cstdint>

#include "Headers\Globals.h"

#define MODREGRM_RM_DISP32 5
#define MODREGRM_RM_SIB 4

enum X86Register {
	al = 0, ax = 0, eax = 0,
	cl = 1, cx = 1, ecx = 1,
	dl = 2, dx = 2, edx = 2,
	bl = 3, bx = 3, ebx = 3,
	ah = 4, sp = 4, esp = 4,
	ch = 5, bp = 5, ebp = 5,
	dh = 6, si = 6, esi = 6,
	bh = 7, di = 7, edi = 7
};

class Chip8Engine_CodeEmitter_x86 : ILogComponent 
{
public:
	Chip8Engine_CodeEmitter_x86();
	~Chip8Engine_CodeEmitter_x86();

	std::string getComponentName();

	// DYNAREC HELPER FUNCTIONS
#ifdef LIMIT_SPEED_BY_INSTRUCTIONS
	void DYNAREC_EMIT_INTERRUPT(Chip8Globals::X86_STATE::X86_INT_STATUS_CODE code); // Used only with the speed limiter by instructions option.
#endif
	void DYNAREC_EMIT_INTERRUPT(Chip8Globals::X86_STATE::X86_INT_STATUS_CODE code, uint16_t c8_opcode);
	void DYNAREC_EMIT_INTERRUPT(Chip8Globals::X86_STATE::X86_INT_STATUS_CODE code, uint16_t c8_opcode, uint16_t c8_return_pc);
	void DYNAREC_EMIT_MOV_EAX_EIP();
	void DYNAREC_EMIT_RETURN_CDECL_JUMP();

	void MOV_RtoM_8(uint8_t* dest, X86Register source);
	void MOV_MtoR_8(X86Register dest, uint8_t* source);
	void MOV_ImmtoR_8(X86Register dest, uint8_t immediate);
	void MOV_ImmtoM_8(uint8_t* dest, uint8_t immediate);
	void MOV_ImmtoR_32(X86Register dest, uint32_t immediate);
	void MOV_PTRtoR_8(X86Register dest, X86Register PTR_source);
	void MOV_ImmtoM_16(uint16_t* dest, uint16_t immediate);
	void MOV_MtoR_16(X86Register dest, uint16_t* source);
	void MOV_RtoM_16(uint16_t* dest, X86Register source);
	void MOV_RtoPTR_8(X86Register PTR_dest, X86Register source);
	void MOV_RtoM_32(uint32_t* dest, X86Register source);

	void ADD_ImmtoR_8(X86Register dest, uint8_t immediate);
	void ADD_ImmtoM_8(uint8_t* dest, uint8_t immediate);
	void ADD_ImmtoM_16(uint16_t* dest, uint16_t immediate);
	void AND_RwithImm_8(X86Register dest, uint8_t immediate);
	void ADD_RtoR_8(X86Register dest, X86Register source);
	void ADD_MtoR_8(X86Register dest, uint8_t* source);
	void ADD_RtoR_16(X86Register dest, X86Register source);
	void ADD_RtoM_16(uint16_t* dest, X86Register source);
	void ADD_MtoR_16(X86Register dest, uint16_t* source);
	void ADD_ImmtoR_32(X86Register dest, uint32_t immediate);

	void SUB_ImmfromR_8(X86Register dest, uint8_t immediate);
	void SUB_MfromR_8(X86Register dest, uint8_t* source);

	void CMP_RwithImm_8(X86Register dest, uint8_t immediate);
	void CMP_RwithR_8(X86Register dest, X86Register source);
	void CMP_RwithImm_32(X86Register dest, uint32_t immediate);

	void OR_RwithM_8(X86Register dest, uint8_t* source);
	void AND_RwithM_8(X86Register dest, uint8_t* source);
	void XOR_RwithM_8(X86Register dest, uint8_t* source);
	void XOR_RwithR_32(X86Register dest, X86Register source);
	void XOR_RwithR_8(X86Register dest, X86Register source);

	void JE_32(int32_t relative); // near jump
	void JNE_32(int32_t relative); // near jump
	void JNG_8(int8_t relative);
	void JNC_8(int8_t relative);
	void JNE_8(int8_t relative);

	void JMP_M_PTR_32(uint32_t * address);

	void SHL_R_8(X86Register reg, uint8_t count);
	void SHR_R_8(X86Register reg, uint8_t count);
	void SHR_R_32(X86Register reg, uint8_t count);

	void MUL_RwithR_8(X86Register source);
	void DIV_RwithR_8(X86Register source);

	void CALL_M_PTR_32(uint32_t * ptr_address); // CALL opcode
	void RET(); // RET opcode

	void POP(X86Register reg); // POP opcode
	void PUSH(X86Register reg); // PUSH opcode

	void RDTSC(); // Read time-stamp counter into EDX:EAX (used for random numbers).

private:
	// Misc opcode functions
	// Helper function for ModRegRM byte of opcodes.
	inline uint8_t ModRegRM(uint8_t mod, X86Register reg, X86Register rm);
};
