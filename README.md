智慧公交系统
--------------
**大二下学期末实训作业**
* 用 C语言 + Mysql 实现的智慧公交系统。
* 环境 Visual studio 2022   +   Mysql front(mysql 8.0)
* 实现方式在命令行中，没有UI界面，查询信息以表的方式打印

<br>

**实现功能**
* 用户登录，连接数据库查询用户身份
* 普通用户查询系统
  * 普通查询，查询所有公交线路信息
  * 根据车辆编号查询线路信息
  * 根据线路查询相关车辆及站点信息
  * 根据起点站，终点站信息查询相关线路及车辆信息
* 调度员管理系统
  * 可以进行车辆信息的增删改查
  * 可以增删改排班信息
* 管理员系统
  * 用户信息管理
    * 添加用户角色
    * 修改用户状态
    * 删除用户
  * 车辆管理，增删改
  * 线路管理，增删改
  * 排班管理，增删改
* 个人信息修改

<br>

**老师指出后添加的功能**
* 登录时密码输入隐藏为‘*’，密码中必须包含大小写字母 + 数字
* 身份证必须为标准格式
* 车牌号必须为标准格式（例：鄂B-64912）
