start .\compiler.csc test.c test.asm 
start .\csasm.exe test.asm bc.txt
start .\bcgen bc.txt bc
start .\csvm.exe bc