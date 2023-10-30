#ifndef SOLVE_H
#define SOLVE_H

/**
 * @author amir kamalian
 * @date   06 oct 2023
 * */


#include <iostream>
#include <algorithm>
#include <vector>
#include "solved_coordinate.hpp"
#include "gird.hpp"

#define OUT_OF_BOUNDS(i) ((i - 1) < 0)
#define VALID_POS (' ')

/** forward declerations of helper functions */
template<u_int16_t W, u_int16_t H>
coord valid_next_coord(const Grid<W, H>& maze, const coord& curr) noexcept;

template<u_int16_t W, u_int16_t H>
bool __left__(const Grid<W, H>& _maze_, const coord& _c_);

template<u_int16_t W, u_int16_t H>
bool __up__(const Grid<W, H>& _maze_, const coord& _c_);

template<u_int16_t W, u_int16_t H>
bool __right__(const Grid<W, H>& _maze_, const coord& _c_);

template<u_int16_t W, u_int16_t H>
bool __down__(const Grid<W, H>& _maze_, const coord& _c_);


/** buffer of visited coordinates */
static std::vector<coord> visited = std::vector<coord>();

/** @brief check if coordinates exist in visited vector. */
inline bool __already_visited__(const coord& c) noexcept {
    return std::find(visited.begin(), visited.end(), c) != visited.end();
}

/** @brief check if the solve condition is true. Solve condition means the next
 * valid coordinates are equal to the end coordinates of the maze. */
inline bool __solved__(const coord& c1, const coord& end) noexcept {
    return c1 == end;
}

/** @brief checks if the maze end and begin coordinates have been set */
inline bool __maze_condition__(const coord& c1, const coord& c2) noexcept {
    return ((c1.first == 0 && c1.second == 0) || (c2.first == 0 && c2.second == 0));
}

/** @brief check if the coordinate is a null value. In this case null meaning first and
 * second value of the pair are both zero */
inline bool __is_null__(const coord& c) noexcept {
    return (c.first == 0 && c.second == 0);
}

/** ====================================================================================== */

/** @brief solves the passed maze using depth first search. */
template<u_int16_t W, u_int16_t H>
void solve(Grid<W, H>& maze) noexcept {
    // stack structure that contains the solved maze coordinates
    SolvedCoordinates solved_coord = SolvedCoordinates();

    coord current = maze.get_begin();
    coord end = maze.get_end();

    if(__maze_condition__(current, end)) return; // maze begin and win coordinates not set

    do { // while the maze has not been solved yet
        if(!__is_null__(current)) {
            // push to the solved stack
            solved_coord.push(current);
            maze.fill_coordinate(current, '*');
        } else {
            // pop from the solved stack
            if(!solved_coord.check()) {
                maze.fill_coordinate(solved_coord.top(), ' ');
                solved_coord.pop();
                current = solved_coord.top();
            }
        }

        visited.push_back(current);
        current = valid_next_coord(maze, current);
    } while(!__solved__(current, end));

    maze.fill_coordinate(current, '*'); //end special character
}

/** ====================================================================================== */

//TODO: CHANGE RETURN TYPE HERE TO STD::OPTIONAL<COORD> ?
/** @brief returns the valid coordinate within the maze relative
 * to the passed coordinates. A visited coordinate is considered invalid
 * and so is not returned. */
template<u_int16_t W, u_int16_t H>
coord valid_next_coord(const Grid<W, H>& maze, const coord& curr) noexcept {
    //left
    if( __left__(maze, curr) && !__already_visited__(coord(curr.first - 1, curr.second)) ) {
        return {curr.first - 1, curr.second};
    }

    //up
    else if( __up__(maze, curr) && !__already_visited__(coord(curr.first, curr.second - 1)) ) {
        return {curr.first, curr.second - 1};
    }

    //right
    else if( __right__(maze, curr) && !__already_visited__(coord(curr.first + 1, curr.second)) ) {
        return {curr.first + 1, curr.second};
    }

    //down
    else if( __down__(maze, curr) && !__already_visited__(coord(curr.first, curr.second + 1)) ) {
        return {curr.first, curr.second + 1};
    }

    return {0, 0};
}

/**
 * @brief below standalone functions check corresponding grid
 * positions to see if they are valid or not. A valid coordinate
 * is en empty char at the checked position.
 *
 *       # U #
 *       L X R
 *       # D #
 *
 * The corresponding function that checks that position.
 * U - __up__
 * L - __left__
 * R - __right__
 * D - __down__
 * X - coordinate position being checked.
 * */
template<u_int16_t W, u_int16_t H>
bool __left__(const Grid<W, H>& _maze_, const coord& _c_) {
    if(_c_.first <= _maze_.get_width() || _c_.second <= _maze_.get_height()) {
        if(!OUT_OF_BOUNDS(_c_.first)) {
            char t = _maze_.get_value_at((_c_.first - 1), _c_.second);
            return t == VALID_POS;
        } else { return false; }
    } else {
        return false;
    }
}

template<u_int16_t W, u_int16_t H>
bool __up__(const Grid<W, H>& _maze_, const coord& _c_) {
    if (_c_.first <= _maze_.get_width() || _c_.second <= _maze_.get_height()) {
        if(!OUT_OF_BOUNDS(_c_.second)) {
            char t = _maze_.get_value_at(_c_.first, (_c_.second - 1));
            return t == VALID_POS;
        } else { return false; }
    } else {
        return false;
    }
}

template<u_int16_t W, u_int16_t H>
bool __right__(const Grid<W, H>& _maze_, const coord& _c_) {
    if(_c_.first <= _maze_.get_width() || _c_.second <= _maze_.get_height()) {
        if((_c_.first + 1) <= _maze_.get_width()) {
            char t = _maze_.get_value_at((_c_.first + 1), _c_.second);
            return t == VALID_POS;
        } else { return false; }
    } else {
        return false;
    }
}

template<u_int16_t W, u_int16_t H>
bool __down__(const Grid<W, H>& _maze_, const coord& _c_) {
    if (_c_.first <= _maze_.get_width() || _c_.second <= _maze_.get_height()) {
        if((_c_.second + 1) <= _maze_.get_height()) {
            char t = _maze_.get_value_at(_c_.first, (_c_.second + 1));
            return t == VALID_POS;
        } else { return false; }
    } else {
        return false;
    }
}

#endif

