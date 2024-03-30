CXX = g++
CXXFLAGS = -I include/
SRCS = $(wildcard src/*.cpp) main.cpp
OBJS = $(patsubst %.cpp,temp/%.o,$(SRCS))
EXEC = main
OBJDIR = temp/src

# Cria a pasta de objetos se ela não existir
$(shell mkdir -p $(OBJDIR))

# Verifica o sistema operacional
ifeq ($(OS),Windows_NT)
    CLEAN_CMD = if exist temp\src\*.o (del /f /q temp\src\*.o) && if exist temp\main.o (del /f /q temp\main.o) && if exist $(EXEC) (del /f /q $(EXEC))
else
    CLEAN_CMD = rm -f temp/src/*.o temp/main.o $(EXEC)
endif

all: clean $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

temp/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)
