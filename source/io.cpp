#include <iostream>

#include "util/math.hpp"
#include "util/numeric.hpp"
#include "util/string.hpp"

#include "info.hpp"
#include "io.hpp"

using std::cout;
using std::cerr;

std::ostream & dice::operator<<(std::ostream & os, const Die & d) {
	return os << 'd' << d.num_sides();
}

std::ostream & dice::operator<<(std::ostream & os, const std::vector<Die> & dice) {
	if (!dice.empty()) {
		os << dice.front();
		for (auto i = dice.begin() + 1; i != dice.end(); ++i) {
			os << ' ' << *i;
		}
	}
	
	return os;
}

void dice::write_die_roll(const Die & d, Die::result_type r, std::ostream & os) {
	auto max_r = d.num_sides();
	
	auto str = std::to_string(r);
	auto len = util::num_digits(max_r);
	util::pad_front(str, ' ', len);
	
	os << str;
}

void dice::write_dice_roll_sum(const std::vector<Die> & dice, const std::vector<Die::result_type> & roll, std::ostream & os) {
	auto sum = util::sum(roll);
	Die::result_type max_sum = 0;
	for (auto & d: dice) max_sum += d.num_sides();
	
	auto str = std::to_string(sum);
	auto len = util::num_digits(max_sum);
	util::pad_front(str, ' ', len);
	
	os << str;
}

void dice::print_chosen_dice(const std::vector<Die> & dice) {
	if (dice.empty()) {
		cout << "(no dice chosen)\n";
	} else {
		cout << dice << '\n';
	}
}

void dice::print_default_dice(const std::vector<Die> & dice) {
	if (dice.empty()) {
		cout << "(default choice: no dice)\n";
	} else {
		cout << "(default choice: " << dice << ")\n";
	}
}

void dice::print_dice_roll(const std::vector<Die> & dice, const std::vector<Die::result_type> & roll) {
	switch (roll.size()) {
	 case 0:
		cout << "0\n";
		break;
		
	 case 1:
		write_die_roll(dice[0], roll[0], cout);
		cout << '\n';
		break;
		
	 default: {
		write_die_roll(dice[0], roll[0], cout);
		
		for (typename std::vector<Die>::size_type i = 1; i < dice.size(); ++i) {
			cout << " + ";
			write_die_roll(dice[i], roll[i], cout);
		}
		
		cout << " = ";
		write_dice_roll_sum(dice, roll, cout);
		cout << '\n';
		break;
	 }
	}
}

void dice::print_program_help() {
	cout << "Press ENTER with a blank input to roll the dice.\n"
			  "Enter 'c n1 n2 ...' to choose a new set of dice to roll,\n"
			  "  where n1, n2, ... are the number of sides on the dice.\n"
			  "Enter 'l' to list the chosen dice.\n"
			  "Enter 'h' to display this help message.\n"
			  "Enter 'q' to quit the program.\n";
}

void dice::print_invalid_input() {
	cerr << "Your input could not be recognised.\n"
			  "(enter 'h' for help)\n";
}

void dice::print_cl_help() {
	cout << "Usage:\n"
			  "  dice: start with a d6\n"
			  "  dice 3 4 5: start with a d3, a d4, and a d5\n"
			  "  dice n1 n2 ...: start with a dn1, a dn2, ...\n"
			  "\n"
			  "Options:\n"
			  "  [-h | --help]\n"
			  "  [-v | --version]\n"
			  "  [-1 | --once]: roll the dice once, then quit\n";
}

void dice::print_version() {
	cout << "dice v" << version_c_str << "\n";
}

void dice::print_invalid_clo(const std::string & str) {
	cerr << "The command-line option '" << str << "' could not be recognised.\n"
			  "(try 'dice --help' if you're stuck)\n";
}

bool dice::read_die(const std::string & str, std::vector<Die> & dice) {
	auto success = true;
	
	try {
		dice.emplace_back(util::to_i(str));
	} catch (std::invalid_argument &) {
		success = false;
		cerr << "Error: the string '" << str << "' is not an integer!\n";
	} catch (std::out_of_range &) {
		success = false;
		cerr << "Error: the number '" << str << "' is too big to store!\n";
	} catch (Die::bad_num_sides & ex) {
		success = false;
		cerr << "Error: a die with " << ex.n << " sides cannot be created!\n";
	}
	
	return success;
}
