1、du -h * | sort -nr > $HOME/script.txt
#du 查询当前文件的使用空间，| 传递命令，将当前的结果传递给sort排序
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