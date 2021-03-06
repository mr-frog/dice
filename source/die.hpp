#ifndef DICE_DIE
#define DICE_DIE

#include "random.hpp"

namespace dice {
	struct die {
		/// The type of value returned when the die is rolled.
		using result_type = int;
		
		/// An exception signifying that a die cannot be created with `n` sides.
		struct bad_num_sides { result_type n; };
		
		/// Construct a six-sided die.
		die() = default;
		
		/// Construct an `n`-sided die.
		///
		/// @throws `bad_num_sides` if `n` is less than 1.
		die(result_type n) :
			dist{1, (n > 0) ? n : throw bad_num_sides{n}}
		{ }
		 
		/// The number of sides that the die has.
		result_type sides() const {
			return dist.max();
		}
		
		/// Roll the die.
		result_type operator() () const {
			return dist(rand_eng);
		}
		
	private:
		mutable std::uniform_int_distribution<result_type> dist{1, 6};
	};
}

#endif
