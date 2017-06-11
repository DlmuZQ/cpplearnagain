1、尽可能使用const
	a、const成员函数：*可方便理解函数是否可以改变对象
					  *使其可操作const对象和non-const对象
	b、mutable bool b;可使b在const函数中改变
2、确保对象被使用前已经先被初始化
	a、初始化与赋值的区别：如下代码，第一个为赋值，第二个为初始化；初始化的效率往往会高于赋值，而且不会调用成员对象的默认构造函数。
	class A{
	public:
		A(string s,int i){
		_s = s;
		_i = i;//赋值
		}
	private:
		string _s;
		int _i;
	};
	class A{
	public:
		A(string s,int i):_s(s),_i(i){}//初始化
	private:
		string _s;
		int _i;
	};
	b、非局部静态成员（non-local static）的初始化次序:(函数类的static对象为local-static对象，其余为non-local static对象)；C++中没有明确的这两种
	对象的初始化次序，为避免以下代码的问题，可采用单例模式。
	class A{
	public:
		...
		int number() const;
		...
	}
	A a;
	class B
	{
	public:
		...
		B(){
			int num = a.number();
		}
		...	
	};
	B b();//若a没在b之前初始化，将会出现问题
	===》
	class A{
	public:
		...
		int number() const;
		...
	}
	A &a(){
		static A _a;
		return _a;
	}
	class B
	{
	public:
		...
		B(){
			int num = _a().number();
		}
		...	
	};
	B &b(){
		static B _b;
		return _b;
	}	

3、多态基类声明virtual析构函数
   a、局部销毁现象：C++明确指出，当derived class对象经由一个base class指针被删除，而该base class带有一个non-virtual析构函数，其结构为
   未定义（实际执行时通常表现为对象的derived成分没有被销毁）；
   b、必须为纯虚析构函数提供定义；

4、在构造和析构工程中调用virtual函数会造成问题
   理解：继承类在构造之前会调用基类，若是在基类中使用virtual函数，则不会发生多态行为，因为此时继承类并没有形成。

5、在operation中处理自我赋值问题
///前提
class val {...};
class useval{
	...
private:
	val * _v;
};
///版本1 operator=
///问题：rv与*this可能是同一个对象，这样会删除当前对象
useval& useval::operator=(const useval& rv){
	delete _v;
	_v = new val(*rv._v);
	return *this;
}
///版本2 operator=
///问题：若在构造时失败，将会导致_v为空
useval& useval::operator=(const useval& rv){
	if(this == &rv) return *this;

	delete _v;
	_v = new val(*rv._v);
	return *this;
}
///版本3 operator=
///可确保多个对象是同一个对象时，其行为仍然正确
useval& useval::operator=(const useval &rv){
	val *v = _v;
	_v = new val(*rv._v);
	delete v;
	return *this;
}

6、以对象管理资源
   把资源放进对象内，便可依赖C++的“析构函数自动调用机制”确保资源被释放。
   a、使用auto_ptr（在头文件memory中）
   class test{
	public:
	    test():i(0){}
	private:
	    int i;
	};
	test * createtest(){
	    return new test();
	}
	int main()
	{
		/*
	   *获得资源后立即放进管理对象中
	   *管理对象运用析构函数确保资源被释放
	   */
	    auto_ptr<test> pTest(createtest());	
	    ///为防止多个auto_ptr指针指向同一对象，auto_ptr在调用copy构造函数或者copy assignment时，
	    ///原本的将会变成null，复制的将保留获得资源的唯一权利
	    ///因此auto_ptr不能用于STL容器    
	    auto_ptr<test> p2(pTest);
	    cout <<pTest.get() <<endl;//null
    	cout <<p2.get()<<endl;	   
	    return 0;
	}
	b、使用shared_ptr（采用应用计数机制）
	class test{
	public:
	    test():i(0){}
	private:
	    int i;
	};
	test * createtest(){
	    return new test();
	}	
	int main()
	{	    
	    shared_ptr<test> pTest1(createtest());	    
	    shared_ptr<test> p1(pTest1);
	    cout << pTest1.get()<<endl;//两个地址相同
	    cout << p1.get() << endl;
	    return 0;
	}
	c、auto_ptr与shared_ptr两者的析构函数都是采用delete而不是delete[],因此以下方法将出现问题
	auto_ptr<stirng> aps(new string[10]);
	shared_ptr<int> spi(new int[32]);