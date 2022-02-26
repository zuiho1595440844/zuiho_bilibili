# 导入模块
import json
import time
import dweepy
import requests

# 循环，将每一页的数据都抓取到
while True:
    result_1 = 0
    result_2 = 0
    thing_name="zuiho_bilibili" #dweet设备名，与arduino一致
    for i in range(1, 50): #循环页数，将每个视频播放量评论数相加
        # 模拟浏览器
        headers = {
            'User-Agent': ' Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36'
        }
        # 包含待爬取信息的url,将mid改为要爬取用户的
        url = 'https://api.bilibili.com/x/space/arc/search?mid=6195521&pn=%s&ps=25&jsonp=jsonp' % (i)
        #url="https://member.bilibili.com/x/web/index/stat"
        # 访问url
        r = requests.get(url, headers)
        # 将爬取道德json格式的数据转化为字典
        text = json.loads(r.text)
        print(text)
        # 取出嵌套字典里我们想要的部分
        # 这里的字典嵌套在控制台里其实看的很清楚，我在上面的截图里圈了出来
        res = text['data']['list']['vlist']
        for item in res:
            # 以列表的形式取出对我们有用的数据
            list = ['av: ' + str(item['aid']), ' 视频标题: ' + item['title'], ' 播放量: ' + str(item['play']),
                    ' 评论条数: ' + str(item['video_review'])]
            # 转化格式
            result_1 = result_1 + int(str(item['play']))
            result_2 = result_2 + int(str(item['video_review']))
    # 包含待爬取信息的url,将mid改为要爬取用户的
    url_2 = 'https://api.bilibili.com/x/relation/stat?vmid=6195521&jsonp=jsonp'
    r_2 = requests.get(url_2)
    print("follower: " + str(r_2.json()["data"]["follower"]))
    print("comment: " + str(result_2))
    print("play: " + str(result_1))
    dweet = {"follower: ": str(r_2.json()["data"]["follower"]),
             "comment: ":str(result_2),
             "play: ": str(result_1)}
    dweepy.dweet_for(thing_name, dweet)



    time.sleep(10)