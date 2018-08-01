#ifndef GBMMU_H
#define GBMMU_H
#include <stdint.h>

struct gbmmu {
	uint8_t *memory;
	uint8_t *cartridge;
};

void gbmmu_init(struct gbmmu *mmu);

#endif