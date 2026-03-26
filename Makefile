CC = gcc
CFLAGS = -Wall -Wextra -g

AR = ar
ARFLAGS = rcs

INCLUDES = -Idictionary -Ilinked_list -Inodes -Iqueues -Itrees

SRCS = $(wildcard dictionary/*.c) \
       $(wildcard linked_list/*.c) \
       $(wildcard nodes/*.c) \
       $(wildcard queues/*.c) \
       $(wildcard trees/*.c)

OBJS = $(SRCS:.c=.o)
TARGET = libdata_structures.a


all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Buildando a lib estatica...: $(TARGET)..."
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)	
	@echo "Build concluído com sucesso!"

%.o: %.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Limpando arquivos compilados..."
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
