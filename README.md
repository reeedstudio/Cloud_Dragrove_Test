Cloud_Dragrove_Test
===================

首先需要把dragrove和电脑连接，打开硬串口，进行操作。
使用串口AT命令,有三种命令。每个命令以换行结尾（在串口调试助手上选择发送新行）

1。 添加设备：ATADD #id （注：不用‘#’，仅表示这是个数）
    ATADD后跟着一个空格，然后是一个1-9的数字，表示deviceID。sensorID和actuatorID固定为1和200

2。 删除设备：ATDEL #id
    删除deviceID = id的设备
    
3。 推送数据：ATPUSH
    推送一个0-1023的随机数到deviceID = id的设备。
    
如果命令有误，会返回ERR ATCMD
如果命令被接受，会返回正确的信息

