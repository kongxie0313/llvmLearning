Note: This program is based on **llvm 16.0.0**.

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

3.To check the diagnostic funciton, please create file 'hello.c' like this:

```
	int main() {
		printf("hello world")
		return 0;
	}
```

4.Set the env variable. Note, you must replace the dir path below!

```
 $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:{Your llvm installation root dir}/lib
```

5.Run command and check the diagnostic information.

```
 $ ./myproject hello.c
```

