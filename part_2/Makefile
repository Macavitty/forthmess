all:
	nasm -f elf64 -g src/forthmess.asm
	ld -o forthmess src/*.o
clean: 
	rm *.o
	rm forthmess
