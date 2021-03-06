#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "debug.h"

void gbcpu_init(struct gbcpu *cpu, struct gbmmu *mmu)
{
	cpu->r.pc = 0x0;
	cpu->mmu = mmu;
}

void gbcpu_execute(struct gbcpu *cpu)
{
	while (1) {
		//Fetch
		uint8_t op_code = cpu->mmu->memory[cpu->r.pc];

		gbprint("PC: 0x%04X, Op code 0x%02X: %s, Size: 0x%02X, Cycles: 0x%02X\n",
			cpu->r.pc, op_code, cpu_op_map[op_code].disassembly,
			cpu_op_map[op_code].size, cpu_op_map[op_code].cycles);

		cpu_op_map[op_code].fn(cpu);
		cpu->r.pc++;
	}
}

static void gbcpu_dump(struct gbcpu *cpu)
{
	gbprint("\n-------------------\n\n");
	gbprint("Stack pointer: 0x%04X\n", cpu->r.sp);
	gbprint("Program counter: 0x%04X\n", cpu->r.pc);
	gbprint("Flag register: 0x%02X\n", cpu->r.f);
	gbprint("HL: 0x%01X%01X\n", cpu->r.h, cpu->r.l);
	gbprint("Immediate instruction stack: ");
	for (short i=0; i<8; ++i)
		gbprint("0x%02X ", cpu->mmu->memory[cpu->r.pc++]);
	gbprint("\n\n-------------------\n");
}

void cpu_nip(struct gbcpu *cpu)
{
	printf("NIP: Not implemented\n");
	gbcpu_dump(cpu);
	exit(1);
}

void cpu_noop(struct gbcpu *cpu)
{
	printf("NOP\n");
}


static void cpu_ld_16(uint16_t *dest, struct gbcpu *cpu)
{
	//Read the proceeding two bytes of data from the PC and store them in a
	//16 bit register.
	uint16_t res;
	res = cpu->mmu->memory[++cpu->r.pc];
	res = res | (cpu->mmu->memory[++cpu->r.pc] << 8); //We are little endian.
	*dest = res;
}

static void cpu_ld_16_join(uint8_t *dest_h, uint8_t *dest_l, struct gbcpu *cpu)
{
	//Read the proceeding two bytes of data from the PC and store them in a
	//two 8-bit register to collectively make 16 bits.
	*dest_l = cpu->mmu->memory[++cpu->r.pc];
	*dest_h = cpu->mmu->memory[++cpu->r.pc];
}

static inline uint16_t cpu_read_16_join(const uint8_t *reg1, const uint8_t *reg2)
{
	//Read two registers as a 16-bit value.
	return (*reg1 << 8) | (*reg2);
}

static inline void cpu_splt_16_ld_8(uint8_t *dest_h, uint8_t *dest_l, 
		const uint16_t value)
{
	*dest_h = value >> 8;
	*dest_l = value & 0xFF;
}

void cpu_ld_sp_nn(struct gbcpu *cpu)
{
	cpu_ld_16(&cpu->r.sp, cpu);
}

void cpu_ld_hl_nn(struct gbcpu *cpu)
{
	cpu_ld_16_join(&cpu->r.h, &cpu->r.l, cpu);
}

static void cpu_xor_8(uint8_t *dest, const uint8_t r, const uint8_t s,
	struct gbcpu *cpu)
{
	*dest = (r ^ s);
	if (*dest == 0)
		gbcpu_set_flag(cpu->r.f, GBCPU_FLAG_Z);
	gbcpu_clear_flag(cpu->r.f, GBCPU_FLAG_N);
	gbcpu_clear_flag(cpu->r.f, GBCPU_FLAG_H);
	gbcpu_clear_flag(cpu->r.f, GBCPU_FLAG_C);

}

void cpu_xor_a_n(struct gbcpu *cpu)
{
	cpu_xor_8(&cpu->r.a, cpu->r.a, cpu->r.a, cpu);
}

void cpu_ld_hld_a(struct gbcpu *cpu)
{
	//Put A into memory addr HL. Decrements HL.
	uint16_t addr = cpu_read_16_join(&cpu->r.h, &cpu->r.l);
	gbmmu_abs_write(cpu->mmu, addr, cpu->r.a);
	cpu_splt_16_ld_8(&cpu->r.h, &cpu->r.l, --addr);
}
