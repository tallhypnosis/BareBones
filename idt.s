.global isr0_stub

isr0_stub:
  pusha
  push dword 0
  push dword 0
  call isr_common_stub
  add esp, 8
  popa
  iret 
