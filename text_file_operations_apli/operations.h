//
// Created by marynmonro on 4/11/2022.
//

#ifndef TEXT_FILE_OPERATIONS_APLI_OPERATIONS_H
#define TEXT_FILE_OPERATIONS_APLI_OPERATIONS_H

#include <algorithm>
#include <set>

auto help(){
    auto info = " application for various operations on the contents of text files in ANSI format "
                "\nFlag -f or --file : passing a file, please enter the file path as the next argument"
                "\nFlag -n or --newlines: number of lines in the file"
                "\nFlag -d or --digits: number of digits in the file"
                "\nFlag -dd or --numbers: the number of real numbers in the file"
                "\nFlag -c or --chars: number of characters in the file"
                "\nFlag -w or --words: number of words in the file"
                "\nFlag -s or --sorted: sorted words in alphabetical order"
                "\nFlag -rs or --reverse-sorted: words sorted in reverse alphabetical order"
                "\nFlag -l or --by-length: modifies the behavior of the following -s or -rs flag"
                "\nFlag -a or --anagrams: displays all words from the source file which are anagrams of the words specified after this flag"
                "\nFlag -p or --palindromes: displays all words from the source file which are palindromes of the words specified after this flag"
                "\nFlag -i or --input: modifies the operation of the program in such a way that instead of specifying the rest of the flags as arguments to the call, the application gets the flags and data about them from the input file mentioned before"
                "\nFlag -fi or --find: looks for a word that contains the characters given as the next argument (it can be a word or a single character, no matter what order the characters are in)";
    return info;
}

/**
 * The function returns number of lines in the file
 * @param stream - ifstream - input file stream
 * @return counter - number of lines in the file
 */
auto lines_counter(std::ifstream& stream ){
    auto counter = 0;
    for ( auto line = std::string(); std::getline(stream, line); ){
        counter++;
    }
    return counter;
}

/**
 * The function returns number of digits in the file
 * @param stream - ifstream - input file stream
 * @return counter - number of digit numbers in the file
 */
auto numbers_counter( std::ifstream& stream ) {
    auto counter = 0;
    for (auto line = std::string(); std::getline(stream, line);) {
        for ( int i = 0; i < line.size(); i++ ) if( isdigit(line[i]) ) counter++;
    }
    return counter;
}
/**
 * The function returns number of real numbers in the file
 * @param stream - ifstream - input file stream
 * @return counter - number of real numbers in the file
 */
auto real_numbers_counter( std::ifstream& stream ){
    auto counter = 0;
    for (auto word = std::string(); stream >> word; ){
        auto is_number = false;
        for ( int i = 0; i < word.size(); i++ ) {
            if ( isdigit(word[i]) || word[i] == '.' || word[i] == ',' ) is_number = true;
            else {
                is_number = false;
                break;
            }
        }
        if( is_number ) counter++;
    }
    return counter;
}

/**
 * The function returns number of characters in the file
 * @param stream - ifstream - input file stream
 * @return number of character in file
 */
auto chars_counter( std::ifstream& stream ) {
    auto counter = 0;
    for (auto line = std::string(); std::getline(stream, line);)
        for( const char &c : line ){
            if ( c != ' ' ) counter++;
        }
    return counter;
}

/**
 * The function counts the number of words in the file
 * @param stream - ifstream - input file stream
 * @return number of words in file
 */
auto words_counter( std::ifstream& stream ) {
    auto counter = 0;
    for (auto word = std::string(); stream >> word; ++counter);
    return counter;
}

/**
 * The function outputs all words from the input file in alphabetical order,
 * if is_sorted_by_length is true then words are sorted by length first then alphabetically
 * @param stream - ifstream - input file stream
 * @param is_sorted_by_length - value of argument is true if flag -l or --by-length is found and false if the flag is not found
 * @param out - ostream - handling output stream
 */
auto sorted_words( std::ifstream& stream, const bool& is_sorted_by_length, std::ostream& out ){
    auto words_container = std::vector<std::string>();
    for (auto word = std::string(); stream >> word; ){
        words_container.push_back(word);
    }
    if ( is_sorted_by_length ) {
        std::sort(words_container.begin(), words_container.end(), []( const std::string& x, const std::string& y) {
            if( x.size() == y.size() ){
                return x < y;
            } else return x.size() < y.size(); });
    } else  std::sort(words_container.begin(), words_container.end(), []( const std::string& x, const std::string& y){return x < y;} );

    for ( auto &wrd : words_container ){
        out << wrd << ' ';
    }
}

/**
 * The function outputs all words from the input file in reverse alphabetical order,
 * if is_sorted_by_length is true then words are sorted by length first then alphabetically
 * @param stream - ifstream - input file stream
 * @param is_sorted_by_length - value of argument is true if flag -l or --by-length is found and false if the flag is not found
 * @param out - ostream - handling output stream
 */
auto reverse_sorted( std::ifstream& stream, const bool& is_sorted_by_length, std::ostream& out){
    auto words_container = std::vector<std::string>();
    for (auto word = std::string(); stream >> word; ){
        words_container.push_back(word);
    }
    if ( is_sorted_by_length ) {
        std::sort(words_container.begin(), words_container.end(), []( const std::string& x, const std::string& y) {
            if( x.size() == y.size() ){
                return x > y;
            } else return x.size() < y.size(); }); // mistake
    } else  std::sort(words_container.begin(), words_container.end(), []( const std::string& x, const std::string& y){return x > y;} );

    for ( auto& wrd : words_container ){
        out << wrd << ' ';
    }
}


/**
 * The function compares two words and returns true if they are anagrams, otherwise returns false
 * @param str1 - first word
 * @param str2 - second word
 * @return true if words are anagrams otherwise false
 */
auto are_anagrams( std::string str1, std::string str2 ){
    if (str1.length() != str2.length()) return false;
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    for (int i = 0; i < str2.length(); i++)
        if (str1[i] != str2[i])
            return false;
    return true;
}
/**
 * The function returns vectors of words that are anagrams and they are in input vector and in the file at the same time
 * @param input - vector of words entered as arguments after flag -a or --anagrams
 * @param source - ifstream - input file stream
 * @return a vector of words which are anagrams
 */
auto find_anagrams( const std::vector<std::string>& input, std::ifstream& source ){
    auto result = std::set<std::string>();
    for (auto word1 = std::string(); source >> word1; ){
        for ( auto& word2 : input ){
            if( are_anagrams(word1, word2) ){
                result.insert(word1);
            }
        }
    }
    return result;
}

/**
 * The function compares chars in the word and returns true if it's palindrome, otherwise false
 * @param str - any word
 * @return true if the word is a palindrome, otherwise false
 */
auto is_palindrome( const std::string& str ){
    for( int i=0; i < str.length(); i++)
        if(str[i] != str[str.length()-i-1])
            return false;
    return true;
}
/**
 * The function returns vectors of words that are palindromes and they are in input vector and in the file at the same time
 * @param input - vector of words entered as arguments after flag -p or --palindomes
 * @param source - ifstream - input file stream
 * @return a vector of words which are palindromes
 */
auto find_palindrome( const std::vector<std::string>& input, std::ifstream& source ){
    auto result = std::set<std::string>();
    for (auto word1 = std::string(); source >> word1; ){
        for ( auto& word2 : input ){
            if( is_palindrome(word1) && word1.compare(word2) == 0 ){
                result.insert(word1);
            }
        }
    }
    return result;
}

/**
 * The function searches words which contains of characters(or words) in the vector and outputs them
 * The result is independent of the order of the elements in the input vector
 * @param source - ifstream - input file stream
 * @param input - vector that consists of characters entered as arguments after flag -fi or --find.
 * @param out - ostream - handling output stream
 */
auto find_word( std::ifstream& source, const std::vector<std::string>& input, std::ostream& out ){
    for (auto word = std::string(); source >> word; ){
        int counter = 0;
        for ( auto& i : input ) {
            auto poz = word.find(i);
            if( poz != -1 ) counter++;
        }
        if( counter == input.size() ) out << word << ' ';
    }
}

#endif //TEXT_FILE_OPERATIONS_APLI_OPERATIONS_H