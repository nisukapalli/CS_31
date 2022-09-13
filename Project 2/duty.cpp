//
//  duty.cpp
//
//  Created by Nikhil Isukapalli on 10/17/20.
//

#include <iostream>     //to read or write standard input and output streams
#include <iomanip>      //needed for setprecision()
#include <string>       //needed for string variables
using namespace std;        //to avoid writing "std::" everytime

int main() {
    
    string cheeseType;
    double value;
    string importer;
    double duty;
    
    cout << "Enter the type of cheese: " << endl;
    getline(cin, cheeseType);       //read user input for string "cheeseType"
    
    cout << "Enter the value of the cheese: " << endl;
    cin >> value;       //read user input for double "value"
    cin.ignore(10000, '\n');        //ignore everything before and including the '\n' character to avoid any unexpected output
    
    cout << "Enter the name of the importer: " << endl;
    getline(cin, importer);     //read user input for string "importer"
    
    if (value <= 1000.00) {     //if value is less than or equal to $1000.00
        duty = value * 0.011;       //the first $1000.00 has 1.1% duty
    }
    else if (value <= 13000.00) {       //if value is less than or equal to $13000.00
        if (cheeseType == "cheshire" || cheeseType == "stilton") {    //if cheeseType is cheshire or stilton
            duty = (1000.00 * 0.011) + ((value - 1000.00) * 0.014);   //the first $1000.00 has 1.1% duty, the next $12000.00 has 1.4% duty
        }
        else {      //if cheeseType is anything other than cheshire or stilton
            duty = (1000.00 * 0.011) + ((value - 1000.00) * 0.02);    //the first $1000.00 has 1.1% duty, the next $12000.00 has 2% duty
        }
    }
    else {      //if value is over $13000.00
        if (cheeseType == "cheshire" || cheeseType == "stilton") {    //if cheeseType is cheshire or stilton
            duty = (1000.00 * 0.011) + (12000.00 * 0.014) + ((value - 13000.00) * 0.029);   //the first $1000.00 has 1.1% duty, the next $12000.00 has 1.4% duty, anything over $13000.00 has 2.9% duty
        }
        else {      //if cheeseType is anything other than cheshire or stilton
            duty = (1000.00 * 0.011) + (12000.00 * 0.02) + ((value - 13000.00) * 0.029);    //the first $1000.00 has 1.1% duty, the next $12000.00 has 2% duty, anything over $13000.00 has 2.9% duty
        }
    }
    cout << "---" << endl;
    cout << fixed;
    cout << setprecision(2);        //set precision to 2 decimal places
    
    if ( cheeseType == "") {        //if cheeseType is blank
        cout << "You must enter a cheese type" << endl;
        return 1;
    }
    else if (value <= 0.00) {       //if value is not positive
        cout << "The value must be positive" << endl;
        return 1;
    }
    else if (importer == "") {      //if importer is blank
        cout << "You must enter an importer" << endl;
        return 1;
    }
    else {      //if there are no other errors
        cout << "The import duty for " << importer << " is $" << duty << endl;
    }
    
    return 0;
}
