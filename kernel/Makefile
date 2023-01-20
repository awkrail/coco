TARGET = kernel.elf
OBJS = main.o graphics.o font.o hankaku.o

CFLAGS += -Og -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
					-std=c11
LDFLAGS += --entry KernelMain -z norelro --image-base 0x100000 --static

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o

kernel.elf: $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS)

%.o: %.c Makefile
	clang $(CPPFLAGS) $(CFLAGS) -c $<

hankaku.o: hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $< $@
