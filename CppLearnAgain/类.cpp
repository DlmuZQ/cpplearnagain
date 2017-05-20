########################################(一)##############################################
struct Sales_data
{
	//构造函数
	Sales_data() = default;//c++11新标准
	Sales_data(const std::string &s):bookNo(s){ }
	Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(p*n) { }

	std::string isbn() const {return bookNo;}
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
Sales_data add(const Sales_data&,const Sales_data&);
std::ostream &print(std::ostream &,const Sales_data&);
std::istream &read(std::istream &,Sales_data&);

对以上代码作相关说明：
1、定义在类内部函数是隐式的inline函数;

2、代码如下
Sales_data total;
total.isbn();
编译器负责把total的地址传递给isbn的隐式形参this；

3、isbn()函数后的const，修改隐式this指针的类型，
   std::string isbn() const {return bookNo;}  <=> std::string Sales_data::isbn(const Sales_data * const this){return this->isbn;}//伪代码

4、不依赖于默认构造函数的三个原因：
   a、编译器只会在发现没有定义任何构造函数时，生成默认构造函数
   b、对于某些内置类型或者复合类型（数组和指针）的对象被默认初始化时，至将是为定义
   c、不能为某些类生成默认构造函数；比如当该类中的包含一个没有默认构造函数的类型成员时

########################################(二)##############################################
class Screen;
1、这种声明为前向声明（不完全类型），可以定义其指针、引用、或者作为函数的参数或返回值（终于理解了以前链表结构体中的指针类型为啥有效）。

########################################(三)##############################################
struct X
{
	friend void f() {/*...*/}
	X() {f();} // error,f还没有声明
	void g();
	void h();
};
void X::g(){return f();}//error,f还没有声明
void f();
void X::h(){return f();}
1、友元函数必须在类外部声明后才能使用。
########################################(四)##############################################
class Sales_data{
public:
	//非委托构造函数初始化对应成员变量
	Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(p*n) { }
	//以下为委托构造函数
	Sales_data():Sales_data("",0,0){}
	Sales_data(std::string s):Sales_data(s,0,0){}
	Sales_data(std::istream &is):Sales_data(){read(is,*this);}
}

注意：
Sales_data obj();//声明了一个函数
Sales_data obj;//使用默认构造函数

int ia = new int;//不初始化，值为随意的
int ib = new int();//初始化为0
########################################static#############################################
1、static 关键字只能出现在类内部的声明语句中；
2、static 数据成员可以是不完全类型；
3、可以使用 static 成员作为类默认参数；