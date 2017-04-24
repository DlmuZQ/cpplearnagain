#==================================string=============================================#
/*
string 类型的读取
*/
int main(){
	string s;
	cin >> s;
	cout << s <<endl;//将自动忽略开始的空格，直到读取到下一个空格
	return 0;
}
//使用getline可以获取整行，并且去掉换行符
int main(){
	string line;
	while(getline(cin,line))
		cout << line <<endl;
	return 0;
}

/*
cctype中包含的一些函数
*/
tolower(c); \\如果c是大写字母，则输出小写；否则不变
toupper(c);\\同理

string s("Hello world!!!");
//转换成大写
for(auto &c : s)//注意为引用
	c = toupper(c);
cout << s << endl;

/*
string 与 C风格字符串转换
*/
string s("Hello world");
char * str = s;//error
char * str = s.c_str();

#==================================vector=============================================#
/*
创建指定数量的元素
*/
std::vector<int> v(10,-1);
std::vector<string> v(10,"hi");
std::vector<int> v(10);

/*
初始化列表与元素数量
*/
std::vector<char> v(10);//10个元素，初始化为null
std::vector<int> v{1,2};//2个y元素

#==================================iterator=============================================#
/*
尾后迭代器
*/
std::vector<int> v(10);
auto s = v.end();

int a[10] = {0};
auto a = &a[10];//int * a = &a[10];
auto s = end(a);//int * s = &a[10];end在iterator头文件中

/*
迭代器返回值根据对象的类型而定，常量则返回const_iterator,否则为iterator
*/
std::vector<int> v1;
const std::vector<int> v2;
auto v1 = v1.begin();
auto v2 = v2.begin();//const_iterator

/*
利用迭代器运算实现二分查找,必须有序
*/
bool binarySearch(std::vector<int> v,int obj){
	auto ibegin = v.begin();
	auto iend = v.end();
	auto mid = ibegin + (iend - ibegin)/2;

	while(mid != iend && *mid != obj){
		if(*mid > obj)
			ibegin = mid + 1;
		else
			iend = mid
		mid = ibegin + (iend - ibegin)/2;
	}
	if (mid != iend)
	{
		return true;
	}
	return false;
}

#==================================数组和指针=============================================#
/*
使用数组作为一个auto变量的初始值时，其推断得到的类型为指针
*/
int ia[] = {1,2,3,4,5};
auto ia2(ia);//ia2为指针指向，ia的第一个元素

decltype(ia) ia3 = {1,2,3,4,5};//ia3为含有5个元素的数组

/*
标准库函数中的begin和end
*/
int ia[] = {1,2,3,4,5};
int *beg = begin(ia);//ia的首元素

std::vector<int> v(begin(ia),end(ia));

#==================================多维数组=============================================#
/*
采用auto打印二维数组
*/
int a[3][3] = {0};
for(const auto &row : a)
	for(const auto col : row)
		cout << col <<endl;

//一下为错误用法,auto row,会解析为int *,因此不允许在int *中遍历
for(auto row : a)
	for(auto col : row)
		cout << col << endl;

