# IL-Plates-Hashmap

### Original Author: Prof. Joe Hummel (UIC - CS Dept)
### Modified by: Keegan Bain (GitHub - RubberDuckE)


**NOTE:** This code was written in CLion so it also contains some files for plugins that I regularly use.


This project creates a hashmap of Illinois license plates that are stored in the "tickets" text file. 
The license plates are first filtered out based on the following two categories:

1. Personalized:
     letters and numbers, with a space between the letters
     and numbers.  Format: 1-5 letters plus 1..99 *OR*
     6 letters plus 1..9
     Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
     
2. Vanity:
     Format: 1-3 numbers *OR* 1-7 letters 
     Examples: 007, 1, 42, X, AAA, ZZZEFGH

