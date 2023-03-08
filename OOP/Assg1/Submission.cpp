#include <iostream>
using namespace std;

/*char *removeSentence(char *Para, char *input) {
  char *storePara = Para;
  char *storeInput = input;
  int paraLen = 0;
  int inputLen = 0;
  int testCount = 0;
  // Storing the total size of the input to cross-check in the actual Paragraph
  while (*storeInput != '\0') {
    storeInput++;
    inputLen++;
  }
  while (*storePara != '\0') {
    storePara++;
    paraLen++;
  }
  storePara = Para;
  storeInput = Para;
  char *inputOrigin = input;
  while (testCount != inputLen) {
    inputOrigin = input;
    testCount = 0;
    while (*storeInput != *input)
      storeInput++;
    while (*storeInput == *inputOrigin) {
      inputOrigin++;
      storeInput++;
      testCount++;
    }
  }
  char *tempPara = new char[paraLen];
  for (int i = 0; i < paraLen; i++)
    *(tempPara + i) = *(Para + i);
  paraLen -= inputLen;
  for (int i = (storeInput - storePara - inputLen - 1); i < paraLen; i++) {
    *(tempPara + i) = *(tempPara + i + inputLen + 1);
  }
  *(tempPara + paraLen) = '\0';

  return tempPara;
}*/

/*bool FindSubString(char *Str, char *substr, int &start, int &end) {
  char *count = substr, *iterateStr = Str, *iterateSubStr = substr;
  while (*count != '\0')
    count++;
  int subStrLen = count - substr;
  count = Str;
  while (*count != '\0')
    count++;
  int strLen = count - Str, iteration = 0, trackStart = 0;
  count = NULL;
  bool subStrFound = false, findStr = false;
  while (*iterateStr != '\0') {
    iterateStr++;
    if (*iterateStr == *substr) {
      findStr = 1;
      start = iterateStr - Str;
      break;
    }
  }

  if (!findStr) {
    start = -1, end = -1;
    return 0;
  }

  while (*iterateStr != '\0') {
    trackStart = 0;
    while (*iterateStr == *iterateSubStr) {
      if (trackStart == 0)
        start = iterateStr - Str;
      if (*(iterateStr) == '\0' && iteration == 0) {
        iterateStr = Str;
        iteration++;
      }
      iterateStr++;
      iterateSubStr++;
      if (*iterateSubStr == '\0') {
        subStrFound = 1;
        end = iterateStr - Str - 1;
      }
      if (subStrFound)
        break;
      trackStart++;
      if (*iterateStr == '\0' && iteration == 0) {
        iterateStr = Str;
        iteration++;
      }
    }
    if (subStrFound)
      break;
    if (*(iterateStr) == '\0' && iteration == 0) {
      iterateStr = Str;
      iteration++;
    }
    iterateStr++;
    if (iteration == 0)
      iterateSubStr = substr;
  }

  if (!subStrFound) {
    start = -1, end = -1;
    return 0;
  }
  if (end > strLen) {
    end = end - start - 1;
  }
  return subStrFound;
}*/

// Q2, 50 MARKS. I LOVE THIS QUESTION!

/* char ***ConvertToDynamic(char arr[], int x, int y, int z) {
  // Allocating
  char ***fastIsTheBest = new char **[x];
  for (int i = 0; i < x; i++) {
    *(fastIsTheBest + i) = new char *[y];
    for (int j = 0; j < y; j++)
      *(*(fastIsTheBest + i) + j) = new char[z];
  }
  // Converting the elements to 3d form
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      for (int k = 0; k < z; k++) {
        if (k == z - 1) {
          // Z - 1th element in the final Z position will always be terminating
          // null.
          *(*(*(fastIsTheBest + i) + j) + k) = '\0';
          break;
        }
        *(*(*(fastIsTheBest + i) + j) + k) = *(arr++);
      }

  return fastIsTheBest;
}

bool checkLegality(int xSize, int ySize, int zSize, int x1, int y1, int z1,
                   int x2, int y2, int z2, int xDiff, int yDiff, int zDiff) {

  // Maximum page difference must be 1
  if (x1 < (x2 - 1) || x2 > (x1 + 1)) {
    return 0;
  }
  // Maximum row difference is also 1
  if (y1 < (y2 - 1) || y2 > (y1 + 1)) {
    return 0;
  }
  // MAXIMUM COL DIFFERENCE IS ALSO 1
  if (z1 < (z2 - 1) || z2 > (z1 + 1)) {
    return 0;
  }

  // To ensure that every successive element is traversed in the same direction.
  if (xDiff != (x2 - x1) || yDiff != (y2 - y1) || zDiff != (z2 - z1))
    return 0;
  return 1;
}
bool MatchString3DArray(char ***mat, int xSize, int ySize, int zSize,
                        char *input, int **&resultMat, int &colSize) {

  // Getting the column size of the input
  char *countInput = input;
  while (*countInput != '\0')
    countInput++;
  colSize = countInput - input;
  bool stringFound = false;

  bool charFound = false;

  char *traverseInput = input;
  int curChar = 0;

  bool atFinalIndex = 0;

  bool checkedFinalChar = 0;

  int TRACKDECREMENT = 1;

  int THISISTOITERATE = 0;
  int i = 0, j = 0, k = 0;
  int xInd = 0, yInd = 0, zInd = 0;
  // Storing the location of the first character in the input in the StoreInputs
  // array
  int *xLoc = new int[xSize * ySize * zSize];
  int *yLoc = new int[xSize * ySize * zSize];
  int *zLoc = new int[xSize * ySize * zSize];
  int xDiff, yDiff, zDiff;
  int numChars = 0;
  while (!stringFound) {
    atFinalIndex = false;
    charFound = false;
    for (i = xInd; i < xSize; i++, yInd = 0) {
      for (j = yInd; j < ySize; j++, zInd = 0) {
        for (k = zInd; k < zSize; k++) {
          if (mat[i][j][k] == *(traverseInput + curChar)) {
            {
              if (curChar > 0) {
                if (curChar == 1) {
                  xDiff = i - *(xLoc);
                  yDiff = j - *(yLoc);
                  zDiff = k - *(zLoc);
                }
                if (checkLegality(xSize, ySize, zSize, *(xLoc + curChar - 1), *(yLoc + curChar - 1),
                                  *(zLoc + curChar - 1), i, j, k, xDiff, yDiff, zDiff)) {
                  *(xLoc + curChar) = i;
                  *(yLoc + curChar) = j;
                  *(zLoc + curChar) = k;
                  curChar++;
                  charFound = true;
                }
              } else {
                *(xLoc) = i;
                *(yLoc) = j;
                *(zLoc) = k;
                curChar++;
                charFound = true;
              }
            }
          }
          if (k == zSize - 1 && j == ySize - 1 && i == xSize - 1)
            atFinalIndex = true;
          if (charFound)
            break;
        }
        if (charFound)
          break;
      }
      if (charFound)
        break;
    }
    THISISTOITERATE++;
    if (curChar == colSize) {
      int iteration = 0;
      for (int A = 0; A < colSize - 1; A++) {
        if (iteration == 0) {
          xDiff = *(xLoc + A + 1) - *(xLoc + A);
          yDiff = *(yLoc + A + 1) - *(yLoc + A);
          zDiff = *(zLoc + A + 1) - *(zLoc + A);
          iteration++;
        }
        if (checkLegality(xSize, ySize, zSize, *(xLoc + A), *(yLoc + A),
                          *(zLoc + A), *(xLoc + A + 1), *(yLoc + A + 1),
                          *(zLoc + A + 1), xDiff, yDiff, zDiff)) {
          stringFound = 1;
        } else {
          stringFound = 0;
        }
      }
    }
    if (stringFound) {

      resultMat = new int * [3];
      for (int i = 0; i < 3; i++)
        resultMat[i] = new int[colSize];
      // The row size will always be 3 since this is a 3d array.
      for (int B = 0; B < colSize; B++) {
        resultMat[0][B] = *(xLoc + B);
        resultMat[1][B] = *(yLoc + B);
        resultMat[2][B] = *(zLoc + B);
      }
      return 1;
    }
    if (THISISTOITERATE != curChar) {
      // IN THE CASE THAT THE FIRST INPUT CHARACTER ISN'T PRESENT IN THE ENTIRE
      // 3D ARRAY, THIS EVALUATES TRUE
      if (*(traverseInput + curChar) == *(input)) {
        colSize = -1;
        return 0;
      }
      // I HAVE NO IDEA WHEN THIS EVALUATES TRUE BUT IT SEEMS TO WORK
    }
    if (!stringFound && curChar == colSize && !atFinalIndex) {
      curChar -= TRACKDECREMENT - 1;
      xInd = *(xLoc + curChar);
      yInd = *(yLoc + curChar);
      zInd = *(zLoc + curChar);
    } else if (!stringFound && curChar == colSize && atFinalIndex) {
      curChar -= TRACKDECREMENT;
      TRACKDECREMENT--;
      xInd = *(xLoc + curChar);
      yInd = *(yLoc + curChar);
      zInd = *(zLoc + curChar);
      checkedFinalChar = 1;
    }
    else if (!stringFound && atFinalIndex)
    {
      curChar--;
      xInd = *(xLoc + curChar);
      yInd = *(yLoc + curChar);
      zInd = *(zLoc + curChar);
      if ((zInd + 1) <= zSize - 1)
        zInd++;
      else if ((yInd + 1) <= ySize - 1)
        yInd++;
      else if ((xInd + 1) < xSize - 1)
        xInd++;
      else
        break;

    }
    if (!stringFound && atFinalIndex && curChar < 0) {
      break;
    }
    if (THISISTOITERATE > colSize)
      THISISTOITERATE = 0;
  }
  colSize = -1;
  return 0;
}

void DeleteArray(char***& arr, int x, int y, int z)
{
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      delete[] arr[i][j];
    }
    delete[] arr[i];
  }
  delete[] arr;
  arr = NULL;
} */
// Q3 part 1, recursive perfect number (10 marks)

// Calculating the sum of every divisor of the number
/*int sumDivisors(int n, int i) {
  if (i == 1)
    return 1;
  if (i > 1) {
    if (n % i == 0)
      return i + sumDivisors(n, i - 1);
    return sumDivisors(n, i - 1);
  }
  return 0;
}

bool isperfectNumber(int n) {
  if (n <= 1)
    return 0;
  int sum = sumDivisors(n, n / 2);
  // If the number is prime, then it is not a perfect number.
  if ((n % sum == 0 && sum != 1))
    return 1;
  return 0;
}*/

// Q3 part 2, finding vowels (10 marks)

/* int findVowels(char *str) {
  if (*str == '\0')
    return 0;
  if (*str == 'a' || *str == 'e' || *str == 'o' || *str == 'u' || *str ==
'i') return 1 + findVowels(str + 1); return findVowels(str + 1);
} */

// Q3 part 3, pascal triangle

/*int pascal(int row, int col) {
  if (col > row || col < 0)
    return 0;
  if (row <= 1)
    return 1;
  return pascal(row - 1, col - 1) + pascal(row - 1, col);
}*/

// Q3 part 4, pattern printing

/* void printSpace(int n, int n2)
{
  if (n <= n2)
    return;
  printSpace(n - 1, n2);
  cout << "  ";
}

void printPat(int n, int max)
{
  if (n <= 0)
    return;
  printSpace(n - 1, n / 2);
  cout << '*' << endl;
  printPat(n - 2, max);

  if (max % 2 == 0)
  {
    printSpace(n, n / 2);
    if (n == max)
      return;
    cout << '*' << endl;
  }
  else
  {
    printSpace(n - 1, n / 2);
    cout << '*' << endl;
  }
}

void PrintPattern1(int start, int end)
{
  // Start is always gonna be one so I won't even bother

  printPat(end, end);
} */

// Q3 part 5, print diamond

void printSpaces(int n)
{
  if (n == 0)
    return;
  cout << ' ';
  printSpaces(n - 1);
}

void printStars(int n, int track)
{
  if (n == 0)
    return;
  cout << '*';
  printStars(n - 1, track);
}

void printDiamond(int n, int track)
{
  if (n <= 1)
    return;

  printStars(n - 1, track);
  printSpaces((track - n) * 2);
  printStars(n - 1, track);
  cout << '\n';

  printDiamond(n - 1, track);

  if (n >= 3)
    cout << '\n';
  printStars(n - 1, track);
  printSpaces((track - n) * 2);
  printStars(n - 1, track);
}

void printHollowDiamond(int n)
{
  printDiamond(n + 1, n + 1);
}

int main() {
  //  Q1: removeSentence, 10 marks
  /*char *para =
      "Helpdesk: There is an icon on your computer labeled My Computer.
  Double " "click on it. User: What's your computer doing on mine?"; char
  *remove = "Double click on it."; char *tempPara = removeSentence(para,
  remove); cout
  << tempPara; delete[] tempPara;

  // Q1 part 2: Find substring, 10 marks

  char *Str = "affects";
  char *substr = "sad";
  int start = 0, end = 0;
  cout << FindSubString(Str, substr, start, end);
  cout << "\nstart: " << start << "\nend: " << end;*/

  // Q2: Dynamic 3d Array matching, 50 marks

  /*char arr[28] = "sbtaicztieahrnltagtsjvehfyf";
  char ***mat = ConvertToDynamic(arr, 3, 3, 4);
  int **res, col;
  cout << MatchString3DArray(mat, 3, 3, 4, "tag", res, col);*/

  // Q3, perfect number

  // cout << isperfectNumer(496);

  // Q3 part 2, finding vowels:

  /*char* input = "rm -rf /osama/bin/laden";
  cout << findVowels(input);*/

  // Q3 part 3, pascal triangle

  // cout << pascal(5, 3);

  // Q3 part 4, pattern

  // PrintPattern1(1, 13);

  // Q3 part 5, hollow diamond

  printHollowDiamond(11);
}
