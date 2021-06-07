# Pseudocode
DECLARE libraries

DECLARE functions to get AND manipulate user data
    string getText
    string getKey
    string formatText
    string formatKey
    int getColumns
    int getTransform
    void fillSmall
    void fillLarge
    void transformSmall
    void transformLarge
    void outputResults

ENTER MAIN

DECLARE variables

    transformChoice
    vigenereSize
    runProgramAgain
    userText
    userKey
    formattedKey
    formattedText

DECLARE Vigenere tables
    vSmall[26][26]
    vLarge[93][93]

CALL FUNCTION fillSmall 
    FOR EACH row
        FOR EACH column
            each element is equal to the sum of 65 and both iterators modded by 26

CALL FUNCTION fillLarge 
    FOR EACH row
        FOR EACH column
            each element is equal to the sum of 33 and both iterators modded by 26

DO

CALL FUNCTION getColumns

    DECLARE variables
    prompt user for Vigenere size
    store input

    IF user chose first option 
        RETURN size as 26x26

    ELSE IF user chose second option
        RETURN size as 93x93

    ELSE 
        EXIT PROGRAM

CALL FUNCTION getTransform 

     DECLARE variables
     prompt the user for Encryption or Decryption
     store the input

     IF input is invalid
       EXIT PROGRAM
     ELSE
        RETURN choice 

CALL FUNCTION getText 

    DECLARE variable
    prompt user for the text
    store input

    IF input is invalid
        EXIT PROGRAM
    ELSE 
        RETURN text

CALL FUNCTION getKey 

    DECLARE variable
    prompt user for key
    store input

    IF input is invalid
        EXIT PROGRAM
    ELSE 
        RETURN key

CALL FUNCTION formattedText 

    remove spaces in text using erase
    IF small vigenere = true
        force uppercase of the user text
        remove any chars outside the range of valid values

    ELSE IF large vigenere = true
        remove chars outside the valid range of values

    IF text is empty
        EXIT PROGRAM

    ELSE
        RETURN text

CALL FUNCTION formattedKey

    DECLARE local variables
    FOR each character in the key
        remove spaces
    IF small vigenere = true
        FOR each character in the key
            force uppercase

    FOR each character in the key
        remove chars outside valid range
        OUTPUT removed char

    IF key is empty
     EXIT PROGRAM

    make a copy of the key to use for comparisons

    IF key is smaller than the users text
        append the key to itself until it is of equal length
    
    ELSE IF key is longer than the users text
        trim the key by using the resize function

    ELSE
        RETURN key

CALL FUNCTION outputResults

    OUTPUT original text and key
    OUTPUT formatted text and key

IF small vigenere = true

    CALL FUNCTION transformSmall 
    DECLARE variables to hold encrypted or decrypted text
    set the ASCII starting index to 65 ('A')

    IF user wanted to ENCRYPT
        FOR each character in the user text
            encrypt the text by representing table indices
            the row index as each text char minus 65
            the column index each as each key char minus 65

        OUTPUT encrypted text

    ELSE IF user wanted DECRYPT
        FOR each character in the text
            FOR each character in each column of the vigenere table
                IF current index minus 65 is equal to the current char in the text
                    add that character to the decrypted string variable

        OUTPUT decrypted text
    ELSE 
        EXIT PROGRAM



ELSE IF large vigenere = true

    CALL FUNCTION transformLarge 
    DECLARE variables to hold encrypted or decrypted text
    set the ASCII starting index to 33 ('!')

    IF user wanted to ENCRYPT
        FOR each character in the user text
            encrypt the text by representing table indices
            the row index as each text char minus 33
            the column index each as each key char minus 33
        OUTPUT encrypted text

    ELSE IF user wanted DECRYPT
        FOR each character in the text
            FOR each character in each column of the vigenere table

                IF current index minus 65 is equal to the current char in the text
                    add that character to the decrypted string variable

        OUTPUT decrypted text
    ELSE 
        EXIT PROGRAM

prompt user to run program again
    WHILE runAgain = true