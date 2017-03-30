
include std_makevars

TARGET = libtrickle.so
TEST = test_trickle

DIR = $(shell pwd)
BIN = bin
SRCDIR = src
TESTDIR = test
TESTBIN = $(TESTDIR)/$(BIN)

SRCS_F = \
    TrSchema.cpp \
    TrResources.cpp \
    TrRow.cpp \
    TrTable.cpp \
    TrCell.cpp \
    TrView.cpp \

TESTSRCS_F = \
    test_main.cpp \
    test_Table.cpp \
    test_View.cpp \
    test_initialize.cpp \

SRCS = $(addprefix $(SRCDIR)/,$(SRCS_F))
TESTSRCS = $(addprefix $(TESTDIR)/,$(TESTSRCS_F))

CATCH = Catch-master/include/catch.hpp

CXX = g++ -g -std=c++11 -I $(DIR)
SHAREDFLAGS = -g -fPIC -dynamiclib -shared

$(CATCH):
	$(call github,philsquared,Catch)

$(BIN):
	@mkdir $(BIN)

$(TESTBIN):
	@mkdir $(TESTBIN)

$(TARGET): $(SRCS) | $(BIN)
	@$(CXX) $(SHAREDFLAGS) -o $(BIN)/$(TARGET) -I$(SRCDIR) $(SRCS)

$(TEST): $(TESTSRCS) | $(TESTBIN)
	@$(CXX) -g -o $(TESTBIN)/$(TEST) $(TESTSRCS) -I$(SRCDIR) -L$(DIR)/$(BIN) -ltrickle

clean:
	@find $(DIR) -name $(BIN) -exec rm -r {} \; 2>/dev/null || true ;

test: $(TARGET) $(TEST) | $(CATCH)
	@./$(TESTBIN)/$(TEST)

all: $(TARGET)
	@echo "success"
