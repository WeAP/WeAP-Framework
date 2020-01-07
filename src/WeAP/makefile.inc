###################################################################
# @author: xzwang
###################################################################

LIB_PATH = /home/xzwang/WeAP-Framework/dependency

INCLUDE += -I/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src
LIBS    += -L/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src -rdynamic -lpodofo 


LIBS    += /usr/local/lib/libfontconfig.so /usr/local/lib/libz.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libz.so /usr/local/lib/libtiff.so -lcrypto -lcrypto -lssl -lpthread /usr/local/lib/libfreetype.so /usr/local/lib/libpng.so /usr/local/lib/libtiff.so -Wl,-rpath,/home/xzwang/WeAP-Framework/dependency/podofo-0.9.6/src:/usr/local/lib



# openssl lib
INCLUDE += -I$(LIB_PATH)/openssl/include
LIBS    += -L$(LIB_PATH)/openssl/lib -lssl
LIBS    += -L$(LIB_PATH)/openssl/lib -lcrypto 

# mysql lib
#INCLUDE += -I$(LIB_PATH)/mysql/include
#LIBS    += -L$(LIB_PATH)/mysql/lib -lmysqlclient

#INCLUDE += -I/data/mm64/xzwang/QQMail/mm3rd/mysql
#LIBS    += -L/data/mm64/xzwang/QQMail/mm3rd/mysql/lib64 -lmysqlclient


INCLUDE += -I/usr/include/mysql
LIBS    += -L/usr/lib64/mysql/ -lmysqlclient

INCLUDE += -I/usr/local/include
LIBS    += -L/usr/local/lib/ -lglog


# podofo
#INCLUDE += -I/usr/local/include
#LIBS    += -L/usr/local/lib -rdynamic -lpodofo



# Setting for compile
CC       := g++
CFLAGS += $(CFLAG)
CFLAGS += $(INCLUDE)

CFLAGS   += -g -DNDEBUG -Wall -fpic -DGLOG_NO_ABBREVIATED_SEVERITIES -std=c++11









