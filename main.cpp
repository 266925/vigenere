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
  //Local variables
  int transformChoice, matrixSize, runAgain;
  string formattedText, formattedKey, originalText, originalKey;
  
  //Declare sarrays
  char vSmall[26][26]; 
  char vLarge[93][93];

  //Fill arrays
  fillSmall(vSmall); 
  fillLarge(vLarge);

  do { 

    //Get user information
    matrixSize = getColumns();
    transformChoice = getTransform();
    originalText = getText();
    originalKey = getKey();

    //Format text and key
    formattedText = formatText(originalText, matrixSize);
    formattedKey = formatKey(originalKey, formattedText, matrixSize);

    //Output user input
    outputResults(originalText, originalKey, formattedText, formattedKey);

    //Transform
    if (matrixSize == 26) { 
      transformSmall(formattedText, formattedKey, transformChoice, vSmall);
    } else if (matrixSize == 93) {
      transformLarge(formattedText, formattedKey, transformChoice, vLarge);
    }

    //Prompt user to run  again
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

  //Remove Spaces from TEXT
  cout << "\nRemoving spaces from the TEXT...";
  text.erase(std::remove_if(text.begin(), text.end(), ::isspace), text.end());

  if (size == 26) {
    //Force UPPERCASE of TEXT
    cout << "\nForcing uppercase letters in the TEXT...";
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    for (int i = 0; i < text.size(); i++) {
      //Remove characters outside ASCII range (small)
      if (text[i] < (char) 65 || text[i] > (char) 90) {
        cout << "\nInvalid character found in TEXT! Removing [" << text[i] << "]...";
        text.erase(i, 1);
        i--;
      }
    }

  } else if (size == 93) {
    for (int i = 0; i < text.size(); i++) {
      //Remove characters outside ASCII range (large)
      if ((text[i] < (char) 33 || text[i] > (char) 126)) {
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

  int textSize = text.size();

  //Remove spaces from key
  cout << "\nRemoving spaces from the KEY...";
  key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

  if (tableSize == 26) {
    //Force key to uppercase
    cout << "\nForcing uppercase letters in the KEY...";
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    for (int i = 0; i < key.size(); i++) {
            //Remove characters outside ASCII range (small)
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

  //Copy key
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

  for (int row = 0; row < 26; row++) {
    for (int col = 0; col < 26; col++) {
      vSmall[row][col] = 65 + (row + col) % 26;
      //cout << vSmall[row][col] << " ";
    } //cout << endl;
  }

}

void fillLarge(char vLarge[][93]){

  for (int row = 0; row < 93; row++) {
    for (int col = 0; col < 93; col++) {
      vLarge[row][col] = 33 + (row + col) % 93;
      //cout << vLarge[row][col] << " ";
    }
    //cout << endl;
  }

}

void outputResults(string orgT, string orgK, string textF, string keyF){
cout << "\n\nOriginal Text : " << orgT <<
        "\nOriginal Key  : " << orgK << 
        "\n\nFormatted Text: " << textF <<
        "\nFormatted Key : " << keyF << 
        endl;

}

void transformSmall(string text, string key, int choice, char vSmall[][26]){

  string encryptedText, decryptedText;
  int ASCII_INDEX = 65;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vSmall[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }
    
    cout << "\nEncrypted Text: " << encryptedText << endl;

  } else if (choice == 2) {

    for (int col = 0; col < text.size(); col++) { 
      for (int row = 0; row < 26; row++) { 
        if (vSmall[row][key[col] - (char) ASCII_INDEX] == text[col]) { 
          decryptedText += (char) ASCII_INDEX + row;  
    
        }
      }
    }
    cout << "\nDecrypted Text: " << decryptedText << endl;
  } else {
    exit(1);
  }

}

void transformLarge(string text, string key, int choice, char vLarge[][93]){

  string encryptedText, decryptedText;
  int ASCII_INDEX = 33;

  if (choice == 1) {

    for (int i = 0; i < text.size(); i++) {
      encryptedText += vLarge[text[i] - (char) ASCII_INDEX][key[i] - (char) ASCII_INDEX];
    }
    cout << "Encrypted Text: " << encryptedText << endl;

  } else if (choice == 2) {

    for (int col = 0; col < text.size(); col++) {
      for (int row = 0; row < 93; row++) {
        if (vLarge[row][key[col] - (char) ASCII_INDEX] == text[col]) {
          decryptedText += (char) ASCII_INDEX + row;
        }
      }
    }
    cout << "Decrypted Text: " << decryptedText << endl;
  } else {
    exit(1);
  }

}

