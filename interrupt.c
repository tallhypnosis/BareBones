#include <stdint.h>

typedef struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecs, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags;
} regs;

extern void isr0_stub();

void isr_common_stub(regs* r) {
  if(r->int_no == 0) {
    terminal_write("Divide by zero exception\n");
    for(;;);
  }
}

void set_idt_gate(int n, uint32_t handler_addr, uint16_t selector, uint8_type_attr) {
  idt[n].offset1 = handler_addr & 0xFFFF;
  idt[n].segmentSelector = 0x08;
  idt[n].type_attr = type_attr;
  idt[n].offset2 = (handler_addr >> 16) & 0xFFFF;
  idt[n].reserved = 0;  
}

typedef struct {
  uint16_t offset1;
  uint16_t segmentSelector;
  uint8_t reserved;
  uint8_t type_attr;
  uint16_t offset2;
} InterruptDescriptor_t __atribute__((packed));


InterruptDescriptor_t idt[256];
