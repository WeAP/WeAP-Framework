###################################################################
# @author: xzwang
# @date: 2018-06-01 
##################################################################

LIB_PATH = /home/xzwang/WeAP-Framework/dependency


# openssl lib
INCLUDE += -I$(LIB_PATH)/openssl/include
LIBS    += -L$(LIB_PATH)/openssl/lib -lssl
LIBS    += -L$(LIB_PATH)/openssl/lib -lcrypto 

# mysql lib
#INCLUDE += -I$(LIB_PATH)/mysql/include/mysql
#LIBS    += -L$(LIB_PATH)/mysql/lib/mysql -lmysqlclient


# Setting for compile
CC       := g++
CFLAGS += $(CFLAG)
CFLAGS += $(INCLUDE)

CFLAGS   += -g -DNDEBUG -Wall -fpic









