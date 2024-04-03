0.1.0-文件夹版
==============

## 使用说明
请将verilog代码放在`lab/code/`中，测试代码放在`/lab/test/`中。
在`lab/test/`下创建`testX.asm`，其中`X`代表数字。生成机器码`testX.txt`后双击`make`快捷方式，即可完成转换和插入。
### 注意事项⚠️
#### 插入位置
插入`InstructionMemory.v`的位置是
```verilog
//TEST CODE
```
所在的位置，请勿修改这一行。
#### 生成格式
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


## 示例
### 使用前
#### 文件夹结构
```
lab
├─code
│   ├─InstructionMemory.v
│   └─其他verilog代码
└─test
    ├─test0
    │   ├─test0.asm
    │   ├─test0.txt
    │   └─test0.v
    ├─test1.asm
    ├─test1.txt
    ├─toolbox
    └─make快捷方式
```

#### `InstructionMemory.v`
```verilog
`define TEST0

module InstructionMemory(
    input reset,
    ...
);

reg [31:0] InstructionMemory[511:0];

always@(posedge reset)
begin
//TEST CODE

end

endmodule

`undef TEST0
```


### 使用后
#### 文件夹结构
```
lab
├─code
│   ├─InstructionMemory.v
│   └─其他verilog代码
└─test
    ├─test0
    │   ├─test0.asm
    │   ├─test0.txt
    │   └─test0.v
    ├─test1
    │   ├─test1.asm
    │   ├─test1.txt
    │   └─test1.v
    ├─toolbox
    └─make快捷方式
```

#### `InstructionMemory.v`
```verilog
`define TEST1

module InstructionMemory(
    input reset,
    ...
);

reg [31:0] InstructionMemory[511:0];

always@(posedge reset)
begin
//TEST CODE
`include "../test/test1/test1.v"

end

endmodule

`undef TEST1
`undef TEST0
```
