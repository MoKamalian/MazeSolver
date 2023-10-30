#ifndef GRID_H
#define GRID_H
/**
 * @author amir kamalian
 * @date   02 oct 2023
 * */


#include <iostream>
#include <fstream>
#include "solved_coordinate.hpp"
#include "color_codes.hpp"

#define DEFAULT_WIDTH (51)
#define DEFAULT_HEIGHT (51)
#define INVALID_POS ('?')


/** Grid representation of maze */
template<u_int16_t W = DEFAULT_WIDTH, u_int16_t H = DEFAULT_HEIGHT>
class Grid {
private:
    u_int16_t m_width = W;
    u_int16_t m_height = H;
    char m_matrix[H][W] = { ' ' };
    coord m_begin;
    coord m_end;

public:
    Grid();
    explicit Grid(std::fstream& maze_file) noexcept;
    Grid(const Grid&) = delete;
    ~Grid() = default;

    /***/
    [[nodiscard("insertion success")]]
    bool fill_coordinate(u_int16_t x, u_int16_t y, const char value) noexcept;

    [[nodiscard("insertion success")]]
    bool fill_coordinate(const coord& c, const char value) noexcept;

    /** getters */
    [[nodiscard("matrix width")]]
    u_int16_t get_width() const noexcept;

    [[nodiscard("matrix height")]]
    u_int16_t get_height() const noexcept;

    [[nodiscard("value at coord")]]
    char get_value_at(const coord& c) const noexcept;

    [[nodiscard("value at coord")]]
    char get_value_at(u_int16_t x, u_int16_t y) const noexcept;

    [[nodiscard("begin coord")]]
    coord get_begin() const noexcept;

    [[nodiscard("end coord")]]
    coord get_end() const noexcept;

    [[nodiscard("matrix")]]
    auto get_matrix() const noexcept;

    /** setters */
    void set_begin(u_int16_t x, u_int16_t y) noexcept;

    void set_end(u_int16_t x, u_int16_t y) noexcept;

    /** printing the maze */
    friend std::ostream& operator<<(std::ostream& ostream, const Grid& grid) {
        for(auto& row : grid.m_matrix) {
            for(auto& each : row) {
                each == '*' ? std::cout << BOLDRED << each << RESET :
                              std::cout << BOLDGREEN << each << RESET;
            }
            std::cout << std::endl;
        }
        return ostream;
    }

};


/** default with an empty maze matrix */
template<u_int16_t W, u_int16_t H>
Grid<W, H>::Grid() = default;

/** @brief When the maze text file is specified, contents are directly transferred to the
 * maze matrix. When a non-open file is provided, the default object is instantiated. \
 * @param maze_file: text file to extract maze from.
 * @note there is undefined behaviour when a non-text file is provided. */
template<u_int16_t W, u_int16_t H>
Grid<W, H>::Grid(std::fstream& maze_file) noexcept {
    if(maze_file.is_open() && maze_file.good()) {

        for(int i=0; i<H; i++) {
            std::string line;
            std::getline(maze_file, line);
            for(int j=0; j<W; j++) {
                this->m_matrix[i][j] = line[j];
            }
        }

    } else {
        Grid<W, H>();
    }
}

/** @brief fills the specific coordinate with the char value provided. Coordinate
 * limits are checked before insertion and out of bounds values return false. A
 * successful insertion return true.
 * */
template<u_int16_t W, u_int16_t H>
bool Grid<W, H>::fill_coordinate(u_int16_t x, u_int16_t y, const char value) noexcept {
    if(x > this->m_width || y > this->m_height) return false;
    this->m_matrix[y][x] = value;
    return true;
}

template<u_int16_t W, u_int16_t H>
bool Grid<W, H>::fill_coordinate(const coord& c, const char value) noexcept {
    return this->fill_coordinate(c.first, c.second, value);
}


/** getters */
template<u_int16_t W, u_int16_t H>
u_int16_t Grid<W, H>::get_width() const noexcept {
    return this->m_width;
}

template<u_int16_t W, u_int16_t H>
u_int16_t Grid<W, H>::get_height() const noexcept {
    return this->m_height;
}

template<u_int16_t W, u_int16_t H>
char Grid<W, H>::get_value_at(const coord& c) const noexcept {
    return this->get_value_at(c.first, c.second);
}

template<u_int16_t W, u_int16_t H>
char Grid<W, H>::get_value_at(u_int16_t x, u_int16_t y) const noexcept {
    if(x > this->m_width || y > this->m_height) {
        return INVALID_POS;
    } else {
        return this->m_matrix[y][x];
    }
}

/** @brief return value may be null. */
template<u_int16_t W, u_int16_t H>
coord Grid<W, H>::get_begin() const noexcept {
    return this->m_begin;
}

/** @brief return value may be null. */
template<u_int16_t W, u_int16_t H>
coord Grid<W, H>::get_end() const noexcept {
    return this->m_end;
}

template<u_int16_t W, u_int16_t H>
auto Grid<W, H>::get_matrix() const noexcept {
    return this->m_matrix;
}

/** setters */
template<u_int16_t W, u_int16_t H>
void Grid<W, H>::set_begin(u_int16_t x, u_int16_t y) noexcept {
    if((x < this->m_width) && (y < this->m_height)) {
        this->m_begin = coord(x, y);
    }
}

template<u_int16_t W, u_int16_t H>
void Grid<W, H>::set_end(u_int16_t x, u_int16_t y) noexcept {
    if((x < this->m_width) && (y < this->m_height)) {
        this->m_end = coord(x, y);
    }
}

#endif

