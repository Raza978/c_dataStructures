CC := gcc

# Compiler flags: warnings, debug, look in current dir for headers, generate dependency files (.d), add phony targets for dependencies
CFLAGS := -Wall -g -I. -MMD -MP

SOURCES := $(wildcard *.c)
OBJS := $(SOURCES:.c=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: output
	./output

output: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o output

# generic compile rule (produces .o and .d via -MMD -MP)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# include generated dependency files when present
-include $(DEPS)

clean:
	rm -f *.o *.d output
