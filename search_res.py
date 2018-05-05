#set encoding=utf-8
"""
/*
 * File Name: search_res.py
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Mon Apr 30 16:09:09 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 检索相似案情裁判文书 
*/ 
"""

import sys
import os
import MySQLdb
import json
import db_conf as conf

def select_keywords_in_table():
    """ 从数据库表中选择裁判文书的关键词信息
    """
    try:
        conn= MySQLdb.connect(
                host = conf.mysql_host,
                port = conf.mysql_port,
                user = conf.mysql_user,
                passwd = conf.mysql_pwd,
                db = conf.mysql_db,
                charset="utf8"  
              )
        cur = conn.cursor()
    
        #sqli = 'select id, keywords from wenshu_list where keywords != "" limit 500' 
        sqli = 'SELECT id, keywords  FROM wenshu_list WHERE id >= (SELECT floor(RAND() * (SELECT MAX(id) FROM wenshu_list))) ORDER BY id LIMIT 1000'
    
        cur.execute(sqli)
        conn.commit()
   
        res = cur.fetchall()
        cur.close()
        conn.close()
        return res
    except Exception as ex:
        print str(ex)
        pass

def select_maininfo_in_table(_id):
    """根据id查询裁判文书的关键信息，用于展示在网页上
    """
    try:
        conn= MySQLdb.connect(
                host = conf.mysql_host,
                port = conf.mysql_port,
                user = conf.mysql_user,
                passwd = conf.mysql_pwd,
                db = conf.mysql_db,
                charset="utf8"  
              )
        cur = conn.cursor()
    
        sqli = 'select name, court, date , docid from wenshu_list where id = ' + str(_id)
        cur.execute(sqli)
        conn.commit()
   
        res = cur.fetchone()
        cur.close()
        conn.close()
        return res
    except Exception as ex:
        print str(ex)
        pass

def sortedDic(adict):
    """对字典按键排序
    """
    keys = adict.keys()
    keys.sort(reverse = True)
    return [(key, adict[key])  for key  in keys]

#获取用户案情输入，并抽取关键词信息
user_contents = sys.argv[1]
user_keywords = os.popen('./info_extract/a.out "' + user_contents + '"').read()

#print user_keywords

keywords = select_keywords_in_table()
sim_res = dict()
count = 0
for i in range(len(keywords)):
    #计算数据库中每个裁判文书的关键词信息与用户案情关键词信息的相似度
    kw = keywords[i][1].encode("utf-8") 
    sim = os.popen('./sim_calc/a.out "' + user_keywords + '" "' + kw + '"').read()
    
    if sim != "-nan": #相似度不为0的情况
        sim_res[float(sim)] = keywords[i][0]
        count += 1

    if(count == 10): #考虑到时间效率问题，一次只给用户返回10条相似案情裁判文书
        break



json_res = dict()
index = 0
for r in sortedDic(sim_res):
    #print r[0], "\t", r[1]
    tmp1 = select_maininfo_in_table(r[1])
    
    tmp2 = dict()
    tmp2["name"] = tmp1[0]
    tmp2["court"] = tmp1[1]
    tmp2["date"] = str(tmp1[2])
    tmp2["score"] = str(r[0])[0:4]
    tmp2["docid"] = tmp1[3]
    tmp2["user_contents"] = user_contents
    json_res[index] = tmp2
    index += 1
    if(index == 20):
        break


print json.dumps(json_res)
