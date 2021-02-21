//
// Created by Owner on 12-Nov-19.
//

/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << KEEGAN BAIN >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;

bool isVanityDigit(string plate, int& numCount)
{
    // Vanity:
    //   Format: 1-3 numbers *OR* 1-7 letters
    //
    //   Examples: 007, 1, 42, X, AAA, ZZZEFGH
    //
    for (int i = 1; i < plate.length(); i++)
    {
        if (isdigit(plate[i]))
            numCount++;
        else if (plate[i] == ' ')
            return false;
        else
            return false;
    } // for int i ends

    if (numCount >= 1 && numCount <= 3)
        return true;
    else
        return false;
} // isVanityDigit() ends

bool isVanityAlpha(string plate, int &letterCount)
{
    // Vanity:
    //   Format: 1-3 numbers *OR* 1-7 letters
    //
    //   Examples: 007, 1, 42, X, AAA, ZZZEFGH
    //
    for (int i = 1; i < plate.length(); i++)
    {
        if (isalpha(plate[i]) && isupper(plate[i]))
            letterCount++;
        else
            return false;
    } // for int i ends

    if (letterCount >= 1 && letterCount <= 7)
        return true;
    else
        return false;
} // isVanityAlpha() ends

bool isPersonal(string str1, string str2, int& numCount, int& letterCount)
{
    // Personalized:
    //   letters and numbers, with a space between the letters
    //   and numbers.  Format: 1-5 letters plus 1..99 *OR*
    //   6 letters plus 1..9
    //
    //   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
    //
    // NOTE: (1) str1 should contain only upper case letters
    //           (space has already been taken care of by using substr)
    //       (2) str2 should contain only digits, if there is
    //           another space then plate is invalid

    // check str1
    for (int i = 1; i < str1.length(); i++)
    {
        if (isalpha(str1[i]) && isupper(str1[i]))
            letterCount++;
        else
            return false;
    } // for int i ends

    // check str2
    for (int i = 0; i < str2.length(); i++)
    {
        if (isdigit(str2[i]))
            numCount++;
        else if (str2[i] == ' ')
            return false;
        else
            return false;
    } // for int i ends

    if ((letterCount >= 1 && letterCount <= 5) && (numCount >= 1 && numCount <= 2))
        return true;
    else if ((letterCount >= 1 && letterCount <= 6) && numCount == 1)
        return true;
    else
        return false;
} // isPersonal() ends

bool isValidPlate (string plate)
{
    // Personalized:
    //   letters and numbers, with a space between the letters
    //   and numbers.  Format: 1-5 letters plus 1..99 *OR*
    //   6 letters plus 1..9
    //
    //   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
    //
    // Vanity:
    //   Format: 1-3 numbers *OR* 1-7 letters
    //
    //   Examples: 007, 1, 42, X, AAA, ZZZEFGH
    //
    int numCount = 0;
    int letterCount = 0;
    int spaceIndex = -1;

    // plate could be vanity (only letters) or could be personalized
    if (isalpha(plate[0]))
    {
        if(islower(plate[0]))
            return false;

        letterCount++;

        for (int i = 0; i < plate.length(); i++)
        {
            if (plate[i] == ' ' && i != (plate.length() - 1))
            {
                spaceIndex = i;
                break;
            } // if ends
        } // for int i ends

        // if the spaceIndex is -1 that means plate could be a vanity plate
        if (spaceIndex == -1)
        {
            if (isVanityAlpha(plate, letterCount))
                return true;
            else
                return false;
        } // if (spaceIndex == -1) ends

        string str1 = plate;
        str1.erase(spaceIndex, plate.length());
        string str2 = plate.substr(spaceIndex + 1);

        if (isPersonal(str1, str2, numCount, letterCount))
            return true;
        else
            return false;
        // cout << str1 << str2 << endl; // testing
    } // if (isalpha(plate[0])) ends

    // most probably a vanity plate
    else if (isdigit(plate[0]))
    {
        numCount++;

        if (isVanityDigit(plate, numCount))
            return true;
        else
            return false;
    } // else if ends

    else
        return false;
} // isValidPlate()

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters
//   and numbers.  Format: 1-5 letters plus 1..99 *OR*
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
//
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
    unsigned long long index = 711;

    //
    // TODO: work on making the hashing better
    // current # of probes for tickets9: 39218
    // improvements could be made but I'm not sure what else to add?
    //

    if (!isValidPlate(plate))
        return -1;

    for (int i = 0; i < plate.length(); i++)
        index = index + (long long) (pow(36, i) * plate[i] * plate.length());

    return index % HT.Size();
}

//
// Search
//
// Hashes and searches for the given license plate; returns the
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
    //
    // TODO:
    //
    int index = Hash(plate);
    bool empty;
    // TKey key == string plate
    // TValue value == some int value
    string myPlate;
    int myValue = -1;

    if (!isValidPlate(plate))
        return -1;

    // probe through the table looking for the plate until we
    // find an empty index, if plate is not found before we
    // encounter an empty index then return -1
    while (true)
    {
        if (index >= HT.Size() || index < 0)
            index = 0;

        HT.Get(index, empty, myPlate, myValue);

        if (empty)
            break;

        if (myPlate.compare(plate) == 0)
            return myValue;

        index++;
    } // while ends

    return -1;
}

//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
    //
    // TODO:
    //
    int index = Hash(plate);
    bool empty;
    string myPlate;
    int myValue = -1;

    if (!isValidPlate(plate))
        return;

    // probe through the table looking for an empty index
    // if an empty index is found then insert the plate &
    // value pair into that index
    // if the index is not empty but the plate already at
    // that index is the same as the plate we are trying
    // to insert then overwrite the plate & value pair at
    // that index
    while (true)
    {
        if (index >= HT.Size() || index < 0)
            index = 0;

        HT.Get(index, empty, myPlate, myValue);

        if (empty)
        {
            HT.Set(index, plate, newValue);
            return;
        } // if (empty) ends

        else if (!empty && myPlate.compare(plate) == 0)
        {
            HT.Set(index, plate, newValue);
            return;
        } //  else if (!empty && myPlate.compare(plate) == 0) ends

        index++;
    } // while ends
}
