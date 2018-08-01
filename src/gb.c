#include "cpu.h"
#include "mmu.h"
#include "gb.h"

void gb_init(struct gb *gb)
{
	gbmmu_init(&gb->mmu);
	gbcpu_init(&gb->cpu, &gb->mmu);

	gbcpu_execute(&gb->cpu);
}