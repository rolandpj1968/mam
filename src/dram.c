#include "all.h"

Dram *finddram(u8 ndram, Dram **dram, v64 addr) {
	for (u8 n = 0; n < ndram; n++) {
		if (dram[n]->addr <= addr && addr < dram[n]->addr+dram[n]->len)
			return dram[n];
	}
	return 0;
}
