/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << KEEGAN BAIN >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
    string infilename = basename + ".txt";
    ifstream infile(infilename);

    if (!infile.good())
    {
        cout << endl;
        cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
        cout << endl;
        exit(-1);
    }

    //
    // input the plates and fines:
    //
    cout << "Reading '" << infilename << "'..." << endl;

    string fine;
    string plate;

    getline(infile, fine);

    //
    // for each pair (fine, license plate), hash and store/update fine:
    //
    while (!infile.eof())
    {
        getline(infile, plate);

        //cout << fine << endl;
        //cout << plate << endl;

        //
        // is plate valid?  Only process valid plates:
        //
        if (hashplates.Hash(plate) >= 0)  // yes:
        {
            int amount = hashplates.Search(plate);

            if (amount < 0)  // not found:
            {
                hashplates.Insert(plate, stoi(fine));
            }
            else  // we found it, so update total in hash table:
            {
                amount += stoi(fine);
                hashplates.Insert(plate, amount);
            }

        }//valid

        getline(infile, fine);
    }
}

//
// write the sorted data to the output file
//
void writeToFile(string basename, vector<string> plates, vector<int> amounts)
{
    string outfilename = basename + "-output.txt";
    ofstream outfile(outfilename);

    cout << "Writing to \'" << outfilename << "\'..." << endl;

    for (int i = 0; i < plates.size(); i++)
        outfile << "\"" << plates[i] << "\"" << " $" << amounts[i] << endl;
} // writeToFile() ends

//
// sort the plates and amounts using Bubble Sort
//
void BubbleSort(vector<string>& plates, vector<int>& amounts)
{
    cout << "Sorting..." << endl;

    string tempStr;
    int tempAmt = 0;

    for (int i = 0; i < plates.size(); i++)
    {
        for (int j = 0; j < plates.size() - i - 1; j++)
        {
            if (plates[j] > plates[j + 1])
            {
                // swap the plates
                tempStr = plates [j];
                plates[j] = plates[j + 1];
                plates[j + 1] = tempStr;

                // swap the corresponding amounts
                tempAmt = amounts[j];
                amounts[j] = amounts[j + 1];
                amounts[j + 1] = tempAmt;
            } // if (plates[j] > plates[j + 1])
        } // for int j ends
    } // for int i ends
} // BubbleSort() ends

int main()
{
    int    N;        // = 10000;
    string basename; // = "tickets1";

    cout << "Enter hashtable size> ";
    cin >> N;

    hashtable<string, int>  ht(N);
    ILplates                hashplates(ht);

    cout << "Enter base filename> ";
    cin >> basename;
    cout << endl;

    //
    // process input file of fines and license plates:
    //
    hashInput(basename, hashplates);

    //
    // debugging:
    //
    vector<string> plates = ht.Keys();
    vector<int> amounts = ht.Values();

    //
    // call BubbleSort() to sort the plates and amounts vectors
    //
    BubbleSort(plates, amounts);

    //
    // call writeToFile() to write the sorted data to the output
    // file
    //
    writeToFile(basename, plates, amounts);

//    for (size_t i = 0; i < plates.size(); ++i)
//    {
//        cout << plates[i] << ", " << amounts[i] << endl;
//    }

    //
    // done:
    //
    return 0;
}