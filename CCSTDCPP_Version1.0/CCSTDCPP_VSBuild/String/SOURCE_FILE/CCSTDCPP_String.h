#pragma once
#include<iostream>

#define CCSTDCPP_ISNUL_TERMINATE 1 // Generally, we considered NUL as our terminate char in string.
#include<string>

namespace CCSTDCPP {

	class StringA; // preAnnounced
	class StringW; // preAnnounced
#ifdef UNICODE
#define String StringW
#define CCSTDCPP_UNICODE_TYPE_PRIORITY
#define CCSTDCPP_COUT std::wcout
#define Position wchar_t*
#define PositionGroup wchar_t**
#define String_Array StringW_Array
#else
#define String StringA
#define CCSTDCPP_ASCII_MULTYBYTES_PRIORITY
#define CCSTDCPP_COUT std::cout
#define Position char*
#define PositionGroup char**

#endif

#if CCSTDCPP_ISNUL_TERMINATE 
	// For default NUL END
#else
#define NUL_CHAR '\0'
#endif

#ifndef _SIZE__INDEX__CCSTDDCPP_
#define _SIZE__INDEX__CCSTDDCPP_ 1

	using Index = unsigned int;
	using Size = unsigned int;

#endif



#define DEF_POSGRP_SIZE 10
#define	DEF_END 0 // using in Building String
	enum class StringOverLoadSelection 
	{
		IgnoreOverload,
		WarningOverload,
		DisableOverload
	};

	const StringOverLoadSelection def_ConfOverLoadSelection = StringOverLoadSelection::WarningOverload;
#ifdef CCSTDCPP_ASCII_MULTYBYTES_PRIORITY
	using StringA_Array = StringA**;

	class StringA {

	private:

		char*		m_coreString; /*string*/
		Size		m_currentSize;/*current size*/
		bool		checkAndRefresh(); /*check if is Illegal*/


	public:
		// initer
		StringA();
		StringA(const char* CString, Index beg = 0, Index end = DEF_END);
		StringA(char ch, Size repeatN = 1);
		StringA(const StringA& aString);
		StringA(const StringA&& aString) noexcept;
		StringA& operator=(const char* CString);
		StringA& operator=(const StringA& aStr);
		// eraser
		~StringA();

		// getter
		[[nodiscard]] Size			size() const;
		[[nodiscard]] const char*	data() const;

		// if a string is null, 
		// it means that we have just call the default constructor and the core string is nullptr. 
		// Meanwhile, if a str is empty,
		// it means that the core string is ONE CHAR size and *m_coreString will be \0 (NUL in ASCII)
		// a null string must be an empty string, but an empty string can not be a null string! 
		[[nodiscard]] bool			isNull() const;
		[[nodiscard]] bool			isEmpty() const;
		char& operator[](Index index) const;
		[[nodiscard]] char&			at(Index index) const;
		// push_back and reset data
		StringA&					setStr(const char* CString, Index beg = 0, Index end = DEF_END, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringA&					setStr(char ch, Size repeatN = 1, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringA&					setStr(const StringA& aString, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringA&					setStr(const StringA&& aString, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);

		StringA&					append(const char* CString, Index beg = 0, Index end = DEF_END);
		StringA&					append(char ch, Size repeatN = 1);
		StringA&					append(const StringA& aString);

		// insert

		void						insert(const char* CString, Index toWhere);
		void						insert(const StringA& str, Index toWhere);
		void						insert(char ch, Index toWhere, Size repeatN);

		// reverse
		StringA						reverseStr();
		void						reverse();

		// find substr	
		Position					findSub(const char* CString, Index beg = 0, Index end = DEF_END);
		Position					findSub(char ch, Index beg = 0, Index end = DEF_END);
		Position					findSub(const StringA& str, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(const char* CString, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(char ch, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(const StringA& str, Index beg = 0, Index end = DEF_END);
		// spilt
		StringA_Array				split(const char* CString);
		StringA_Array				split(char ch);
		StringA_Array				split(const StringA& str);
		// kick all substr, The parameters of Index Type simply indicates the range of the ORIGINAL STRINGA
		StringA						remove(const char* CString, Index beg = 0, Index end = DEF_END);
		StringA						remove(const StringA& str, Index beg = 0, Index end = DEF_END);
		StringA						remove(char ch, Index beg = 0, Index end = DEF_END);

		// clear
		void						clear();

		// isEqual
		bool						isEqual(const char* CString, Index beg = 0, Index end = DEF_END);
		bool						isEqual(const StringA& str, Index beg = 0, Index end = DEF_END);
		bool						operator==(const char* CString);
		bool						operator==(const StringA& str);
		bool						operator!=(const char* CString);
		bool						operator!=(const StringA& str);


		// other operator 

		// +
		StringA						operator+(const char* CString);
		StringA						operator+(char ch) const;
		StringA						operator+(const StringA& aStr);

		// - SAME AS REMOVE
		StringA						operator-(const char* CString);
		StringA						operator-(char ch);
		StringA						operator-(const StringA& aStr);

		// +=
		StringA&					operator+=(const char* CString);
		StringA&					operator+=(char ch);
		StringA&					operator+=(const StringA& aStr);

		// -=
		StringA&					operator-=(const char* CString);
		StringA&					operator-=(char ch);
		StringA&					operator-=(const StringA& aStr);
	};

	// namespace global function

	std::ostream& operator<<(std::ostream& os, CCSTDCPP::StringA& aStr);

#else

	using StringW_Array = StringW**;


	class StringW{
	private:
		wchar_t*					m_coreString;
		Size						m_currentSize;/*current size*/
		bool						checkAndRefresh();
	public:
		// initer
		StringW();
		StringW(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		StringW(wchar_t ch, Size repeatN = 1);
		StringW(const StringW& aString);
		StringW(const StringW&& aString) noexcept;
		StringW& operator=(const wchar_t* CString);
		StringW& operator=(const StringW& aStr);
		// eraser
		~StringW();

		// getter
		[[nodiscard]] Size				size() const;
		[[nodiscard]] const wchar_t*	data() const;

		// if a string is null, 
		// it means that we have just call the default constructor and the core string is nullptr. 
		// Meanwhile, if a str is empty,
		// it means that the core string is ONE CHAR size and *m_coreString will be \0 (NUL in ASCII)
		// a null string must be an empty string, but an empty string can not be a null string! 
		[[nodiscard]] bool				isNull() const;
		[[nodiscard]] bool				isEmpty() const;
		wchar_t&						operator[](Index index) const;
		[[nodiscard]] wchar_t&			at(Index index) const;
		// push_back and reset data
		StringW& setStr(const wchar_t* CString, Index beg = 0, Index end = DEF_END, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringW& setStr(wchar_t ch, Size repeatN = 1, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringW& setStr(const StringW& aString, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);
		StringW& setStr(const StringW&& aString, StringOverLoadSelection thisSelection = def_ConfOverLoadSelection);

		StringW& append(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		StringW& append(wchar_t ch, Size repeatN = 1);
		StringW& append(const StringW& aString);

		// insert

		void						insert(const wchar_t* CString, Index toWhere);
		void						insert(const StringW& str, Index toWhere);
		void						insert(wchar_t ch, Index toWhere, Size repeatN);

		// reverse
		StringW						reverseStr();
		void						reverse();

		// find substr	
		Position					findSub(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		Position					findSub(wchar_t ch, Index beg = 0, Index end = DEF_END);
		Position					findSub(const StringW& str, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(wchar_t ch, Index beg = 0, Index end = DEF_END);
		PositionGroup				findAllSub(const StringW& str, Index beg = 0, Index end = DEF_END);
		// spilt
		StringW_Array				split(const wchar_t* CString);
		StringW_Array				split(wchar_t ch);
		StringW_Array				split(const StringW& str);
		// kick all substr, The parameters of Index Type simply indicates the range of the ORIGINAL STRINGA
		StringW						remove(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		StringW						remove(const StringW& str, Index beg = 0, Index end = DEF_END);
		StringW						remove(wchar_t ch, Index beg = 0, Index end = DEF_END);
		// clear

		void						clear();

		// isEqual
		bool						isEqual(const wchar_t* CString, Index beg = 0, Index end = DEF_END);
		bool						isEqual(const StringW& str, Index beg = 0, Index end = DEF_END);
		bool						operator==(const wchar_t* CString);
		bool						operator==(const StringW& str);
		bool						operator!=(const wchar_t* CString);
		bool						operator!=(const StringW& str);

		// other operator 

		// +
		StringW						operator+(const wchar_t* CString);
		StringW						operator+(wchar_t ch) const;
		StringW						operator+(const StringW& aStr);

		// - SAME AS REMOVE
		StringW						operator-(const wchar_t* CString);
		StringW						operator-(wchar_t ch);
		StringW						operator-(const StringW& aStr);

		// +=
		StringW&					operator+=(const wchar_t* CString);
		StringW&					operator+=(wchar_t ch);
		StringW&					operator+=(const StringW& aStr);

		// -=
		StringW&					operator-=(const wchar_t* CString);
		StringW&					operator-=(wchar_t ch);
		StringW&					operator-=(const StringW& aStr);
	};

	std::wostream& operator<<(std::wostream& os, CCSTDCPP::StringW& aStr);

#endif
#ifndef _Error_CCSTDCPP_
#define _Error_CCSTDCPP_ 1

	enum class StringErrorCode {
		STRING_OVERFLOW,
		STRING_UNDERFLOW,
		STRING_WRONGCONF,
		STRING_NULLPTR,
		STRING_BADSTR,
		STRING_BAD_OVERLOAD
	};

	class String_Exceptions : public std::exception {
	protected:
		const char* m_forWhat;
		CCSTDCPP::StringErrorCode m_errorIndex;
	public:
		String_Exceptions(const char* forWhat, CCSTDCPP::StringErrorCode index) : m_forWhat{ forWhat }, m_errorIndex{ index } {};
		~String_Exceptions()override = default;
		virtual void what() { std::cerr << m_forWhat; };
	};

	class String_Exp_OverFlow : public String_Exceptions {
	public:
		explicit String_Exp_OverFlow(const char* msg = "Sadly OverFlow!",
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_OVERFLOW) : String_Exceptions{ msg, index } {}
	};

	class String_Exp_UnderFlow : public String_Exceptions {
	public:
		explicit String_Exp_UnderFlow(const char* msg = "Sadly UnderFlow!",
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_UNDERFLOW) :String_Exceptions{ msg, index } {}
	};

	class String_Exp_WrongConf : public String_Exceptions {
	public:
		explicit String_Exp_WrongConf(const char* msg = "Sadly, This function can not RECOGNIZE what you pass to him :( ",
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_WRONGCONF) :String_Exceptions{ msg, index } {}
	};

	class String_Exp_Nullptr : public String_Exceptions {
	public:
		explicit String_Exp_Nullptr(const char* msg = "What we have got is a nullptr",
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_NULLPTR) :String_Exceptions{ msg,index } {}
	};

	class String_Exp_BadStr : public String_Exp_WrongConf {
	public:
		explicit String_Exp_BadStr(
			const char* msg = "Sadly, the string's counter dismatches it's real visitable size!",
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_BADSTR
		) : String_Exp_WrongConf{ msg, index } {}
	};

	class String_Exp_InvalidOverload : public String_Exp_WrongConf {
	public:
		explicit String_Exp_InvalidOverload(
			const char* msg = "Sadly, here has been disabled reset the data in String!"
			"Disable def_conf may solve this problem", // USING ANSI C's specialized characteristic actually
			CCSTDCPP::StringErrorCode index = CCSTDCPP::StringErrorCode::STRING_BAD_OVERLOAD
		) :String_Exp_WrongConf{ msg, index } {}
	};
#endif
}

