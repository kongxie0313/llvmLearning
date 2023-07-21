Note: This program is based on llvm 16.0.4.

1.Modify the first line of **Makefile**

```
LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm/bin/llvm-config

	to

LLVM_CONFIG?=(Your llvm installation root dir)/bin/llvm-config
```

2.Compile and link this program:

```
 $ make
```

3.Create the source file "sum.c":

```
	void sum(int a, int b) {
		return a + b;
	}
```

4.Compile 'sum.c', note, if terminal tells you **'clang: command not found'**, you should use the absolute path or modify the env variables.
```
 $ clang -emit-llvm -c sum.c -o sum.bc
```

5.Run this program:
```
 $ ./sum-jit
Sum result: 9
Sum result: 15
```
