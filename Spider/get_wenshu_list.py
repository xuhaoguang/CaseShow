#encoding=utf-8
import random
import requests
import time
import execjs
import json
import sys
import MySQLdb
import chardet
import db_conf as conf

reload(sys)
sys.setdefaultencoding('utf8')

ip_pool = [
        'http://60.177.229.56:18118',
        'http://60.177.224.135:18118',
        'http://218.72.110.206:18118',
        'http://203.174.112.13:3128',
        'http://114.55.3.98:7777',
        'http://119.139.198.222:3128',
        'http://113.12.72.24:3128',
        'http://112.95.91.101:9999',
        'http://122.114.31.177:808',
        'http://61.135.217.7:80',
        'http://112.115.57.20:3128',
        'http://222.76.187.56:8118',
        'http://180.168.198.141:18118',
        'http://183.159.90.121:18118',
        'http://116.196.120.31:808',
    ]

headers = {
        "Accept": "*/*",
        "Accept-Encoding": "gzip, deflate",
        "Accept-Language": "zh-CN,zh;q=0.9",
        "Connection": "keep-alive",
        "Content-Length": "285",
        "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
        "Host": "wenshu.court.gov.cn",
        "Origin": "http://wenshu.court.gov.cn",
        "Referer": "http://wenshu.court.gov.cn/list/list/?sorttype=1&number=VSLFH5P4&guid=262990df-a52c-a6976bc4-f10127576726&conditions=searchWord+%E5%A9%9A%E5%A7%BB%E5%AE%B6%E5%BA%AD%E3%80%81%E7%BB%A7%E6%89%BF%E7%BA%A0%E7%BA%B7+++%E4%BA%8C%E7%BA%A7%E6%A1%88%E7%94%B1:%E5%A9%9A%E5%A7%BB%E5%AE%B6%E5%BA%AD%E3%80%81%E7%BB%A7%E6%89%BF%E7%BA%A0%E7%BA%B7",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36",
        "X-Requested-With": "XMLHttpRequest",
    }

def insert_to_db(values):
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
    
        sqli = 'insert ignore into wenshu_list values(0, %s, %s, %s, %s, %s, %s, %s, %s, %s)' 
    
        cur.executemany(sqli, values)
        
        conn.commit()
        cur.close()
        conn.close()
    
    except Exception as ex:
        print str(ex)
        pass

def createGuid():
    return hex(int((random.random() + 1) * 0x10000))[3:]

def calc_vl5x(vjkl5):
    f = open("/home/xuhaoguang/vl5x.js", 'r')
    line = f.readline()
    htmlstr = ''
    
    while line:
        htmlstr += line
        line = f.readline()
    
    ctx = execjs.compile(htmlstr)
    vl5x = ctx.call('getKey', vjkl5)
    vl5x = str(vl5x) 
    return vl5x

for page in range(53, 101):
     
    guid = createGuid() + createGuid() + "-" + createGuid() + "-" + createGuid() + createGuid() + "-" + createGuid() + createGuid() + createGuid()
    data = {
        'guid': guid
    } 
    #print guid
    s = requests.session()
    #s.proxies = {
    #    #'http': random.choice(ip_pool)
    #    'http': 'http://39.134.61.76:80'
    #    #'https': 'socks5://127.0.0.1:8087'}
    #} 
    try:
        cookie_res = s.post(
                url = 'http://wenshu.court.gov.cn/list/list/?sorttype=1&number=VSLFH5P4&guid=262990df-a52c-a6976bc4-f10127576726&conditions=searchWord+%E5%A9%9A%E5%A7%BB%E5%AE%B6%E5%BA%AD%E3%80%81%E7%BB%A7%E6%89%BF%E7%BA%A0%E7%BA%B7+++%E4%BA%8C%E7%BA%A7%E6%A1%88%E7%94%B1:%E5%A9%9A%E5%A7%BB%E5%AE%B6%E5%BA%AD%E3%80%81%E7%BB%A7%E6%89%BF%E7%BA%A0%E7%BA%B7',
                headers = headers,
                data = data
        )

        vjkl5 = requests.utils.dict_from_cookiejar(cookie_res.cookies)['vjkl5']
    except Exception as ex:
        print str(ex)
        continue
    
    #print vjkl5
   
    try:
        number_res = s.post(
                url = 'http://wenshu.court.gov.cn/ValiCode/GetCode',
                headers = headers,
                data = data,
        )
        number = number_res.content
        #print number
        vl5x = calc_vl5x(vjkl5)
        #print vl5x
    except Exception as ex:
        print str(ex)
        continue

    
    
    data1 = {
            #'Param': '案由:民事案由,全文检索:财产纠纷,裁判日期:2017-07-01  TO 2017-12-31',
            'Param': '全文检索:财产纠纷,裁判日期:2013-10-01  TO 2013-12-31',
            'Index': page,
            'Page': '20',
            'Order': '法院层级',
            'Direction': 'asc',
            'vl5x': vl5x,
            'number': number,
            'guid': guid, 
    }

    try:
        content_json = s.post(
                url = 'http://wenshu.court.gov.cn/List/ListContent',
                headers = headers,
                data = data1,
                #proxies={
                #    'http': random.choice(ip_pool)
                #} 
        ).content.decode("string_escape")
        content_json =  content_json[1:-1].replace("\\n", '')
        #print content_json
        content_list = eval(content_json)
    except Exception as ex:
        print str(ex)
        continue

    values = []
    for i in range(1, len(content_list)):
        #print type(d)
        #for k, v in content_list[i].items():
            #if(k != '裁判要旨段原文'):
                #print k.encode('utf8'), ' : ', v.encode('utf8')
        docid = content_list[i].get('文书ID')

        #print chardet.detect(content_list[i].get('案件名称'))
        name = content_list[i].get('案件名称')
        #print name
        doctype = content_list[i].get('案件类型')
        chengxu = content_list[i].get('审判程序')
        court = content_list[i].get('法院名称')
        date = content_list[i].get('裁判日期')
        number = content_list[i].get('案号')
        download = 0
        keywords = ''
        values.append((docid, name, doctype, chengxu, court, date, number, download, keywords))
        #print (docid, name, doctype, chengxu, court, date, number, download, keywords)
        #print values

    insert_to_db(values)
    print "\n 已经完成第 ", page , " 页的插入\n" 
    #store_res = json.loads('{' + content_json + '}')
    #print store_res
    #for key in store_res:
    #    print key
    #    print store_res.get(key)
    time.sleep(2)
