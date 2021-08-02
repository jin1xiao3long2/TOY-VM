start cs .\compiler\gen_new_tree.csc .\compiler\c_minus.ebnf test.c test.asm
start .\csasm.exe test.asm bc.txt
start .\bcgen bc.txt bc
start .\csvm.exe bc
