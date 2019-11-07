###################################################################
# @author: xzwang
# @date: 2018-06-01 
##################################################################

include makefile.inc

WEAP_SRC = .
WEAP_OBJ = ../../obj
WEAP_BIN = ../../bin
WEAP_LIB  = $(WEAP_BIN)/libweap-framework.a


INCLUDE += -I$(WEAP_SRC)/System
INCLUDE += -I$(WEAP_SRC)/Security
INCLUDE += -I$(WEAP_SRC)/Thread
INCLUDE += -I$(WEAP_SRC)/Framework


#WEAP_OBJS := $(patsubst $(WEAP_SRC)/System/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/System/*.cpp)) \
		$(patsubst $(WEAP_SRC)/Security/%.cpp, $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Security/*.cpp)) \
		$(patsubst $(WEAP_SRC)/Thread/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Thread/*.cpp)) \
		$(patsubst $(WEAP_SRC)/Framework/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Framework/*.cpp)) \

WEAP_OBJS := $(patsubst $(WEAP_SRC)/System/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/System/*.cpp)) \
		$(patsubst $(WEAP_SRC)/Thread/%.cpp,   $(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Thread/*.cpp)) \
		$(patsubst $(WEAP_SRC)/Framework/%.cpp,$(WEAP_OBJ)/%.o, $(wildcard $(WEAP_SRC)/Framework/*.cpp)) \

$(WEAP_LIB) : $(WEAP_OBJS) 
	@ar rv $@ $^

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/System/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

#$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Security/%.cpp 
#	$(CC) $(CFLAGS) -c $< -o $@

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Thread/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@

$(WEAP_OBJ)/%.o :  $(WEAP_SRC)/Framework/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@	
	
.PHONY : clean install
clean:
	rm -f $(WEAP_OBJ)/*.o $(WEAP_LIB) 

install:
#	cp * /usr/local/weap-framework/

