/**
 *
 * @author: amir Kamalian
 * @date:   02 oct 2023
 *
 * */

// TODO: read and write to matrix locations, two methods, in template class


#include <iostream>
#include <fstream>
#include "../inc/gird.hpp"
#include "../inc/color_codes.hpp"
#include "../inc/solved_coordinate.hpp"
#include "../inc/solve.hpp"

#define print(f) std::cout << f << std::endl;


using std::cout, std::endl, std::string;

/** @brief Validates the arguments given to program. Only one argument should be provided
 * (the file) with .txt extension. Program exits and returns an error otherwise. */
bool validate_arg(string& arg) noexcept;

/** @brief writes the contents of the maze to a text file. */
template<u_int16_t W, u_int16_t H>
void write_maze(const Grid<W, H>& maze, const std::string& path) noexcept;

int main(int argc, char** argv) {

    if(argc != 3) {
        cout << BOLDRED << "[ error : not enough arguments provided ]" << RESET << endl;
        exit(0);
    }

    string file_path = argv[1];
    if(!validate_arg(file_path)) {
        cout << BOLDRED << "[ error : non-text file provided ]" << RESET << endl;
        exit(0);
    }

    string solved_path = argv[2];
    if(!validate_arg(solved_path)) {
        cout << BOLDRED << "[ error : non-text file provided for writing ]" << RESET << endl;
        exit(0);
    }

    std::fstream file = std::fstream(file_path, std::ios_base::in | std::ios_base::out);
    if(!file) {
        cout << BOLDRED << "[ error : input file does not exist ]" << RESET << endl;
        exit(0);
    }

    Grid maze = Grid<51, 51>(file);
    maze.set_end(50, 49);
    maze.set_begin(0, 1);

    solve(maze);

    print(maze);

    write_maze(maze, solved_path);

    return 0;
}

/** Validate text file provided */
bool validate_arg(string& arg) noexcept {
    return arg.find(".txt");
}

/** @brief writes the contents of the maze to a text file. */
template<u_int16_t W, u_int16_t H>
void write_maze(const Grid<W, H>& maze, const std::string& path) noexcept {
    std::ofstream f(path);
    int w = maze.get_width();
    int h = maze.get_height();
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            f << maze.get_value_at(x, y);
        }
        f << endl;
    }
    f.close();
}






