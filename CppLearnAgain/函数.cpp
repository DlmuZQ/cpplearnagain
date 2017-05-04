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

函数值是如何被返回的：返回一个值的方式和初始化一个变量或形参的方式完全一样；返回的值用于初始化调用点的一个临时变量

不要返回局部对象的指针和引用：局部对象会销毁

列表初始化返回值（C++11）
vector<string> process()
{
	//
	//...
	//a和b为string对象
	if(a == b)
		return {};//返回一个空的vect对象
	else if (a > b)
		return {"hello","word"}; //返回vector初始化列表
	else
		return {"hello",a,b};
}
