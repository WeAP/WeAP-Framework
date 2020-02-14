
TEST_SRC = .
TEST_OBJ = ../../obj
TEST_BIN = .
TEST_MAIN := ./unittest_main

WEAP_SRC = ../../src/WeAP
WEAP_OBJ = ../../obj
WEAP_BIN = ../../bin
WEAP_LIB  = $(WEAP_BIN)/libweap-framework.a



include ../../src/WeAP/makefile.inc

INCLUDE += -I$(WEAP_SRC)/System
INCLUDE += -I$(WEAP_SRC)/Security
INCLUDE += -I$(WEAP_SRC)/Thread
INCLUDE += -I$(WEAP_SRC)/Framework
INCLUDE += -I$(WEAP_SRC)/Redis
INCLUDE += -I$(WEAP_SRC)/MySQL
INCLUDE += -I$(WEAP_SRC)/CURL

INCLUDE += -I$(TEST_SRC)/System
INCLUDE += -I$(TEST_SRC)/Security
INCLUDE += -I$(TEST_SRC)/Thread
INCLUDE += -I$(TEST_SRC)/Framework
INCLUDE += -I$(TEST_SRC)/Redis
INCLUDE += -I$(TEST_SRC)/MySQL
INCLUDE += -I$(TEST_SRC)/CURL


INCLUDE   +=  -I$(LIB_PATH)/gtest/include


LIBS     += $(WEAP_LIB) 


#CFLAGS   +=  -isystem

# Setting for compile
CFLAGS   +=  -I$(LIB_PATH)/gtest/include
LIBS     +=  -L$(LIB_PATH)/gtest/lib -lgtest_main -lgtest -lpthread

# Target to create
TEST_OBJS := $(patsubst $(TEST_SRC)/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/*.cpp)) \
			$(patsubst $(TEST_SRC)/System/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/System/*.cpp)) \
			$(patsubst $(TEST_SRC)/Security/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/Security/*.cpp)) \
			$(patsubst $(TEST_SRC)/Thread/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/Thread/*.cpp)) \
			$(patsubst $(TEST_SRC)/Framework/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/Framework/*.cpp)) \
			$(patsubst $(TEST_SRC)/MySQL/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/MySQL/*.cpp)) \
			$(patsubst $(TEST_SRC)/Redis/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/Redis/*.cpp)) \
			$(patsubst $(TEST_SRC)/CURL/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/CURL/*.cpp)) \

$(TEST_MAIN) : $(WEAP_LIB) $(TEST_OBJS)
	#$(CC) -O -lc -o $@ $(CFLAGS) $^ $(LIBS)
#	$(CC) -g -lc -o $@ $(CFLAGS) $^ $(LIBS) 
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) 

$(TEST_OBJ)/%.o :  $(TEST_SRC)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/System/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/Security/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/Thread/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/Framework/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/Redis/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/MySQL/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ)/%.o :  $(TEST_SRC)/CURL/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

# Create libweap-framework.a 
WEAP_OBJS := $(patsubst $(WEAP_SRC)/System/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/System/*.cpp)) \
			$(patsubst $(WEAP_SRC)/Security/%.cpp, $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Security/*.cpp)) \
			$(patsubst $(WEAP_SRC)/Thread/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Thread/*.cpp)) \
			$(patsubst $(WEAP_SRC)/Framework/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Framework/*.cpp)) \
			$(patsubst $(WEAP_SRC)/MySQL/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/MySQL/*.cpp)) \
			$(patsubst $(WEAP_SRC)/Redis/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Redis/*.cpp)) \
			$(patsubst $(WEAP_SRC)/CURL/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/CURL/*.cpp)) \


$(WEAP_LIB) : $(WEAP_OBJS) 
	@ar rv $@ $^

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/System/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Security/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Thread/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Framework/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@	

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/MySQL/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@	

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Redis/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@	

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/CURL/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@	

DEPS = $(patsubst %.o, .%.d, $(TEST_OBJS), $(WEAP_OBJS))


clean:
	rm -f $(WEAP_OBJ)/*.o $(WEAP_LIB) $(TEST_MAIN)
