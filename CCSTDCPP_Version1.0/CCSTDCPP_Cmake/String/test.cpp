#include"CCSTDCPP_String.hpp"

using namespace CCSTDCPP;
int main()
{
	// test the def init
	StringA def;
	if (def.isEmpty() && def.isNull()) {
		std::cout << "Not only the str is Empty, but also null!\n";
	}

	// test the def
	StringA a("hello, world");
	std::cout << a << std::endl;

	StringA tmp1("Hello,CPP!");
	std::cout << tmp1 << std::endl;

	StringA sameAlpha('a', 4);
	std::cout << sameAlpha << std::endl;

	sameAlpha.setStr("Hello");
	std::cout << sameAlpha << std::endl;

	StringA copy(sameAlpha);
	std::cout << copy << std::endl;

	StringA move(std::move(sameAlpha));
	std::cout << move << std::endl;
	
	move.append(",World");
	std::cout << move << std::endl;

	move.append('!', 3);
	std::cout << move << std::endl;

	move.append(move);
	std::cout << move << std::endl;

	tmp1.reverse();
	std::cout << tmp1 << std::endl;

	StringA reverse = tmp1.reverseStr();
	std::cout << "reverse of tmp1:> " << reverse << std::endl;


	StringA Compare("aaa");
	if (Compare == "aaa") {
		std::cout << "yep, of course\n";
	}
	else {
		std::cout << "buggy\n";
	}

	if (Compare == "bbb") {
		std::cout << "buggy\n";
	}
	else {
		std::cout << "yep, of course\n";
	}

	if (Compare != "bbb") {
		std::cout << "yep, of course\n";
	}
	else {
		std::cout << "buggy\n";
	}

	if (Compare != "aaa") {
		std::cout << "buggy\n";
	}
	else {
		std::cout << "yep, of course\n";
	}

	if (Compare.isEqual("aaaaa",0,1)) {
		std::cout << "yep, of course\n";
	}

	if (Compare.isEqual(StringA("aaa"))) {
		std::cout << "yep, of course\n";
	}

	Compare[0] = 'b';
	std::cout << Compare << '\n';


	StringA finder("CPP,HelloCPP");

	std::cout << finder.findSub("ello",1,5) << std::endl;

	std::cout << finder.findSub('C') << std::endl;

	PositionGroup arr = finder.findAllSub('C',0,4);

	for (int i = 0; *arr[i] != '\0'; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << '\n';
	delete[] arr;

	StringA finderB = "HelHelloCPPCPPHelloHelloCPP";
	PositionGroup arr2 = finderB.findAllSub("Hello");
	for (int i = 0; *arr2[i] != '\0'; i++) {
		std::cout << arr2[i] << " ";
	}
	std::cout << '\n';
	delete[] arr2;

	StringA_Array splity = finderB.split("Hello");
	std::cout << "Splity:\n";
	for (int i = 0; !splity[i]->isNull(); i++) {
		std::cout << *splity[i] << std::endl;
	}

    StringA spec = "AAAAAAAAAAAAAAA";
	StringA_Array splity2 = spec.split("A");
	for (int i = 0; !splity2[i]->isNull(); i++) {
		std::cout << *splity2[i] << std::endl;
	}


	delete[] splity;
	delete[] splity2;

	splity2 = finderB.split('e');
	for (int i = 0; !splity2[i]->isNull(); i++) {
		std::cout << *splity2[i] << std::endl;
	}
	delete[] splity2;

	StringA thisStr = "aaabbbaaa";
	thisStr.insert("ccc", 0);
	std::cout << thisStr << std::endl;

	thisStr.insert(StringA("ddd"), 0);
	std::cout << thisStr << std::endl;

	thisStr.insert('e', 0, 3);
	std::cout << thisStr << std::endl;

	StringA remove = finderB.remove(StringA("Hello"),4);
	std::cout << remove << std::endl;

	remove = remove.remove('C');
	std::cout << remove << std::endl;

	remove += "helloCPP";
	std::cout << remove << std::endl;

	remove += StringA("helloCPP");
	std::cout << remove << std::endl;

	remove = remove + StringA("HelloCPP");
	std::cout << remove << std::endl;

	remove -= StringA("HelloCPP");
	std::cout << remove << std::endl;

	remove -= "helloCPP";
	std::cout << remove << std::endl;

	remove -= "HelloCPP";
	std::cout << remove << std::endl;
}

