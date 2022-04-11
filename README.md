# text-file-operartions-c-project
application is used for various operations on the contents of text file
#
the program used for various operations on the contents of text files saved in ANSI format (ASCII characters only).
Supported operations include displaying the number of words in the file, displaying the number of numbers in the file, displaying the number of lines in the file, ordering the elements in the file or searching the contents of the file to find elements that meet given criteria.

The application should be run from the command line and, based on the flags passed to it, produce the appropriate text containing the required information.

Flag -f or --file : passing a file, please enter the file path as the next argument
Flag -n or --newlines: number of lines in the file
Flag -d or --digits: number of digits in the file
Flag -dd or --numbers: the number of real numbers in the file
Flag -c or --chars: number of characters in the file
Flag -w or --words: number of words in the file
Flag -s or --sorted: sorted words in alphabetical order
Flag -rs or --reverse-sorted: words sorted in reverse alphabetical order (reverse sorted)
Flag -l or --by-length: modifies the behavior of the following -s or -rs flag
Flag -a or --anagrams: displays all words from the source file which are anagrams of the words specified after this flag
Flag -p or --palindromes: displays all words from the source file which are palindromes of the words specified after this flag
Flag -i or --input: modifies the operation of the program in such a way that instead of specifying the rest of the flags as arguments to the call, the application gets the flags and data about them from the input file mentioned before
Flag -fi or --find: looks for a word that contains the characters given as the next argument (it can be a word or a single character, no matter what order the characters are in)
