#ifndef CORD_UTILITIES_HPP
#define CORD_UTILITIES_HPP

#include "cord.hpp"
/**
 * Concatenates the two cords (see above).
 * Throws an exception if either of the left cord or
 * right_cord holder points to nullptr.
 */
SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                       SharedPointer<Cord> right_cord);
/**
 * Substrings the cord pointed to by curr_cord with the
 * given indices (lower_idx is inclusive and upper_idx is
 * exclusive).For more information,kindly see above.
 * Throws an exception if lower idx or upper_idx is
 * outside the bounds of the cord pointed to by
 * curr cord,or if lower_idx >upper_idx.
 */
SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                                unsigned int lower_idx, unsigned int upper_idx);
#endif