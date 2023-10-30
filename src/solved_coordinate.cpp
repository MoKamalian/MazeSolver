
/**
 * @author amir kamalian
 * @date   05 oct 2023
 * */


#include "../inc/solved_coordinate.hpp"


/** @brief adds coordinate to stack.
 * @param valid_coord: a valid set of coordinates (i.e. valid positions
 * within the maze. */
void SolvedCoordinates::push(const coord& valid_coord) noexcept {
    this->m_valids.push_back(valid_coord);
}

/** @brief removes value from top of end of the stack. */
bool SolvedCoordinates::pop() noexcept {
    if(!this->check()) {
        this->m_valids.pop_back();
        return true;
    } else {
        return false;
    }
}

/** @brief check if the vector of valid coordinates is empty.
 * @return ture if vector is empty */
bool SolvedCoordinates::check() const noexcept {
    return this->m_valids.empty();
}

/** @brief check for presence of specific coord. */
bool SolvedCoordinates::check(const coord& pair) const noexcept {
    return (std::find(this->m_valids.begin(), this->m_valids.end(), pair) != this->m_valids.end());
}

/** @brief return the coordinate at the top of the stack */
coord SolvedCoordinates::top() noexcept {
    if(!this->m_valids.empty()) {
        return this->m_valids.back();
    }
}

/** @brief clears entire vector of coordinates */
void SolvedCoordinates::clear() noexcept {
    this->m_valids.clear();
}

/***/
std::ostream& operator<<(std::ostream& ostream, const SolvedCoordinates& s) {
    if(!s.m_valids.empty()) {
        for (coord c: s.m_valids) {
            std::cout << "[" << c.first << "," << c.second << "]" << std::endl;
        }
    } else {
        std::cout << "[ empty ]" << std::endl;
    }
    return ostream;
}


