# IL-Plates-Hashmap

### Original Author: Prof. Joe Hummel (UIC - CS Dept)
### Modified by: Keegan Bain (GitHub - RubberDuckE)


**NOTE:** This code was written in CLion so it also contains some files for plugins that I regularly use.  

---


### Description

This project creates a hashmap of Illinois license plates that are stored in the "tickets" text file.  
The license plates are first filtered out and checked if they are valid or not based on the following  
two categories:  

1. **Personalized:**  
     Letters and numbers, with a space between the letters  
     and numbers.  Format: 1-5 letters plus 1..99 *OR*
     6 letters plus 1..9  
     Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3  
     
2. **Vanity:**  
     Format: 1-3 numbers *OR* 1-7 letters  
     Examples: 007, 1, 42, X, AAA, ZZZEFGH  


The code then generates an index for the hash table and stores the data. The hashmap is then sorted using  
bubble sort and the contents of the sorted hashmap are written to a text file.
