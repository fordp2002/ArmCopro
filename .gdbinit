set architecture arm
set remotebaud 115200
target remote COM3
load build/output.elf
continue
detach
quit