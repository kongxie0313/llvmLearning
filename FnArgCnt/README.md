Note: This program is based on **llvm 16.0.4**.

1.Modify the first line of **Makefile**

```
LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm/bin/llvm-config

	to

LLVM_CONFIG?=(Your llvm installation root dir)/bin/llvm-config
```

2.Compile the shared library **fnarg.so**.

```
 $ make
```

3.Create file 'sum.c' under this directory like thie:

```
	int sum(int a, int b) {
		if(a < b) {
			return a;
		}
		return b;
	}
```

4.Compile 'sum.c' to llvm bitcode:

```
clang sum.c -emit-llvm -c -o sum.bc
```

5.Execute Opt command with the **fnargcnt** pass. Note, if terminal prompt "'opt' command not found", set the env virables first or create a soft link under this directory to **opt** installed.

```
 $ opt -load=./fnarg.so -fnargcnt < sum.bc -enable-new-pm=0
```

6.Check the output. Normally, it will print the function name and result type information of the bitcode file.

```
...
FnArgCnt --- sum: Return typeid: 13. Info: IntegerTyID: Arbitrary bit width integers
```
