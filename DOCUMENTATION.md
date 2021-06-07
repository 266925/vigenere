# Documentation

### What problems are you solving in this project?
Some of the problems I encountered were errors due to improper formatting of the text and key, invalid input when presented with menu choices, and the implementation of an array whose size is not known at compile time. If the user wants to use the 26x26 Vigenere table, the text and key must use uppercase alphabetic chars exclusively. The ASCII range of these values is 6510 to 9010. The valid range of ASCII values for the larger Vigenere Table is 3310 to 12610. Spaces must also be removed from the user text and key for both tables.



### What solutions are you implementing in the project?

To resolve errors from having invalid characters in the text and key, spaces from both strings are removed, then the text and key are converted to uppercase if the user is using the 26x26 Vigenere Table. Lowercase and uppercase characters are valid for the larger table. Then, both strings are checked for any characters outside the accepted range of ASCII values. If any are found, the user is notified and the characters are removed. In the event that the user only inputted invalid characters, a check is performed to make sure neither string is empty. A final check is performed on the user key’s length; If longer than the user text, it is trimmed. If shorter than the text, it is appended to itself until the length of the text and key are of equal length. For the array issue, I decided to declare 2 different Vigenere Tables locally in the main function.



### Provide an explanation of calculations and algorithm implementation.

The program algorithm was straightforward but not easy to implement. The process is identical when using the 26x26 or 93x93 array, just with different values for the valid range of valid ASCII codes. Because the Vigenere table is essentially a stack of caesar ciphers with different shift values, it was necessary to write a function to fill the array with the correct characters. With a nested for loop, the function iterates over every element in every row. For each element, the starting ASCII index is added to the sum of the row iterator modded by the sets cardinality and the column iterator modded by the cardinality of the set, modded by the set cardinality. Because the iterators for the outer and inner for loop are also used as the index locations for row and column, when the starting ASCII index is added on each iteration, the result is a character with a shift value of the current row index. Modular arithmetic is used on the set of valid symbols to get the appropriate shift for each row in the Vigenere Table. To verify, the table can be outputted to the console. This is commented out in the source code by default. After the tables are filled, the algorithm then decides between the encryption or decryption branch. When encrypting the user text, the algorithm iterates over each character in the user text. For each character, a lookup is performed on the Vigenere Table. The row index is represented by the difference between the ASCII value of the first character in the valid set of symbols and the current character in the user text. The row index is represented the same way but using the user key instead. The index of the user text and the key is represented by the iterator. For Decryption, the algorithm performs a linear search on the Vigenere Table, starting with the first element of each row before moving to the next column, testing to see if the current character at that location minus the set's cardinality is equal to that character in the text. If so, that char is then added to the decrypted text variable. Then the user's original text, original key, formatted text, formatted key, and transformed text is output to the console. The user is then prompted to run the program again.



### What are the program objectives? How is your program is interacting with the user and its purpose?

The objective of this program was fairly simple; to let the user input text to encrypt or decrypt using a chosen key, then show the output. Because I wanted to allow the user to select from two Vigenere Table sizes, it was essential to interact with the user several times to receive operating parameters. Based on the user's input, the program determines the appropriate method to transform the text using the key and correct Vigenere table. If the user enters invalid input the program attempts to resolve errors before exiting. Formatting is performed using modular arithmetic and the results are outputted to the console.



### How are discrete structures implemented in the C++ program?

Discrete Structures are implemented in this program by way of functions performing operations on discontinuous sets. For example, the valid members of alphabetic and alphanumeric sets. The symbols themselves are a subset of a larger group of printable ASCII characters. Discrete Structure concepts such as user-defined strings as containers, checking for members outside the set of valid symbols, modular arithmetic on integers representing the members of subsets, and the rules of the functions that modify them. Although the program itself does not contain probability analysis, it could be utilized to estimate the worst-case scenario when attempting to brute force the ciphertext.



### What are the limitations of the program?

One of the strengths of the Vigenere cipher is that it is resistant to frequency analysis due to the use of multiple ciphers with different shift values. A character won’t necessarily be substituted with the same symbol each time. Trying to brute force a standard Vigenere cipher is not an easy task, as the key adds a level of complexity making the number of possible cases equal to n to the K , where n is equal to the number of the valid set of symbols and k is equal to the length of the key. Although the key is a source of strength for the Vigenere cipher, it is also the source of its weakness due to its repetitive nature. If an individual were to guess the length of the key, then the ciphertext can be split into individual Caesar ciphers which are much easier to brute force. If the ciphertext expresses repetition, it is also expressed in the plaintext. Although the strength and weaknesses of the Vigenere cipher are relatively clear, the program itself has its own set of limitations. First, it is entirely possible that the program won’t run correctly due to invalid input or the code-breaking in some way. Second, declaring multiple containers but only utilizing one is inefficient.



### Provide recommendations on improving the limitations of the program.

Utilizing vectors or dynamic memory allocation could improve the program's simplicity and reduce overall lines of code. Classes could also be used. With a truly random key longer than the plaintext and only used once, it would become significantly more difficult to decrypt. External hardware could also be used as a vector of input for entropic data. Increasing the effective key length can be done by relatively prime key lengths and if the ciphertext is shorter than the effective key length the ciphertext becomes even more difficult to decode. The program itself could also be improved by removing the formatting functions and editing the transformation functions to only utilize the valid characters in a string while being able to account for the invalid ones.