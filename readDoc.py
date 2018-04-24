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
document = docx.Document("wenshu3/" + sys.argv[1])

docText = ''.join([
    paragraph.text.encode('utf-8') for paragraph in document.paragraphs
])

#TextRes = '"' + docText.replace('\\n', '') + '"' 
TextRes = '"' + docText.replace('\n', '').replace(' ', '').replace('\t', '')+ '"' 
print TextRes
