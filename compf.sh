nasm BootLoader.asm
dd if=/dev/zero of=diskc.img bs=512 count=1000
dd if=BootLoader of=diskc.img bs=512 count=1 conv=notrunc
bcc -ansi -c -o kernel_c.o kernel.c
as86 kernal.asm -o kernel_asm.o
ld86 -o kernel -d kernel_c.o kernel_asm.o
./loadFile kernel
./loadFile message.txt
bcc -ansi -c -o tstpr1.o tstpr1.c
as86 -o userlib.o userlib.asm
ld86 -d -o tstpr1 tstpr1.o userlib.o
bcc -ansi -c -o tstpr2.o tstpr2.c
as86 -o userlib.o userlib.asm
ld86 -d -o tstpr2 tstpr2.o userlib.o
./loadFile tstpr1
./loadFile tstpr2 
bcc -ansi -c -o shell.o Shell.c
as86 userlib.asm -o shell_asm.o
ld86 -o shell -d shell.o Shell_asm.o
./loadFile shell


