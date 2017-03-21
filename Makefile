

TARGET = libtrickle.so
TEST = test_trickle

SRCS = \
    TrSchema.cpp \
    TrResources.cpp \
    TrRow.cpp \
    TrTable.cpp \
    TrCell.cpp \

TESTSRCS = \
    test/test_main.cpp \
    test/test_initialize.cpp \

CATCH = Catch/include/catch.hpp

DIR = $(shell pwd)
BIN = bin
TESTBIN = test/$(BIN)
CXX = g++ -g -std=c++11 -I $(DIR)
SHAREDFLAGS = -g -fPIC -dynamiclib -shared

$(CATCH):
	git clone https://github.com/philsquared/Catch.git

$(BIN):
	@mkdir $(BIN)

$(TESTBIN):
	@mkdir $(TESTBIN)

$(TARGET): $(BIN)
	@$(CXX) $(SHAREDFLAGS) -o $(BIN)/$(TARGET) $(SRCS)

$(TEST): $(TESTBIN)
	@$(CXX) -o $(TESTBIN)/$(TEST) $(TESTSRCS) -L$(DIR)/$(BIN) -ltrickle

.PHONY: test

clean:
	@find $(DIR) -name $(BIN) -exec rm -r {} \; 2>/dev/null || true ;

test: clean $(CATCH) $(TARGET) $(TEST)
	./$(TESTBIN)/$(TEST)

all: $(TARGET)
	@echo "success"
