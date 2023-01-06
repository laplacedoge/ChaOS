
asm_srcs := $(shell find src -name *.asm)
asm_objs := $(patsubst src/%.asm, build/%.o, $(asm_srcs))

c_srcs := $(shell find src -name *.c)
c_objs := $(patsubst src/%.c, build/%.o, $(c_srcs))

.PHONY: all clean

all: $(asm_objs) $(c_objs)
	@ld -m elf_i386 --nmagic --output=build/kernel.bin --script=src/link/link.ld $^
	@cp build/kernel.bin src/iso/boot/kernel.bin
	@grub-mkrescue -o build/kernel.iso src/iso

clean:
	@rm -rf build/*
	@rm -f src/iso/boot/kernel.bin

build/%.o: src/%.asm
	@mkdir -p $(dir $@)
	@nasm -f elf32 -o $@ $<

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@x86_64-elf-gcc -m32 -o $@ -c $<
