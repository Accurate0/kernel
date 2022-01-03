gdtr DW 0 ; For limit storage
     DD 0 ; For base storage

extern gdt_flush
gdt_flush:
   mov   eax, [esp + 4]
   mov   [gdtr + 2], eax
   mov   ax, [esp + 8]
   dec   ax
   mov   [gdtr], ax
   lgdt  [gdtr]

   call gdt_reload_segments

   ret

gdt_reload_segments:
   ; Reload CS register containing code selector:
   jmp   0x08:.reload_CS ; 0x08 points at the new code selector
.reload_CS:
   ; Reload data segment registers:
   mov   ax, 0x10 ; 0x10 points at the new data selector
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax
   mov   ss, ax
   ret
