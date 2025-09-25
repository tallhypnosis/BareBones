
%macro ISR_NOERR 1
.global isr%1_stub
isr%1_stub:
  cli
  pusha
  push dword 0
  push dword 0
  call isr_common_stub
  add esp, 8
  popa
  sti
  iretd
%endmacro

%macro ISR_ERR 1
.global is%1_stub
isr%1_stub:
  cli
  pusha
  push dword 0
  call isr_common_stub
  add esp, 4
  popa
  sti
  iretd
 %endmacro


ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR 8
ISR_NOERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_ERR 17 




