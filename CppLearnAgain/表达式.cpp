#==================================基础=============================================#
左值与右值的区别：
当对象用作左值时，用的是对象的身份（也就是内存中的位置）；而用作右值时，则用的是对象的值（内容）。

/*
布尔值不应参与运算
*/
bool b = true;
bool b2 = -b;//b2将提升为int类型，-1

//以下程序
std::vector<int> v{1,2,3,4};
auto obeg = v.begin();
while(obeg != v.end())
	cout << *obeg++ << endl;
/*
1、vector初始化方式
2、递增运算符的优先级高于解应用运算符
3、最有一句等价于：
	cout << *obeg << endl;
	obeg ++;
*/

/*
sizeof相关
1、对应用类型执行sizeof，得到被应用类型的大小
2、对指针执行sizeof，得到指针本身所占有的空间
3、对解引用指针执行sizeof，得到指针指向的对象的大小，并且指针不需要有效
4、对数组执行sizeof，得到数组长度*元素所占内存大小的值；不会将数组转换成指针
5、对string、vector只会返回固定值的大小。
*/
double b = 0.2;//8
float f = 1;//4
float *p = &f;//4
double &rb = b;//rb 8,&rb 4

string s1("1234");// 4
string s2("12");// 4
vector<int> v1{1,2};// 14
vector<int> v2{1,3,2};// 14
//不同环境得到的结果不同

//by the way
void *p = &d;
double *dp = static_cast<double *>(p);
//static_cast可以找回存在于void*中的指针
#==================================switch=============================================#
//by the way
switch结构以一个空default结尾，则该default后面必须跟上一条空语句或一个块

case true:
	//因为执行的流可能绕开下面的初始化语句，所以该switch语法不合法
	string file_name;//错误，控制流绕过一个隐式转换
	int ival = 0;//错误，控制流绕过一个显示转换
	int jval;//正确，没有初始化
	break;
case false:
	jval = next_num();
	if(file_name.empty())
		//...