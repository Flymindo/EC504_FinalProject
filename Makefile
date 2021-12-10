.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET	=  segment

C_SOURCES =  source/*.cpp
C_OBJS     = source/main.o
MY_INCLUDES = 

CCX = g++
CXXFLAGS = -g -std=c++11  -Wall -Isource

#============================================================
all: $(TARGET)

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET) :   $(C_OBJS)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = makeFind $(C_SOURCES) $(MY_INCLUDES)

# INPUT_FILES  =  Sorted100.txt  Sorted100K.txt  Sorted1M.txt

clean:
	rm -f $(TARGET) $(C_OBJS) core *~

tar: $(ALL_SOURCES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)

$(TARGET).ps: $(ALL SOURCES) 
	enscript -pcode.ps $(ALL_SOURCES)
