#include <kernel/instructions.h>
#include <kernel/isr.h>
#include <kernel/printk.h>

char kbdus[128] = {
    0,    27,  '1', '2', '3',  '4', '5', '6', '7',  '8', /* 9 */
    '9',  '0', '-', '=', '\b',                           /* Backspace */
    '\t',                                                /* Tab */
    'q',  'w', 'e', 'r',                                 /* 19 */
    't',  'y', 'u', 'i', 'o',  'p', '[', ']', '\n',      /* Enter key */
    0,                                                   /* 29   - Control */
    'a',  's', 'd', 'f', 'g',  'h', 'j', 'k', 'l',  ';', /* 39 */
    '\'', '`', 0,                                        /* Left shift */
    '\\', 'z', 'x', 'c', 'v',  'b', 'n',                 /* 49 */
    'm',  ',', '.', '/', 0,                              /* Right shift */
    '*',  0,                                             /* Alt */
    ' ',                                                 /* Space bar */
    0,                                                   /* Caps lock */
    0,                                                   /* 59 - F1 key ... > */
    0,    0,   0,   0,   0,    0,   0,   0,   0,         /* < ... F10 */
    0,                                                   /* 69 - Num lock*/
    0,                                                   /* Scroll Lock */
    0,                                                   /* Home key */
    0,                                                   /* Up Arrow */
    0,                                                   /* Page Up */
    '-',  0,                                             /* Left Arrow */
    0,    0,                                             /* Right Arrow */
    '+',  0,                                             /* 79 - End key*/
    0,                                                   /* Down Arrow */
    0,                                                   /* Page Down */
    0,                                                   /* Insert Key */
    0,                                                   /* Delete Key */
    0,    0,   0,   0,                                   /* F11 Key */
    0,                                                   /* F12 Key */
    0,                                                   /* All other keys are undefined */
};

void keyboard_handler(__attribute__((unused)) register_t *r) {
    int i, scancode;
    // get scancode with "timeout"
    for (i = 1000; i > 0; i++) {
        // Check if scan code is ready
        if ((inb(0x64) & 1) == 0)
            continue;
        // Get the scan code
        scancode = inb(0x60);
        break;
    }
    if (i > 0) {
        if (scancode & 0x80) {
            // Key release
        } else {
            // Key down
            printk(PRINTK_SERIAL | PRINTK_TTY, "Key pressed '%c'\n", kbdus[scancode]);
        }
    }
}
void keyboard_init() {
    register_interrupt_handler(IRQ1_Keyboard, keyboard_handler);
}
