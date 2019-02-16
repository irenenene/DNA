//main.cpp
//DONT FORGET TO OUTPUT THE PROBABILITY OF BIGRAMS
//BIGRAM DIVIDED BY TOTALSUM / 2
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>


using namespace std;

string sanitize(string);

int main(int argc, char *argv[])
{
  string fileName = "";
  fileName = argv[1];
  ifstream inputFile;

  int totalSum = 0;
  int totalLines = 0;

  double mean = 0;
  double varianceTop = 0;
  double variance = 0;
  double stdDev = 0;

  int acount = 0;
  int ccount = 0;
  int tcount = 0;
  int gcount = 0;

  double aprob = 0;
  double cprob = 0;
  double tprob = 0;
  double gprob = 0;

  int countAA = 0;
  int countAC = 0;
  int countAT = 0;
  int countAG = 0;
  int countCA = 0;
  int countCC = 0;
  int countCT = 0;
  int countCG = 0;
  int countTA = 0;
  int countTC = 0;
  int countTT = 0;
  int countTG = 0;
  int countGA = 0;
  int countGC = 0;
  int countGT = 0;
  int countGG = 0;

  const double pi = 3.1415926535897;
  srand(time(NULL));


  inputFile.open(fileName);
  if (inputFile.is_open())
  {
    string line;

    while (getline(inputFile, line))
    {
      totalLines++;

      line = sanitize(line);

      for (int i = 0; i < line.length(); i++)
      {
        switch(line.at(i))
        {
          case 'a':
            acount++;
            break;
          case 'c':
            ccount++;
            break;
          case 't':
            tcount++;
            break;
          case 'g':
            gcount++;
            break;
        }

        if(i % 2 == 0)
        {
          if(line.at(i) == 'a')
          {
            if(line.at(i+1) == 'a')
            {
              countAA++;
            }
            if(line.at(i+1) == 'c')
            {
              countAC++;
            }
            if(line.at(i+1) == 't')
            {
              countAT++;
            }
            if(line.at(i+1) == 'g')
            {
              countAG++;
            }
          }
          else if(line.at(i) == 'c')
          {
            if(line.at(i+1) == 'a')
            {
              countCA++;
            }
            if(line.at(i+1) == 'c')
            {
              countCC++;
            }
            if(line.at(i+1) == 't')
            {
              countCT++;
            }
            if(line.at(i+1) == 'g')
            {
              countCG++;
            }
          }
          else if(line.at(i) == 't')
          {
            if(line.at(i+1) == 'a')
            {
              countTA++;
            }
            if(line.at(i+1) == 'c')
            {
              countTC++;
            }
            if(line.at(i+1) == 't')
            {
              countTT++;
            }
            if(line.at(i+1) == 'g')
            {
              countTG++;
            }
          }
          else if(line.at(i) == 'g')
          {
            if(line.at(i+1) == 'a')
            {
              countGA++;
            }
            if(line.at(i+1) == 'c')
            {
              countGC++;
            }
            if(line.at(i+1) == 't')
            {
              countGT++;
            }
            if(line.at(i+1) == 'g')
            {
              countGG++;
            }
          }
          else
          {
            cout << "hmm" << endl;
          }
        }
      }

      cout << line << endl;

      totalSum = acount + ccount + tcount + gcount;
      mean = double(totalSum) / double(totalLines);


    }

    aprob = double(acount) / totalSum;
    cprob = double(ccount) / totalSum;
    tprob = double(tcount) / totalSum;
    gprob = double(gcount) / totalSum;

    cout << aprob << " " << cprob << " " << tprob << " " << gprob << endl;

    inputFile.clear();
    inputFile.seekg(0, ios::beg);


    while (getline(inputFile, line))
    {
      double difference = 0;
      difference = (line.length() - 1) - mean;
      varianceTop += (difference * difference);

    }



    variance = (varianceTop / totalLines);
    stdDev = sqrt(variance);

    cout << "Variance: " << variance << endl;
    cout << "Standard Deviation: " << stdDev << endl;

    cout << totalSum << " " << mean << endl;

    cout << acount << " " << ccount << " " << tcount << " " << gcount << endl;
    cout << "Bigram count: " << endl;
    cout << countAA << " " << countAC << " " << countAT << " " << countAG << endl;
    cout << countCA << " " << countCC << " " << countCT << " " << countCG << endl;
    cout << countTA << " " << countTC << " " << countTT << " " << countTG << endl;
    cout << countGA << " " << countGC << " " << countGT << " " << countGG << endl;

    for ( int n = 0; n < 10; n++)
    {
      double aValue = rand() / (RAND_MAX + 1.0);
      double bValue = rand() / (RAND_MAX + 1.0);
      double cValue = sqrt(-2 * log(aValue)) * cos(2 * pi * bValue);
      double dValue = (stdDev * cValue) + mean;
      int length = int(dValue);

      if (length % 2 != 0)
      {
        length++;
      }

      string newDNA = "";

      for (int i = 0; i < length; i++)
      {
        double rando = rand() / double(RAND_MAX);

        if (rando < (aprob))
        {
          newDNA += 'a';
        }
        else if(rando < (aprob + cprob))
        {
          newDNA += 'c';
        }
        else if(rando < (aprob + cprob + tprob))
        {
          newDNA += 't';
        }
        else
        {
          newDNA += 'g';
        }
      }

      newDNA += '\n';
      cout << newDNA;
    }
  }
  inputFile.close();


  return 0;
}

//sanitizing inputs
string sanitize(string input)
{
  string newString = "";

  for (int i = 0; i < input.length(); i++ )
  {
    char letter = tolower(input.at(i));
    newString += letter;
  }
  return newString;
}
