# The toolchain to use. arm-none-eabi works
ARMGNU ?= arm-none-eabi

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The assembly source directory.
ASM = asm/

# The name of the linker script to use.
LINKER = $(ASM)linker.ld

# The name of the output directory 
OUTPUT = output/
# The name of the assembler listing file to generate.
LIST = $(OUTPUT)kernel.list

# The name of the output file to generate.
BIN = $(OUTPUT)kernel.img

# The name of the output file to generate.
TARGET = $(OUTPUT)output.hex

# The names of all object files that must be generated.
OBJ_C := $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))
OBJ_A := $(patsubst $(ASM)%.s,$(BUILD)%.o,$(wildcard $(ASM)*.s))

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 


all : $(TARGET)

# Rule to remake everything.
rebuild: clean all

clean :
	rm -f $(BUILD)*.o
	rm -f $(OUTPUT)*.*	
	

# Rule to make the object files from C source files.
$(BUILD)%.o: $(SOURCE)%.c
	$(ARMGNU)-gcc $(COPS) -c  $< -o $@ 
# Rule to make the object files from ASM source files.
$(BUILD)%.o: $(ASM)%.s
	$(ARMGNU)-as -I $(ASM) $< -o $@

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJ_A) $(OBJ_C)  $(LINKER)
	$(ARMGNU)-ld --no-undefined $(OBJ_A) $(OBJ_C) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the hex file.
$(TARGET) : $(BUILD)output.elf
	$(ARMGNU)-objdump -D $(BUILD)output.elf > $(LIST)
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(BIN)
	$(ARMGNU)-objcopy $(BUILD)output.elf -O ihex $(TARGET) 
        

#********************************************************************************************************************************************************
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal #in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell #copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

# Author    : Geoffrey 
 
# Date	   : 2012

# version   :

#**********************************************************************************************************************************************************/


