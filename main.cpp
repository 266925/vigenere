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

  int transformChoice, matrixSize, runAgain;
  string userText, userKey, originalKey;

  char vSmall[26][26];
  char vLarge[95][95];

  fillSmall(vSmall);
  fillLarge(vLarge);

  do {
    transformChoice = getTransform();
    userText = getText();
    userKey = getKey();
    matrixSize = getColumns();

    originalKey = userKey;
    userText = formatText(userText, matrixSize);
    userKey = formatKey(userKey, userText, matrixSize);

    if (matrixSize == 26) {
      transformSmall(userText, userKey, originalKey, transformChoice, vSmall);
    } else if (matrixSize == 95) {
      transformLarge(userText, userKey, originalKey, transformChoice, vLarge);
    }

    cout << "\nRun again? ";
    cin >> runAgain;

  } while (runAgain != 0);

}

string getText() {
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

string getKey() {
  string key;
  cout << "Input KEY : ";
  getline(cin, key);
  if (key.length() < 1) {
    cout << "\nINVALID INPUT\n";
    exit(1);
  }
  return key;
}

int getColumns() {
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

int getTransform() {
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
    cout << endl;

  } else if (size == 95) {

    for (int i = 0; i < text.size(); i++) {

      if ((text[i] < (char) 32 || text[i] > (char) 127)) {
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

string formatKey(string key, string text, int tableSize) {

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

  string newKey = key;

  if (newKey.size() < textSize) {
    for (int newKeyIndex = key.size(), oldKeyIndex = 0; newKeyIndex < textSize; newKeyIndex++, oldKeyIndex++) {
    newKey += newKey[oldKeyIndex % key.size()];
    }
  } else if (newKey.size() > textSize) {
    cout << "\nKey is too long. Trimming the key...\n";
    newKey.resize(textSize);
  } else {
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

void fillLarge(char vLarge[][95]) {
  for (int row = 0; row < 95; row++) {
    for (int col = 0; col < 95; col++) {
      vLarge[row][col] = 32 + (row + col) % 95;
      //cout << vLarge[row][col] << " ";
    }
    //cout << endl;
  }

}

void transformSmall(string text, string key, string org, int choice, char vSmall[][26]) {
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

void transformLarge(string text, string key, string org, int choice, char vLarge[][95]) {

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

//Test commit..