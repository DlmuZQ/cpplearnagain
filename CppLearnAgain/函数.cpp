函数的形参初始化的机理与变量初始化一样

数组形参

/*
数组具有两个特殊的性质：
1、不允许拷贝数组
2、使用数组时会将转换成指针
*/
//等价的三种方式
void print(const int *);
void print(const int[]);
void print(const int[10]);

//管理指针参数的三种方法
//1、数组本身含一个结束标志
void print(const char *cp){
	if(cp)
		while(*cp)
			cout << *cp++;
}
//2、使用标准库规范
void print(const int *beg,const int *end){
	while(beg != end)
		cout << *beg++;
}
//3、显示传递一个数组长度
void print(const int a[],int size){

}
