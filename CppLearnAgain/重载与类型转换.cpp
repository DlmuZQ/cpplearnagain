########################################重载运算与类型转换##############################################
1、基本概念
a、重载运算符不能含有默认参数，除了operator()；
b、运算符或者是类成员，或者至少含一个类类型参数；
int operator+(int,int);//error

2、相等运算符和不相等运算符中的一个应该把工作委托给另一个
bool operator=(const A &a1,const A &a2){....}
bool operator!=(const A &a1,const A &a2){
	return !(a1 == a2);
}

3、接受花括号赋值的运算符
class A{
public:
	A &operator=(initializer_list<string>);
};

4、下标运算符：通常包括两个版本常量版本与非常量版本
//程序1
class Test{
public:
	//
	//...
	//
	string & operator[](int n){
		return p_test[n];
	}
	const string & operator[](int n) const{
		return p_test[n];
	}
private:
	string *p_test;
};

Test t1("Test");
const Test t = t1;
t1[0] = "t1"; //ok，调用非常量版本
t[0] = "t";//error

5、重载前置与后置（++、--）
区别：返回值（对象的引用、对象常量）与参数（无参数，int（默认为0））不同；
	  操作顺序；
//程序2
class UPInt{
public:
	UPInt& operator++();			//前置
	const UPInt operator++(int);	//后置
	UPInt& operator+=(int);
};
UPInt& UPInt::operator++(){
	*this += 1;						//累加
	return *this;					//取出
}
const UPInt UPInt::operator++(int){
	UPInt old = *this;				//取出
	++(*this);						//累加
	return old;						//返回未累加之前的值
}

6、函数对象（常常作为泛型算法的实参）
//程序3
//普通函数
int add(int a,int b){
    return a+b;
}
//lambda
auto mod = [](int a,int b){return a%b;};
//函数对象类
struct divide{
    int operator() (int a,int b){
        return a/b;
    }
};
//函数表，使用map实现，并利用function模板存储不同的可调用类型（调用形式必须相同）
void test_maptable(){
    map<string,function<int(int,int)>> binops = {
    {"+",add},
    {"-",minus<int>()},
    {"/",divide()},
    {"*",[](int a,int b){return a*b;}},
    {"%",mod}
};
    cout << binops["+"](10,5) << endl;
    cout << binops["-"](10,5) << endl;
    cout << binops["/"](10,5) << endl;
    cout << binops["*"](10,5) << endl;
    cout << binops["%"](10,5) << endl;
}