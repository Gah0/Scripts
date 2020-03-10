import urllib.request
import urllib.parse
from fake_useragent import UserAgent
import json

url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=http://www.youdao.com/"
data = {}
data['type'] = 'AUTO'
data['i'] = '参数'
data['doctype'] = 'json'
data['xmlVerson'] = '2.1'
data['keyfrom'] = 'fanyi.web'
data['ue'] = 'UTF-8'
data['typeResult'] = 'true'
data = urllib.parse.urlencode(data).encode('utf-8')
response = urllib.request.urlopen(url,data)
html = response.read().decode('utf-8')
print(html)  #{"errorCode":50}


json.loads(html)
