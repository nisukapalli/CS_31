//
//  array.cpp
//  array
//
//  Created by Nikhil Isukapalli on 11/8/20.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main() {
    
    string str1 [8] = {"aa", "bb", "hh", "ee", "cc", "gg", "dd", "ff"};
    string str2 [5] = {"aa", "bb", "hhh", "cc", "ee"};
    string str3 [6] = {"a", "a", "a", "b", "c", "c"};
    cerr << appendToAll(str1, 4, "...") << endl;
    cerr << lookup(str1, 8, "cc") << endl;
    cerr << positionOfMax(str1, 8) << endl;
    cerr << rotateLeft(str2, 5, 2) << endl;
    cerr << countRuns(str3, 6) << endl;
    cerr << flip(str3, 6) << endl;
    cerr << differ(str1, 8, str2, 5) << endl;
    cerr << subsequence(str1, 4, str2, 2) << endl;
    cerr << lookupAny(str1, 8, str3, 5) << endl;
    cerr << divide(str1, 8, "e") << endl;
    
    return 0;
}

int appendToAll(string a[], int n, string value) {
    if (n < 0) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i < n; i++) {
        a[i] += value;      //append value to each element
    }
    return n;
}

int lookup(const string a[], int n, string target) {
    if (n <= 0) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {   //if element equals target
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n) {
    if (n <= 0) {    //unreasonable value for n
        return -1;
    }
    int pos = 0;    //set position of max value to 0
    for (int i = 0; i < n; i++) {
        if (a[i] > a[pos]) {    //find position of new max value
            pos = i;
        }
    }
    return pos;
}

int rotateLeft(string a[], int n, int pos) {
    if (n <= 0 || pos <= 0 || pos >= n) {    //unreasonable parameter values
        return -1;
    }
    string temp = a[pos];   //the element to be moved to the end
    for (int i = pos; i < n-1; i++) {   //copy elements 1 position to the left
        a[i] = a[i+1];
    }
    a[n-1] = temp;  //move to the end
    return pos;
}

int countRuns(const string a[], int n) {
    if (n < 0) {    //unreasonable parameter values
        return -1;
    }
    if (n == 0 || n == 1) { //arrays of size 0 or 1 should return 0 or 1, respectively
        return n;
    }
    int count = 1;  //arrays must have at least 1 distinct element
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i-1]) {   //if consecutive elements are different
            count++;
        }
    }
    return count;
}

int flip(string a[], int n) {
    if (n < 0) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i < n/2; i++) { //loop until midpoint
        string temp = a[i];     //swap elements across the midpoint
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {    //unreasonable parameter values
        return -1;
    }
    int n;  //to check which array has fewer elements
    if (n1 > n2) {
        n = n2;
    }
    else {
        n = n1;
    }
    for (int i = 0; i < n; i++) {
        if (a1[i] != a2[i]) {   //if the corresponding elements are not equal
            return i;
        }
    }
    return n;   //if we loop through the smaller array with no matches
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0 || n2 > n1) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i <= n1-n2; i++) {  //a2 must be within the bounds of a1
        if (a1[i] == a2[0]) {   //check if the first element of a2 is in a1
            int count = n2;     //counter to check if all elements of a2 are in a1
            for (int j = 0; j < n2; j++) {
                if (a1[i+j] == a2[j]) {
                    count--;
                }
            }
            if (count == 0) {   //if all elements in a2 are in a1
                return i;
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) {   //if an element in a1 equals an element in a2
                return i;
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider) {
    if (n < 0) {    //unreasonable parameter values
        return -1;
    }
    for (int i = 0; i < n-1; i++) {     //bubble sort
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {    //order elements from least to greatest
                string temp = a[j];     //swap adjacent elements
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {   //print out sorted array
        cerr << a[i]<< " ";
    }
    for (int i = 0; i < n; i++) {   //find position of the first element that is >= divider
        if (a[i] >= divider) {
            return i;
        }
    }
    return n;
}
