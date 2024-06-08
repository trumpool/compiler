TESTSRC = lab2

CXX = g++
FLEX = flex
BISON = bison
CXXFLAGS = -std=c++17 -g -Wall
SRC_DIR = src
PYTHON = python3
OUTPUTS_DIR = outputs

MAIN_OBJS = $(CCFILES:.cc=.o)
LEX_CCFILES = $(shell find $(SRC_DIR) -name "lex.cc")
LEX_OBJS = $(LEX_CCFILES:.cc=.o)
LFILE = $(shell find $(SRC_DIR) -name "*.l")
YFILE = $(shell find $(SRC_DIR) -name "*.y")
CFILES = $(shell find $(SRC_DIR) -name "*.c")
CPPFILES = $(shell find $(SRC_DIR) -name "*.cpp")
CCFILES = $(shell find $(SRC_DIR) -name "main.cc")
LCCFILE = $(LFILE:.l=.yy.cc)
YCCFILE = $(YFILE:.y=.tab.cc)
YHEADER = $(YCCFILE:.cc=.hh)
LOBJ = $(LCCFILE:.cc=.o)
YOBJ = $(YCCFILE:.cc=.o) 
OBJS = $(CFILES:.c=.o)
OBJS += $(CPPFILES:.cpp=.o)
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

.PHONY: clean all clean_again test python_test python_test1 python_test2 remake clean_outputs
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
	python3 test.py ./compiler $(TESTSRC)
python_test1:
	python3 test.py ./compiler lab1
python_test2:
	python3 test.py ./compiler lab2
test:
	./compiler $(TESTSRC)/add.sy  
all: clean compiler python_test1 python_test2
remake: clean compiler test
clean_outputs:
	rm -f $(OUTPUTS_DIR)/*