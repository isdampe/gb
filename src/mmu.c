#include <stdint.h>
#include <stdlib.h>
#include "mmu.h"
#include "bios.h"

void gbmmu_init(struct gbmmu *mmu)
{
	mmu->memory = malloc(2^16 * sizeof(uint8_t));

	//Load bios into memory entrypoint.
	for (int i=0; i<0x100; ++i)
		mmu->memory[i] = bios_rom[i];
}

void gbmmu_abs_write(struct gbmmu *mmu, const uint16_t addr, const uint8_t val)
{
	if (addr > 2^16) {
		gbprint("SEGMENETATION FAULT: ");
		return;
	}
	mmu->memory[addr] = val;
}