#include"CCSTDCPP_Vector.hpp"
#include"FunctionalizeClass.hpp"
#include<iostream>
#define SLASH putchar('\n')

using namespace CCSTDCPP;
using testType = int;

void printInt(int& data) {
	std::cout << data << " ";
}

template<class data>
void printMtVec(Vector<data>& vec)
{
	SLASH;
	VectorIterator<data> it;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << " ";
	}
}



int main()
{
	Vector<testType> def;
	std::cout << def.size();
	std::cout << def.begin() << '\t' << def.end() << std::endl;
	/* 经典点元素推送构造 */
	Vector<testType> a(1);
	std::cout << a.size();
	std::cout << a.begin() << '\t' << a.end() << std::endl;

	/* Copy assignment */
	Vector<testType> b(a);
	std::cout << b.size();
	std::cout << b.begin() << '\t' << b.end() << std::endl;

	/* Move assignment */
	Vector<testType> c(std::move(Vector<testType>(4)));
	std::cout << c.size();
	std::cout << c.begin() << '\t' << c.end() << std::endl;

	/* push back */
	a.push_back(10);
	std::cout << "push_back the" << 10 << '\n';
	std::cout << a.size() << '\t';
	std::cout << a.begin() << '\t' << a.end() << std::endl;
	/*调试打印仿函数*/
	FuncPrintPtr<testType> printIntPtr = printInt;
	Print<testType> aIntprinter(printIntPtr);
	int aInt = 10;
	aIntprinter(aInt);

	VectorIterator<testType> aIt;
	std::cout << "当前的元素有：";
	for (aIt = a.begin(); aIt != a.end(); aIt++)
	{
		aIntprinter(*aIt);
	}
	/* 测试推送动态数组尾插 */
	a.push_back(b);
	std::cout << a.size() << '\t';
	std::cout << a.begin() << '\t' << a.end() << std::endl;
	std::cout << "当前的元素有：";
	for (aIt = a.begin(); aIt != a.end(); aIt++)
	{
		aIntprinter(*aIt);
	}

	for (int i = 0; i < 1; i++)
	{
		a.push_back(a);
	}
	std::cout << a.size() << '\t' << a.capicity() << "\t";
	std::cout << a.begin() << '\t' << a.end() << std::endl;
	std::cout << "当前的元素有：";
	for (aIt = a.begin(); aIt != a.end(); aIt++)
	{
		aIntprinter(*aIt);
	}

	a.push_back(a.begin(), a.end()); // 自拷贝
	std::cout << a.size() << '\t' << a.capicity() << "\t";
	std::cout << a.begin() << '\t' << a.end() << std::endl;
	std::cout << "当前的元素有：";
	for (aIt = a.begin(); aIt != a.end(); aIt++)
	{
		aIntprinter(*aIt);
	}

	/* pop and pop_back */
	a.pop();
	a.pop();
	a.pop();
	std::cout << a.size() << '\t' << a.capicity() << "\t";
	std::cout << a.begin() << '\t' << a.end() << std::endl;
	std::cout << "当前的元素有：";
	for (aIt = a.begin(); aIt != a.end(); aIt++)
	{
		aIntprinter(*aIt);
	}

	std::cout << "fetch the popped one: " << a.pop_back() << std::endl;

	/* test the overflow */
	// int aOverflow = a[10];
	/* test at and [] */
	std::cout << a[1] << " while at: " << a.at(1) << std::endl;

	/* 调试++ -- 功能*/

	/* 调试后置++ -- */
	aIt = a.begin();
	std::cout << "It is supposed to be the begin elem as to do *(aIt++):  " << *(aIt++) << '\t';
	std::cout << "And that's it :" << *aIt << std::endl;
	std::cout << "Within expectation, what it supposed to be when we do *(aIt--):  " << *(aIt--) << "\t";
	std::cout << "And that's it :" << *aIt << std::endl;
	/* 调试前置++ -- */
	aIt = a.begin();
	std::cout << "Well, and then it must be the *(++aIt): " << *(++aIt) << "\t";
	std::cout << "And that's it :" << *aIt << std::endl;
	std::cout << "Within expectation, what it supposed to be when we do *(--aIt):  " << *(--aIt) << "\t";
	std::cout << "And that's it :" << *aIt << std::endl;

	/* test the clear */
	a.clear();
	std::cout << "It is cleared :> " << a.size() << '\t' << a.capicity() << "\t";
	std::cout << a.begin() << '\t' << a.end() << std::endl;

	/* test the insert group*/
	int intArray[10] = { 1,2,3,4,5,6,7,8,9,10 };
	a.push_back(intArray, &intArray[9]);
	printMtVec(a);
	a.insert(1, intArray[1]);
	printMtVec(a);
	a.insert(1, 8, &intArray[0]);
	printMtVec(a);
	/* test pointer range */
	a.clear();

	/* you can test here the SAFE_MODE ,by only switch on this mode, program will be terminated here*/
	a.insert(1, &intArray[0], &intArray[9]);
	printMtVec(a);

	VectorIterator<testType> test;
	test = a.begin();
	a.insert(test,intArray[0]);
	printMtVec(a);

	/* test erase */
	a.erase(1);
	printMtVec(a);

	/* test range erase */

	a.erase(2, 7);
	printMtVec(a);
	a.clear();

	a.push_back(intArray, &intArray[9]);
	printMtVec(a);
	a.erase(a.begin(), a.end());
	printMtVec(a);
	a.clear();

	a.push_back(intArray, &intArray[9]);
	a.erase(VectorIterator<testType>(a.begin() + 9));

	printMtVec(a);

	// same as the erase back
	b.clear();
	b.push_back(intArray, &intArray[9]);
	SLASH;
	SLASH;
	SLASH;
	SLASH;
	SLASH;
	printMtVec(b);
	std::cout << *b.erase_back(0) << std::endl; // 开摆了，这个b.erase_back就泄露罢，相信操作系统！
	printMtVec(b);
	testType* arrayFromErase = b.erase_back(2, 7);
	const testType* read = arrayFromErase;
	SLASH;
	for (int i = 0; i < 7 - 2 + 1; i++)
	{
		std::cout << *(read++) << " ";
	}
	delete[] arrayFromErase;
	SLASH;
	SLASH;
	b.clear();
	b.push_back(intArray, &intArray[9]);
	printMtVec(b);
	arrayFromErase = b.erase_back(b.begin() + 1, b.end() - 1);
	read = arrayFromErase;
	SLASH;
	for (int i = 0; i < 8; i++)
	{
		std::cout << *(read++) << " " ;
	}
	delete[] arrayFromErase;
	VectorIterator<testType> eraseOne;
	eraseOne = b.begin();
	SLASH;
	std::cout << *b.erase_back(eraseOne) << std::endl;

	Vector<testType> vec1, vec2;
	vec1.push_back(intArray, &intArray[9]);
	vec2.push_back(intArray, &intArray[9]);
	SLASH;
	if (vec1 == vec2)
	{
		std::cout << "Obviously...";
	}
	else {
		std::cout << "Sadly... there muuuuuuuuuuuuuuuuuuuuuuust be a bug!";
	}
	SLASH;
	vec2.pop();
	if (vec1 != vec2)
	{
		std::cout << "Obviously...";
	}
	else {
		std::cout << "Sadly... there muuuuuuuuuuuuuuuuuuuuuuust be a bug!";
	}

	printMtVec(vec2);
	SLASH;
	std::cout << "front:> " << vec2.front() << "\t rear:> " << vec2.rear();
	SLASH;

	testType* arrayFromRaw = vec2.rawDataStaticArray();
	read = arrayFromRaw;
	for (int i = 0; i < vec2.size(); i++)
	{
		std::cout << *(read++) << " ";
	}
	SLASH;
	BytesArray<testType> static_one = vec2.wrappeddata();
	for (int i = 0; i < static_one.size(); i++)
	{
		std::cout << static_one[i] << " ";
	}
}