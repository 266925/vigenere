#include <iostream>

#include <algorithm>

using namespace std;

string getText();
string getKey();
string formatText(string, int);
string formatKey(string, string, int);
int getColumns();
int getTransform();
void fillSmall(char[][26]);
void fillLarge(char[][95]);
void transformSmall(string, string, string, int, char[][26]);
void transformLarge(string, string, string, int, char[][95]);

int main() {

  int transformChoice, matrixSize, runAgain; // User variables
  string userText, userKey, originalKey;

  char vSmall[26][26]; // Declare matrices
  char vLarge[95][95];

  fillSmall(vSmall); //Fill matrices
  fillLarge(vLarge);

  do { //Main Menu

    // Get user information
    transformChoice = getTransform();
    userText = getText();
    userKey = getKey();
    matrixSize = getColumns();

    // Format accordingly
    originalKey = userKey;
    userText = formatText(userText, matrixSize);
    userKey = formatKey(userKey, userText, matrixSize);

    if (matrixSize == 26) { // Transform text according to user selection and matrix size
      transformSmall(userText, userKey, originalKey, transformChoice, vSmall);
    } else if (matrixSize == 95) {
      transformLarge(userText, userKey, originalKey, transformChoice, vLarge);
    }

    cout << "\nRun again? "; // Prompt user to run again
    cin >> runAgain;

  } while (runAgain != 0);

}

string getText() //Get user text
{
  string text;
  cin.ignore();
  cout << "\nInput TEXT: ";
  getline(cin, text);
  if (text.length() < 1) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return text;
}

string getKey() //Get the user key 
{
  string key;
  cout << "Input KEY : ";
  getline(cin, key);
  if (key.length() < 1) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return key;
}

int getColumns() //Get matrix size
{
  int columns;
  cout << "\n1. Small Vigenere (26x26)\n" <<
    "2. Large Vigenere (95x95)\n";
  cin >> columns;
  if (columns == 1) {
    return 26;
  } else if (columns == 2) {
    return 95;
  } else {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
}

int getTransform() //Get the transform choice
{
  int choice;
  cout << "\nInput Choice Number\n1. Encryption\n2. Decryption\n";
  cin >> choice;
  if (choice != 1 && choice != 2) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return choice;
}

string formatText(string text, int size) {
  /* 
    If the user is using the small matrix, we will force the text to UPPERCASE
    and remove characters outside that range. We will do the same for the 
    expanded range of the larger matrix. A check at the end of the function 
    checks to make sure the text is not empty. 
  */

  if (size == 26) {
    cout << "\nForcing uppercase letters in the TEXT..";
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    for (int i = 0; i < text.size(); i++) {
      if (text[i] < (char) 65 || text[i] > (char) 90) {
        cout << "\nInvalid character found in TEXT! Removing [" << text[i] << "]...";
        text.erase(i, 1);
        i--;
      }
    }

  } else if (size == 95) {
    for (int i = 0; i < text.size(); i++) {
      if ((text[i] < (char) 32 || text[i] > (char) 127)) {
        cout << "\nInvalid character found in TEXT! Removing [" << text[i] << "]...";
        text.erase(i, 1);
        i--;
      }
    }

  }
  if (text.length() < 1) {
    cout << "\nText is NULL after format. Please enter at least 1 VALID character.";
    exit(1);
  }
  return text;
}

string formatKey(string key, string text, int tableSize) 
{
  /* If the user is using the small matrix, the key is forced to UPPERCASE
    and any characters outside that range are removed. If the user is using
    the large matrix, case is preserved but characters outside the range of 
    (33-127) are removed. Then the key is resized to be of equal length to 
    the user text.
  */

  int textSize = text.size();

  if (tableSize == 26) {

    cout << "\nForcing uppercase letters in the KEY..";
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    for (int i = 0; i < key.size(); i++) {
      if (key[i] < (char) 65 || key[i] > (char) 90) {
        cout << "\nInvalid character found in KEY! Removing [" << key[i] << "]...";
        key.erase(i, 1);
        i--;
      }
    }
    cout << endl;
    if (key.length() < 1) {
      cout << "\nKey is NULL after format. Please enter at least 1 VALID character.\n";
      exit(1);
    }
  }

  string newKey = key; //Copy the original key

  if (newKey.size() < textSize) { //Resize Case 1: too small
    
    for (int newKeyIndex = key.size(), oldKeyIndex = 0; newKeyIndex < textSize; newKeyIndex++, oldKeyIndex++) {
      newKey += newKey[oldKeyIndex % key.size()]; //Append the key to itself
    }
  } else if (newKey.size() > textSize) { //Resize Case 2: too large
    cout << "\nKey is too long. Trimming the key...\n";
    newKey.resize(textSize);
  } else { //Resize Case 3: just right
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

void fillLarge(char vLarge[][95]){

  /* 
    Fills the large Vigenere table (95x95) with appropiate values
    from the set of useable characters. All cases, numbeers and 
    most symbols are used. Remove comment tags at the end of the 
    function to display the table as it is filled. 
  */

  for (int row = 0; row < 95; row++) {
    for (int col = 0; col < 95; col++) {
      vLarge[row][col] = 32 + (row + col) % 95;
      //cout << vLarge[row][col] << " ";
    }
    //cout << endl;
  }

}

void transformSmall(string text, string key, string org, int choice, char vSmall[][26]){

  /*
    This function utilizes the smaller Vigenere 2D array to encrypt or decrypt the user text.
    
    For ENCRYPTION, Variables to hold the transformed text are declared and the ASCII starting index 
    (65 or 'A') is set. When the lookup is performed, the row index is represented by the 
    first characters ASCII code in the working set 
    of uppercase letters subtracted from the ASCII code of the current character in the users
    text. The columns are represented indentically but using the key instead of the text. The
    character in the 2D Vigenere array at those indices is the appended to the encrypted text
    varaible.  

    For DECRYPTION, 
  */

  string encryptedText, decryptedText;
  int ASCII_INDEX = 65;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vSmall[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }

    cout << "\nOriginal_Text:   " << text;
    cout << "\nEncrypted_Text:  " << encryptedText;
    cout << "\nFormatted_Key:   " << key;
    cout << "\nOriginal_Key:    " << org << endl;

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

    cout << "\nOriginal_Text:   " << text;
    cout << "\nDecrypted_Text:  " << decryptedText << endl;
    cout << "\nFormatted_Key:   " << key;
    cout << "\nOriginal_Key:    " << org << endl;
  } else {
    exit(1);
  }

}

void transformLarge(string text, string key, string org, int choice, char vLarge[][95]) //Tranform (95x95)
{

  string encryptedText, decryptedText;
  int ASCII_INDEX = 32;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vLarge[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }

    cout << "\nOriginal_Text:   " << text;
    cout << "\nEncrypted_Text:  " << encryptedText;
    cout << "\nFormatted_Key:   " << key;
    cout << "\nOriginal_Key:    " << org << endl;

  } else if (choice == 2) {

    for (int i = 0; i < text.size(); i++) {
      for (int j = 0; j < 95; j++) {
        if (vLarge[j][key[i] - (char) ASCII_INDEX] == text[i]) {
          decryptedText += (char) ASCII_INDEX + j;
        }
      }
    }

    cout << "\nOriginal_Text:   " << text;
    cout << "\nDecrypted_Text:  " << decryptedText << endl;
    cout << "\nFormatted_Key:   " << key;
    cout << "\nOriginal_Key:    " << org << endl;
  } else {
    exit(1);
  }

}