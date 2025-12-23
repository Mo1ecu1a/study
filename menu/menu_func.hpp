#pragma once

#include "menu.hpp"

namespace ypa {
	const MenuItem* show_menu(const MenuItem* current);
	const MenuItem* exit(const MenuItem* current);
	
	const MenuItem* algebra(const MenuItem* current);
	const MenuItem* math_analysis(const MenuItem* current);
		
	const MenuItem* diff(const MenuItem* current);
	const MenuItem* integral(const MenuItem* current);
	const MenuItem* sum(const MenuItem* current);
	const MenuItem* substract(const MenuItem* current);
	const MenuItem* multiply(const MenuItem* current);
	const MenuItem* divide(const MenuItem* current);
	const MenuItem* go_back(const MenuItem* current);
}
