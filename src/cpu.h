#ifndef GBCPU_H
#define GBCPU_H
#include <stdint.h>
#include "mmu.h"

struct gbcpu_registers {
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t f;
	uint8_t h;
	uint8_t l;
	uint16_t sp;
	uint16_t pc;
};

struct gbcpu {
	uint16_t addr_bus;
	uint8_t data_bus;
	uint8_t accu;
	struct gbcpu_registers r;
	struct gbmmu *mmu;
};

// Flag register masks.
#define GBCPU_FLAG_Z 0x7
#define GBCPU_FLAG_N 0x6
#define GBCPU_FLAG_H 0x5
#define GBCPU_FLAG_C 0x4

struct cpu_op {
	uint8_t op;
	char *disassembly;
	uint8_t size;
	void(*fn)(struct gbcpu *cpu);
	uint8_t cycles;
};

void gbcpu_init(struct gbcpu *cpu, struct gbmmu *mmu);
void gbcpu_execute(struct gbcpu *cpu);
static void gbcpu_dump(struct gbcpu *cpu);

// CPU operations.
#define gbcp struct gbcpu *cpu

void cpu_nip(gbcp);
void cpu_noop(gbcp);

#define gbcpu_set_flag(fr, f) fr |= 1 << f
#define gbcpu_clear_flag(fr, f) fr &= ~(1 << f)

//16-bit loads.
static void cpu_ld_16(uint16_t *dest, gbcp);
static void cpu_ld_16_join(uint8_t *dest_h, uint8_t *dest_l, gbcp);
static inline uint16_t cpu_read_16_join(const uint8_t *reg1, const uint8_t *reg2);
static inline void cpu_splt_16_ld_8(uint8_t *dest_h, uint8_t *dest_l, 
		const uint16_t value);

void cpu_ld_hl_nn(gbcp); //0x21
void cpu_ld_sp_nn(gbcp); //0x31
void cpu_ld_hld_a(gbcp); //0x32

//XOR n
static void cpu_xor_8(uint8_t *dest, const uint8_t r, const uint8_t s, gbcp);
void cpu_xor_a_n(gbcp); //0xAF

// Operation map.
static const struct cpu_op cpu_op_map[256] = {
	{0x0, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF, "NIP", 0x1, &cpu_nip, 0x1},
	{0x10, "NIP", 0x1, &cpu_nip, 0x1},
	{0x11, "NIP", 0x1, &cpu_nip, 0x1},
	{0x12, "NIP", 0x1, &cpu_nip, 0x1},
	{0x13, "NIP", 0x1, &cpu_nip, 0x1},
	{0x14, "NIP", 0x1, &cpu_nip, 0x1},
	{0x15, "NIP", 0x1, &cpu_nip, 0x1},
	{0x16, "NIP", 0x1, &cpu_nip, 0x1},
	{0x17, "NIP", 0x1, &cpu_nip, 0x1},
	{0x18, "NIP", 0x1, &cpu_nip, 0x1},
	{0x19, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x1F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x20, "NIP", 0x1, &cpu_nip, 0x1},
	{0x21, "LD HL,NN", 0x2, &cpu_ld_hl_nn, 0x0C},
	{0x22, "NIP", 0x1, &cpu_nip, 0x1},
	{0x23, "NIP", 0x1, &cpu_nip, 0x1},
	{0x24, "NIP", 0x1, &cpu_nip, 0x1},
	{0x25, "NIP", 0x1, &cpu_nip, 0x1},
	{0x26, "NIP", 0x1, &cpu_nip, 0x1},
	{0x27, "NIP", 0x1, &cpu_nip, 0x1},
	{0x28, "NIP", 0x1, &cpu_nip, 0x1},
	{0x29, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x2F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x30, "NIP", 0x1, &cpu_nip, 0x1},
	{0x31, "LD SP,NN", 0x2, &cpu_ld_sp_nn, 0xC},
	{0x32, "LD (HL-),A", 0x0, &cpu_ld_hld_a, 0x8},
	{0x33, "NIP", 0x1, &cpu_nip, 0x1},
	{0x34, "NIP", 0x1, &cpu_nip, 0x1},
	{0x35, "NIP", 0x1, &cpu_nip, 0x1},
	{0x36, "NIP", 0x1, &cpu_nip, 0x1},
	{0x37, "NIP", 0x1, &cpu_nip, 0x1},
	{0x38, "NIP", 0x1, &cpu_nip, 0x1},
	{0x39, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x3F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x40, "NIP", 0x1, &cpu_nip, 0x1},
	{0x41, "NIP", 0x1, &cpu_nip, 0x1},
	{0x42, "NIP", 0x1, &cpu_nip, 0x1},
	{0x43, "NIP", 0x1, &cpu_nip, 0x1},
	{0x44, "NIP", 0x1, &cpu_nip, 0x1},
	{0x45, "NIP", 0x1, &cpu_nip, 0x1},
	{0x46, "NIP", 0x1, &cpu_nip, 0x1},
	{0x47, "NIP", 0x1, &cpu_nip, 0x1},
	{0x48, "NIP", 0x1, &cpu_nip, 0x1},
	{0x49, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x4F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x50, "NIP", 0x1, &cpu_nip, 0x1},
	{0x51, "NIP", 0x1, &cpu_nip, 0x1},
	{0x52, "NIP", 0x1, &cpu_nip, 0x1},
	{0x53, "NIP", 0x1, &cpu_nip, 0x1},
	{0x54, "NIP", 0x1, &cpu_nip, 0x1},
	{0x55, "NIP", 0x1, &cpu_nip, 0x1},
	{0x56, "NIP", 0x1, &cpu_nip, 0x1},
	{0x57, "NIP", 0x1, &cpu_nip, 0x1},
	{0x58, "NIP", 0x1, &cpu_nip, 0x1},
	{0x59, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x5F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x60, "NIP", 0x1, &cpu_nip, 0x1},
	{0x61, "NIP", 0x1, &cpu_nip, 0x1},
	{0x62, "NIP", 0x1, &cpu_nip, 0x1},
	{0x63, "NIP", 0x1, &cpu_nip, 0x1},
	{0x64, "NIP", 0x1, &cpu_nip, 0x1},
	{0x65, "NIP", 0x1, &cpu_nip, 0x1},
	{0x66, "NIP", 0x1, &cpu_nip, 0x1},
	{0x67, "NIP", 0x1, &cpu_nip, 0x1},
	{0x68, "NIP", 0x1, &cpu_nip, 0x1},
	{0x69, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x6F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x70, "NIP", 0x1, &cpu_nip, 0x1},
	{0x71, "NIP", 0x1, &cpu_nip, 0x1},
	{0x72, "NIP", 0x1, &cpu_nip, 0x1},
	{0x73, "NIP", 0x1, &cpu_nip, 0x1},
	{0x74, "NIP", 0x1, &cpu_nip, 0x1},
	{0x75, "NIP", 0x1, &cpu_nip, 0x1},
	{0x76, "NIP", 0x1, &cpu_nip, 0x1},
	{0x77, "NIP", 0x1, &cpu_nip, 0x1},
	{0x78, "NIP", 0x1, &cpu_nip, 0x1},
	{0x79, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x7F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x80, "NIP", 0x1, &cpu_nip, 0x1},
	{0x81, "NIP", 0x1, &cpu_nip, 0x1},
	{0x82, "NIP", 0x1, &cpu_nip, 0x1},
	{0x83, "NIP", 0x1, &cpu_nip, 0x1},
	{0x84, "NIP", 0x1, &cpu_nip, 0x1},
	{0x85, "NIP", 0x1, &cpu_nip, 0x1},
	{0x86, "NIP", 0x1, &cpu_nip, 0x1},
	{0x87, "NIP", 0x1, &cpu_nip, 0x1},
	{0x88, "NIP", 0x1, &cpu_nip, 0x1},
	{0x89, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x8F, "NIP", 0x1, &cpu_nip, 0x1},
	{0x90, "NIP", 0x1, &cpu_nip, 0x1},
	{0x91, "NIP", 0x1, &cpu_nip, 0x1},
	{0x92, "NIP", 0x1, &cpu_nip, 0x1},
	{0x93, "NIP", 0x1, &cpu_nip, 0x1},
	{0x94, "NIP", 0x1, &cpu_nip, 0x1},
	{0x95, "NIP", 0x1, &cpu_nip, 0x1},
	{0x96, "NIP", 0x1, &cpu_nip, 0x1},
	{0x97, "NIP", 0x1, &cpu_nip, 0x1},
	{0x98, "NIP", 0x1, &cpu_nip, 0x1},
	{0x99, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9A, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9B, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9C, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9D, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9E, "NIP", 0x1, &cpu_nip, 0x1},
	{0x9F, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xA9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xAF, "XOR A,N", 0x1, &cpu_xor_a_n, 0x4},
	{0xB0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xB9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xBF, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xC9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xCF, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xD9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xDF, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xE9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xEA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xEB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xEC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xED, "NIP", 0x1, &cpu_nip, 0x1},
	{0xEE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xEF, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF0, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF1, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF2, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF3, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF4, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF5, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF6, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF7, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF8, "NIP", 0x1, &cpu_nip, 0x1},
	{0xF9, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFA, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFB, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFC, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFD, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFE, "NIP", 0x1, &cpu_nip, 0x1},
	{0xFF, "NIP", 0x1, &cpu_nip, 0x1}
};

#endif
