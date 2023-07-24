#pragma once
#include<iostream>
#define SAFE_PRIORITY_SWITCH 0

#if SAFE_PRIORITY_SWITCH
#define SAFE_PRIORITY 1
#else 
#define QUICK_PRIORITY 1
#endif
namespace CCSTDCPP {
#ifndef _SIZE__INDEX__CCSTDDCPP_
#define _SIZE__INDEX__CCSTDDCPP_ 1
	using Size = unsigned int;
	using Index = unsigned int;

#endif
	const Size def_capicity = 10;
	const double def_Expandcoeffiency = 1.3;

#ifndef _CopySeletion_CCSTDCPP_
#define _CopySeletion_CCSTDCPP_ 1
	enum class CopySelection{
		Shared_Reference,
		Independent_Copy
	};
#endif

#ifndef _Error_CCSTDCPP_
#define _Error_CCSTDCPP_ 1
	enum class ErrorCode {
		VECTOR_OVERFLOW,
		VECTOR_UNDERFLOW,
		VECTOR_WRONGCONF,
		VECTOR_NULLPTR
	};

	class Exceptions {
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

	class Exp_WrongConf : public Exceptions {
	public:
		Exp_WrongConf(const char* msg = "Sadly, This function can not RECOGNIZE what you pass to him :( ",
			CCSTDCPP::ErrorCode index = CCSTDCPP::ErrorCode::VECTOR_WRONGCONF) :Exceptions{ msg, index } {}
	};

	class Exp_Nullptr : public Exceptions {
	public:
		Exp_Nullptr(const char* msg = "What we have got is a nullptr",
			CCSTDCPP::ErrorCode index = CCSTDCPP::ErrorCode::VECTOR_NULLPTR) :Exceptions{ msg,index } {}
	};

#endif 

#ifndef _VECTOR_WITH_ITERATOR_
#define _VECTOR_WITH_ITERATOR_ 1
	template<typename data>
	class Vector; // 不得不声明
	template<typename data>
	class BytesArray;
	template<class data>
	class VectorIterator
	{
	private:
		data* currentElemPtr;
		data* begin;
		data* end;
		bool autoCheck;
		void checkValidness();
	public:
		VectorIterator(data* begin, data* end);
		VectorIterator(data* curPtr);
		VectorIterator();
		data* currentElemAddress() const;
		data* operator=(const data* dataPtr);
		VectorIterator& operator=(const VectorIterator& passvVec);
		data& operator*() const;
		data* operator++();
		data* operator++(int);
		data* operator--();
		data* operator--(int);
		void operator+=(int offset);
		void operator-=(int offset);
		bool operator==(const data* dataPtr);
		bool operator!=(const data* dataPtr);
		bool operator>(const data* dataPtr);
		bool operator>=(const data* dataPtr);
		bool operator<(const data* dataPtr);
		bool operator<=(const data* dataPtr);
		data* operator+(int);
		data* operator-(int);
	};


	template<typename data>
	class Vector
	{
	public:
		/* def call */
		Vector();

		/* init from a singel data */
		Vector(const data& singleData);

		/* copy assignment */
		Vector(const Vector& vec);

		/* move assignment */
		Vector(const Vector&& vec);

		/* operator =*/

		Vector&				operator=(const Vector<data>& vec);

		/* eraser */
		~Vector();

		/* push back */ 
		void				push_back(const data& singleData);
		void				push_back(const Vector& vec);
		void				push_back(const data* beg, const data* end);
		void				push_back(const CCSTDCPP::VectorIterator<data>& it);

		/* pop and pop_back */
		data				pop_back();
		void				pop();

		/* visiter */
		data&				operator[](Index index) const;
		data&				at(Index index) const;

		/* insert */
		void				insert(const Index index, const data& insert_data);
		void				insert(const Index beg, const Index end,const data* insertDataArray);
		void				insert(Index fromWhere, const data* beg, const data* end);
		void				insert(CCSTDCPP::VectorIterator<data>& it, const data& insert_data);

		/* erase */
		data*				erase_back(const Index index);
		data*				erase_back(const Index beg, const Index end);
		data*				erase_back(const data* beg, const data* end);
		data*				erase_back(const CCSTDCPP::VectorIterator<data>& it);
		void				erase(const Index index);
		void				erase(const Index beg, const Index end);
		void				erase(const data* beg, const data* end);
		void				erase(const CCSTDCPP::VectorIterator<data>& it);

		/* public getter */
		data*				rawDataStaticArray(
								CCSTDCPP::CopySelection usrSelection = 
								CCSTDCPP::CopySelection::Independent_Copy
								) const;
		data				front();
		data				rear();
		Size				size() const;
		Size				capicity() const;	
		data*				begin() const;
		data*				end() const;
		bool				isFull() const;
		bool				isEmpty() const;
		BytesArray<data>	wrappeddata();

		/* set clear */
		void				clear();
		/* compare */
		bool				operator==(const Vector& vec);
		bool				operator!=(const Vector& vec);

	private:
		data*				m_DataArray;
		Size				m_Current_size;
		Size				m_Capicity;
		double 				m_coeffiencyOfExpandSizeRate;
		bool				isSupposedToResize(Size size) const;
		void				resize(const Size newSize);
		Size				getSuitableSize(Size newWishedSize) const;
		bool				checkIndexValid(Index index) const;
		
	};


}

// VectorIterator

template<typename data>
CCSTDCPP::VectorIterator<data>::VectorIterator(data* begin, data* end)
{
	this->begin = begin;
	this->end = end;
	this->currentElemPtr = begin;
	autoCheck = true;
}

template<typename data>
CCSTDCPP::VectorIterator<data>::VectorIterator(data* curPtr)
{
	currentElemPtr = curPtr;
}
template<typename data>
CCSTDCPP::VectorIterator<data>::VectorIterator()
{} // set as default

template<typename data>
void CCSTDCPP::VectorIterator<data>::checkValidness()
{
	try
	{
		if (currentElemPtr < begin) {
			throw CCSTDCPP::Exp_UnderFlow();
		}
		else if (currentElemPtr > end) {
			throw CCSTDCPP::Exp_OverFlow();
		}
	}

	catch (CCSTDCPP::Exp_UnderFlow& underFlow) {
		underFlow.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_OverFlow& overflow) {
		overflow.what();
		terminate();
	}
}

template<typename data>
data* CCSTDCPP::VectorIterator<data>::currentElemAddress() const
{
	return currentElemPtr;
}


// 1
template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator++()
{
	return ++currentElemPtr;
}

// 1
template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator++(int)
{
	return currentElemPtr++;
}

// 1
template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator--()
{
	return --currentElemPtr;
}

// 1
template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator--(int)
{
	return currentElemPtr--;
}

template<typename data>
void CCSTDCPP::VectorIterator<data>::operator+=(int offset)
{
	currentElemPtr += offset;
	if (autoCheck) {
		checkValidness();
	}
}

template<typename data>
void CCSTDCPP::VectorIterator<data>::operator-=(int offset)
{
	currentElemPtr -= offset;
	if (autoCheck) {
		checkValidness();
	}
}

// 1
template<typename data>
data& CCSTDCPP::VectorIterator<data>::operator*() const {
	return *currentElemPtr;
}

// 1
template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator=(const data* ptr) {
	currentElemPtr = const_cast<data*>(ptr);
	return currentElemPtr;
}

// 1
template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator!=(const data* ptr) {
	return ptr != currentElemPtr;
}

// 1
template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator==(const data* ptr) {
	return ptr == currentElemPtr;
}


template<typename data>
CCSTDCPP::VectorIterator<data>& CCSTDCPP::VectorIterator<data>::operator=(const VectorIterator<data>& passingVec) {
	begin = passingVec.begin;
	end = passingVec.end;
	currentElemPtr = passingVec.currentElemPtr;
	return *this;
}

template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator>(const data* dataPtr)
{
	return currentElemPtr > dataPtr;
}

template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator>=(const data* dataPtr)
{
	return currentElemPtr >= dataPtr;
}

template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator<(const data* dataPtr)
{
	return currentElemPtr < dataPtr;
}

template<typename data>
bool CCSTDCPP::VectorIterator<data>::operator<=(const data* dataPtr)
{
	return currentElemPtr <= dataPtr;
}

template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator+(int offset)
{
	return currentElemPtr + offset;
}

template<typename data>
data* CCSTDCPP::VectorIterator<data>::operator-(int offset)
{
	return currentElemPtr - offset;
}

// Vector
template<typename data>
bool CCSTDCPP::Vector<data>::isEmpty() const
{
	return m_Current_size == 0;
}

template<typename data>
bool CCSTDCPP::Vector<data>::isFull() const{
	return m_Capicity <= m_Current_size; // to include some ex-planned situation;
}

template<typename data>
bool CCSTDCPP::Vector<data>::isSupposedToResize(Size size) const
{
	return m_Capicity <= size || m_Current_size <= m_Capicity/2;
}

template<typename data>
CCSTDCPP::Size CCSTDCPP::Vector<data>::getSuitableSize(Size newWishedSize) const
{
	if (newWishedSize >= m_Capicity && newWishedSize <= m_Capicity * 2) {
		return 2 * m_Capicity;
	}

	else if(newWishedSize > 2 * m_Capicity ){
		return newWishedSize * m_coeffiencyOfExpandSizeRate;
	}

}

template<typename data>
bool CCSTDCPP::Vector<data>::checkIndexValid(Index index) const
{
	try {
		if (index >= m_Current_size) {
			std::cerr << "Out of index!";
			throw CCSTDCPP::Exp_OverFlow();
		}

		if (index < 0) {
			std::cerr << "HEY! I have never thought a negative number is suitable!";
			throw CCSTDCPP::Exp_UnderFlow();
		}
	}
	catch (CCSTDCPP::Exp_OverFlow& overflow)
	{
		overflow.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_UnderFlow& underflow) {
		underflow.what();
		terminate();
	}

	return true;
}



template<typename data>
CCSTDCPP::Vector<data>::Vector()
{
	m_Capicity = def_capicity;
	m_DataArray = new data[10];
	m_Current_size = 0;
	m_coeffiencyOfExpandSizeRate = def_Expandcoeffiency;
	
}

template<typename data>
CCSTDCPP::Vector<data>::Vector(const data& ref_data)
{
	m_Capicity = def_capicity;
	m_Current_size = 1;
	m_DataArray = new data[10];
	m_DataArray[0] = ref_data;
	m_coeffiencyOfExpandSizeRate = def_Expandcoeffiency;
}


template<typename data>
CCSTDCPP::Vector<data>::Vector(const Vector& vec)
{
	m_Capicity = vec.m_Capicity;
	m_Current_size = vec.m_Current_size;
	if (vec.m_DataArray == nullptr || vec.m_Current_size == 0) {
		return;
	}
	m_DataArray = new data[m_Current_size];
	for (Size i = 0; i < m_Current_size; i++) {
		m_DataArray[i] = vec.m_DataArray[i];
	}
}

template<typename data>
CCSTDCPP::Vector<data>::Vector(const Vector&& vec)
{
	m_Capicity = vec.m_Capicity;
	m_Current_size = vec.m_Current_size;
	if (vec.m_DataArray == nullptr || vec.m_Current_size == 0) {
		return;
	}
	m_DataArray = new data[m_Current_size];
	for (CCSTDCPP::Size i = 0; i < m_Current_size; i++) {
		m_DataArray[i] = vec.m_DataArray[i];
	}

}


template<typename data>
CCSTDCPP::Vector<data>& CCSTDCPP::Vector<data>::operator=(const CCSTDCPP::Vector<data>& vec)
{
	if (this->m_DataArray == vec.m_DataArray) {
		return *this;
	}

	delete[] m_DataArray;
	m_DataArray = new data[vec.m_Capicity];
	for (int i = 0; i < vec.m_Current_size; i++) {
		m_DataArray[i] = vec.m_DataArray[i];
	}

	m_Capicity = vec.m_Capicity;
	m_Current_size = vec.m_Current_size;
	m_coeffiencyOfExpandSizeRate = vec.m_coeffiencyOfExpandSizeRate;
	
	return *this;
}


template<typename data>
CCSTDCPP::Size CCSTDCPP::Vector<data>::size() const
{
	return m_Current_size;
}

template<typename data>
CCSTDCPP::Size CCSTDCPP::Vector<data>::capicity() const
{
	return m_Capicity;
}

template<typename data>
data* CCSTDCPP::Vector<data>::rawDataStaticArray(CCSTDCPP::CopySelection usrSelection) const
{
	if (m_DataArray == nullptr) {
		return nullptr;
	}

	try {
		switch (usrSelection)
		{
		case CopySelection::Independent_Copy:
		{
			data* copyOne = new data[m_Current_size];

			for (int i = 0; i < m_Capicity; i++) {
				copyOne[i] = m_DataArray[i];
			}

			return copyOne;
		}
		case CopySelection::Shared_Reference:
			return m_DataArray;
		default:
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::cerr << "Process return back nullptr";
		return nullptr;
	}
}

template<typename data>
CCSTDCPP::Vector<data>::~Vector()
{
	if (m_DataArray != nullptr)
	{
		delete[] m_DataArray;
	}
}

template<typename data>
data* CCSTDCPP::Vector<data>::begin() const
{
	return m_DataArray;
}

template<typename data>
data* CCSTDCPP::Vector<data>::end() const
{
	return m_DataArray + m_Current_size ;
}

template<typename data>
void CCSTDCPP::Vector<data>::resize(const Size newWishedSize)
{
	data* newSpace = new data[newWishedSize];
	for (int i = 0; i < m_Current_size; i++)
	{
		newSpace[i] = m_DataArray[i];
	}

	delete[] m_DataArray;

	m_DataArray = newSpace;
	m_Capicity = newWishedSize;
}

template<typename data>
data CCSTDCPP::Vector<data>::front()
{
	return data(*m_DataArray);
}

template<typename data>
data CCSTDCPP::Vector<data>::rear()
{
	return data(*(m_DataArray + m_Current_size - 1));
}

template<typename data>
void CCSTDCPP::Vector<data>::push_back(const data& fromdata)
{
	m_Current_size++;

	if (this->isFull())
	{
		resize(static_cast<Size>(m_Capicity * 1.3));
	}

	m_DataArray[m_Current_size - 1] = fromdata;
}

template<typename data>
void CCSTDCPP::Vector<data>::push_back(const CCSTDCPP::VectorIterator<data>& it)
{
	m_Current_size++;

	if (this->isFull())
	{
		resize(static_cast<Size>(m_Capicity * 1.3));
	}

	m_DataArray[m_Current_size - 1] = *it;
}

template<typename data>
void CCSTDCPP::Vector<data>::push_back(const Vector& vector)
{
	Size supposedSize = m_Current_size + vector.m_Current_size;

	if (isSupposedToResize(supposedSize)) {
		resize(getSuitableSize(supposedSize));
	}

	for (int i = m_Current_size, j = 0; j < vector.m_Current_size; i++, j++) {
		m_DataArray[i] = vector.m_DataArray[j];
	}
	
	m_Current_size += vector.m_Current_size;
}

template<typename data>
void CCSTDCPP::Vector<data>::push_back(const data* beg, const data* end)
{
	Size countElems = 1;

	/* 解决自拷贝问题 */
	Index offsetBeg = -1; 

	if (beg > end)
	{
#ifdef QUICK_PRIORITY
		std::cerr << "detect the invalid args for beg and end, call the swap";
		const data* tmp = beg;
		beg = end;
		end = tmp;
#elif SAFETY_PRIORITY
#endif
	}

	if (beg >= this->begin() && end <= this->end())
	{
		offsetBeg = this->begin() - beg;
	}

	VectorIterator<data> it;
	for (it = beg; it != end; it++) {
		countElems++;
	}

	Size supposedSize = m_Current_size + countElems;


	if (isSupposedToResize(supposedSize)) {
		resize(getSuitableSize(supposedSize));
	}

	if (offsetBeg != -1) // 数值发生改动，证明拷贝内容发生在数组内，需要计算偏移而不是原地址
	{
		for (int i = m_Current_size, j = 0; j < countElems; i++, j++) {
			m_DataArray[i] = *(this->begin() + offsetBeg + j);
		}
	}
	else
	{
		for (int i = m_Current_size, j = 0; j < countElems; i++, j++) {
			m_DataArray[i] = *(beg + j);
		}
	}

	m_Current_size += countElems;
}


template<typename data>
data CCSTDCPP::Vector<data>::pop_back()
{
	// 偷懒了一下，本质上应当采取跟push_back自身一样的策略,
	// 但是resize带来的迁移使得备忘录或许占领更大的开销，所以干脆拷贝拿到数据
	data res = m_DataArray[m_Current_size - 1];
	m_Current_size--;
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
	return res;
}

template<typename data>
void CCSTDCPP::Vector<data>::pop()
{
	m_Current_size--;
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
}

template<typename data>
data& CCSTDCPP::Vector<data>::operator[](Index index) const
{
	checkIndexValid(index);
	return m_DataArray[index];
}

template<typename data>
data& CCSTDCPP::Vector<data>::at(Index index) const
{
	checkIndexValid(index);
	return m_DataArray[index];
}

template<typename data>
void CCSTDCPP::Vector<data>::insert(const Index index,const data& insert_data)
{
	checkIndexValid(index);
	m_Current_size++;

	if (this->isFull())
	{
		resize(static_cast<Size>(m_Capicity * 1.3));
	}

	for (int i = m_Current_size - 1; i > index; i--) {
		m_DataArray[i] = m_DataArray[i - 1];
	}

	m_DataArray[index] = insert_data;
}

template<typename data>
void CCSTDCPP::Vector<data>::insert(CCSTDCPP::VectorIterator<data>& it,const data& insert_data)
{
	try
	{
		if (this->end() < it.currentElemAddress() || this->begin() > it.currentElemAddress())
		{
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch(CCSTDCPP::Exp_WrongConf& wrongConf)
	{
		wrongConf.what();
		terminate();
	}

	m_Current_size++;

	if (this->isFull())
	{
		resize(static_cast<Size>(m_Capicity * 1.3));
	}

	data* ptr1 = it.currentElemAddress();
	data* ptr2 = this->begin();

	Index index = ptr1 - ptr2;

	for (int i = m_Current_size - 1; i > index; i--) {
		m_DataArray[i] = m_DataArray[i - 1];
	}

	m_DataArray[index] = insert_data;
}


template<typename data>
void CCSTDCPP::Vector<data>::insert(const Index Beg, const Index End, const data* dataArray)
{
	try {
		if (End < Beg) {
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::Exp_WrongConf& wrongConf) {

		wrongConf.what();
		terminate();
	}

	checkIndexValid(Beg);
	checkIndexValid(End);
	Index supposedSize = End - Beg + 1 + m_Current_size;

	if (isSupposedToResize(supposedSize)) {
		resize(getSuitableSize(supposedSize));
	}

	for (
		int i = supposedSize - 1, j = m_Current_size-1;
		j >= (int)Beg; 
		i--,j--
		)
	{
		m_DataArray[i] = m_DataArray[j];
	}


	for (int i = 0 ; i < (int)End - (int)Beg + 1; i++)
	{
		m_DataArray[Beg + i] = dataArray[i];
	}

	m_Current_size += End - Beg + 1;
}

template<typename data>
void CCSTDCPP::Vector<data>::insert(Index fromWhere, const data* Beg, const data* End)
{
	try 
	{
		if (Beg == nullptr || End == nullptr) {
			throw CCSTDCPP::Exp_Nullptr();
		}
		if (Beg > End) {
			throw CCSTDCPP::Exp_WrongConf();
		}

		if (fromWhere > m_Current_size) {
			throw CCSTDCPP::Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::Exp_Nullptr& nullOne) {
		nullOne.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_WrongConf& wrongConf) {
		wrongConf.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_OverFlow& overFlow) {
#ifdef SAFE_PRIORITY
		overFlow.what();
		terminate();
#elif QUICK_PRIORITY 
		overFlow.what();
		isEmpty() ? fromWhere = 0 : fromWhere = m_Current_size - 1;
#endif
	}

	Size supposedSize = (End - Beg) + 1 + m_Current_size;

	if (isSupposedToResize(supposedSize)) {
		resize(getSuitableSize(supposedSize));
	}

	for (
		int i = supposedSize - 1, j = m_Current_size - 1;
		j >= (int)fromWhere;
		i--, j--
		)
	{
		m_DataArray[i] = m_DataArray[j];
	}

	for (int i = fromWhere, j = 0; j < (End - Beg) + 1; j++, i++)
	{
		m_DataArray[i] = *const_cast<data*>(Beg + j);
	}

	m_Current_size += (End - Beg)  + 1;
}

template<typename data>
void CCSTDCPP::Vector<data>::clear()
{
	if (m_DataArray != nullptr) {
		delete[] m_DataArray;
		m_DataArray = nullptr;
	}

	m_Capicity = def_capicity;
	m_Current_size = 0;
}

template<class data>
void CCSTDCPP::Vector<data>::erase(const Index index)
{
	checkIndexValid(index);

	for (int i = index; i < m_Current_size - 1; i++)
	{
		m_DataArray[i] = m_DataArray[i + 1];
	}

	m_Current_size--;

	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
}

template<class data>
void CCSTDCPP::Vector<data>::erase(const Index beg, const Index end)
{
	checkIndexValid(beg);
	checkIndexValid(end);

	try {
		if (end < beg) {
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::Exp_WrongConf& wrongConf) {
		putchar('\n');
		wrongConf.what();
		std::cerr << "I mean, you just make it opposite between beg and end!";
		terminate();
	}

	int putter = beg;

	for (int i = end + 1; i < m_Current_size; i++)
	{
		m_DataArray[putter++] = m_DataArray[i];
	}

	m_Current_size -= (end - beg + 1);
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
}

template<class data>
void CCSTDCPP::Vector<data>::erase(const data* beg, const data* end)
{
	try
	{
		if (beg == nullptr || end == nullptr)
		{
			throw CCSTDCPP::Exp_Nullptr();
		}

		if (beg < this->begin())
		{
			throw CCSTDCPP::Exp_UnderFlow();
		}

		if (end > this->end())
		{
			throw CCSTDCPP::Exp_OverFlow();
		}

		if (beg > end)
		{
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (Exp_Nullptr& null) {
		null.what();
		terminate();
	}
	catch (Exp_OverFlow& overFlow) {
		overFlow.what();
		terminate();
	}
	catch (Exp_UnderFlow& underFlow) {
		underFlow.what();
		terminate();
	}
	catch (Exp_WrongConf& wrongConf) {
		wrongConf.what();
		terminate();
	}

	VectorIterator<data> it, putter,edge;
	
	Index endOne = end - this->begin();
	Index begOne = beg - this->begin();

	for (int i = endOne + 1; i < m_Current_size - 1; i++)
	{
		m_DataArray[i] = m_DataArray[begOne++];
	}

	m_Current_size -= (endOne - begOne) ;
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
}

template<class data>
void CCSTDCPP::Vector<data>::erase(const CCSTDCPP::VectorIterator<data>& it)
{
	try {
		if (it.currentElemAddress() < this->begin()) {
			throw Exp_UnderFlow();
		}
		if (it.currentElemAddress() > this->end()) {
			throw Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::Exp_UnderFlow& underflow) {
		underflow.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_OverFlow& overflow) {
		overflow.what();
		terminate();
	}
	VectorIterator<data> putter;
	for (putter = it.currentElemAddress(); putter != this->end(); putter++) {
		*putter = *(putter + 1);
	}

	m_Current_size--;
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}
}

template<class data>
data* CCSTDCPP::Vector<data>::erase_back(const Index index)
{
	checkIndexValid(index);

	data* res = new data(m_DataArray[index]);

	for (int i = index; i < m_Current_size - 1; i++)
	{
		m_DataArray[i] = m_DataArray[i + 1];
	}

	m_Current_size--;

	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}

	return res;
}

template<class data>
data* CCSTDCPP::Vector<data>::erase_back(const Index beg, const Index end)
{
	checkIndexValid(beg);
	checkIndexValid(end);

	try {
		if (end < beg) {
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::Exp_WrongConf& wrongConf) {
		putchar('\n');
		wrongConf.what();
		std::cerr << "I mean, you just make it opposite between beg and end!";
		terminate();
	}

	data* eraseArray = new data[end - beg + 1];

	int putter = beg;

	for (int i = 0; i < end - beg + 1; i++) {
		eraseArray[i] = m_DataArray[putter++];
	}

	putter = beg;

	for (int i = end + 1; i < m_Current_size; i++)
	{
		m_DataArray[putter++] = m_DataArray[i];
	}

	m_Current_size -= (end - beg + 1);
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}

	return eraseArray;
}

template<class data>
data* CCSTDCPP::Vector<data>::erase_back(const data* beg, const data* end)
{
	try
	{
		if (beg == nullptr || end == nullptr)
		{
			throw CCSTDCPP::Exp_Nullptr();
		}

		if (beg < this->begin())
		{
			throw CCSTDCPP::Exp_UnderFlow();
		}

		if (end > this->end())
		{
			throw CCSTDCPP::Exp_OverFlow();
		}

		if (beg > end)
		{
			throw CCSTDCPP::Exp_WrongConf();
		}
	}
	catch (Exp_Nullptr& null) {
		null.what();
		terminate();
	}
	catch (Exp_OverFlow& overFlow) {
		overFlow.what();
		terminate();
	}
	catch (Exp_UnderFlow& underFlow) {
		underFlow.what();
		terminate();
	}
	catch (Exp_WrongConf& wrongConf) {
		wrongConf.what();
		terminate();
	}

	VectorIterator<data> it, edge;

	Index endOne = end - this->begin();
	Index begOne = beg - this->begin();

	data* eraseArray = new data[endOne - begOne + 1];
	int putter = begOne;
	for (int i = 0; i < endOne - begOne + 1; i++) {
		eraseArray[i] = m_DataArray[putter++];
	}

	for (int i = endOne + 1; i < m_Current_size - 1; i++)
	{
		m_DataArray[i] = m_DataArray[begOne++];
	}

	m_Current_size -= (endOne - begOne);
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}

	return eraseArray;
}

template<class data>
data* CCSTDCPP::Vector<data>::erase_back(const CCSTDCPP::VectorIterator<data>& it)
{
	try {
		if (it.currentElemAddress() < this->begin()) {
			throw Exp_UnderFlow();
		}
		if (it.currentElemAddress() > this->end()) {
			throw Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::Exp_UnderFlow& underflow) {
		underflow.what();
		terminate();
	}
	catch (CCSTDCPP::Exp_OverFlow& overflow) {
		overflow.what();
		terminate();
	}

	data* eraseOne = new data(*it);


	VectorIterator<data> putter;
	for (putter = it.currentElemAddress(); putter != this->end(); putter++) {
		*putter = *(putter + 1);
	}

	m_Current_size--;
	if (isSupposedToResize(m_Current_size)) {
		resize(
			static_cast<Size>(m_Capicity / 2)
		);
	}

	return eraseOne;
}

template<class data>
bool CCSTDCPP::Vector<data>::operator==(const Vector<data>& vec)
{
	if (vec.m_Current_size != this->m_Current_size) {
		return false;
	}

	for (int i = 0; i < m_Current_size - 1; i++)
	{
		if (vec[i] != (*this)[i])
		{
			return false;
		}
	}

	return true;
}

template<class data>
bool CCSTDCPP::Vector<data>::operator!=(const Vector<data>& vec)
{
	if (vec.m_Current_size != this->m_Current_size) {
		return true;
	}

	for (int i = 0; i < m_Current_size - 1; i++)
	{
		if (vec[i] != (*this)[i])
		{
			return true;
		}
	}

	return false;
}

#endif

#include"staticArray.hpp"

#ifdef _BytesArray_CCSTDCPP_
template<class data>
CCSTDCPP::BytesArray<data> CCSTDCPP::Vector<data>::wrappeddata()
{
	return BytesArray<data>(this->m_DataArray, m_Current_size);
}

#endif // _BytesArray_CCSTDCPP_
