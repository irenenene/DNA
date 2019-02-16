/*
Irene Liu
2313260
irliu@chapman.edu
CPSC 350-02
Assignment: 1

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//changes to lower case
string strLower(string);
//gets percentage of bigrams
double getPercent(double, double);
//tests if a string is valid
bool validString(string);

int main(int argc, char *argv[])
{
  const string HEADER_COMMENT = "Irene Liu\n2313260\nirliu@chapman.edu\nCPSC350-2\nAssignment 1\n";
  const double PI = 3.1415926535897;
  const int LINES_TO_WRITE = 1000;

  string fileName = "";
  fileName = argv[1];
  ifstream inputFile;
  ofstream outputFile;
  string ofName = "irene.out";
  bool firstwrite = true;

  bool isContinue = true;
  string uinput = "";

  while(isContinue)
  {
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

    srand(time(NULL));

  /*
  First parse of the file will grab:
  mean, totalLines, total and individual nucleotide count, bigram count
  */
    inputFile.open(fileName);
    if (inputFile.is_open())
    {
      string line;

//Begin first runthrough of File
      while (getline(inputFile, line))
      {
        line = strLower(line);

        if(validString(line))
        {
          for (int i = 0; i < line.length(); i++)
          {
//getting individual nucleotide count
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

//getting bigram count
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
          /*    else
              {
                cout << "hmm" << endl;
              }*/
            }
          }

          totalLines++;
        }
      }
// end first runthrough

      totalSum = acount + ccount + tcount + gcount;
      mean = double(totalSum) / double(totalLines);

      aprob = double(acount) / totalSum;
      cprob = double(ccount) / totalSum;
      tprob = double(tcount) / totalSum;
      gprob = double(gcount) / totalSum;

//resetting EOF for another run through of file
      inputFile.clear();
      inputFile.seekg(0, ios::beg);

//another runthrough, this time we have the mean so we can calculate the difference for variance
      while (getline(inputFile, line))
      {
        line = strLower(line);
        if(validString(line))
        {
          double difference = 0;
          difference = (line.length() - 1) - mean;
          varianceTop += (difference * difference);
        }
      }
    }
    else
    {
      cout << "Error reading from file. Aborting. " << endl;
      return -1;
    }
    inputFile.close();

    variance = (varianceTop / totalLines);
    stdDev = sqrt(variance);

  /*
  //for debugging
    cout << "Variance: " << variance << endl;
    cout << "Standard Deviation: " << stdDev << endl;
    cout << totalSum << " " << mean << endl;
    cout << acount << " " << ccount << " " << tcount << " " << gcount << endl;
    cout << aprob << " " << cprob << " " << tprob << " " << gprob << endl;
    cout << "Bigram count: " << endl;
    cout << countAA << " " << countAC << " " << countAT << " " << countAG << endl;
    cout << countCA << " " << countCC << " " << countCT << " " << countCG << endl;
    cout << countTA << " " << countTC << " " << countTT << " " << countTG << endl;
    cout << countGA << " " << countGC << " " << countGT << " " << countGG << endl;
  */

  //writing to file
    if(firstwrite)
    {
      outputFile.open(ofName, ios::out);
      outputFile << HEADER_COMMENT;
      firstwrite = false;
    }
    else
    {
      outputFile.open(ofName, ios::out | ios::app);
    }

    if(outputFile.is_open())
    {
      outputFile << "Sum of each line's length: " << totalSum << endl;
      outputFile << "Mean: " << mean << endl;
      outputFile << "Variance: " << variance << endl;
      outputFile << "Standard Deviation: " << stdDev << endl;
      outputFile << "Probability of Each Nucletide:" << endl;
      outputFile << "A: " << (aprob * 100) << "% - ";
      outputFile << "C: " << (cprob * 100) << "% - ";
      outputFile << "T: " << (tprob * 100) << "% - ";
      outputFile << "G: " << (gprob * 100) << "%" << endl;
      outputFile << "Probability of Each Bigram: " << endl;

      outputFile << "   [A][C][T][G]" << endl;
      outputFile << "[A] " << setprecision(4) << getPercent(countAA, totalSum) << "% "
                          << setprecision(4) << getPercent(countAC, totalSum) << "% "
                          << setprecision(4) << getPercent(countAT, totalSum) << "% "
                          << setprecision(4) << getPercent(countAG, totalSum) << "% " << endl;
      outputFile << "[C] " << setprecision(4) << getPercent(countCA, totalSum) << "% "
                          << setprecision(4) << getPercent(countCC, totalSum) << "% "
                          << setprecision(4) << getPercent(countCT, totalSum) << "% "
                          << setprecision(4) << getPercent(countCG, totalSum) << "% " << endl;
      outputFile << "[T] " << setprecision(4) << getPercent(countTA, totalSum) << "% "
                          << setprecision(4) << getPercent(countTC, totalSum) << "% "
                          << setprecision(4) << getPercent(countTT, totalSum) << "% "
                          << setprecision(4) << getPercent(countTG, totalSum) << "% " << endl;
      outputFile << "[G] " << setprecision(4) << getPercent(countGA, totalSum) << "% "
                          << setprecision(4) << getPercent(countGC, totalSum) << "% "
                          << setprecision(4) << getPercent(countGT, totalSum) << "% "
                          << setprecision(4) << getPercent(countGG, totalSum) << "% " << endl;
      outputFile << "-----------" << endl;

  //determining the length of each new string
      for ( int n = 0; n < LINES_TO_WRITE; n++)
      {
      double aValue = rand() / (RAND_MAX + 1.0);
      double bValue = rand() / (RAND_MAX + 1.0);
      double cValue = sqrt(-2 * log(aValue)) * cos(2 * PI * bValue);
      double dValue = (stdDev * cValue) + mean;
      int length = int(dValue);

  //if length of new string is odd, round up to even number
      if (length % 2 != 0)
      {
        length++;
      }

  //building each new DNA string
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
      outputFile << newDNA;
      }

      cout << "Results written to " << ofName << endl;
    }
    outputFile.close();

    bool prompt = true;

//prompt user to process another file
    while(prompt)
    {
      cout << "Would you like to process another file? (y/n)";
      cin >> uinput;
      uinput = strLower(uinput);
      if(uinput.compare("y") == 0)
      {
        cout << "Enter a filename: ";
        cin >> uinput;
        fileName = uinput;
        prompt = false;
      }
      else if(uinput.compare("n") == 0)
      {
        isContinue = false;
        prompt = false;
      }
      else
      {
        prompt = true;
      }
    }
  }

  return 0;
}

double getPercent(double n, double c)
{
  double percent = n / (c / 2.0);
  percent *= 100;

  return percent;
}

string strLower(string input)
{
  string newString = "";

  for (int i = 0; i < input.length(); i++ )
  {
    char letter = tolower(input.at(i));
    newString += letter;
  }
  return newString;
}

bool validString(string l)
{
  for (int i = 0; i < l.length() -1; i++)
  {
    if((l.at(i) != 'a') && (l.at(i) != 'c') &&
    (l.at(i) != 't') && (l.at(i) != 'g'))
    {
      return false;
    }
  }

  return true;
}
