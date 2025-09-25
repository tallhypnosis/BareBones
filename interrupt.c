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
