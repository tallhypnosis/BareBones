#include <stdint.h>

typedef struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecs, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags;
} regs;

extern void isr0_stub(); 
extern void isr1_stub(); 
extern void isr2_stub(); 
extern void isr3_stub(); 
extern void isr4_stub(); 
extern void isr5_stub(); 
extern void isr6_stub(); 
extern void isr7_stub(); 
extern void isr8_stub(); 
extern void isr9_stub(); 
extern void isr10_stub(); 
extern void isr11_stub(); 
extern void isr12_stub(); 
extern void isr13_stub(); 
extern void isr14_stub(); 
extern void isr15_stub(); 
extern void isr16_stub(); 
extern void isr17_stub(); 
extern void isr18_stub(); 
extern void isr19_stub(); 
extern void isr20_stub(); 
extern void isr21_stub(); 
extern void isr22_stub(); 
extern void isr23_stub(); 
extern void isr24_stub(); 
extern void isr24_stub(); 
extern void isr25_stub(); 
extern void isr26_stub();
extern void isr27_stub();
extern void isr28_stub(); 
extern void isr29_stub(); 
extern void isr30_stub(); 
extern void isr31_stub(); 
extern void isr32_stub(); 
 
 
 
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


set_idt_gate(0, isr0_stub, 0x08, 0x08E);
set_idt_gate(1, isr1_stub, 0x08, 0x08E);
set_idt_gate(2, isr2_stub, 0x08, 0x08E);
set_idt_gate(3, isr3_stub, 0x08, 0x08E);
set_idt_gate(4, isr4_stub, 0x08, 0x08E);
set_idt_gate(5, isr5_stub, 0x08, 0x08E);
set_idt_gate(6, isr6_stub, 0x08, 0x08E);
set_idt_gate(7, isr7_stub, 0x08, 0x08E);
set_idt_gate(8, isr8_stub, 0x08, 0x08E);
set_idt_gate(9, isr9_stub, 0x08, 0x08E);
set_idt_gate(10, isr10_stub, 0x08, 0x08E);
set_idt_gate(11, isr11_stub, 0x08, 0x08E);
set_idt_gate(12, isr12_stub, 0x08, 0x08E);
set_idt_gate(13, isr13_stub, 0x08, 0x0E);
set_idt_gate(14, isr14_stub, 0x08, 0x08E);
set_idt_gate(15, isr15_stub, 0x08, 0x08E);
set_idt_gate(16, isr16_stub, 0x08, 0x08E);
set_idt_gate(17, isr17_stub, 0x08, 0x08E);

