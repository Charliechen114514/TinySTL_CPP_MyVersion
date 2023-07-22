#pragma once

namespace CCSTDCPP {

	template<class data>
	using FuncPrintPtr = void(*)(data&);

	template<class data>
	class Print {
	public:
		Print(FuncPrintPtr<data> printer);
		Print& operator=(Print&) = delete;
		Print(Print&) = delete;
		void operator()(data& data);
	private:
		FuncPrintPtr<data> printer;
	};

	template<class data>
	Print<data>::Print(FuncPrintPtr<data> printer)
		:printer{ printer }
	{
	}

	template<class data>
	void Print<data>::operator()(data& data) {
		(*printer)(data);
	}

}

