# Compiler options
CXX = g++
# CXXFLAGS = -Wall -Wextra -Wpedantic

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Executable name
TARGET = a

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCDIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
