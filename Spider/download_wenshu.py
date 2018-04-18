# -*- coding: utf-8 -*-
import random
import requests
import time
import execjs
import json
import sys
import MySQLdb
import chardet
import db_conf as conf
import codecs
reload(sys)
sys.setdefaultencoding('utf-8')

ip_pool = [
        'http://116.196.120.31:808',
    ]

headers = {
    "POST": "/CreateContentJS/CreateListDocZip.aspx?action=1 HTTP/1.1",
    "Host": "wenshu.court.gov.cn",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Accept-Language": "en-us",
    "Accept-Encoding": "gzip, deflate",
    "Content-Type": "application/x-www-form-urlencoded",
    "Origin": "http://wenshu.court.gov.cn",
    "Content-Length": "584",
    "Connection": "keep-alive",
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_5) AppleWebKit/601.6.17 (KHTML, like Gecko) Version/9.1.1 Safari/601.6.17",
    "Referer": "http://wenshu.court.gov.cn/list/list/?sorttype=1&number=KUMJQJMR&guid=92eff18c-d297-9243811f-9a0f92f10d9b",
}

def select_doc_info():
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
    
        sqli = 'select id, docid, name, date from wenshu_list where download = 0 limit 2000' 
    
        cur.execute(sqli)
        conn.commit()
   
        res = cur.fetchall()
        cur.close()
        conn.close()
        return res
    except Exception as ex:
        print str(ex)
        pass

def update_db_download(is_download, docid):
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
    
        sqli = 'update wenshu_list set download = %s where id = %s' 
    
        cur.execute(sqli % (is_download, docid))
        
        conn.commit()
    
        cur.close()
        conn.close()
    
    except Exception as ex:
        print str(ex)
        pass

s = requests.session()
s.encoding  = 'utf-8'
s.proxies = {
    'http': 'http://39.134.10.15:8000'
} 


try:
    res = select_doc_info()
    for i in range(len(res)):
        did = res[i][0] 
        docid = res[i][1].encode('utf-8')
        #print docid
        
        docname = res[i][2].encode('utf-8')
        #print docname 
        
        docdate = str(res[i][3]).encode('utf-8')
        if (docdate == '0000-00-00'): #处理脏数据
            update_db_download(3, did)
            continue
        #print docdate
        
        docids = docid + '|' + docname + '|' + docdate
        #print docids
        data1 = {
            'docids':docids,
            "conditions": " ",
            "keyCode": " "
        }
        
        content_json = s.post(
                url = 'http://wenshu.court.gov.cn/CreateContentJS/CreateListDocZip.aspx?action=1',
                data = data1,
                headers = headers,
        )
        
        if (content_json.status_code == 200):
            try:
                filepath ="doc/"+ docid + '|' + docname[0:210] +".doc"
                savefile = codecs.open(filepath, "wb")
                savefile.write(content_json.content)
                savefile.close()
                update_db_download(1, did)
                print "当前已经下载完 ", i , " 条数据" 
            except Exception as ex:
                print "==================ERROR================"
                print str(ex)
                pass
        #time.sleep(0.2)
except Exception as ex:
    print str(ex)
