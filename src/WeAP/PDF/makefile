
TEST_SRC = .
TEST_OBJ = .
CC       := g++

TEST_MAIN := ./main.bin

#LIBS = -L/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src -rdynamic -lpodofo /usr/local/lib/libfontconfig.so /usr/local/lib/libz.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libz.so /usr/local/lib/libtiff.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libtiff.so -Wl,-rpath,/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src:/usr/local/lib


# podofo
#INCLUDE += -I/usr/local/include
#LIBS    += -L/usr/local/lib -rdynamic -lpodofo

LIBS += -L/usr/local/lib -rdynamic -lpodofo /usr/local/lib/libfontconfig.so /usr/local/lib/libz.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libz.so /usr/local/lib/libtiff.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libtiff.so -Wl,-rpath,/usr/local/lib

# Target to create
TEST_OBJS := $(patsubst $(TEST_SRC)/%.cpp,$(TEST_OBJ)/%.o,$(wildcard $(TEST_SRC)/*.cpp))

$(TEST_MAIN) : $(WEAP_LIB) $(TEST_OBJS)
	$(CC) -g -lc -o $@ $(CFLAGS) $^ $(LIBS) 


$(TEST_OBJ)/%.o :  $(TEST_SRC)/%.cpp 
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f ./*.o ./*.bin