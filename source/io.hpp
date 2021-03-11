#ifndef DICE_IO
#define DICE_IO

#include <ostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "die.hpp"

namespace dice {
	/// A regular expression to parse the number of dice rolls specified
	/// at the command line.
	inline auto const rolls_option_regex = std::regex{"(?:--rolls=)(.*)"};

	/// Write "dN" to `os`, where N is the number of sides of `d`.
	std::ostream & operator<<(std::ostream & os, Die const& d);
	
	/// Write `dice` to `os` as a list in the form "dn1 dn2 ...".
	std::ostream & operator<<(std::ostream & os, std::vector<Die> const& dice);
	
	/// Write the die roll `r` obtained from `d` to `os`.
	///
	/// Extra spaces are inserted at the front of the outputted text based on the
	/// number of sides of `d`, so that the same number of characters will be
	/// output regardless of which value `r` takes.
	///
	/// `r` should be a valid roll, i.e. obtainable by rolling `d`.
	void write_die_roll(Die const& d, Die::result_type r, std::ostream & os);
	
	/// Write the sum of the dice rolls in `roll` to `os`.
	///
	/// Extra spaces are inserted at the front of the outputted text based on the
	/// maximum possible sum that can be obtained by rolling the dice in `dice`,
	/// so that the same number of characters will be output regardless of the
	/// rolls that are passed in.
	///
	/// Each `roll[i]` should be obtainable by rolling `dice[i]`.
	/// Furthermore, `dice.size()` and `roll.size()` should be equal.
	void write_dice_roll_sum(std::vector<Die> const& dice, std::vector<Die::result_type> const& roll, std::ostream & os);
	
	/// Print the chosen set of dice.
	void print_chosen_dice(std::vector<Die> const& dice);
	
	/// Print the default set of dice.
	void print_default_dice(std::vector<Die> const& dice, bool verbose);
	
	/// Print the given dice roll and its sum.
	///
	/// If `verbose` is true, make the output more user-friendly.
	///
	/// Each `roll[i]` should be obtainable by rolling `dice[i]`.
	/// Furthermore, `dice.size()` and `roll.size()` should be equal.
	void print_dice_roll(std::vector<Die> const& dice, std::vector<Die::result_type> const& roll, bool verbose);
	
	/// Print help related to the interface within the program.
	void print_program_help();
	
	/// Print help related to the command-line interface.
	void print_cl_help(std::string_view basename);
	
	/// Print the version of the program.
	void print_version();
	
	/// Print an error message indicating that an invalid string was input into
	/// the program.
	void print_invalid_input();
	
	/// Print an error message indicating that `str` is not a command-line
	/// option.
	void print_invalid_clo(std::string_view str, std::string_view basename);
	
	/// Convert `str` to an `int` and append a new die to the end of `dice` with
	/// that many sides.
	///
	/// An error message is printed if this fails for some reason. In this case,
	/// `dice` remains in the same state as before the function was called.
	///
	/// @returns whether the function succeeded.
	bool read_die(std::string_view str, std::vector<Die> & dice);
}

#endif
