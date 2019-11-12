###################################################################
# @author: xzwang
###################################################################

LIB_PATH = /home/xzwang/WeAP/dependency


# openssl lib
INCLUDE += -I$(LIB_PATH)/openssl/include
LIBS    += -L$(LIB_PATH)/openssl/lib -lssl
LIBS    += -L$(LIB_PATH)/openssl/lib -lcrypto 

# mysql lib
INCLUDE += -I$(LIB_PATH)/mysql/include
LIBS    += -L$(LIB_PATH)/mysql/lib -lmysqlclient


# Setting for compile
CC       := g++
CFLAGS += $(CFLAG)
CFLAGS += $(INCLUDE)

CFLAGS   += -g -DNDEBUG -Wall -fpic









