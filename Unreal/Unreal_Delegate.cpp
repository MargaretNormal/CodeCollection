/** 
* 在Unreal中，Delagate(中文文档翻译为代理)是一种在对象B中调用对象A中的方法而无需知晓对象A信息的方式。
* 
* 代理允许您在C++对象上以通用的但类型安全的方式调用成员函数。通过使用代理，您可以将其动态地绑定到任何对象的成员函数上，然后在该对象上调用函数，即时调用者不知道该对象的类型也没关系。
*
* 复制代理对象是非常安全的。代理可以进行值传递，但是一般不推荐这样做，因为这样就必须在堆上为其分配内存。因此 任何时候您都应该通过引用传递代理。 
*
* 代理有：单播单例，多播代理和动态代理
*
* 代理是函数签名
*
* 相关文档：https://docs.unrealengine.com/latest/CHN/Programming/UnrealArchitecture/Delegates/index.html
*/


// TODO 补充 多播代理 和 动态代理

// 单播代理
// WriteToLog()是被代理的函数，即需要在其他地方引用这个函数，但是无需获取FlogWriter对象
class FLogWriter
{
    void WriteToLog( FString );
};

// 定义一个代理类型
DECLARE_DELEGATE_OneParam( FStringDelegate, FString );

class FMyClass
{
	public:
	// 定义的代理类型声明具体的代理
    FStringDelegate WriteToLogDelegate;
	private:
	void ProcessDelegate();
};


void FMyClass::ProcessDelegate()
{
	// 创建代理使用的特殊数据类型
	FSharedRef< FLogWriter > LogWriter( new FLogWriter() );
	// 'BindSP' 中的 'SP' 部分代表 '共享指针' ，因为我们正在绑定到一个由共享指针拥有的对象上。
	// 不同的对象类型有不同的函数版本，比如BindRaw()和BindUObject()。
	WriteToLogDelegate.BindSP( LogWriter, &FLogWriter::WriteToLog );
	
	
	// 如果在将函数绑定到代理上之前调用了 Execute() 函数，那么将会触发产生断言
	// TODO 补充 断言 简介
	WriteToLogDelegate.Execute( TEXT( "Delegates are spiffy!" ) );
	// 忽略断言
	WriteToLogDelegate.ExecuteIfBound( TEXT( "Only executes if a function was bound!" ) );
}
