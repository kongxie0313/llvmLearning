Note: This program is based on llvm 16.0.4.

This program will create a bitcode IR file manually. And you can verify the validity of the IR by llvm tool **llvm-dis**. The C++ source of the IR is a simple sum function.

1.Modify the first line of **Makefile**

```
LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm/bin/llvm-config

	to

LLVM_CONFIG?=(Your llvm installation root dir)/bin/llvm-config
```

2.To compile and link this program, run command:

```
 $ make
```

3.Run this program to generate the IR bitcode file **sum.bc**.

```
 $ ./genIR
```

4.Disassemble the bitcode file **sum.bc**. If terminal prompts "llvm-dis command not found", you need to create soft link to installed llvm tool or set the env variable.

```
 $ llvm-dis sum.bc -o sum.ll
```

5.Print the result **sum.ll**.

```
 $ cat sum.ll
 ; ModuleID = 'sum.bc'
 source_filename = "sum.ll"
 target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
 target triple = "x86_64-unknown-linux-gnu"

 define i32 @sum(i32 %a, i32 %b) {
 entry:
   %a.addr = alloca i32, align 4
   %b.addr = alloca i32, align 4
   store i32 %a, ptr %a.addr, align 4
   store i32 %b, ptr %b.addr, align 4
   %0 = load i32, ptr %a.addr, align 4
   %1 = load i32, ptr %b.addr, align 4
   %add = add i32 %0, %1
   ret i32 %add
 }
```

6.To verify the validity of this program, you can create the C++ source file **sum.c**, then compile it into llvm-IR.

```
int sum(int a, int b) {
	return a + b;
}
```

7.Compile **sum.c**, and print the result.

```
 $ clang sum.c -emit-llvm -S -c -o sum.ll && cat sum.ll
```
