#encoding=utf-8
"""
/*
 * File Name: get_ip_proxy.py
 * Author: xuhaoguang (hgxu1993@163.com)
 * Created Time: Sun Apr 22 15:39:25 2018
 * copyright (c) 2017 for xuhaoguang. All Right Reserved
 * @brief: 获取ip代理
*/ 
"""
import sys
import requests
import re

s = requests.session()

html = s.get(url = "http://www.89ip.cn/apijk/?&tqsl=100&sxa=&sxb=&tta=&ports=80&ktip=&cf=1")
result = re.findall(r"\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b", html.content)

for ip in result:
    try:  
        #r = requests.get('http://www.baidu.com', proxies={"https": ip + ':8080'}, timeout=0.05)
        r = s.post(
                url = 'http://www.ip3389.com/ip/check/',
                data = {
                    'proxy': ip + ':80',
                } 
            )
        #print type(r.content)
        res = eval(r.content)
        #print res
        #print res.get('time')
        if (res.get('is_valid') and res.get('time') < '1.000'):
            print ip
        #if (r.status_code == 200):
        #    print ip
        #    print r.content

        #print r
    except Exception as ex:  
        print str(ex)
        #print('connect failed' + ip) 

