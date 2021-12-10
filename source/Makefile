.SUFFIXES:
.SUFFIXES: .o .cpp
#============================================================
TARGET	=  segment

C_SOURCES =  main.cpp graph.cpp
C_OBJS     = main.o graph.o
MY_INCLUDES = 

CCX = g++
CXXFLAGS = -g -std=c++11  -Wall

#============================================================
all: $(TARGET)

.o:.cpp	$(MY_INCLUDES)
	$(CCX)  -c  $(CXXFLAGS) $<  

$(TARGET) :   $(C_OBJS)
	$(CCX) $(CXXFLAGS)  $^ $(LIBDIRS)  -o $@

# Implicit rules: $@ = target name, $< = first prerequisite name, $^ = name of all prerequisites
#============================================================

ALL_SOURCES = makeFind $(C_SOURCES) $(MY_INCLUDES)

clean:
	rm -f $(TARGET) $(C_OBJS) core *~

tar: $(ALL_SOURCES)
	tar cvf $(TARGET).tar $(ALL_SOURCES)

$(TARGET).ps: $(ALL SOURCES) 
	enscript -pcode.ps $(ALL_SOURCES)
