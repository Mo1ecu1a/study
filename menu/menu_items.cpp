#include <cstddef>
#include "menu.hpp"
#include "menu_func.hpp"
#include "menu_items.hpp"

const ypa::MenuItem ypa::GO_BACK =  {
	"0 - вернуться к выбору предметов...", ypa::go_back, &ypa::ALGEBRA
};
const ypa::MenuItem ypa::GO_BACK_TO_MENU = {
	"0 - вернуться в главное меню...", ypa::go_back, &ypa::STUDY
};

const ypa::MenuItem ypa::SUM = {
	"1 - хочу научиться складывать", ypa::sum, &ypa::ALGEBRA
};
const ypa::MenuItem ypa::SUBSTRACT = {
	"2 - хочу научиться вычитать", ypa::substract, &ypa::ALGEBRA
};
const ypa::MenuItem ypa::MULTIPLY = {
	"3 - хочу научиться умножать", ypa::multiply, &ypa::ALGEBRA
};
const ypa::MenuItem ypa::DIVIDE = {
	"4 - хочу научиться делить", ypa::divide, &ypa::ALGEBRA
};

namespace {
	const ypa::MenuItem* const algebra_children[]  =  {
		&ypa::GO_BACK,
		&ypa::SUM,
		&ypa::SUBSTRACT,
		&ypa::MULTIPLY,
		&ypa::DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}

const ypa::MenuItem ypa::DIFF = {
	"1 - хочу изучить дифференциальное исчисление", ypa::diff &ypa::MATH_ANALYSIS
};
const ypa::MenuItem ypa::INTEGRAL = {
	"2 - хочу изучить интегральное исчисление", ypa::integral, &ypa::MATH_ANALYSIS
};

namespace {
	const ypa::MenuItem* const math_analysis_children[] =  {
		&ypa::GO_BACK,
		&ypa::DIFF,
		&ypa::INTEGRAL
	};
	const int math_analysis_size = sizeof(math_analysis_children) / sizeof(math_analysis_children[0]);
}

const ypa::MenuItem ypa::ALGEBRA = {
	"1 - очу изучать алгебру", ypa::show_menu, &ypa::STUDY, algebra_children, algebra_size
};
const ypa::MenuItem ypa::MATH_ANALYSIS = {
	"2 - хочу изучать математический анализ", ypa::show_menu, &ypa::STUDY, math_analysis_children, math_analysis_size
};

namespace {
	const ypa::MenuItem* const study_children[] = {
		&ypa::GO_BACK_TO_MENU,
		&ypa::ALGEBRA,
		&ypa::MATH_ANALYSIS
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const ypa::MenuItem ypa::STUDY = {
	"1 - хочу учиться математике", ypa::show_menu, &ypa::MAIN, study_children, study_size
};
const ypa::MenuItem ypa::EXIT = {
	"0 - я лучше пойду...", ypa::exit, &ypa::MAIN
};

namespace {
	const ypa::MenuItem* const main_children[] = {
		&ypa::EXIT,
		&ypa::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const ypa::MenuItem ypa::MAIN = {
	nullptr, ypa::show_menu, nullptr, main_children, main_size
};
