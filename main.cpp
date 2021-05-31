#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string getText();
string getKey();
string formatText(string, int);
string formatKey(string, string, int);
int getColumns();
int getTransform();
void fillSmall(char[][26]);
void fillLarge(char[][93]);
void transformSmall(string, string, int, char[][26]);
void transformLarge(string, string, int, char[][93]);
void outputResults(string, string, string, string);

int main(){
  //Local variables to hold user information and menu choices
  int transformChoice, matrixSize, runAgain;
  string formattedText, formattedKey, originalText, originalKey;
  
  //Declare small and large arrays to represent a Vigenere Table
  char vSmall[26][26]; 
  char vLarge[93][93];

  //Fill the large and small arrays with values
  fillSmall(vSmall); 
  fillLarge(vLarge);

  do { 

    //Get user information
    matrixSize = getColumns();
    transformChoice = getTransform();
    originalText = getText();
    originalKey = getKey();

    //Store the formatted text and key in new variables 
    formattedText = formatText(originalText, matrixSize);
    formattedKey = formatKey(originalKey, formattedText, matrixSize);

    //Output user input before and after formatting
    outputResults(originalText, originalKey, formattedText, formattedKey);

    //Transform the text according to the user's Vigenere selection
    if (matrixSize == 26) { 
      transformSmall(formattedText, formattedKey, transformChoice, vSmall);
    } else if (matrixSize == 93) {
      transformLarge(formattedText, formattedKey, transformChoice, vLarge);
    }

    //Prompt user to run the program again
    std::cout << "\nRun again?\n1. Yes\n2. No\n"; 
    cin >> runAgain;
  } while (runAgain != 2);

}

string getText(){
  string text;
  cin.ignore();
  cout << "\nInput your TEXT: ";
  getline(cin, text);
  if (text.length() < 1) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return text;
}

string getKey(){
  string key;
  cout << "Input your KEY : ";
  getline(cin, key);
  if (key.length() < 1) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return key;
}

int getColumns(){
  int columns;
  cout << "\nInput Selection Number\n1. Small Vigenere (26x26)\n" <<
    "2. Large Vigenere (93x93)\n";
  cin >> columns;
  if (columns == 1) {
    return 26;
  } else if (columns == 2) {
    return 93;
  } else {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
}

int getTransform(){
  int choice;
  cout << "\nInput Selection Number\n1. Encryption\n2. Decryption\n";
  cin >> choice;
  if (choice != 1 && choice != 2) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return choice;
}

string formatText(string text, int size) {
  /* 
    Function removes spaces from the text.

    If the user is using the 26x26 Vigenere Table,
    remove any characters outside the accepted
    ASCII range.
    
    If the user is using the 93x93 Vigenere Table,
    preserve case but also continue to remove any
    characters outside the accepted ASCII range.

    If any invalid characters are found, the user
    is notified and each removed character is 
    outputted to the terminal. 
  */

  //Remove Spaces from TEXT
  cout << "\nRemoving spaces from the TEXT...";
  text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());

  if (size == 26) {
    //Force UPPERCASE
    cout << "\nForcing uppercase letters in the TEXT...";
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    for (int i = 0; i < text.size(); i++) {
      //Remove characters outside ASCII range
      if (text[i] < (char) 65 || text[i] > (char) 90) {
        cout << "\nInvalid character found in TEXT! Removing [" << text[i] << "]...";
        text.erase(i, 1);
        i--;
      }
    }

  } else if (size == 93) {
    for (int i = 0; i < text.size(); i++) {
      //Remove characters outside ASCII range
      if ((text[i] < (char) 33 || text[i] > (char) 126)) {
        cout << "\nInvalid character found in TEXT! Removing [" << text[i] << "]...";
        text.erase(i, 1);
        i--;
      }
      
    }
      
  }
  //If the user entered invalid characters exclusivley
  if (text.length() < 1) {
    cout << "\nText is NULL after format. Please enter at least 1 VALID character.";
    exit(1);
  }
  return text;
}

string formatKey(string key, string text, int tableSize) 
{
  /* 
    Function behaves identically to formatText function.

    Additionally, if the key is too long, it is trimmed 
    until of equal length to the user inputted text.
  */

  int textSize = text.size();

  //Remove Spaces from KEY
  cout << "\nRemoving spaces from the KEY...";
  key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

  if (tableSize == 26) {
    //Force UPPERCASE
    cout << "\nForcing uppercase letters in the KEY...";
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    for (int i = 0; i < key.size(); i++) {
      //Remove invalid characters
      if (key[i] < (char) 65 || key[i] > (char) 90) {
        cout << "\nInvalid character found in KEY! Removing [" << key[i] << "]...";
        key.erase(i, 1);
        i--;
      }
    }
    cout << endl;
    if (key.length() < 1) {
      //If the user entered invalid characters exclusivley
      cout << "\nKey is NULL after format. Please enter at least 1 VALID character.\n";
      exit(1);
    }
  }

  //Copy the original key for comparisons
  string newKey = key; 

  //If the key is not long enough
  if (newKey.size() < textSize) { 
    for (int newKeyIndex = key.size(), oldKeyIndex = 0; newKeyIndex < textSize; newKeyIndex++, oldKeyIndex++) {
      //Append the key to itself
      newKey += newKey[oldKeyIndex % key.size()];
    }
    //If the key is too long
  } else if (newKey.size() > textSize) {
    cout << "\nKey is too long. Trimming the key...";
    //Trim the key's length
    newKey.resize(textSize);
  }//If the key does NOT need to be resized 
  else{ 
    return newKey;
  }
  return newKey;
}

void fillSmall(char vSmall[][26]) {
  /* 
    Fills the small Vigenere table (26x26) with appropiate values
    from the set of useable characters. Uppercase letters are used
    exclusivley. Remove comment tags at the end of the function to
    display the table as it is filled. 
  */

  for (int row = 0; row < 26; row++) {
    for (int col = 0; col < 26; col++) {
      vSmall[row][col] = 65 + (row + col) % 26;
      //cout << vSmall[row][col] << " ";
    } //cout << endl;
  }

}

void fillLarge(char vLarge[][93]){

  /* 
    Fills the large Vigenere table (93x93) with appropiate values
    from the set of useable characters. Both cases, numbers and 
    most symbols are used. Remove comment tags at the end of the 
    function to display the table as it is filled. 
  */

  for (int row = 0; row < 93; row++) {
    for (int col = 0; col < 93; col++) {
      vLarge[row][col] = 33 + (row + col) % 93;
      //cout << vLarge[row][col] << " ";
    }
    //cout << endl;
  }

}

void outputResults(string orgT, string orgK, string textF, string keyF){

//Outputs the original text and key, then the formatted text and key.
cout << "\n\nOriginal Text : " << orgT <<
        "\nOriginal Key  : " << orgK << 
        "\n\nFormatted Text: " << textF <<
        "\nFormatted Key : " << keyF << 
        endl;

}

void transformSmall(string text, string key, int choice, char vSmall[][26]){

  /*
    This function utilizes the smaller Vigenere 2D array to encrypt or decrypt the user text.
    
    For ENCRYPTION, Variables to hold the transformed text are declared and the ASCII starting index 
    (65 or 'A') is set. When the lookup is performed, the row index is represented by the 
    first characters ASCII code in the working set of uppercase letters subtracted from the 
    ASCII code of the current character in the users text. The columns are represented 
    indentically but using the key instead of the text. The character in the 2D Vigenere 
    array at those indices is then appended to the encrypted text varaible.  

    For DECRYPTION, a lookup is performed on the generated Vigenere Table to determine the 
    decryptedcharactyer.

  */

  string encryptedText, decryptedText;
  int ASCII_INDEX = 65;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vSmall[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }
    
    cout << "\nEncrypted Text: " << encryptedText << endl;


  } else if (choice == 2) {

    for (int i = 0; i < text.size(); i++) { 
      for (int j = 0; j < 26; j++) { 
        if (vSmall[j][key[i] - (char) ASCII_INDEX] == text[i]) { 
          decryptedText += (char) ASCII_INDEX + j;  
          /*
          For each character in the key, the function iterates through each row in the vigenere table and checks to see if the 
          difference of the character at that location minus the starting ASCII index is equal to the current index of the text.
          If this is the case, 
          */
        }
      }
    }
    cout << "\nDecrypted Text: " << decryptedText << endl;
  } else {
    exit(1);
  }

}

void transformLarge(string text, string key, int choice, char vLarge[][93]){

  /*
    Function behaves identically to the transformSmall function, just with 
    expanded ranges for valid character ASCII codes. (Decimal 33-126)
  */

  string encryptedText, decryptedText;
  int ASCII_INDEX = 33;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vLarge[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }
    cout << "Encrypted Text: " << encryptedText << endl;

  } else if (choice == 2) {

    for (int i = 0; i < text.size(); i++) {
      for (int j = 0; j < 93; j++) {
        if (vLarge[j][key[i] - (char) ASCII_INDEX] == text[i]) {
          decryptedText += (char) ASCII_INDEX + j;
        }
      }
    }
    cout << "Decrypted Text: " << decryptedText << endl;
  } else {
    exit(1);
  }

}

