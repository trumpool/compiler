CXX = g++
FLEX = flex
BISON = bison
CXXFLAGS = -std=c++17 -g -Wall
SRC_DIR = src
PYTHON = python3
LEX_CCFILES = $(shell find $(SRC_DIR) -name "lex.cc")
LEX_OBJS = $(LEX_CCFILES:.cc=.o)
LFILE = $(shell find $(SRC_DIR) -name "*.l")
YFILE = $(shell find $(SRC_DIR) -name "*.y")
CFILES = $(shell find $(SRC_DIR) -name "*.c")
LCCFILE = $(LFILE:.l=.yy.cc)
YCCFILE = $(YFILE:.y=.tab.cc)
YHEADER = $(YCCFILE:.cc=.hh)
LOBJ = $(LCCFILE:.cc=.o)
YOBJ = $(YCCFILE:.cc=.o) 
OBJS = $(CFILES:.c=.o)
CPPFILES = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS += $(CPPFILES:.cpp=.o)
CCFILES = $(shell find $(SRC_DIR) -name "main.cc")
MAIN_OBJS = $(CCFILES:.cc=.o)

compiler: $(LOBJ) $(YOBJ) $(OBJS) $(MAIN_OBJS)
	$(CXX) -o $@ $^

$(YOBJ): $(YCCFILE)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(YCCFILE) $(YHEADER): $(YFILE)
	$(BISON) -d -o $(YCCFILE) $^ $(Wex)

$(LOBJ): $(LCCFILE)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(LCCFILE): $(LFILE) $(YHEADER)
	$(FLEX) -o $@ $<

lex: $(LOBJ) $(OBJS) $(LEX_OBJS)
	$(CXX) -o $@ $^

.PHONY: clean all clean_again test
clean:
	rm -f $(LCCFILE) $(YCCFILE) $(YHEADER)
	rm -f $(LOBJ) $(YOBJ)
	rm -f $(OBJS)
	rm -f $(MAIN_OBJS)
	rm -f compiler
clean_again:
	rm -f $(LCCFILE) $(YCCFILE) $(YHEADER)
	rm -f $(LOBJ) $(YOBJ)
	rm -f $(OBJS)
	rm -f $(MAIN_OBJS)
	rm -f compiler
python_test:
	python3 test.py ./compiler lab1
test:
	./compiler lab1/while_test1.sy
all: clean compiler python_test clean_again
remake: clean compiler python_test