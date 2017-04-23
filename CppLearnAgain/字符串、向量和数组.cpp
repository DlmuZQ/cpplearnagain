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