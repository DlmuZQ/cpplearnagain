########################################拷贝控制##############################################
1、区分直接初始化、拷贝初始化以及拷贝赋值
//直接初始化
string dots(10,'.');
string s(dots);
//拷贝初始化
string s2 = s;
string s3 = string(100,'9');
//拷贝赋值
string s4;
s4 = s3;

2、拷贝初始化发生的一些情况：
*用 = 定义变量
*将一个对象作为实参传递给一个非引用类型的形参（说明拷贝构造函数参数为什么是 const & 类型；若该参数不是引用类型则调用永远
都不会成功，为了调用拷贝构造函数，必须拷贝其参数，而拷贝其参数又要调用拷贝构造函数，无限循环）
*从一个返回类型为非引用类型的函数返回一个对象
*用花括号列表初始化一个数组中的元素或一个聚合类中的成员

3、当指向一个对象的引用或指针离开作用域时，析构函数不会执行。（内存泄漏）

4、=default与=delete：
a、=default:显示的要求编译器使用编译器自己生成的版本
class A{
public:
	A() = default;
	A(const A &) = default;
	...
};
b、=delete：阻止拷贝（删除函数）
class Nocopy{
public:
	Nocopy() = default;//使用默认版本
	Nocopy(const Nocopy &) = delete; //阻止拷贝
	Nocopy & operator= (const Nocopy &) = delete;//阻止赋值
	~Nocopy() = default;
};
c、private拷贝控制与=delete：
*可以将拷贝构造与拷贝赋值声明为private类型实现拷贝控制，但是该方法存在一定的问题，比如：友元可以使用（若是对拷贝构造和
赋值构造函数声明并定义）；在不定义的情况下可能会导致链接错误。可以使用以下方法解决：
class Nocopy{
private:
	Nocopy(const Nocopy &);
	Nocopy & operator=(const Nocopy &);
protected:
	Nocopy(){}
	~Nocopy(){}
}
class Test:private Nocopy{

}
*尽量使用delete来阻止拷贝

5、行为像值的类
*为了提供类值的行为，对于类管理的资源，每个对象都应该拥有自己的一份拷贝
//程序1
class HasPtr{
public:
	HasPtr(const string &s = string()):
		ps(new string(s)),i(0){}
	HasPtr(const HasPtr &p):
		ps(new string(*p.ps)),i(p.i){}
	HasPtr & operator=(const HasPtr &);
	~HasPtr() {delete ps;}
private:
	string * ps;
	int i;
};
//注意拷贝复制函数，需要处理自我赋值的情况
HasPtr & HasPtr::operator=(const HasPtr &rhs){
	auto newp = new string(*rhs.ps); //拷贝底层的string，如果是自己的，则拷贝自己的
	delete ps;//释放旧内存
	ps = newp;
	return *this;
}

6、行为像指针的类
*需要为其定义拷贝构造和拷贝赋值来拷贝指针成员本身而不是它指向的值
*资源管理的方式使用引用计数
//程序2
class HasPtr{
public:
	//构造函数，分配新的引用计数，并且设置为 1
	HasPtr(const string &s = string()):
		ps(new string(s)),i(0),use(new size_t(1)){}
	//拷贝所有的成员变量，引用计数加 1
	HasPtr(const HasPtr &p):
		ps(p.ps),i(p.i),use(p.use) {++*use;}
	HasPtr & operator=(const HasPtr &);
	~HasPtr();
private:
	string *ps;
	int i;
	size_t *use;//用于记录共享ps的对象的个数
};
HasPtr & HasPtr::operator=(const HasPtr &rhs){
	//右侧对象引用计数增加
	++*rhs.use;
	//递减左侧对象的引用计数，若为0时释放
	if(--*use == 0){
		delete ps;
		delete use;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this;
}

7、动态内存管理类
*实现类似vector管理的类，适用于string
//程序3
#ifndef STRVEC_H
#define STRVEC_H
#include <iostream>
#include <string>
#include <memory>
using namespace std;
//类似vector动态分配内存简单的实现
class StrVec
{
public:
    StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec &);
    StrVec &operator =(const StrVec &);
    ~StrVec();

    void push_back(const string &);
    //返回元素个数
    size_t size() const {return first_free-elements;}
    //fan返回容量大小
    size_t capacity() const {return cap - elements;}
    string *begin() const {return elements;}
    string *end() const {return first_free;}
private:
    static allocator<string> alloc;        //用于分配元素
    //添加元素前检查，是否容量不够
    void chk_n_alloc(){
        if (size() == capacity()) reallocate();
    }
    //拷贝，赋值，析构函数所使用，返回值为pair<elements,first_free>
    pair<string *,string *> alloc_n_copy(const string *,const string *);
    void free();                                //释放元素
    void reallocate();                          //获取更多的内存并拷贝已有元素
    string *elements;                           //首元素指针
    string *first_free;                         //指向下一个的空闲指针
    string *cap;                                //指向尾后位置的指针
};

#endif // STRVEC_H
*三个指针位置
-----------------------------------
| 0 | 1 | 2 | 3 | 4|  未构造的元素 |
-----------------------------------
^                   ^              ^
elements            first_free     cap

//cpp
#include "StrVec.h"

allocator<string> StrVec::alloc = allocator<string>();

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(),s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec &StrVec::operator =(const StrVec &rhs)
{
    //拷贝原始到新的
    auto data = alloc_n_copy(rhs.begin(),rhs.end());
    //free当前的
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const string &s)
{
    //确保有够的空间
    chk_n_alloc();
    //在frist_free指向的元素中添加构造s的副本
    alloc.construct(first_free++,s);
}

pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e)
{
    //分配空间
    auto data = alloc.allocate(e - b);
    //返回初始化pair
    return {data,uninitialized_copy(b,e,data)};
}

void StrVec::free()
{
    if(elements){
        //逆序摧毁旧元素
        for(auto p = first_free; p != elements;)
            alloc.destroy(--p);
        //释放内存空间
        alloc.deallocate(elements,cap - elements);
    }
}
//①重新分配空间，并且将已有元素移动到新空间。将vector转成指针时得注意，指针移动时会出现问题
//②std::move==>将对象移动而不是拷贝到新空间。
void StrVec::reallocate()
{
    //在原始不为空的情况下，分配当前空间的2倍
    auto newcapacity = size() ? 2*size() : 1;
    //分配新内存
    auto newdata = alloc.allocate(newcapacity);
    //从旧数据内存拷贝到新数据内存
    auto dest = newdata;                //新内存的第一个指针
    auto elem = elements;               //旧内存的第一个指针
    for(size_t i = 0; i != size(); ++i)
        alloc.construct(dest++,std::move(*elem++));
    free();                             //释放旧内存
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

7、采用对象移动的原因
a、旧内存中的元素拷贝到新内存中并不是必要的
b、有些类包含不能被共享的资源，如IO类，unique_ptr类

8、右值引用（&&）与左值引用（&）
a、右值引用只能绑定到一个将要销毁的对象；
b、左值具有持久的状态，右值要么是字面量，要么是子啊表达式求值过程中创建的临时变量；
c、右值的特点：所引用的对象将要被销毁；该对象没有其他用户；
d、表达式都是左值
int &&rr1 = 42; //ok
int &&rr2 = rr1; //error;rr1为左值，不能将一个右值绑定到一个右值引用的类型上

9、move
a、显示的将一个左值转换为对应的右值引用类型。
int &&rr3 = std::move(rr1);//ok
b、对于move后的对象，可以销毁、重新赋值，但是不能使用该对象的值。

10、移动构造函数与移动赋值运算（C++11）
a、从给定对象“窃取”而不是拷贝资源
b、函数的参数为右值引用

StrVec::StrVec(StrVec &&s) noexcept  //移动操作不应该抛出任何异常
//接管s中的资源
:elements(s.elements),first_free(s.first_free),cap(s.cap)
{
    //按照9b的原则
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept
{
    //检测自我赋值
    if(this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        //按照9b原则，将rhs置于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}
c、必须在头文件的声明和定义中都指定noexcept
  
d、只有当一个类没有定义任何自己定义版本的拷贝控制成员，且它的所有数据成员都能移动构造或移动复制时，编译器才能为其合成移动构造
或移动赋值

e、定义了一个移动构造函数或移动赋值运算符的类必须也定义自己的拷贝操作；否则，这些成员默认被定义为删除的。

11、移动迭代器（通过适配器包装）：重新Strvec的reallocate函数
void reallocate(){
    auto newcapacity = size() ? 2*size() : 1;
    auto first = alloc.allocate(newcapacity);

    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()),
                                   first);

    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
*使用移动迭代器，必须确认移动后源对象没有其他用户*