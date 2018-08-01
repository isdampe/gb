#ifndef GB_H
#define GB_H
#include "cpu.h"
#include "mmu.h"

struct gb {
	struct gbcpu cpu;
	struct gbmmu mmu;
};

void gb_init(struct gb *gb);

#endif