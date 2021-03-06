static inline void sti(void)
{
    __asm__ volatile ("sti");
}

static inline void cli(void)
{
    __asm__ volatile ("cli");
}
