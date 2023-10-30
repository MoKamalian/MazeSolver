#ifndef SOLVED_COORDINATE_HPP
#define SOLVED_COORDINATE_HPP

/**
 * @author amir kamalian
 * @date   05 oct 2023
 * */


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


typedef std::pair<u_int16_t, u_int16_t> coord;

/** @brief contains the solved coordinates for a maze.
 * Valid coordinates mean a coordinate value that is part of the
 * solved maze. The m_valids stack structure is dynamic and changes
 * until the maze is solved. */
struct SolvedCoordinates {
private:
    std::vector<coord> m_valids;
public:
    SolvedCoordinates() = default;
    SolvedCoordinates(const SolvedCoordinates&) = delete;
    ~SolvedCoordinates() = default;

    void push(const coord& valid_coord) noexcept;

    bool pop() noexcept;

    [[nodiscard("check if empty")]]
    bool check() const noexcept;

    [[nodiscard("check for value")]]
    bool check(const coord& pair) const noexcept;

    [[nodiscard("value at end of stack")]]
    coord top() noexcept;

    void clear() noexcept;

    friend std::ostream& operator<<(std::ostream& ostream, const SolvedCoordinates& s);

};



#endif //SOLVED_COORDINATE_HPP

