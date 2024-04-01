@echo off

echo form test?.v
set /p var=?=

cd ..
md test%var%
move test%var%.asm test%var%\test%var%.asm
move test%var%.txt test%var%\test%var%.txt

cd toolbox
form %var%
echo verilog file formed

cd ..\..\code
move /y temp.v InstructionMemory.v

pause
