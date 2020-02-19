#!/usr/bin/python3
 
import pymysql



import logging

#import log.logger

from utils.logger import Logger

#logger = logger()
logger.info("12345")

#logging.basicConfig(level=logging.INFO, filename='test.log', filemode='w',format="%(levelname)s:%(message)s")


logging.basicConfig(level=logging.INFO, format="%(levelname)s:%(message)s")


logging.info("打印信息")
logging.warning("警告信息")
logging.error("出现了错误")



# 打开数据库连接
db = pymysql.connect("localhost","root","xzwang@wxpay", "account_db")
 
# 使用 cursor() 方法创建一个游标对象 cursor
cursor = db.cursor()
 
# 使用 execute()  方法执行 SQL 查询 
#cursor.execute("SELECT VERSION()")
#cursor.execute("desc account_db.account")

 
# 使用 fetchone() 方法获取单条数据.
#data = cursor.fetchone()
 
#print ("Database version : %s " % data)

# SQL 查询语句
#sql = "SELECT accountId, accountType, currencyType, balance, freezedBalance FROM account_db.account \
#       WHERE accountId > %s" % (100001)
sql = "desc account_db.account"
try:
   # 执行SQL语句
   cursor.execute(sql)
   # 获取所有记录列表
   results = cursor.fetchall()
   print ("Field, Type, Null, Key, Default")
   for row in results:
      Field = row[0]
      Type = row[1]
      Null = row[2]
      Key = row[3]
      Default = row[4]
       # 打印结果
      print ("%s, %s, %s, %s, %s" % \
             (Field, Type, Null, Key, Default ))
except:
   print ("Error: unable to fetch data")



# 关闭数据库连接
db.close()
