#include <kernel/multiboot.h>
#include <kernel/printk.h>

#include <stddef.h>
#include <stdint.h>

void pmm_init(uint32_t mmap_length, uint32_t mmap_addr) {
    printk(PRINTK_SERIAL | PRINTK_TTY, "memory map from multiboot\n");
    for (size_t i = 0; i < mmap_length; i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmmt = (multiboot_memory_map_t *)(mmap_addr + i);

        if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE && mmmt->addr_low >= 0x1) {
            printk(PRINTK_SERIAL | PRINTK_TTY,
                   "Start Addr: %lx | Length: %d | Size: %d | Type: %d\n", mmmt->addr_low,
                   mmmt->len_low, mmmt->size, mmmt->type);
        }
    }
    // we don't actually want to use the low addresses
    // that where our stuff is
}
