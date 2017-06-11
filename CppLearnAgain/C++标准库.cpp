########################################顺序容器##############################################
1、标准库array具有固定大小
array<int,10>;
array<int,20>;

//可以对array数组进行拷贝或赋值操作
int digs[10] = {0,1,2,3,4,5,6,7,8,9};
int cpy[10] = digs; //error,不能对内置数值进行拷贝或赋值
array<int,10> digs1 = {0,1,2,3,4,5,6,7,8,9};
array<int,10> cpy1 = digs1;

2、使用assign(array除外):可以指定元素（的拷贝）替换左边容器的所有元素，如下：
list<string> names;
vector<const char *> oldstyle;
names = oldstyle;//error,容器类型不匹配
names.assign(oldstyle.cbegin(),oldstyle.cend());//ok,可以将const char*类型转换为string

list<sting> slit(1);//1个元素，为空string
slit.assign(10,"Hi");

3、使用swap：可交换两个相同数据结构的内容（除array外，swap不对任何元素进行拷贝、删除或者插入操作，因此可以保证在常数时间内完成）

4、向顺序容器中添加内容：
...
c.insert(p,t)
c.emplace(p,args)
//在迭代器p之前插入元素，并返回新添加元素的迭代器
//insert与emplace的区别：insert需要将对象传递给他们，并对对象进行拷贝；emplace可使参数在容器内直接构造。
...

//可将元素插入到vector,deque,string的任何位置，但是比较耗时（除头部和尾部）
//迭代器要拷贝的范围不能指向与目的位置相同的容器,运行时会报错
vector<> v;
list<string> l;

l.insert(l.begin(),"hello！");//等价于l.push_front("hello!");

v.insert(v.end(),10,"hello");//在尾部插入10个元素

l.insert(l.begin(),l.end()-2,l.end());//将最后两个元素插入到开始

5、元素访问时，尽量用c.at(n),返回下标为n的引用，越界时会抛出异常。

6、删除元素：（可单独删除一个元素，也可删除迭代器指定的范围）
...
c.erase(p)//删除迭代器p指向的元素，并返回删除元素之后元素的迭代器
c.erase(b,e)//指定范围删除
...
list<string> l;
l.clear();
l.erase(l.begin(),l.end());
//等价

7、两个版本删除list中所有的奇数,链表与单链表
//①
list<int> lst = {0,1,2,3,4,5,6,7,8,9};
auto it = lst.begin();
while (it != lst.end()){
	if (*it % 2 == 0)
		it = lst.erase(it);
	else
		++it;
}

//②
forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
auto pre = flst.before_begin();//获取头指针（并不是头节点），没有数据
auto cur = flst.begin();
while (cur != flst.end()){
	if (*cur % 2 == 0)
		cur = flst.erase_after(pre);
	else
		pre = cur;
}

8、改变容器的大小
list<int> l(10,42);//10g个元素,每个位42
l.resize(15);//15个元素,后5个为0
l.resize(20,-1);//在l后添加5个元素，每个位-1
l.resize(5,1);//删除元素，剩下5个

9、vector对象的增长
  a、vector和string对象在获取新的空间时，通常会分配比新空间需求更大的空间；
  b、一些成员函数：
   c.shrink_to_fit();//将capacity缩减为与size相同大小
   c.capacity();//c的内存空间大小
   c.size();//c含元素的多少
   c.reserve(n);//分配至少能含n个元素的内存空间
   //reserve并不改变容器中元素的数量，只是影响vector中预先分配多大的内存空间，且reverse不能减少内存空间

10、string额外的操作
  a、额外的构造方法：
     string s(cp,n);//拷贝cp数组的前n个
     string s(s2,pos2);//从s2的pos2开始拷贝
     string s(s2,pos2,len);
     //如果未传递计数值且数组也未以空字符结尾，或者给定的数值大于数组大小，则构造的结果将是为定义
  b、substr(pos,n);
  c、append(str),replace(pos,erase_num,str);
  d、搜索操作：(未找到结果，返回string::npos)
    ////找到name中的第一个数字，返回1
    string numbers("0123456789"),name("r2d2");
    auto pos = name.find_first_of(numbers);
    ////找到name中的第一个非数字字符
    auto pos1 = name.find_first_not_of(numbers);
  e、数值转换：
    ////
    int i = 42;
    string s = to_string(i);
    double d = stod(s);
    ////********
    string s2 = "pi = 3.14";
    d = stod(s2.substr(s2.find_first_of("+-.0123456789")));//d = 3.14 

11、容器适配器
  a、本质：是一种机制，使某种事物的行为看起来像另外一种事物。（每个适配器都需要一个以某种容器实现，stack默认以deque实现）
    stack<int> idst;
    stack<int,vector<int>> vdst;

########################################泛型算法##############################################
1、算法一般情况下，不直接操作容器，而是遍历由两个迭代器指定的一个元素范围来进行操作。
  //////find返回第二个参数表示收索失败
  int val = 42;
  auto result = find(vec.begin(),vec.end(),val);
  int a[] = {1,23,4,56,7,90};
  int * result1 = find(begin(a),end(a),val);

2、只读算法：find、count、equal、accumulate（<numeric>）
  a、accumulate
  /////第三个参数类型决定了函数中使用哪种加法和返回值类型
  int result = accumulate(vec.begin(),vec.end(),0);
  string num = accumulate(v.cbegin(),v.cend(),string(""));
  /////""为const char * 类型，没有定义+运算符，错误
  string num2 = accumulate(v.cbegin(),v.cend(),"");

3、写容器的算法：fill,fill_n,back_inserter,copy,replace,replace_copy
  a、fill
  ////算法不会执行容器操作，因此它们自身不可能改变容器的大小；
  fill(vec.begin(),vec.end(),0);
  b、fill_n
  vector<int> vec;
  fill_n(vec.begin(),vec.end(),0);//所有元素重置为0
  fill_n(dest,n,val);//dest指向一个元素，从dest开始的序列至少包含n个元素
  ////在没有足够多的元素的vec中使用fill_n是错误的
  vector<int> v;
  fill_n(v,10,0);
  c、back_inserter:插入迭代器，执行赋值运算时，会调用push_back将一个具体给定的值元素添加到容器中
  ///正确
  vector<int> v;
  fill_n(back_inserter(v),10,0)
  d、replace、replace_copy
  ///注意两者的区别
  replace(list.begin(),list.end(),0,42);
  replace_copy(list.begin(),list.end(),back_inserter(vec),0,42);

4、重排容器算法：sort，unique
  a、sort
  b、unique
  ///删除vstr中重复的元素
  void deleteTheComWords(vector<string> &vstr){
    sort(vstr.begin(),vstr.end());
    //返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(vstr.begin(),vstr.end());
    //标准库算法对迭代器而不是对容器进行操作，因此不能直接添加或删除元素
    vstr.erase(end_unique,vstr.end());
  }
5、定制操作
  a、向算法传递函数（一般指谓词）
  sort具有操作版本接受第三个参数：二元谓词
  ///程序一
  bool bigger(int a,int b){
    return a > b;
  }
  int main()
  {
      vector<int> v = {1,5,3,6,4};
      ostream_iterator<int> out_iter(cout," ");
      copy(v.begin(),v.end(),out_iter);
      cout << endl;
      //sort(v.begin(),v.end());//从小到大
      sort(v.begin(),v.end(),bigger);//从大到小
      copy(v.begin(),v.end(),out_iter);
      return 0;
  }
  
  b、lambda表达式（C++11）
  ①[捕获列表](参数列表) -> 返回值类型 {函数主体} （可以忽略参数列表和返回值）
  ////程序二
  //删除重复单词、排序打印vector中长度大于sz的元素
  void bigger(vector<string> &words,vector<string>::size_type sz){
      sort(words.begin(),words.end());
      auto end_unique = unique(words.begin(),words.end());
      words.erase(end_unique,words.end());
      //在按照长度稳定排序
      stable_sort(words.begin(),words.end(),[](const string &s1,const string $s2){return s1.size() < s2.size();});
      //获取满足大于sz的迭代器
      auto wc = find_if(words.begin(),words.end(),[sz](const string &s){return s.size() >= sz;});
      //打印结果
      for_each(wc,words.end(),[](const string &s){cout << s << " ";});
      cout << endl;
  }
  *stable_sort算法：可维持相等元素的原有顺序;
  *lambda表达式中的捕获列表只能用于局部非static变量（sz），可直接使用局部static变量
  
  ②捕获列表：
  ////程序三
  //值捕获方式：前提变量可拷贝；被捕获变量的值是在lambda创建时拷贝，而不是调用时拷贝
  void fun1(){
    int a = 42;
    auto f = [a]{return a;};
    a = 0;
    auto j = f();//j = 42;f保持了a的拷贝
  }
  //引用捕获方式：
  void fun2(){
    int a = 42;
    auto f = [&a]{return a;};
    a = 0;
    int j = f();//j为0
  }
  //隐式捕获：在捕获列表中使用=或&，表示值捕获和应用捕获
  void printbigger(vector<int> vec,int bigger,ostream &os = cout, char c = ' '){
    //隐式捕获os,显示捕获c
    for_each(vec.begin(),vec.end(),[&,c](const int & i){os << i << c;});
    for_each(vec.begin(),vec.end(),[=,&os](const int & i){os << i << c;});
  }
  //可变的lambda
  void fcn3(){
    int v1 = 42;
    auto f = [v1]() mutable {return ++v1;};
    v1 = 0;
    auto j = f();//j = 43
  }
  ③指定lambda的返回值
  ////程序四
  //返回一个条件表达式，编译器可以推断返回类型
  transform(v.begin(),v.end(),v.begin(),[](int i){return i < 0 ? -i:i;});
  //将会产生错误不能推断具体的返回类型
  transform(v.begin(),v.end(),v.begin(),[](int i){if (i < 0) return -i;else return i;});
  //正确
  transform(v.begin(),v.end(),v.begin(),
            [](int i) -> int
            {if (i < 0) return -i;else return i;});

  c、参数绑定（将多元谓词转化为一元谓词）
  ////程序5
  //二元谓词
  bool check_size(const string &s,string::size_type sz){
    return s.size() > sz;
  }
  auto check5 = bind(check_size,_1,5);//_1为占位符;using namespace std::placeholders;
  string s = "hello";
  bool b = check5(s);//=>check_size(s,5)

6、<iterator>中的迭代器
  a、插入迭代器
  *back_inserter <==> push_back
  *front_inserter <==> push_front
  *inserter <==> 元素被插入到给定迭代器之前

  list<int> lst = {1,2,3,4};
  list<int> lst1,lst2;
  copy(lst.begin(),lst.end(),front_inserter(lst1));//4 3 2 1
  copy(lst.being(),lst.end(),inserter(lst2,lst2.begin()));//1 2 3 4

  ////程序6
  //将vector中不重复的元素copy到list中
  void v2l(vector<int> &v,list<int> &l){
    sort(v.begin(),v.end());
    unique_copy(v.begin(),v.end(),inserter(l,l.begin()));
  }

  int main()
  {
      vector<int> v = {1,5,3,6,4,5,8,2,3};
      list<int> l;
      v2l(v,l);
      ostream_iterator<int> out_iter(cout," ");
      copy(l.begin(),l.end(),out_iter);
      cout<<endl;
      return 0;
  }

  b、输入输出迭代器
  *输出迭代器（ostream_iterator）在程序6中使用过了
  *输入迭代器（istream_iterator）
  ////程序7
  void testistream_iter()
  {
      vector<int> vec;
      ostream_iterator<int> out_iter(cout," ");
      
      istream_iterator<int> in_iter(cin);
       
      istream_iterator<int> eof;//结束标志
      while (in_iter != eof)//输入非数字时结束
          vec.push_back(*in_iter++);
      copy(vec.begin(),vec.end(),out_iter);
  }

########################################关联容器##############################################
1、关联容器的迭代器都是双向的

2、有序容器的关键字类型：
  a、关键字类型必须定义一个严格弱序
  b、multiset必须提供两个类型：关键字类型以及比较操作符

3、pair类型：make_pair(v1,v2),返回一个用v1和v2初始化的pair。
  ///程序8
  pair<string,int> preocess(vector<string> &v){
    if(!v.empty())
      return {v.back(),v.back().size()};//列表初始化
    else
      return pair<string,int>();//隐式构造返回值
  }

4、关联容器操作
  a、key_type（此类容器类型的关键字类型）、mapped_type（每个关键字关联的类型（map））、以及value_type（对于set与key_type相同
  ，对于map为：pair<const key_type,mapped_type>）
  b、对于map的value_type类型，不能改变其关键字成员的值，因为是const类型。

5、添加元素
  a、insert(emplace)方法：会返回一个pair类型，fisrt是一个迭代器，指向具体给定关键字的元素；sencod为bool类型，插入是否成功
  map的几种插入方式：
  word_map.insert({word,1});
  word_map.insert(make_pair(word,1));
  word_map.insert(pair<string,int>(word,1));
  word_map.insert(map<string,int>::value_type(word,1));

6、元素访问（find，count，lower_bound，upper_bound，equal_range）
  a、lower_bound,upper_bound
  前：返回一个迭代器，指向第一个关键字不小于k的元素；后：指向第一个关键字大于k的元素
  b、equal_range
  返回一个迭代器pair，表示关键字等于k的元素范围。若k不存在，pair的两个成员均等于end();

########################################动态内存##############################################
1、shared_ptr与unique_ptr,在头文件memory中
a、都支持的一些操作
  shared_ptr<T> sp;
  unique_ptr<T> up;//空智能指针，指向类型为T的对象
  p;//若P指向一个对象，则为true
  *P;
  p->mem <==> (*p).mem;
  p.get();//返回p中保存的指针

b、shared_ptr独有的操作
  make_shared<T>(args);//使用args初始化一个指向T对象的shard_ptr
  shared_ptr<T> p(q);//p为q的拷贝，增加q中的引用计数
  p = q;//在p和q都是shared_ptr的情况下，p的引用计数会减少，q的引用计数会增加

c、定义和改变shared_ptr的其他方法
  shared_ptr<T> p(q);//q必须指向new分配的内存
  shared_ptr<T> p(u);//接管u（unique_ptr）的所有权，将u置空
  shared_ptr<T> p(q,d);//p接管q的所有权，并且可调用d来代替delete
  /*
  void end_connect(connection *p){disconnect(*p);}
  connection c = connect(&d);
  shared_ptr<connection> p(&c,end_connect);
  */
  q.reset();//若q是唯一指向对象shared_ptr，释放此对象
  q.reset(p);//令q指向p
  q.reset(p,d);

d、unique_ptr的操作
  
  unique_ptr<T> u;
  unique_ptr<T,D> u;//指定类型为D的对象代替delete（P419有具体例子）
  u = nullptr;//释放u，并置空
  u.release();//释放u，并返回u所指向的指针
  u.reset();
  u.reset(p);//若存在p，则u指向p；否则置空

  ///程序1
  void test_uniqueptr(){
    unique_ptr<string> p1(new string("TEST"));
    unique_ptr<string> p2(p1.release());//转移所有权，并置空p1；

    //p2.release();//error,p2不会释放，而且丢失了指针
    auto p = p1.release();//ok,记得delete(p)
  }


e、shared_ptr和new结合使用
  ①接受指针参数的智能指针的构造函数是explicit的,因此不能将一个内置的指针转换为智能指针，必须使用显示初始化形式
  shared_ptr<int> p1 = new int(1024);//error
  shared_ptr<int> p2(new int(1024));//ok
  //返回
  shared_ptr<int> clone(int p){
    //return new int(p);//error 不能隐式转换一个普通的指针
    return shared_ptr<int>(new int(p));
  }
  ②不能混用普通指针和智能指针
  //程序2
  //在调用process时，ptr创建并被初始化
  void process(shared_ptr<int> ptr){
    //使用ptr
  }//ptr离开作用域，被销毁

  void test_smart_ptr(){
    shared_ptr<int> p(new int(42));//引用计数为1
    process(p);//拷贝，在process中引用计数为2
    int i = *p;//ok,引用计数为1
  }

  void test_com_ptr(){
    int *x(new int(42));
    process(x);//不能将int *传递给shared_ptr
    process(shared_ptr<int> (x));//临时的shared_ptr，参数传递完后，引用计数会减少
    int i = *x;//未定义
  }

f、传递unique_ptr参数和返回unique_ptr
  由于uniq_ptr拥有它指向对象，因此unique_ptr不支持拷贝和赋值操作；但是可以拷贝或者赋值一个将要被销毁的uniq_ptr
  unique_ptr<int> clone(int p){
    return unique_ptr<int> (new int(p));//ok
  }

  unique_ptr<int> clone(int p){
    unique_ptr<int> ret(new int(p));
    return ret;//ok
  }

2、动态数组
  a、不能对动态数组调用begin和end，因为分配的内存不是一个数组类型
  b、shared_ptr、unique_ptr与动态数组

  unique_ptr<int []> up(new int[10]);
  up.release();//自动调用delete[]
  for(size_t i = 0; i != 10; i++)
    up[i] = i;//unique_ptr访问数组

  //使用shared_ptr
  shared_ptr<int> sp(new int[10],[](int *p){delete[] p;});
  sp.reset();//使用提供的lambda释放数组
  for(size_t i = 0; i != 10; i++)
    *(sp.get()+i) = i;

  c、allocator,可以将内存分配与对象构造分离开来

3、使用与管理动态内存
  ①使用动态内存的需求：
  *未知使用对象个数
  *未知使用对象的准确类型
  *需要在多个对象之间共享数据
  ②管理需要注意
  *不要忘记delete内存，易导致内存泄漏
  *不要使用已经释放内存的对象，注意使用之前作check
  *不要对同一块内存释放两次

4、文本查询程序
  ///程序3
  //头文件TextQuery.h
#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <memory>
#include <iostream>
using namespace std;

using line_no = vector<string>::size_type;
//前向声明（不完全类型），可以定义其指针、引用、或者作为函数的参数或返回值
class QueryResult;

class TextQuery
{
public:

    TextQuery(ifstream &);
    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> file;//输入文件
    map<string,shared_ptr<set<line_no>>> wm;//每个单词与对应行号的集合
};

class QueryResult
{
friend ostream & print(ostream &,const QueryResult &);
public:
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f):
        sought(s),lines(p),file(f){}
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;    //将与TextQuery共用一个file，智能指针引用计数机制
};

#endif // TEXTQUERY_H

//TextQuery.cpp
#include "TextQuery.h"
#include <sstream>

TextQuery::TextQuery(ifstream &is):file(new vector<string>)
{
    string text;
    while (getline(is,text)) {          //读取每行数据
        file->push_back(text);          //保存当前行
        int num = file->size() - 1;     //行号
        istringstream line(text);       //分割每个单词
        string word;
        while (line >> word) {
            auto &lines = wm[word];     //lines为shared_ptr类型
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(num);
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought,nodata,file);
    else
        return QueryResult(sought,loc->second,file);
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << "occurs" << qr.lines->size() << " times" << endl;
    for(auto num: *qr.lines)
        os << "\t(line "<< num+ 1 <<")" << *(qr.file->begin() + num) << endl;
    return os;
}

   