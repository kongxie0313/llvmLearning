Note: This program is based on llvm 16.0.4.

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

3.Create file 'test.c' like thie:

```
	void fun() {
		int c, d;
	}

	int main() {
		int a, b;
		fun();
		return 0;
	}
```

4.Compile 'test.c', note, if terminal tells you **'clang: command not found'**, you should use the absolute path or modify the env variables.
```
 $ clang -emit-llvm -c test.c -o test.bc
```

5.Run this program like this:
```
 $ ./helloworld test.bc
```

6.Check the output of this program. Normally, it will print the block number of the Bitcode file.
