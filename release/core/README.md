0.1.0-核心版
============

## 使用说明
把待转换的机器码文件（`.txt`格式）与`txt2v.exe`放在同一文件夹下，使用后可生成`.v`格式的verilog代码。
### 生成格式
原机器码
```
340400ab
ac040000
8c050000
ac050004
```
生成格式
```verilog
InstructionMemory[  0/*  0*/] <= 32'h340400ab;
InstructionMemory[  1/*  4*/] <= 32'hac040000;
InstructionMemory[  2/*  8*/] <= 32'h8c050000;
InstructionMemory[  3/*  c*/] <= 32'hac050004;
```
