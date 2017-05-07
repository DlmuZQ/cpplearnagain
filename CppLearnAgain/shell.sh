1、du -h * | sort -nr > $HOME/script.txt
#du 查询当前文件的使用空间，| （管道）传递命令，将当前的结果传递给sort排序
2、su -
#普通用户转超级用户
3、echo $SHELL
#当前shell的名称
4、logout/exit/Ctrl+D
#退出当前shell
5、printf "1";printf "2"
   date 'test' && date
   date || date 'test'
 # ; =>顺序执行，不管是否有错误, && =>第一个正常执行才能进入第二个, || =>第一个失败时，才执行第二个
6、!! #执行最后一条命令
   !# #执行两次命令
7、file [text_file]
#检测文件类型
8、lsattr [filename]
   chattr [filename]
#如果超级用户也不能删除的东西，用lsattr命令查看
9、wall/write
#wall向所有在线用户发送消息；write向指定用户发消息
10、VAR="value"、unset
#生成变量时，=前后不能用空格；unset可以删除变量
11、export VAR="value"
#将变量变成环境变量
12、$*、$#、$@
#!/bin/bash
POS1="$1"
POS2="$2"
POS3="$3"

echo "第一个参数:$1"
echo "第二个参数:$2"
echo "第三个参数:$3"

echo "参数总个数:$#"
echo "参数类容:$@"
13、$
#$+变量名:可以从变量中读取内容
14、read
#read + 变量：向变量中写入信息
15、set
#生成词目录
16、``
#替换命令
#!/bin/bash
now=`date`
echo $now
17、n=`expr 100 + 100`
#运算符使用
18、while <test-com> do <coms> done
#!/bin/bash
number=0
while [ $number -lt 10 ]
do
	#statements
	echo "$number"
	number=`expr $number + 1`
done
echo "done"
19、for <test-com> in <arg-list> do <coms> done
#!/bin/bash
for f in a b c d
do
echo $f
done
echo "done"
20、文件测试
#!/bin/bash
if [ -f file ]
#注意空格
then
	echo "file exists"
else
	echo "not exists"
fi
if [ -d file ]
then
	echo "file is a directory"
else
	echo "file is not a directory"
fi
21、pwd;date;cal
#多个命令用；隔开