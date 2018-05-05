"""
/*
 * File Name: readDoc.py
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Sun Apr 15 21:13:16 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 
*/ 
"""
import sys
import docx
import os
import MySQLdb
import db_conf as conf

document = docx.Document("/var/local/wenshu/" + sys.argv[1])

docText = ''.join([
    paragraph.text.encode('utf-8') for paragraph in document.paragraphs
])

#TextRes = '"' + docText.replace('\\n', '') + '"' 
TextRes = '"' + docText.replace('\n', '').replace(' ', '').replace('\t', '')+ '"' 
#print TextRes
kw = os.popen('./info_extract/a.out ' + TextRes).read()
print sys.argv[1][0:36]

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

    sqli = 'update wenshu_list set keywords = "%s" where docid = "%s"' % (kw, sys.argv[1][0:36])
    print sqli
    cur.execute(sqli)
    
    conn.commit()
    cur.close()
    conn.close()

except Exception as ex:
    print str(ex)
    pass

