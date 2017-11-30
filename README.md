建立一个能群聊和一对一聊天的安全通讯工具
===================
###主要构思
* 一对一聊天采用分布式，聊天时无需服务器的介入
* 群聊由服务器维护群组，标记群主，只能由群主删群
* 发送的信息采用加密发送
* 连接套接字处采用超时机制防止拒绝服务攻击
* 服务器为守护进程，注意日志的编写


###主要流程
* 刚登录进入后显示在线成员和群
* 输入对应序号后由服务器(群)or客户端(一对一)建立连接
* 服务器维护每个登入的客户，客户离开前告诉服务器自己已离开
