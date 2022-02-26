# 使用说明
## 1. 简介
* 本项目是基于python和arduino的b站粉丝实时显示项目。开发板选用esp8266，oled型号为0.96寸128*64。
* 作者b站账号：瑞凤改二：https://space.bilibili.com/6195521; 邮箱：zuiho@wernjw.tk
## 2. 使用说明
* arduino文件中，将setting.h中ssid,password修改为要连接的wifi名和密码。主文件中 第九行 device_name修改为设备名。第10行oled根据自己设备型号修改。
* python文件中，11行修改为自己的设备名，18行及36行中将url中的mid设为需要查询用户的uid。
* 需要的库均可以在arduino ide及pycharm中下载。
## 3.使用效果
* 详见 https://www.bilibili.com/video/BV1wR4y157Qw?spm_id_from=333.999.0.0