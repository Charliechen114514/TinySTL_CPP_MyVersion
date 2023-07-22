#pragma once
#include<iostream>
namespace CCSTDCPP {
#ifndef _SIZE__INDEX__CCSTDDCPP_
#define _SIZE__INDEX__CCSTDDCPP_ 1
	using Index = unsigned int;
	using Size  = unsigned int;
#endif

#ifndef _Error_CCSTDCPP_
#define _Error_CCSTDCPP_ 1
	enum class ErrorCode {
		VECTOR_OVERFLOW,
		VECTOR_UNDERFLOW,
		VECTOR_WRONGCONF,
		VECTOR_NULLPTR
	};

	class Exceptions :public std::exception{
	protected:
		const char* m_forWhat;
		CCSTDCPP::ErrorCode m_errorIndex;
	public:
		Exceptions(const char* forWhat, CCSTDCPP::ErrorCode index) : m_forWhat{ forWhat }, m_errorIndex{ index } {};
		virtual ~Exceptions() = default;
		virtual void what() { std::cerr << m_forWhat; };
	};

	class Exp_OverFlow : public Exceptions {
	public:
		Exp_OverFlow(const char* msg = "Sadly OverFlow!",
			CCSTDCPP::ErrorCode index = CCSTDCPP::ErrorCode::VECTOR_OVERFLOW) : Exceptions{ msg, index } {}
	};

	class Exp_UnderFlow : public Exceptions {
	public:
		Exp_UnderFlow(const char* msg = "Sadly UnderFlow!",
			CCSTDCPP::ErrorCode index = CCSTDCPP::ErrorCode::VECTOR_UNDERFLOW) :Exceptions{ msg, index } {}
	};

	class Exp_Nullptr : public Exceptions {
	public:
		Exp_Nullptr(const char* msg = "What we have got is a nullptr",
			CCSTDCPP::ErrorCode index = CCSTDCPP::ErrorCode::VECTOR_NULLPTR) :Exceptions{ msg,index } {}
	};
#endif

#ifndef _BytesArray_CCSTDCPP_
#define _BytesArray_CCSTDCPP_ 1
	template<typename data>
	class BytesArray {
	private:
		data*	m_staticData;
		Size	m_size;
        [[nodiscard]]bool	checkIndexValidness(Index index) const;
	public:
		BytesArray(data* dataFront, Size size);
		BytesArray& operator=(const BytesArray&) = delete;
		BytesArray(const BytesArray&) = delete;
		[[nodiscard]]Size	size() const;
		data	operator[](Index index) const;
		data&	at(Index index) const;
		data*	rawData();
		~BytesArray();
	};

#endif
}

template<typename data>
bool CCSTDCPP::BytesArray<data>::checkIndexValidness(Index index) const
{
	try {
		if (index >= m_size)
		{
			throw CCSTDCPP::Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::Exp_OverFlow& overFlow)
	{
		std::cerr << "Out of index, I mean, right index is possibly toooooooooooo big";
	}
	catch (CCSTDCPP::Exp_UnderFlow& underflow)
	{
		std::cerr << "Out of index, I mean, left index can not be possibly toooooooooooo nega";
	}

	return true;
}



template<typename data>
CCSTDCPP::BytesArray<data>::BytesArray(data* dataFront, Size size)
{
	m_staticData = new data[size];
	for (Size i = 0; i < size; i++)
	{
		m_staticData[i] = dataFront[i];
	}
	m_size = size;
}

template<typename data>
CCSTDCPP::Size CCSTDCPP::BytesArray<data>::size() const
{
	return m_size;
}

template<typename data>
data CCSTDCPP::BytesArray<data>::operator[](Index index) const
{
	checkIndexValidness(index);
	return data(m_staticData[index]);
}

template<typename data>
data& CCSTDCPP::BytesArray<data>::at(Index index) const
{
	checkIndexValidness(index);
	return m_staticData[index];
}

template<typename data>
data* CCSTDCPP::BytesArray<data>::rawData()
{
	data* newOne = new data[m_size];
	for (int i = 0; i < m_size; i++)
		newOne[i] = m_staticData[i];

	return newOne;
}

template<typename data>
CCSTDCPP::BytesArray<data>::~BytesArray()
{
    delete[] m_staticData;
}