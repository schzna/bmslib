#include<iostream>
#include"bmslib.hpp"

int main() {
	auto bms = bmslib::loadheader("sample.bme");

	std::cout << "title:" << bms.header.title << std::endl;

	std::cout << "artist:" << bms.header.artist << std::endl;

	std::cout << "genre:" << bms.header.genre << std::endl;

	system("pause");
}