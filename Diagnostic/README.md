1.Modify the first line of *Makefile*

	```LLVM_CONFIG?=~/kxproj/llvm-prebuild/llvm/bin/llvm-config```

	to

	```LLVM_CONFIG?=~**Your llvm installation root dir**/llvm/bin/llvm-config

1.To compile and link this program, run command:

	```make```

2.To check the diagnostic funciton, please create file 'hello.c' like thie:

```
	int main() {

		printf("hello world")

		return 0;

	}
```

3.Set the env:

	```export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:{Your llvm installation root dir}/llvm/lib```

4.Run command and check the diagnostic information.

	```./myproject hello.c```

