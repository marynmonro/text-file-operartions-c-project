#include <iostream>
#include <vector>
#include <fstream>
#include "operations.h"

int main(int args_count, const char* args[]) {
    auto arguments = std::vector<std::string>(args + 1, args + args_count);
    auto* os = &std::cout;
    std::ostream& out = *os;

    if ( arguments[0] == "-i" || arguments[0] == "--input" ){
        if( arguments.size() > 2 ){ //mistake
            out << "Error. Other arguments found";
            return 0;
        }

        auto st = arguments[1];
        std::ifstream file(st);
        arguments.clear();

        for (auto word = std::string(); file >> word;) {
            arguments.push_back(word);
        }
    }

    if ( arguments.empty() || arguments[0]=="--help" ) {
        out << help();
        return 0;
    }

    auto file = std::ifstream();
    std::string sciezka;
    auto is_sorted_by_length = false;
    auto file_not_found = true;

    for( int i = 0; i<arguments.size(); i++ ) {

        if (arguments[i] == "-f" || arguments[i] == "--file") {
            if (arguments.size() <= 1) {
                out << "No path";
                return 0;
            }
            file_not_found = false;
            sciezka = arguments[i + 1];
            file = std::ifstream(arguments[i + 1]);
            if (file.fail()) {
                out << "Incorrect path or no path";
                return 0;
            }
        }

        if( !file_not_found ){
            if (arguments[i] == "-n" || arguments[i] == "--newlines") {
                file = std::ifstream(sciezka);
                out << lines_counter(file) << '\n';
            }

            if (arguments[i] == "-d" || arguments[i] == "--digits") {
                file = std::ifstream(sciezka);
                out << numbers_counter(file) << '\n';
            }

            if (arguments[i] == "-dd" || arguments[i] == "--numbers") {
                file = std::ifstream(sciezka);
                out << real_numbers_counter(file) << '\n';
            }

            if (arguments[i] == "-c" || arguments[i] == "--chars") {
                file = std::ifstream(sciezka);
                out << chars_counter(file) << '\n';
            }

            if (arguments[i] == "-w" || arguments[i] == "--words") {
                file = std::ifstream(sciezka);
                out << words_counter(file) << '\n';
            }

            if (arguments[i] == "-s" || arguments[i] == "--sorted") {
                file = std::ifstream(sciezka);
                sorted_words(file, is_sorted_by_length, *os);
                is_sorted_by_length = false;
                out << '\n';
            }

            if (arguments[i] == "-rs" || arguments[i] == "--reverse-sorted") {
                file = std::ifstream(sciezka);
                reverse_sorted(file, is_sorted_by_length, *os);
                is_sorted_by_length = false;
                out << '\n';
            }

            if (arguments[i] == "-l" || arguments[i] == "--by-length") {
                is_sorted_by_length = true;
            }

            if (arguments[i] == "-a" || arguments[i] == "--anagrams") {
                auto anagrams_container = std::vector<std::string>();
                for (int j = 1; j + i < arguments.size(); j++) {
                    auto poz = arguments[i + j].find('-');
                    if (poz == -1) {
                        anagrams_container.push_back(arguments[i + j]);
                    } else {
                        out << "Error. Flag found" << '\n';
                        return 0;
                    }
                }

                file = std::ifstream(sciezka);
                auto result = find_anagrams(anagrams_container, file);
                for (auto &res : result)
                    out << res << ' ';
                out << '\n';
            }


            if (arguments[i] == "-p" || arguments[i] == "--palindroms") {
                auto anagrams_container = std::vector<std::string>();
                for (int j = 1; j + i < arguments.size(); j++) {
                    auto poz = arguments[i + j].find('-');
                    if (poz == -1) {
                        anagrams_container.push_back(arguments[i + j]);
                    } else {
                        out << "Error. Flag found" << '\n';
                        return 0;
                    }
                }
                file = std::ifstream(sciezka);
                auto result = find_palindrome(anagrams_container, file);
                for (auto &res : result)
                    out << res << ' ';
                out << '\n';
            }

            if (arguments[i] == "-fi" || arguments[i] == "--find") {
                auto find_container = std::vector<std::string>();
                for (int j = 1; j + i < arguments.size(); j++) {
                    auto poz = arguments[i + j].find('-');
                    if (poz == -1) {
                        find_container.push_back(arguments[i + j]);
                    } else {
                        break;
                    }
                }
                file = std::ifstream(sciezka);
                find_word(file, find_container, *os);
                out << '\n';
            }
        } else out << "File not found";

    }



    return 0;
}
