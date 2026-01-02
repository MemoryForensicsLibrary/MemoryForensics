CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -Isrc
AR      = ar
ARFLAGS = rcs

SRC = \
	src/core/process.c \
	src/core/process_priv.c

OBJ = $(SRC:.c=.o)

libmfl.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) libmfl.a
