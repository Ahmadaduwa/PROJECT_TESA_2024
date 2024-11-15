# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -fopenmp
LDFLAGS = -lm -lasound -lsqlite3 -lpaho-mqtt3c -lcjson -fopenmp

# Target application name
TARGET = sound_app

# Source files and object files
SRCS = sound_app.c alsa_thr.c sound_freq.c sound_freq_initialize.c \
       FFTImplementationCallback.c sound_freq_terminate.c abs.c \
       rtGetInf.c rt_nonfinite.c rtGetNaN.c db_helper.c iot_app.c fft_thr.c \
       predictSignal.c predictSignal_initialize.c predictSignal_terminate.c \
       predictSignal_data.c ClassificationKNN.c knnsearch.c kdsearchfun.c \
       sort.c sortIdx.c minOrMax.c

OBJS = $(SRCS:.c=.o)

# Default target to build the application
all: $(TARGET)

# Rule to link object files and create the executable with libraries
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Rule to compile .c files into .o files and generate dependency files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -MM $(CFLAGS) $< > $(@:.o=.d)

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET) $(DEPS)

# Include dependency files if they exist
-include $(DEPS)

# Phony targets
.PHONY: all clean
