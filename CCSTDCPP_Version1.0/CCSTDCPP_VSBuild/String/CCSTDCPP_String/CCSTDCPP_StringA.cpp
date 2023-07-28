#include"CCSTDCPP_String.h"
#ifdef CCSTDCPP_ASCII_MULTYBYTES_PRIORITY
// namespace global
std::ostream& CCSTDCPP::operator<<(std::ostream& os, CCSTDCPP::StringA& aStr)
{
	os << aStr.data();
	return os;
}



bool CCSTDCPP::StringA::isEmpty() const
{
	if (m_coreString == nullptr)
		return true;
	if (*m_coreString == '\0')
		return true;

	return false;
}

bool CCSTDCPP::StringA::isNull() const
{
	if (m_coreString == nullptr)
		return true;

	return false;
}

char& CCSTDCPP::StringA::operator[](Index index) const
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

char& CCSTDCPP::StringA::at(Index index) const
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

bool CCSTDCPP::StringA::checkAndRefresh()
{
	try
	{
		Size check = 0;
		for (
			char* counter = m_coreString;
			*counter != '\0';
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



CCSTDCPP::StringA::StringA()
{
	m_coreString = nullptr;
	m_currentSize = 0;
}


CCSTDCPP::StringA::StringA(const char* CString, Index beg, Index end)
{
	Size count = 1;

	for (
		char* counter = const_cast<char*>(CString);
		*counter != '\0';
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
	m_coreString = new char[end - beg + 2];
	char* copyBeg, * copyTo;
	for (
		copyBeg = const_cast<char*>(CString) + beg,
		copyTo = m_coreString;
		copyBeg != const_cast<char*>(CString) + end;
		*copyTo++ = *copyBeg++
		);

	m_currentSize = end - beg;
	*copyTo = '\0';
}

CCSTDCPP::StringA::StringA(const char ch, Size repeatN)
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

	m_coreString = new char[repeatN + 1];

	for (Size i = 0; i < repeatN + 1; m_coreString[i] = ch, i++);

	m_currentSize = repeatN + 1;
	m_coreString[m_currentSize - 1] = '\0';
}

CCSTDCPP::StringA::StringA(const StringA& aStr)
{
	m_coreString = new char[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = '\0';
}

CCSTDCPP::StringA::StringA(const StringA&& aStr) noexcept
{
	m_coreString = new char[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = '\0';
}

CCSTDCPP::Size CCSTDCPP::StringA::size() const
{
	return m_currentSize;
}

const char* CCSTDCPP::StringA::data() const
{
	char* copy = new char[m_currentSize];
	for (
		Size i = 0;
		i < this->m_currentSize;
		copy[i] = this->m_coreString[i], i++
		);

	return copy;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator=(const StringA& aStr)
{
	if (aStr.m_coreString == this->m_coreString) {
		return *this;
	}

	delete[] m_coreString;
	m_coreString = new char[aStr.m_currentSize];
	char* dst = m_coreString;

	for (const char* source = aStr.m_coreString; *source != '\0'; *dst++ = *source++);

	m_currentSize = aStr.m_currentSize;
	m_coreString[m_currentSize - 1] = '\0';
	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator=(const char* CString)
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
	for (const char* counter = CString; *counter != '\0'; count++,counter++);

	delete[] m_coreString;
	m_coreString = new char[count];

	char* dst = m_coreString;

	for (const char* source = CString; *source != '\0'; *dst++ = *source++);

	m_currentSize = count;
	m_coreString[m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA::~StringA() {
	delete[] m_coreString;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::setStr(const char* CString, Index beg, Index end, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != '\0') /* Empty and Nullptr*/
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
		char* counter = const_cast<char*>(CString);
		*counter != '\0';
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
	m_coreString = new char[end - beg + 2];
	char* copyBeg, * copyTo;
	for (
		copyBeg = const_cast<char*>(CString) + beg,
		copyTo = m_coreString;
		copyBeg != const_cast<char*>(CString) + end;
		*copyTo++ = *copyBeg++
		);

	m_currentSize = end - beg;
	*copyTo = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::setStr(const char ch, Size repeatN, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != '\0') /* Empty and Nullptr*/
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

	m_coreString = new char[repeatN + 1];

	for (Size i = 0; i < repeatN + 1; m_coreString[i] = ch, i++);

	m_currentSize = repeatN + 1;
	m_coreString[m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::setStr(const CCSTDCPP::StringA& aStr, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != '\0') /* Empty and Nullptr*/
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

	m_coreString = new char[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::setStr(const CCSTDCPP::StringA&& aStr, CCSTDCPP::StringOverLoadSelection selection)
{
	try
	{
		if (this->m_coreString != nullptr || *this->m_coreString != '\0') /* Empty and Nullptr*/
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

	m_coreString = new char[aStr.m_currentSize];
	for (
		Size i = 0;
		i < aStr.m_currentSize;
		this->m_coreString[i] = aStr.m_coreString[i], i++
		);

	this->m_currentSize = aStr.m_currentSize;
	this->m_coreString[this->m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::append(const char* CString, Index beg, Index end)
{
	if (CString == nullptr) {
		return *this;
	}

	Size count = 1;

	for (
		char* counter = const_cast<char*>(CString);
		*counter != '\0';
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

	char* newSpace = new char[this->m_currentSize + count - 1];

	char* dest = newSpace;

	for (char* source = m_coreString; *source != '\0'; *dest++ = *source++);

	const char* otherString = CString + beg;

	for (; otherString != CString + end; *dest++ = *otherString++);

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = this->m_currentSize + count - 1;
	m_coreString[m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::append(const char ch, Size repeatN)
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

	char* newSpace = new char[repeatN + this->m_currentSize];

	char* dst = newSpace;
	for (char* source = m_coreString; *source != '\0'; *dst++ = *source++);

	for (Size i = 0; i < repeatN + 1; *dst++ = ch, i++);



	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = repeatN + this->m_currentSize;
	m_coreString[m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::append(const CCSTDCPP::StringA& aStr)
{

	char* newSpace = new char[this->m_currentSize + aStr.m_currentSize - 1];

	char* dst = newSpace;

	for (const char* source = this->m_coreString; *source != '\0'; *dst++ = *source++);

	if (aStr.m_coreString == this->m_coreString)
		for (const char* source = this->m_coreString; *source != '\0'; *dst++ = *source++);
	else
		for (const char* source = aStr.m_coreString; *source != '\0'; *dst++ = *source++);

	delete[] m_coreString;

	m_coreString = newSpace;
	m_currentSize = this->m_currentSize + aStr.m_currentSize - 1;
	m_coreString[m_currentSize - 1] = '\0';

	return *this;
}

CCSTDCPP::StringA CCSTDCPP::StringA::reverseStr()
{
	char* data = (char*)alloca(m_currentSize);
	char* dst = data;
	for (const char* source = m_coreString + m_currentSize - 2; source != m_coreString; *dst++ = *source--);
	*dst = '\0';
	return { data };
}

void CCSTDCPP::StringA::reverse()
{
	char* front = m_coreString;
	char* end = m_coreString + m_currentSize - 2;
	for (; front <= end; front++, end--) {
		char tmp = *front;
		*front = *end;
		*end = tmp;
	}
}

bool CCSTDCPP::StringA::isEqual(const char* CString, Index beg, Index end)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;

	for (
		char* counter = const_cast<char*>(CString);
		*counter != '\0';
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

bool CCSTDCPP::StringA::isEqual(const CCSTDCPP::StringA& str, Index beg, Index end)
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

bool CCSTDCPP::StringA::operator==(const char* CString)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;
	const char* counter = CString;
	for (; *counter != '\0'; counter++, count++);

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

bool CCSTDCPP::StringA::operator==(const CCSTDCPP::StringA& str)
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

bool CCSTDCPP::StringA::operator!=(const char* CString)
{
	if (CString == nullptr)
	{
		return CString == m_coreString;
	}

	Size count = 1;
	const char* counter = CString;
	for (; *counter != '\0'; counter++, count++);

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

bool CCSTDCPP::StringA::operator!=(const CCSTDCPP::StringA& str)
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


CCSTDCPP::StringA CCSTDCPP::StringA::operator+(const char* CString)
{
	if (CString == nullptr) {
		return *this;
	}

	Size count = 1;

	for (
		char* counter = const_cast<char*>(CString);
		*counter != '\0';
		counter++, count++
		);
	char* newSpace = (char*)alloca(this->m_currentSize + count - 1);

	char* dest = newSpace;

	for (char* source = m_coreString; *source != '\0'; *dest++ = *source++);

	const char* otherString = CString;

	for (; *otherString != '\0'; *dest++ = *otherString++);


	return { newSpace }; // initialized lists
}

CCSTDCPP::StringA CCSTDCPP::StringA::operator+(const CCSTDCPP::StringA& str)
{
	char* newSpace = (char*)alloca(str.m_currentSize + this->m_currentSize - 1);

	char* dst = newSpace;

	for (const char* source = this->m_coreString; *source != '\0'; *dst++ = *source++);

	for (const char* source = str.m_coreString; *source != '\0'; *dst++ = *source++);

	*dst = '\0';

	return { newSpace };
}

CCSTDCPP::StringA CCSTDCPP::StringA::operator+(const char ch) const
{
	char* newSpace = (char*)alloca(m_currentSize + 1);

	newSpace[m_currentSize - 1] = ch;

	newSpace[m_currentSize] = '\0';

	return { newSpace };
}

Position CCSTDCPP::StringA::findSub(const char* CString, Index beg, Index end)
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

	if (*CString == '\0')
	{
		return &m_coreString[m_currentSize - 1];
	}
	// 一阶K氏字符串匹配算法(算法导论摸鱼时候看的，大概如此)
	char* source = const_cast<char*>(CString);
	Position cur = m_coreString + beg;
	Position next = cur;
	while (cur <= m_coreString + end - 1 && *cur != '\0')
	{

		// Position: find first match
		for (; *cur != *source && cur <= m_coreString + end - 1; cur++);

		// find next match
		for (next = cur + 1; *next != *source && *next != '\0'; next++); // 到达\0就停止，这下标志着为空了

		// if find first match, then start check WHOLY
		bool isThisPossible = false;
		Position checker = cur;
		for (; !isThisPossible;) {
			if (*checker++ != *source++) {
				source = const_cast<char*>(CString + beg);
				cur = next;
				break;
			}
			// yes, we fetch the End --- check the source wholy
			// in this case, we return 
			if (*source == '\0') {
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

Position CCSTDCPP::StringA::findSub(const StringA& str, Index beg, Index end)
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
	char* source = str.m_coreString;
	Position cur = m_coreString + beg;
	Position next = cur;
	while (cur <= m_coreString + end - 1 && *cur != '\0')
	{

		// Position: find first match
		for (; *cur != *source && cur <= m_coreString + end - 1; cur++);

		// find next match
		for (next = cur + 1; *next != *source && *next != '\0'; next++); // 到达\0就停止，这下标志着为空了

		// if find first match, then start check WHOLY
		bool isThisPossible = false;
		Position checker = cur;
		for (; !isThisPossible;) {
			if (*checker++ != *source++) {
				source = const_cast<char*>(str.m_coreString + beg);
				cur = next;
				break;
			}
			// yes, we fetch the End --- check the source wholy
			// in this case, we return 
			if (*source == '\0') {
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


Position CCSTDCPP::StringA::findSub(const char ch, Index beg, Index end)
{
	if (ch == '\0')
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

	for (char* finder = m_coreString + beg; finder < m_coreString + end && *finder != '\0'; finder++)
	{
		if (*finder == ch) {
			return finder;
		}
	}

	return m_coreString + m_currentSize - 1;
}

PositionGroup CCSTDCPP::StringA::findAllSub(const char ch, Index beg, Index end)
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
	for (; *fetcher != '\0'; fetcher++)
	{
		fetcher = findSub(ch, curFind, end);
		if (fetcher >= m_coreString + end) {
			break;
		}
		if (*fetcher != '\0')
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

	ptr2Arr[countHowMany] = m_coreString + m_currentSize - 1;

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

PositionGroup CCSTDCPP::StringA::findAllSub(const char* CString, Index beg, Index end)
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
	for (; *fetcher != '\0'; fetcher++)
	{
		fetcher = findSub(CString, curFind, end);
		if (fetcher >= m_coreString + end) {
			break;
		}
		else
		{
			if (*fetcher != '\0')
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

	ptr2Arr[countHowMany] = m_coreString + m_currentSize - 1;

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

PositionGroup CCSTDCPP::StringA::findAllSub(const StringA& str, Index beg, Index end)
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
	for (; *fetcher != '\0'; fetcher++)
	{
		fetcher = findSub(str, curFind, end);
		if (fetcher >= m_coreString + end) {
			break;
		}
		else
		{
			if (*fetcher != '\0')
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

	ptr2Arr[countHowMany] = m_coreString + m_currentSize - 1;

	return countHowMany == 0 ?
		delete[] ptr2Arr, nullptr : ptr2Arr;
}

CCSTDCPP::StringA_Array CCSTDCPP::StringA::split(const char* CString)
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
	for (howManySplity = 0; *finderAll[howManySplity] != '\0'; )
		howManySplity++;

	auto splitArr = new StringA * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;
	char* curSplitPiece;
	char* copyTo;
	char* source;
	if (curSplitPieceSize == 0)
	{
		splitArr[0] = new StringA(CString);
	}
	else
	{
		curSplitPiece = new char[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = m_coreString;
		for (Size i = 0; i < curSplitPieceSize; i++) {
			*copyTo++ = *source++;
		}
		*copyTo = '\0';
		splitArr[0] = new StringA(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for mid
	for (Size i = 0; i < howManySplity; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new char[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = '\0';
		splitArr[i + 1] = new StringA(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new char[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = '\0';
	splitArr[howManySplity] = new StringA(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringA;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}

CCSTDCPP::StringA_Array CCSTDCPP::StringA::split(const StringA& str)
{
	PositionGroup finderAll = this->findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *finderAll[howManySplity] != '\0'; )
		howManySplity++;

	auto splitArr = new StringA * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;
	char* curSplitPiece;
	char* copyTo;
	char* source;
	if (curSplitPieceSize == 0)
	{
		splitArr[0] = new StringA(str);
	}
	else
	{
		curSplitPiece = new char[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = m_coreString;
		for (Size i = 0; i < curSplitPieceSize; i++) {
			*copyTo++ = *source++;
		}
		*copyTo = '\0';
		splitArr[0] = new StringA(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for mid
	for (Size i = 0; i < howManySplity; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new char[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = '\0';
		splitArr[i + 1] = new StringA(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new char[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = '\0';
	splitArr[howManySplity] = new StringA(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringA;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}


CCSTDCPP::StringA_Array CCSTDCPP::StringA::split(const char ch)
{
	PositionGroup finderAll = this->findAllSub(ch);

	Size howManySplity = 0;
	for (howManySplity = 0; *finderAll[howManySplity] != '\0'; )
		howManySplity++;

	auto splitArr = new StringA * [howManySplity + 2]; // 2 specify for
	// A | B | C

	// for A
	Size curSplitPieceSize = finderAll[0] - m_coreString;

	char* curSplitPiece = new char[curSplitPieceSize + 1];
	char* copyTo = curSplitPiece;
	char* source = m_coreString;
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = '\0';
	splitArr[0] = new StringA(curSplitPiece);
	delete[] curSplitPiece;

	// for mid
	for (Size i = 0; i < howManySplity; i++)
	{
		curSplitPieceSize = finderAll[i + 1] - finderAll[i];
		curSplitPiece = new char[curSplitPieceSize + 1];
		copyTo = curSplitPiece;
		source = finderAll[i];
		for (Size j = 0; j < curSplitPieceSize; j++) {
			*copyTo++ = *source++;
		}
		*copyTo = '\0';
		splitArr[i + 1] = new StringA(curSplitPiece);
		delete[] curSplitPiece;
	}

	// for fin

	curSplitPieceSize = m_currentSize + m_coreString - finderAll[howManySplity - 1];
	curSplitPiece = new char[curSplitPieceSize + 1];
	copyTo = curSplitPiece;
	source = finderAll[howManySplity - 1];
	for (Size i = 0; i < curSplitPieceSize; i++) {
		*copyTo++ = *source++;
	}
	*copyTo = '\0';
	splitArr[howManySplity] = new StringA(curSplitPiece);
	delete[] curSplitPiece;

	splitArr[howManySplity + 1] = new StringA;

	return howManySplity == 0 ?
		delete[] splitArr, nullptr : splitArr;
}

void CCSTDCPP::StringA::insert(const char* CString, Index toWhere)
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
	char* counter = const_cast<char*>(CString);
	for (; *counter != '\0'; count++, counter++);

	char* newSpace = new char[count + m_currentSize - 1];
	char* copyTo = newSpace;
	char* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	source = const_cast<char*>(CString);
	for (; *source != '\0'; *copyTo++ = *source++);
	source = const_cast<char*>(m_coreString + toWhere);
	for (; *source != '\0'; *copyTo++ = *source++);

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = count + m_currentSize - 1;
}

void CCSTDCPP::StringA::insert(const StringA& aStr, Index toWhere)
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

	char* newSpace = new char[aStr.m_currentSize + m_currentSize - 1];
	char* copyTo = newSpace;
	char* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	source = aStr.m_coreString;
	for (; *source != '\0'; *copyTo++ = *source++);
	source = const_cast<char*>(m_coreString + toWhere);
	for (; *source != '\0'; *copyTo++ = *source++);

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = aStr.m_currentSize + m_currentSize - 1;
}

void CCSTDCPP::StringA::insert(const char ch, Index toWhere, Size repeatN)
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

	char* newSpace = new char[repeatN + m_currentSize];
	char* copyTo = newSpace;
	char* source = m_coreString;
	for (; source != m_coreString + toWhere; *copyTo++ = *source++);
	for (Size i = 0; i < repeatN; *copyTo++ = ch, i++);
	source = const_cast<char*>(m_coreString + toWhere);
	for (; *source != '\0'; *copyTo++ = *source++);

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = repeatN + m_currentSize;
}

CCSTDCPP::StringA CCSTDCPP::StringA::remove(const char* CString, Index beg, Index end)
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
	char* counter = const_cast<char*>(CString);
	for (; *counter != '\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);

	Size newStringASize = m_currentSize - counterOfCString * howManySplity;
	char* newStringACoreData = (char*)alloca(newStringASize);
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString + end && *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';
	return { newStringACoreData };
}

CCSTDCPP::StringA CCSTDCPP::StringA::remove(const StringA& str, Index beg, Index end)
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
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);

	Size newStringASize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	char* newStringACoreData = (char*)alloca(newStringASize);
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString + end && *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';
	return { newStringACoreData };
}

CCSTDCPP::StringA CCSTDCPP::StringA::remove(const char ch, Index beg, Index end)
{
	if (end == DEF_END)
	{
		end = m_currentSize;
	}

	if (ch == '\0') {
		return { *this };
	}
	Size count = 0;
	char* counterCh = m_coreString + beg;
	for (; *counterCh != '\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	char* special = (char*)alloca(m_currentSize - count);
	char* copyTo = special;
	for (; counterCh <= m_coreString + end && *counterCh != '\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = '\0';

	return { special };
}

void CCSTDCPP::StringA::clear()
{
	delete[] m_coreString;
	m_coreString = new char[1];
	*m_coreString = '\0';

	m_currentSize = 0;
}


CCSTDCPP::StringA CCSTDCPP::StringA::operator-(const char* CString)
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
	char* counter = const_cast<char*>(CString);
	for (; *counter != '\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);

	Size newStringASize = m_currentSize - counterOfCString * howManySplity;
	char* newStringACoreData = (char*)alloca(newStringASize);
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString && *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';
	return { newStringACoreData };
}

CCSTDCPP::StringA CCSTDCPP::StringA::operator-(const StringA& str)
{
	PositionGroup removePlace = findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);

	Size newStringASize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	char* newStringACoreData = (char*)alloca(newStringASize);
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; source <= m_coreString && *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';
	return { newStringACoreData };
}

CCSTDCPP::StringA CCSTDCPP::StringA::operator-(const char ch)
{
	if (ch == '\0') {
		return { *this };
	}
	Size count = 0;
	char* counterCh = m_coreString;
	for (; *counterCh != '\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	char* special = (char*)alloca(m_currentSize - count);
	char* copyTo = special;
	for (; *counterCh != '\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = '\0';

	return { special };
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator+=(const StringA& str)
{
	char* newSpace = new char[str.m_currentSize + this->m_currentSize - 1];
	char* copyTo = newSpace;
	char* source = m_coreString;
	for (; *source != '\0'; *copyTo++ = *source++);
	source = str.m_coreString;
	for (; *source != '\0'; *copyTo++ = *source++);
	*copyTo = '\0';

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = str.m_currentSize + this->m_currentSize - 1;

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator+=(const char* CString)
{
	Size counterOfCString = 0;
	char* counter = const_cast<char*>(CString);
	for (; *counter != '\0'; counter++, counterOfCString++);


	char* newSpace = new char[counterOfCString + this->m_currentSize];
	char* copyTo = newSpace;
	const char* source = m_coreString;
	for (; *source != '\0'; *copyTo++ = *source++);
	source = CString;
	for (; *source != '\0'; *copyTo++ = *source++);
	*copyTo = '\0';

	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = counterOfCString + this->m_currentSize;

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator+=(const char ch)
{
	char* newSpace = new char[1 + this->m_currentSize];
	char* source = m_coreString;
	char* copyTo = newSpace;
	for (; *source != '\0'; *copyTo++ = *source++);
	*copyTo++ = ch;
	*copyTo = '\0';
	delete[] m_coreString;
	m_coreString = newSpace;
	m_currentSize = 1 + this->m_currentSize;

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator-=(const StringA& str)
{
	PositionGroup removePlace = findAllSub(str);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);
	if (howManySplity == 1)
	{
		return *this;
	}
	Size newStringASize = m_currentSize - (str.m_currentSize - 1) * howManySplity;
	char* newStringACoreData = new char[newStringASize];
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += str.m_currentSize - 1;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';


	delete[] m_coreString;
	m_coreString = newStringACoreData;
	m_currentSize = newStringASize;

	return *this;
}

CCSTDCPP::StringA& CCSTDCPP::StringA::operator-=(const char ch)
{
	if (ch == '\0') {
		return *this;
	}
	Size count = 0;
	char* counterCh = m_coreString;
	for (; *counterCh != '\0'; counterCh++)
	{
		if (*counterCh == ch) {
			count++;
		}
	}

	// reset place
	counterCh = m_coreString;
	char* special = new char[m_currentSize - count];
	char* copyTo = special;
	for (; *counterCh != '\0';) {
		if (*counterCh == ch) {
			counterCh++;
			continue;
		}
		*copyTo++ = *counterCh++;
	}

	*copyTo = '\0';

	delete[] m_coreString;
	m_coreString = special;
	m_currentSize = m_currentSize - count;

	return *this;
}


CCSTDCPP::StringA& CCSTDCPP::StringA::operator-=(const char* CString)
{
	PositionGroup removePlace = findAllSub(CString);
	Size counterOfCString = 0;
	char* counter = const_cast<char*>(CString);
	for (; *counter != '\0'; counter++, counterOfCString++);

	Size howManySplity = 0;
	for (howManySplity = 0; *removePlace[howManySplity] != '\0'; howManySplity++);

	if (howManySplity == 1)
	{
		return *this;
	}

	Size newStringASize = m_currentSize - counterOfCString * howManySplity;
	char* newStringACoreData = new char[newStringASize];
	char* copyTo = newStringACoreData;
	char* source = m_coreString;
	Index curRemove = 0;
	for (; *source != '\0';)
	{
		if (source == removePlace[curRemove])
		{
			curRemove++;
			source += counterOfCString;
			continue;
		}
		*copyTo++ = *source++;
	}

	*copyTo = '\0';
	delete[] m_coreString;
	m_coreString = newStringACoreData;
	m_currentSize = newStringASize;

	return *this;
}
#endif