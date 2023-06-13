Note: This program is based on **llvm 16.0.0**.

1.Modify the first line of **Makefile**

```
LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm-16.0.0/bin/llvm-config

	to

LLVM_CONFIG?=(Your llvm installation root dir)/bin/llvm-config
```

2.To compile and link this program, run command:

```
 $ make
```

3.To check the parse ability, please create file 'hello.c' like this:

```
	#include<stdio.h>

	int main() {
        	int x = 8000;
        	printf("hello, world!\n");
	}
```

4.Set the env variable:

```
 $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:{Your llvm installation root dir}/lib
```

5.Run command and check tokens parsed.

```
 $ ./parseToken hello.c
```

