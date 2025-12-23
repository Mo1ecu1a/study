#include <cstdlib>
#include <iostream>

#include "menu_items.hpp"
#include "menu_func.hpp"

const ypa::MenuItem* ypa::show_menu(const MenuItem* current) {
	std::cout << "привет" << std::endl;
	for (int i = 1; i < current->children_count; i++)	{	
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка >> ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const ypa::MenuItem* ypa::exit(const MenuItem* current) {
	std::exit(0);
}


const ypa::MenuItem* ypa::sum(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ypa::MenuItem* ypa::substract(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ypa::MenuItem* ypa::multiply(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ypa::MenuItem* ypa::divide(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ypa::MenuItem* ypa::diff(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}
const ypa::MenuItem* ypa::integral(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent;
}

const ypa::MenuItem* ypa::go_back(const MenuItem* current) {
	std::cout << current->title << std::endl << std::endl;
	return current->parent->parent;

}
