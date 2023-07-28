#include"CCSTDCPP_String.h"
// namespace global
#ifdef CCSTDCPP_UNICODE_TYPE_PRIORITY
std::wostream& CCSTDCPP::operator<<(std::wostream& os, CCSTDCPP::StringW& aStr)
{
	os << aStr.data();
	return os;
}



bool CCSTDCPP::StringW::isEmpty() const
{
	if (m_coreString == nullptr)
		return true;
	if (*m_coreString == L'\0')
		return true;

	return false;
}

bool CCSTDCPP::StringW::isNull() const
{
	if (m_coreString == nullptr)
		return true;

	return false;
}

wchar_t& CCSTDCPP::StringW::operator[](Index index) const
{
	try {
		if (index >= m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}

	return m_coreString[index];
}

wchar_t& CCSTDCPP::StringW::at(Index index) const
{
	try {
		if (index >= m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}

	return m_coreString[index];
}

bool CCSTDCPP::StringW::checkAndRefresh()
{
	try
	{
		Size check = 0;
		for (
			wchar_t* counter = m_coreString;
			*counter != L'\0';
			check++
			);

		if (check != m_currentSize)
		{
			throw CCSTDCPP::String_Exp_BadStr();
		}
	}
	catch (CCSTDCPP::String_Exp_BadStr& badString) {
		badString.what();
		std::terminate();
		return false;
	}

	return true;
}



CCSTDCPP::StringW::StringW()
{
	m_coreString = nullptr;
	m_currentSize = 0;
	setlocale(LC_ALL, "");
}


CCSTDCPP::StringW::StringW(const wchar_t* CString, Index beg, Index end)
{
	Size count = 1;

	for (
		wchar_t* counter = const_cast<wchar_t*>(CString);
		*counter != L'\0';
		counter++, count++
		);

	try {
		if (count <= beg) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
		if (beg > end && end != DEF_END)
		{
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end >= count)
		{
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow)
	{
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf)
	{
		wrongConf.what();
		std::terminate();
	}


	if (end == DEF_END)
	{
		end = count;
	}
	m_coreString = new wchar_t[end - beg + 2];
	wchar_t* copyBeg, * copyTo;
	for (
		copyBeg = const_cast<wchar_t*>(CString) + beg,
		copyTo = m_coreString;
		copyBeg != const_cast<wchar_t*>(CString) + end;
		*copyTo++ = *copyBeg++
		);

	m_currentSize = end - beg;
	*copyTo = L'\0';
}

CCSTDCPP::StringW::StringW(const wchar_t ch, Size repeatN)
{
	try
	{
		if (repeatN == 0) {
			std::cerr << "For why??? get 0 means nothing! ";
			throw CCSTDCPP::String_Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	m_coreString = new wchar_t[repeatN + 1];

	for (Size i = 0; i < repeatN + 1; m_coreString[i] = ch, i++);

	m_currentSize = repeatN + 1;
	m_coreString[m_currentSize - 1] = L'\0';
}

CCSTDCPP::StringW::StringW(const StringW& aStr)
{
	m_coreString = new wchar_t[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = L'\0';
}

CCSTDCPP::StringW::StringW(const StringW&& aStr) noexcept
{
	m_coreString = new wchar_t[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = L'\0';
}

CCSTDCPP::Size CCSTDCPP::StringW::size() const
{
	return m_currentSize;
}

const wchar_t* CCSTDCPP::StringW::data() const
{
	wchar_t* copy = new wchar_t[m_currentSize];
	for (
		Size i = 0;
		i < this->m_currentSize;
		copy[i] = this->m_coreString[i], i++
		);
	copy[m_currentSize - 1] = L'\0';
	return copy;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator=(const StringW& aStr)
{
	if (aStr.m_coreString == this->m_coreString) {
		return *this;
	}

	delete[] m_coreString;
	m_coreString = nullptr;
	m_coreString = new wchar_t[aStr.m_currentSize];
	wchar_t* dst = m_coreString;

	for (const wchar_t* source = aStr.m_coreString; *source != L'\0'; *dst++ = *source++);

	m_currentSize = aStr.m_currentSize;
	m_coreString[m_currentSize - 1] = L'\0';
	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator=(const wchar_t* CString)
{
	if (CString == m_coreString) {
		return *this;
	}

	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null) {
		null.what();
		std::terminate();
	}

	Size count = 1;
	for (const wchar_t* counter = CString; *counter != L'\0'; count++,counter++)
		;

	delete[] m_coreString;
	m_coreString = new wchar_t[count];

	wchar_t* dst = m_coreString;

	for (const wchar_t* source = CString; *source != L'\0'; *dst++ = *source++);

	m_currentSize = count;
	m_coreString[m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW::~StringW() {
	delete[] m_coreString;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::setStr(const wchar_t* CString, Index beg, Index end, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != L'\0') /* Empty and Nullptr*/
		{
			switch (selection)
			{
			case CCSTDCPP::StringOverLoadSelection::IgnoreOverload:
				break;
			case CCSTDCPP::StringOverLoadSelection::WarningOverload:
				std::cerr << "Warning: the string is already inited, this process will absolutely reset the string!\n";
				break;
			case CCSTDCPP::StringOverLoadSelection::DisableOverload:
				throw CCSTDCPP::String_Exp_InvalidOverload();
			}
		}
	}
	catch (CCSTDCPP::String_Exp_InvalidOverload& invalidOverload)
	{
		invalidOverload.what();
		std::terminate();
	}

	Size count = 1;

	for (
		wchar_t* counter = const_cast<wchar_t*>(CString);
		*counter != L'\0';
		counter++, count++
		);

	try {
		if (count <= beg) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
		if (beg > end && end != DEF_END)
		{
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end >= count)
		{
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow)
	{
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf)
	{
		wrongConf.what();
		std::terminate();
	}


	if (end == DEF_END)
	{
		end = count;
	}
	m_coreString = new wchar_t[end - beg + 2];
	wchar_t* copyBeg, * copyTo;
	for (
		copyBeg = const_cast<wchar_t*>(CString) + beg,
		copyTo = m_coreString;
		copyBeg != const_cast<wchar_t*>(CString) + end;
		*copyTo++ = *copyBeg++
		);

	m_currentSize = end - beg;
	*copyTo = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::setStr(const wchar_t ch, Size repeatN, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != L'\0') /* Empty and Nullptr*/
		{
			switch (selection)
			{
			case CCSTDCPP::StringOverLoadSelection::IgnoreOverload:
				break;
			case CCSTDCPP::StringOverLoadSelection::WarningOverload:
				std::cerr << "Warning: the string is already inited, this process will absolutely reset the string!\n";
				break;
			case CCSTDCPP::StringOverLoadSelection::DisableOverload:
				throw CCSTDCPP::String_Exp_InvalidOverload();
			}
		}
	}
	catch (CCSTDCPP::String_Exp_InvalidOverload& invalidOverload)
	{
		invalidOverload.what();
		std::terminate();
	}

	try
	{
		if (repeatN == 0) {
			std::cerr << "For why??? get 0 means nothing! ";
			throw CCSTDCPP::String_Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	m_coreString = new wchar_t[repeatN + 1];

	for (Size i = 0; i < repeatN + 1; m_coreString[i] = ch, i++);

	m_currentSize = repeatN + 1;
	m_coreString[m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::setStr(const CCSTDCPP::StringW& aStr, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != L'\0') /* Empty and Nullptr*/
		{
			switch (selection)
			{
			case CCSTDCPP::StringOverLoadSelection::IgnoreOverload:
				break;
			case CCSTDCPP::StringOverLoadSelection::WarningOverload:
				std::cerr << "Warning: the string is already inited, this process will absolutely reset the string!\n";
				break;
			case CCSTDCPP::StringOverLoadSelection::DisableOverload:
				throw CCSTDCPP::String_Exp_InvalidOverload();
			}
		}
	}
	catch (CCSTDCPP::String_Exp_InvalidOverload& invalidOverload)
	{
		invalidOverload.what();
		std::terminate();
	}

	m_coreString = new wchar_t[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::setStr(const CCSTDCPP::StringW&& aStr, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != L'\0') /* Empty and Nullptr*/
		{
			switch (selection)
			{
			case CCSTDCPP::StringOverLoadSelection::IgnoreOverload:
				break;
			case CCSTDCPP::StringOverLoadSelection::WarningOverload:
				std::cerr << "Warning: the string is already inited, this process will absolutely reset the string!\n";
				break;
			case CCSTDCPP::StringOverLoadSelection::DisableOverload:
				throw CCSTDCPP::String_Exp_InvalidOverload();
			}
		}
	}
	catch (CCSTDCPP::String_Exp_InvalidOverload& invalidOverload)
	{
		invalidOverload.what();
		std::terminate();
	}

	m_coreString = new wchar_t[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::append(const wchar_t* CString, Index beg, Index end)
{
	if (CString == nullptr) {
		return *this;
	}

	Size count = 1;

	for (
		wchar_t* counter = const_cast<wchar_t*>(CString);
		*counter != L'\0';
		counter++, count++
		);

	try {
		if (count <= beg) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
		if (beg > end && end != DEF_END)
		{
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end >= count)
		{
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow)
	{
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf)
	{
		wrongConf.what();
		std::terminate();
	}


	if (end == DEF_END)
	{
		end = count;
	}
	else
	{
		count = end - beg;
	}

	wchar_t* newSpace = new wchar_t[this->m_currentSize + count - 1];

	wchar_t* dest = newSpace;

	for (wchar_t* source = m_coreString; *source != L'\0'; *dest++ = *source++);

	const wchar_t* otherString = CString + beg;

	for (; otherString != CString + end; *dest++ = *otherString++);

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = this->m_currentSize + count - 1;
	m_coreString[m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::append(const wchar_t ch, Size repeatN)
{
	try
	{
		if (repeatN == 0) {
			std::cerr << "For why??? get 0 means nothing! ";
			throw CCSTDCPP::String_Exp_WrongConf();
		}
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	wchar_t* newSpace = new wchar_t[repeatN + this->m_currentSize];

	wchar_t* dst = newSpace;
	for (wchar_t* source = m_coreString; *source != L'\0'; *dst++ = *source++);

	for (Size i = 0; i < repeatN + 1; *dst++ = ch, i++);



	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = repeatN + this->m_currentSize;
	m_coreString[m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::append(const CCSTDCPP::StringW& aStr)
{

	wchar_t* newSpace = new wchar_t[this->m_currentSize + aStr.m_currentSize - 1];

	wchar_t* dst = newSpace;

	for (const wchar_t* source = this->m_coreString; *source != L'\0'; *dst++ = *source++);

	if (aStr.m_coreString == this->m_coreString)
		for (const wchar_t* source = this->m_coreString; *source != L'\0'; *dst++ = *source++);
	else
		for (const wchar_t* source = aStr.m_coreString; *source != L'\0'; *dst++ = *source++);

	delete[] m_coreString;

	m_coreString = newSpace;
	m_currentSize = this->m_currentSize + aStr.m_currentSize - 1;
	m_coreString[m_currentSize - 1] = L'\0';

	return *this;
}

CCSTDCPP::StringW CCSTDCPP::StringW::reverseStr()
{
	wchar_t* data = new wchar_t[m_currentSize];
	wchar_t* dst = data;
	for (const wchar_t* source = m_coreString + m_currentSize - 2; source != m_coreString; *dst++ = *source--);
	*dst++ = *m_coreString;
	*dst = L'\0';
	return { data };
}

void CCSTDCPP::StringW::reverse()
{
	wchar_t* front = m_coreString;
	wchar_t* end = m_coreString + m_currentSize - 2;
	for (; front <= end; front++, end--) {
		wchar_t tmp = *front;
		*front = *end;
		*end = tmp;
	}

	m_coreString[m_currentSize - 1] = L'\0';
}

bool CCSTDCPP::StringW::isEqual(const wchar_t* CString, Index beg, Index end)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;

	for (
		wchar_t* counter = const_cast<wchar_t*>(CString);
		*counter != L'\0';
		counter++, count++
		);

	try {
		if (count <= beg) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
		if (beg > end && end != DEF_END)
		{
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end >= count)
		{
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow)
	{
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf)
	{
		wrongConf.what();
		std::terminate();
	}

	if (end == DEF_END)
	{
		end = count;
	}

	for (Size i = beg; i <= end; i++) {
		if (m_coreString[i] != CString[i]) {
			return false;
		}
	}

	return true;
}

bool CCSTDCPP::StringW::isEqual(const CCSTDCPP::StringW& str, Index beg, Index end)
{
	if (str.m_currentSize != this->m_currentSize) {
		return false;
	}

	try {

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}
		if (end > this->m_currentSize || beg > this->m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}

	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}

	if (end == DEF_END) {
		end = m_currentSize;
	}


	for (Size i = beg; i <= end; i++) {
		if (this->m_coreString[i] != str.m_coreString[i]) {
			return false;
		}
	}

	return true;
}

bool CCSTDCPP::StringW::operator==(const wchar_t* CString)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;
	const wchar_t* counter = CString;
	for (; *counter != L'\0'; counter++, count++);

	if (m_currentSize != count) {
		return false;
	}

	for (Size i = 0; i < m_currentSize; i++) {
		if (m_coreString[i] != CString[i]) {
			return false;
		}
	}

	return true;
}

bool CCSTDCPP::StringW::operator==(const CCSTDCPP::StringW& str)
{
	if (str.m_currentSize != this->m_currentSize) {
		return false;
	}

	for (Size i = 0; i < m_currentSize; i++) {
		if (m_coreString[i] != str.m_coreString[i]) {
			return false;
		}
	}

	return true;
}

bool CCSTDCPP::StringW::operator!=(const wchar_t* CString)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;
	const wchar_t* counter = CString;
	for (; *counter != L'\0'; counter++, count++);

	if (m_currentSize != count) {
		return true;
	}

	for (Size i = 0; i < m_currentSize; i++) {
		if (m_coreString[i] != CString[i]) {
			return true;
		}
	}

	return false;
}

bool CCSTDCPP::StringW::operator!=(const CCSTDCPP::StringW& str)
{
	if (str.m_currentSize != this->m_currentSize) {
		return true;
	}

	for (Size i = 0; i < m_currentSize; i++) {
		if (m_coreString[i] != str.m_coreString[i]) {
			return true;
		}
	}

	return false;
}


CCSTDCPP::StringW CCSTDCPP::StringW::operator+(const wchar_t* CString)
{
	if (CString == nullptr) {
		return *this;
	}

	Size count = 1;

	for (
		wchar_t* counter = const_cast<wchar_t*>(CString);
		*counter != L'\0';
		counter++, count++
		);
	wchar_t* newSpace = new wchar_t[this->m_currentSize + count - 1];

	wchar_t* dest = newSpace;

	for (wchar_t* source = m_coreString; *source != L'\0'; *dest++ = *source++);

	const wchar_t* otherString = CString;

	for (; *otherString != L'\0'; *dest++ = *otherString++);


	return { newSpace }; // initialized lists
}

CCSTDCPP::StringW CCSTDCPP::StringW::operator+(const CCSTDCPP::StringW& str)
{
	wchar_t* newSpace = new wchar_t[str.m_currentSize + this->m_currentSize - 1];

	wchar_t* dst = newSpace;

	for (const wchar_t* source = this->m_coreString; *source != L'\0'; *dst++ = *source++);

	for (const wchar_t* source = str.m_coreString; *source != L'\0'; *dst++ = *source++);

	*dst = L'\0';

	return { newSpace };
}

CCSTDCPP::StringW CCSTDCPP::StringW::operator+(const wchar_t ch) const
{
	wchar_t* newSpace = new wchar_t[m_currentSize + 1];

	newSpace[m_currentSize - 1] = ch;

	newSpace[m_currentSize] = L'\0';

	return { newSpace };
}

Position CCSTDCPP::StringW::findSub(const wchar_t* CString, Index beg, Index end)
{

	if (end == DEF_END) {
		end = m_currentSize;
	}
	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null) {
		null.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	if (*CString == L'\0')
	{
		return &m_coreString[m_currentSize - 1];
	}
	// 一阶K氏字符串匹配算法(算法导论摸鱼时候看的，大概如此)
	wchar_t* source = const_cast<wchar_t*>(CString);
	Position cur = m_coreString + beg;
	Position next = cur;
	while (cur <= m_coreString + end - 1 && *cur != L'\0')
	{

		// Position: find first match
		for (; *cur != *source && cur <= m_coreString + end - 1; cur++);

		// find next match
		for (next = cur + 1; *next != *source && *next != L'\0'; next++); // 到达\0就停止，这下标志着为空了

		// if find first match, then start check WHOLY
		bool isThisPossible = false;
		Position checker = cur;
		for (; !isThisPossible;) {
			if (*checker++ != *source++) {
				source = const_cast<wchar_t*>(CString + beg);
				cur = next;
				break;
			}
			// yes, we fetch the End --- check the source wholy
			// in this case, we return 
			if (*source == L'\0') {
				isThisPossible = true;
				break;
			}
		}

		if (!isThisPossible) {
			continue;
		}
		else {
			return cur;
		}

	}

	return m_coreString + m_currentSize - 1;
}

Position CCSTDCPP::StringW::findSub(const StringW& str, Index beg, Index end)
{

	if (end == DEF_END) {
		end = m_currentSize;
	}
	try {

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	if (str.isEmpty())
	{
		return &m_coreString[m_currentSize - 1];
	}
	// 一阶K氏字符串匹配算法(算法导论摸鱼时候看的，大概如此)
	wchar_t* source = str.m_coreString;
	Position cur = m_coreString + beg;
	Position next = cur;
	while (cur <= m_coreString + end - 1 && *cur != L'\0')
	{

		// Position: find first match
		for (; *cur != *source && cur <= m_coreString + end - 1; cur++);

		// find next match
		for (next = cur + 1; *next != *source && *next != L'\0'; next++); // 到达\0就停止，这下标志着为空了

		// if find first match, then start check WHOLY
		bool isThisPossible = false;
		Position checker = cur;
		for (; !isThisPossible;) {
			if (*checker++ != *source++) {
				source = const_cast<wchar_t*>(str.m_coreString + beg);
				cur = next;
				break;
			}
			// yes, we fetch the End --- check the source wholy
			// in this case, we return 
			if (*source == L'\0') {
				isThisPossible = true;
				break;
			}
		}

		if (!isThisPossible) {
			continue;
		}
		else {
			return cur;
		}

	}

	return m_coreString + m_currentSize - 1;
}


Position CCSTDCPP::StringW::findSub(const wchar_t ch, Index beg, Index end)
{
	if (ch == L'\0')
	{
		return &m_coreString[m_currentSize - 1];
	}

	if (end == DEF_END) {
		end = m_currentSize;
	}
	try {

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	for (wchar_t* finder = m_coreString + beg; finder < m_coreString + end && *finder != L'\0'; finder++)
	{
		if (*finder == ch) {
			return finder;
		}
	}

	return m_coreString + m_currentSize - 1;
}

PositionGroup CCSTDCPP::StringW::findAllSub(const wchar_t ch, Index beg, Index end)
{
	if (end == DEF_END)
	{
		end = m_currentSize;
	}

	auto ptr2Arr = new Position[DEF_POSGRP_SIZE];
	Size curLimit = DEF_POSGRP_SIZE;
	Size countHowMany = 0;

	Position fetcher = m_coreString;
	Index curFind = beg;
	for (; fetcher <= m_coreString + m_currentSize; fetcher++)
	{
		fetcher = findSub(ch, curFind, end);
		if (fetcher - m_coreString + 1 >= end) {
			break;
		}
		if (*fetcher != L'\0')
		{
			ptr2Arr[countHowMany++] = fetcher;

			if (countHowMany >= curLimit - 1) {
				// resize UP
				curLimit = static_cast<Size>(1.5 * curLimit);
				auto newPtr = new Position[curLimit];
				for (int i = 0; i < countHowMany - 1; i++) {
					newPtr[i] = ptr2Arr[i];
				}
				delete[] ptr2Arr;
				ptr2Arr = newPtr;
			}

			curFind = fetcher - m_coreString + 1;
		}
	}

	ptr2Arr[countHowMany] = const_cast<wchar_t*>(L"\0");

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

PositionGroup CCSTDCPP::StringW::findAllSub(const wchar_t* CString, Index beg, Index end)
{
	if (end == DEF_END)
	{
		end = m_currentSize;
	}
	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null) {
		null.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	auto ptr2Arr = new Position[DEF_POSGRP_SIZE];
	Size curLimit = DEF_POSGRP_SIZE;
	Size countHowMany = 0;

	Position fetcher = m_coreString;
	Index curFind = beg;
	for (; *fetcher != L'\0'; fetcher++)
	{
		fetcher = findSub(CString, curFind, end);
		if (fetcher >= m_coreString + end - 1) {
			break;
		}
		else
		{
			if (*fetcher != L'\0')
			{
				ptr2Arr[countHowMany++] = fetcher;

				if (countHowMany >= curLimit - 1) {
					// resize UP
					curLimit = static_cast<Size>(1.5 * curLimit);
					auto newPtr = new Position[curLimit];
					for (int i = 0; i < countHowMany; i++) {
						newPtr[i] = ptr2Arr[i];
					}
					delete[] ptr2Arr;
					ptr2Arr = newPtr;
				}

				curFind = fetcher - m_coreString + 1;
			}
			else {
				break;
			}
		}
	}

	ptr2Arr[countHowMany] = const_cast<wchar_t*>(L"\0");

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

PositionGroup CCSTDCPP::StringW::findAllSub(const StringW& str, Index beg, Index end)
{
	if (end == DEF_END)
	{
		end = m_currentSize;
	}
	try {

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}
	auto ptr2Arr = new Position[DEF_POSGRP_SIZE];
	Size curLimit = DEF_POSGRP_SIZE;
	Size countHowMany = 0;

	Position fetcher = m_coreString;
	Index curFind = beg;
	for (; *fetcher != L'\0'; fetcher++)
	{
		fetcher = findSub(str, curFind, end);
		if (fetcher >= m_coreString + end - 1) {
			break;
		}
		else
		{
			if (*fetcher != L'\0')
			{
				ptr2Arr[countHowMany++] = fetcher;

				if (countHowMany >= curLimit - 1) {
					// resize UP
					curLimit = static_cast<Size>(1.5 * curLimit);
					auto newPtr = new Position[curLimit];
					for (int i = 0; i < countHowMany; i++) {
						newPtr[i] = ptr2Arr[i];
					}
					delete[] ptr2Arr;
					ptr2Arr = newPtr;
				}

				curFind = fetcher - m_coreString + 1;
			}
			else {
				break;
			}
		}
	}

	ptr2Arr[countHowMany] = const_cast<wchar_t*>(L"\0");

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

CCSTDCPP::StringW_Array CCSTDCPP::StringW::split(const wchar_t* CString)
{
	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null) {
		null.what();
		std::terminate();
	}
	PositionGroup finderAll = this->findAllSub(CString);

	Size howManySplity = 0;
	for (howManySplity = 0; *finderAll[howManySplity] != L'\0'; )
		howManySplity++;

	auto splitArr = new StringW * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;
	wchar_t* curSplitPiece;
	wchar_t* copyTo;
	wchar_t* source;
	if (curSplitPieceSize == 0)
	{
		splitArr[0] = new StringW(CString);
	}
	else
	{
		curSplitPiece = new wchar_t[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = m_coreString;
		for (Size i = 0; i < curSplitPieceSize; i++) {
			*copyTo++ = *source++;
		}
		*copyTo = L'\0';
		splitArr[0] = new StringW(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for mid
	// especially, we do split minus 1 
	// as the beg and the min should be excluded
	for (Size i = 0; i < howManySplity - 1; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new wchar_t[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = L'\0';
		splitArr[i + 1] = new StringW(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new wchar_t[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = L'\0';
	splitArr[howManySplity] = new StringW(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringW;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}

CCSTDCPP::StringW_Array CCSTDCPP::StringW::split(const StringW& str)
{
	PositionGroup finderAll = this->findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *finderAll[howManySplity] != L'\0'; )
		howManySplity++;

	auto splitArr = new StringW * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;
	wchar_t* curSplitPiece;
	wchar_t* copyTo;
	wchar_t* source;
	if (curSplitPieceSize == 0)
	{
		splitArr[0] = new StringW(str);
	}
	else
	{
		curSplitPiece = new wchar_t[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = m_coreString;
		for (Size i = 0; i < curSplitPieceSize; i++) {
			*copyTo++ = *source++;
		}
		*copyTo = L'\0';
		splitArr[0] = new StringW(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for mid
	for (Size i = 0; i < howManySplity - 1; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new wchar_t[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = L'\0';
		splitArr[i + 1] = new StringW(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new wchar_t[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = L'\0';
	splitArr[howManySplity] = new StringW(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringW;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}


CCSTDCPP::StringW_Array CCSTDCPP::StringW::split(const wchar_t ch)
{
	PositionGroup finderAll = this->findAllSub(ch);

	Size howManySplity = 0;
	for (howManySplity = 0; *finderAll[howManySplity] != L'\0'; )
		howManySplity++;

	auto splitArr = new StringW * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;

	wchar_t* curSplitPiece = new wchar_t[curSplitPieceSize + 1];
	wchar_t* copyTo = curSplitPiece;
	wchar_t* source = m_coreString;
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = L'\0';
	splitArr[0] = new StringW(curSplitPiece);
	delete[] curSplitPiece;

	// for mid
	for (Size i = 0; i < howManySplity - 1; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new wchar_t[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = L'\0';
		splitArr[i + 1] = new StringW(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new wchar_t[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = L'\0';
	splitArr[howManySplity] = new StringW(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringW;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}

void CCSTDCPP::StringW::insert(const wchar_t* CString, Index toWhere)
{
	try {

		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}
		if (toWhere >= m_currentSize) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

	}
	catch (CCSTDCPP::String_Exp_Nullptr& null) {
		null.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}
	Size count = 0;
	wchar_t* counter = const_cast<wchar_t*>(CString);
	for (; *counter != L'\0'; count++, counter++);
	wchar_t* newSpace = new wchar_t[count + m_currentSize];
	wchar_t* copyTo = newSpace;
	wchar_t* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	source = const_cast<wchar_t*>(CString);
	for (; *source != L'\0'; *copyTo++ = *source++);
	source = const_cast<wchar_t*>(m_coreString + toWhere);
	for (; *source != L'\0'; *copyTo++ = *source++);

	*copyTo = L'\0';
	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = count + m_currentSize;
}

void CCSTDCPP::StringW::insert(const StringW& aStr, Index toWhere)
{
	try {
		if (toWhere >= m_currentSize) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	wchar_t* newSpace = new wchar_t[aStr.m_currentSize + m_currentSize - 1];
	wchar_t* copyTo = newSpace;
	wchar_t* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	source = aStr.m_coreString;
	for (; *source != L'\0'; *copyTo++ = *source++);
	source = const_cast<wchar_t*>(m_coreString + toWhere);
	for (; *source != L'\0'; *copyTo++ = *source++);
	*copyTo = L'\0';
	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = aStr.m_currentSize + m_currentSize - 1;
}

void CCSTDCPP::StringW::insert(const wchar_t ch, Index toWhere, Size repeatN)
{
	try {
		if (toWhere >= m_currentSize) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	wchar_t* newSpace = new wchar_t[repeatN + m_currentSize];
	wchar_t* copyTo = newSpace;
	wchar_t* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	for (Size i = 0; i < repeatN; *copyTo++ = ch, i++);
	source = const_cast<wchar_t*>(m_coreString + toWhere);
	for (; *source != L'\0'; *copyTo++ = *source++);
	*copyTo = L'\0';
	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = repeatN + m_currentSize;
}

CCSTDCPP::StringW CCSTDCPP::StringW::remove(const wchar_t* CString, Index beg, Index end)
{
	if (end == DEF_END) {
		end = m_currentSize;
	}

	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null)
	{
		null.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	PositionGroup removePlace = findAllSub(CString, beg, end);
	Size counterOfCString = 0;
	wchar_t* counter = const_cast<wchar_t*>(CString);
	for (; *counter != L'\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);

	Size newStringWSize = m_currentSize - counterOfCString * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t(newStringWSize);
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString + end && *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';
	return { newStringWCoreData };
}

CCSTDCPP::StringW CCSTDCPP::StringW::remove(const StringW& str, Index beg, Index end)
{
	if (end == DEF_END) {
		end = m_currentSize;
	}

	try {

		if (beg > end) {
			throw CCSTDCPP::String_Exp_WrongConf();
		}

		if (end > m_currentSize || beg > m_currentSize) {
			throw CCSTDCPP::String_Exp_OverFlow();
		}
	}
	catch (CCSTDCPP::String_Exp_OverFlow& overflow) {
		overflow.what();
		std::terminate();
	}
	catch (CCSTDCPP::String_Exp_WrongConf& wrongConf) {
		wrongConf.what();
		std::terminate();
	}

	PositionGroup removePlace = findAllSub(str, beg, end);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);

	Size newStringWSize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t(newStringWSize);
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString + end && *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';
	return { newStringWCoreData };
}

CCSTDCPP::StringW CCSTDCPP::StringW::remove(const wchar_t ch, Index beg, Index end)
{
	if (end == DEF_END)
	{
		end = m_currentSize;
	}

	if (ch == L'\0') {
		return { *this };
	}
	Size count = 0;
	wchar_t* counterCh = m_coreString + beg;
	for (; *counterCh != L'\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	wchar_t* special = new wchar_t[m_currentSize - count + 2];
	wchar_t* copyTo = special;
	for (; counterCh <= m_coreString + end && *counterCh != L'\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = L'\0';
	StringW tmp{ special };
	delete[] special;

	return tmp;
}

void CCSTDCPP::StringW::clear()
{
	delete[] m_coreString;
	m_coreString = new wchar_t[1];
	*m_coreString = L'\0';

	m_currentSize = 0;
}

CCSTDCPP::StringW CCSTDCPP::StringW::operator-(const wchar_t* CString)
{
	try {
		if (CString == nullptr) {
			throw CCSTDCPP::String_Exp_Nullptr();
		}
	}
	catch (CCSTDCPP::String_Exp_Nullptr& null)
	{
		null.what();
		std::terminate();
	}

	PositionGroup removePlace = findAllSub(CString);
	Size counterOfCString = 0;
	wchar_t* counter = const_cast<wchar_t*>(CString);
	for (; *counter != L'\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);

	Size newStringWSize = m_currentSize - counterOfCString * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t[newStringWSize];
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString && *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';

	StringW tmp{ newStringWCoreData };
	delete[] newStringWCoreData;

	return tmp;
}

CCSTDCPP::StringW CCSTDCPP::StringW::operator-(const StringW& str)
{
	PositionGroup removePlace = findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);

	Size newStringWSize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t[newStringWSize];
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString && *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';
	
	StringW tmp{ newStringWCoreData };
	delete[] newStringWCoreData;

	return tmp;
}

CCSTDCPP::StringW CCSTDCPP::StringW::operator-(const wchar_t ch)
{
	if (ch == L'\0') {
		return { *this };
	}
	Size count = 0;
	wchar_t* counterCh = m_coreString;
	for (; *counterCh != L'\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	wchar_t* special = new wchar_t[m_currentSize - count];
	wchar_t* copyTo = special;
	for (; *counterCh != L'\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = L'\0';

	return { special };
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator+=(const StringW& str)
{
	wchar_t* newSpace = new wchar_t[str.m_currentSize + this->m_currentSize - 1];
	wchar_t* copyTo = newSpace;
	wchar_t* source = m_coreString;
	for (; *source != L'\0'; *copyTo++ = *source++);
	source = str.m_coreString;
	for (; *source != L'\0'; *copyTo++ = *source++);
	*copyTo = L'\0';

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = str.m_currentSize + this->m_currentSize - 1;

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator+=(const wchar_t* CString)
{
	Size counterOfCString = 0;
	wchar_t* counter = const_cast<wchar_t*>(CString);
	for (; *counter != L'\0'; counter++, counterOfCString++);


	wchar_t* newSpace = new wchar_t[counterOfCString + this->m_currentSize];
	wchar_t* copyTo = newSpace;
	const wchar_t* source = m_coreString;
	for (; *source != L'\0'; *copyTo++ = *source++);
	source = CString;
	for (; *source != L'\0'; *copyTo++ = *source++);
	*copyTo = L'\0';

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = counterOfCString + this->m_currentSize;

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator+=(const wchar_t ch)
{
	wchar_t* newSpace = new wchar_t[1 + this->m_currentSize];
	wchar_t* source = m_coreString;
	wchar_t* copyTo = newSpace;
	for (; *source != L'\0'; *copyTo++ = *source++);
	*copyTo++ = ch;
	*copyTo = L'\0';
	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = 1 + this->m_currentSize;

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator-=(const StringW& str)
{
	PositionGroup removePlace = findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);
	if (howManySplity == 0)
	{
		return *this;
	}
	Size newStringWSize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t[newStringWSize];
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';


	delete[] m_coreString;
	m_coreString = newStringWCoreData;
	m_currentSize = newStringWSize;

	return *this;
}

CCSTDCPP::StringW& CCSTDCPP::StringW::operator-=(const wchar_t ch)
{
	if (ch == L'\0') {
		return *this;
	}
	Size count = 0;
	wchar_t* counterCh = m_coreString;
	for (; *counterCh != L'\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	wchar_t* special = new wchar_t[m_currentSize - count];
	wchar_t* copyTo = special;
	for (; *counterCh != L'\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = L'\0';

	delete[] m_coreString;
	m_coreString = special;
	m_currentSize = m_currentSize - count;

	return *this;
}


CCSTDCPP::StringW& CCSTDCPP::StringW::operator-=(const wchar_t* CString)
{
	PositionGroup removePlace = findAllSub(CString);
	Size counterOfCString = 0;
	wchar_t* counter = const_cast<wchar_t*>(CString);
	for (; *counter != L'\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != L'\0'; howManySplity++);

	if (howManySplity == 0)
	{
		return *this;
	}

	Size newStringWSize = m_currentSize - counterOfCString * howManySplity;
	wchar_t* newStringWCoreData = new wchar_t[newStringWSize];
	wchar_t* copyTo = newStringWCoreData;
	wchar_t* source = m_coreString;
	Index curRemove = 0;
	for (; *source != L'\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = L'\0';
	delete[] m_coreString;
	m_coreString = newStringWCoreData;
	m_currentSize = newStringWSize;

	return *this;
}
#endif