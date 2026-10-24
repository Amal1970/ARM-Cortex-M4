CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -Wall -Wextra -std=gnu11 -O0 -g
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=final.map
OPENOCD_SCRIPTS = /usr/share/openocd/scripts

all : final.elf

final.elf : main.o stm32_startup.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

stm32_startup.o : stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $@

clean : 
	rm -f *.o *.elf *.map

download : 
	openocd -s $(OPENOCD_SCRIPTS) -f board/stm32f4discovery.cfg

.PHONY: all clean download