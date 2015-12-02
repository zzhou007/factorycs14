# the compiler: gcc for C program, define as g++ for C++
CC11 = g++ -std=c++11
	
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
	
# the build target executable:
TARGET = zhou-861090400-factory
INPPUT = mset1.txt
	
all:$(TARGET)
	
$(TARGET): $(TARGET).cpp
	$(CC11) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
clean:
	$(RM) $(TARGET)