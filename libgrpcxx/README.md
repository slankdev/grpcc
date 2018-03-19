
# libgrpcxx

grpc wrapper for pure-c. using libstc++

## Usage

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgrpcxx.h>

int main(int argc, char** argv)
{
}
```

```
CFLAGS += -I../
LDFLAGS += -L../ -lgrpcxx -lstdc++

all:
	$(CC) $(CFLAGS) main.c $(LDFLAGS)
```
