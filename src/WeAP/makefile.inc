###################################################################
# @author: xzwang
###################################################################

LIB_PATH = /home/xzwang/WeAP-Framework/deps

INCLUDE += -I/home/xzwang/WeAP-Framework/deps/podofo-0.9.6/src
LIBS    += -L/home/xzwang/WeAP-Framework/deps/podofo-0.9.6/src -rdynamic -lpodofo 


LIBS    += /usr/local/lib/libfontconfig.so /usr/local/lib/libz.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libz.so /usr/local/lib/libtiff.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libtiff.so -Wl,-rpath,/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src:/usr/local/lib



# openssl lib
INCLUDE += -I$(LIB_PATH)/openssl/include
LIBS    += -L$(LIB_PATH)/openssl/lib -lssl
LIBS    += -L$(LIB_PATH)/openssl/lib -lcrypto 

#pthread
INCLUDE += -I/usr/include
LIBS    += -L//usr/lib64/ -lpthread

# mysql lib
INCLUDE += -I/usr/include/mysql
LIBS    += -L/usr/lib64/mysql/ -lmysqlclient

#redis
INCLUDE += -I/usr/local/include
#LIBS    += -L/usr/local/:/usr/local/jpeg/lib -lhiredis
LIBS    += -L/usr/local/lib -lhiredis


#glog
INCLUDE += -I/usr/local/include
LIBS    += -L/usr/local/lib/ -lglog


# podofo
#INCLUDE += -I/usr/local/include
#LIBS    += -L/usr/local/lib -rdynamic -lpodofo

#curl
INCLUDE += -I/usr/local/include
LIBS    += -L/usr/local/lib/ -lcurl

# Setting for compile
CC       := g++
CFLAGS += $(CFLAG)
CFLAGS += $(INCLUDE)

CFLAGS   += -g -DNDEBUG -Wall -fpic -DGLOG_NO_ABBREVIATED_SEVERITIES -std=c++11









