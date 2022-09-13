//
//  match.cpp
//  match.cpp
//
//  Created by Nikhil Isukapalli on 11/21/20.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
int cleanupRules(char wordin[][MAX_WORD_LENGTH+1],
                 char wordout[][MAX_WORD_LENGTH+1],
                 int nRules);
int determineScore(const char document[],
                   const char wordin[][MAX_WORD_LENGTH+1],
                   const char wordout[][MAX_WORD_LENGTH+1],
                   int nRules);

int main() {
    const int TEST1_NRULES = 3;
    char test1win[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "family", "unhappy", "horse",
    };
    char test1wout[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "",       "horse",   "",
    };
    
    assert(determineScore("Happy families are all alike; every unhappy family is unhappy in its own way.", test1win, test1wout, TEST1_NRULES) == 2);
    assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.", test1win, test1wout, TEST1_NRULES-1) == 0);
    assert(determineScore("Happy horses are all alike; every unhappy horse is unhappy in its own way.", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("A horse!  A horse!  My kingdom for a horse!", test1win, test1wout, TEST1_NRULES) == 1);
    assert(determineScore("horse:stable ratio is 10:1", test1win, test1wout, TEST1_NRULES) == 0);
    assert(determineScore("**** 2020 ****", test1win, test1wout, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;
    
    for (int i = 0; i < TEST1_NRULES; i++) {
        cerr << test1win[i] << "\t" << test1wout[i] << endl;
    }
    
    return 0;
}

int cleanupRules(char wordin[][MAX_WORD_LENGTH+1],
                 char wordout[][MAX_WORD_LENGTH+1],
                 int nRules) {
    
    if (nRules < 0) {
        nRules = 0;
    }
    for (int i = 0; i < nRules; i++) {
        for (int j = 0; wordin[i][j] != '\0'; j++) {
            wordin[i][j] = tolower(wordin[i][j]);   //make chars lowercase
        }
        for (int j = 0; wordout[i][j] != '\0'; j++) {
            wordout[i][j] = tolower(wordout[i][j]); //make chars lowercase
        }
        if (strcmp(wordin[i], wordout[i]) == 0) {   //if win and wout are equal
            strcpy(wordin[i], "");      //make win empty
            strcpy(wordout[i], "");     //make wout empty
        }
    }
    for (int i = 0; i < nRules; i++) {
        for (int j = 0; wordin[i][j] != '\0'; j++) {
            if (! isalpha(wordin[i][j])) {  //if it isn't a letter
                strcpy(wordin[i], "");      //make win empty
                strcpy(wordout[i], "");     //make wout empty
            }
        }
    }
    for (int i = 0; i < nRules; i++) {
        for (int j = i+1; j < nRules; j++) {
            
            if (strcmp(wordout[i], "") == 0 &&      //if the rule has 1 word
                strcmp(wordin[i], wordin[j]) == 0) {   //if 2 rules have the same win
                
                strcpy(wordin[j], "");      //make win in the 2-word rule empty
                strcpy(wordout[j], "");     //make wout in the 2-word rule empty
            }
            if (strcmp(wordout[i], "") != 0) {      //if the first rule has 2 words
                if (strcmp(wordin[i], wordin[j]) == 0 &&    //if both have the same win
                    strcmp(wordout[i], wordout[j]) == 0) {  //if both have the same wout
                    
                    strcpy(wordin[j], "");      //make win in the second rule empty
                    strcpy(wordout[j], "");     //make wout in the second rule empty
                }
                if (strcmp(wordout[j], "") == 0 &&      //if the second rule has 1 word
                    strcmp(wordin[i], wordin[j]) == 0) {    //if both have the same win
                    
                    strcpy(wordin[i], "");      //make win in the 2-word rule empty
                    strcpy(wordout[i], "");     //make wout in the 2-word rule empty
                }
            }
        }
    }
    
    int count = 0;  //count the number of match rules in clean form
    for (int i = 0; i < nRules; i++) {
        if (strcmp(wordin[i], "") != 0) {
            count++;
        }
    }
    
    for (int i = 0; i < count; i++) {
        if (strcmp(wordin[i], "") == 0) {
            for (int j = nRules-1; j >= count; j--) {
                if (strcmp(wordin[i], "") != 0) {
                    strcpy(wordin[i], wordin[j]);
                    strcpy(wordout[i], wordout[j]);
                    strcpy(wordin[j], "");
                    strcpy(wordout[j], "");
                }
            }
        }
    }
    
    if (nRules > 1) {
        for (int i = nRules-2; i >= 0; i--) {
            if (strcmp(wordin[i], "") == 0) {     //if string is empty
                for (int j = i; j < nRules-1; j++) {    //for each string after
                    char temp[MAX_WORD_LENGTH+1];   //swap empty string with clean rule
                    strcpy(temp, wordin[j]);
                    strcpy(wordin[j], wordin[j+1]);
                    strcpy(wordin[j+1], temp);
                    
                    strcpy(temp, wordout[j]);
                    strcpy(wordout[j], wordout[j+1]);
                    strcpy(wordout[j+1], temp);
                }
            }
        }
    }
    
    return count;
}


int determineScore(const char document[],
                   const char wordin[][MAX_WORD_LENGTH+1],
                   const char wordout[][MAX_WORD_LENGTH+1],
                   int nRules) {
    
    if (nRules < 0) {
        nRules = 0;
    }
    
    //adding spaces so the first and last word can be treated like the other words
    char doccopy[300] = " ";    //copy of document with space at beginning
    
    for (int i = 0; document[i] != '\0'; i++) {
        if (isalpha(document[i]) ||     //if char is a letter
            document[i] == ' ') {       //if char is a space
            char temp = tolower(document[i]);   //make char lowercase
            strncat(doccopy, &temp, 1);  //append char to doccopy
        }
    }
    strcat(doccopy, " ");   //add space to end
    
    for (int i = 0; doccopy[i] != '\0'; i++) {
        cerr << doccopy[i];
    }
    cerr << endl;
    
    int count = 0;
    for (int i = 0; i < nRules; i++) {
        
        char tempin[300] = " ";     //individual win elements
        char tempout[300] = " ";    //individual wout elements;
        if (strcmp(wordin[i], "") != 0) {   //if win isn't an empty string
            strcat(tempin, wordin[i]);
            strcat(tempin, " ");    //add space to end
            strcat(tempout, wordout[i]);
            strcat(tempout, " ");   //add space to end
            char *posin = strstr(doccopy, tempin);
            char *posout = strstr(doccopy, tempout);
            
            cerr << tempin << "\t" << tempout << endl;
            
            if (posin != NULL) {    //if the document contains win
                if (strcmp(wordout[i], "") == 0) {  //if the rule has 1 word
                    count++;
                }
                else {      //if the rule has 2 words
                    if (posout == NULL) {   //if the document doesn't contain wout
                        count++;
                    }
                }
            }
        }
    }
    cerr << count << endl;
    
    return count;
}
