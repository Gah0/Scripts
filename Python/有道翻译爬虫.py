import hashlib
import random
import time
import requests
import urllib.request
import json

class Youdao:
    def __init__(self,msg):
        self.msg = msg
        self.url = 'http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule'
        self.D = ""
        self.salt = self.get_salt()
        self.sign = self.get_sign()
        self.ts = self.get_ts()

    def get_md(self,value):
        m = hashlib.md5()
        m.update(value.encode('utf-8'))
        return m.hexdigest()

    def get_salt(self):
        s = int(time.time() * 1000) + random.randint(0,10)
        return str(s)

    def get_sign(self):
        sign = 'fanyideskweb' + self.msg + self.salt + self.D
        return self.get_md(sign)

    def get_ts(self):
        s = int(time.time() * 1000)
        return str(s)

    def get_result(self):
        url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=http://www.youdao.com/"
        data = {}
        data['i'] = 'self.msg'
        data['from'] = 'AUTO'
        data['to'] = 'AUTO'
        data['smartresult'] = 'dict'
        data['client'] = 'fanyideskweb'
        data['salt'] = 'self.salt'
        data['sign'] = 'self.sign'
        data['ts'] = 'self.ts'
        data['bv'] = 'AUTO'
        data['doctype'] = 'json'
        data['xmlVerson'] = '2.1'
        data['keyfrom'] = 'fanyi.web'
        data['action'] = 'FY_BY_CLICKBUTTION'

        data = urllib.parse.urlencode(data).encoude('utf-8')
        req = urllib.request.Request(url, data)

        req.add_header('Cookie','JSESSIONID=abcsmjscaIHDMfFrd4o_w; _ntes_nnid=fad296e8fba4a16cb3bec5e33cb1d52e,1578650057089; OUTFOX_SEARCH_USER_ID_NCOO=1645253102.4170382; OUTFOX_SEARCH_USER_ID=417890353@223.73.120.68; ___rl__test__cookies=1583836175807')
        req.add_header('Referer','http://fanyi.youdao.com/')
        req.add_header('User-Agent','Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.43 Safari/537.36 Edg/81.0.416.28')
        response = urllib.request.urlopen(req)
        html = response.read().decode('utf-8')
        #解析json格式字符串，赋值给translate_results
        translate_results = json.loads(html)

        if 'translateResult' in translate_results:
            translate_results = translate_results['translateResult'][0][0]['tgt']
            print("翻译的结果是：%s" % translate_results)
        else:
            print(translate_results)

if __name__ == "__main__":
    a = Youdao('草，我成功啦')
    a.get_result()
