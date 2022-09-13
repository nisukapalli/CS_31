//
//  poll.cpp
//  poll
//
//  Created by Nikhil Isukapalli on 10/31/20.
//

#include <iostream>
#include <iostream>
#include <cctype>
#include <sstream>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool isSyntacticallyCorrect(string pollData);
int tallyVotes(string pollData, char party, int& voteTally);

int main() {
    
    string str;     //poll data string
    getline(cin, str);
    char ch;        //party code
    cin >> ch;
    cin.ignore(10000, '\n');
    int voteTally = 0;  //tallyVote method changes this value
    int returnVal = tallyVotes(str, ch, voteTally); //tallyVotes return value
    cerr << voteTally << endl;

    if (returnVal == 1) {   //if tallyVotes returns 1
        cerr << "Invalid poll data string" << endl;
        return returnVal;
    }
    else if (returnVal == 2) {  //if tallyVotes returns 2
        cerr << "Invalid party code" << endl;
        return returnVal;
    }
    else if (returnVal == 3) {  //if tallyVotes returns 3
        cerr << "At least 1 state has 0 votes" << endl;
        return returnVal;
    }
    cerr << ch << " will get " << voteTally << " votes" << endl;
    
    return 0;
}

bool isValidUppercaseStateCode(string stateCode) {
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isSyntacticallyCorrect(string pollData) {
    
    //if string is empty
    if(pollData == "") {
        return true;
    }
    
    //checks if poll data string consists of only letters and numbers
    for (int i = 0; i < pollData.length(); i++) {
        
        //if char isn't a letter or number
        if (! (isalpha(pollData[i]) || isdigit(pollData[i]))) {
            return false;
        }
    }

    //checks if poll data string begins with either 1 or 2 digits and ends with a letter
    if (isalpha(pollData[0]) || //if the first char isn't a number
        isdigit(pollData[2]) || //if the first forecast has a 3-digit number
        isdigit(pollData[pollData.length()-1])) {   //if the last char isn't a letter
        return false;
    }
    
    //checks if any numbers have over 2 digits
    for (int i = 0; i < pollData.length(); i++) {
        if (isalpha(pollData[i]) && isdigit(pollData[i+1])) {
            if (isdigit(pollData[i+3])) {
                return false;
            }
        }
    }
    
    //checks if state code is valid
    for (int i = 0; i < pollData.length(); i++) {   //check each char in pollData
        
        //stateCode variable resets after a forecast is checked
        string stateCode = "";
        
        //find state code
        if (isdigit(pollData[i]) && isalpha(pollData[i+1])) {
            
            //makes state code uppercase, appends to stateCode variable
            for (int j = i+1; j < i+3; j++) {
                stateCode += toupper(pollData[j]);
            }
            
            //if state code is invalid
            if (! isValidUppercaseStateCode(stateCode)) {
                return false;
            }
        }
    }

    for (int i = 0; i < pollData.length(); i++) {
        
        //find the letters after the number
        if (isdigit(pollData[i]) && isalpha(pollData[i+1])) {
            
            //checks if there aren't less than 3 letters
            for (int j = i+1; j < i+4; j++) {
                if (! isalpha(pollData[j])) {
                    return false;
                }
            }
            
            //if the 3-letter substring isn't at the end
            if (i+4 < pollData.length()) {
                
                //if there are more than 3 consecutive letters
                if (! isdigit(pollData[i+4])) {
                    return false;
                }
            }
        }
    }
    
    return true;    //if all the conditions are met
}

int tallyVotes(string pollData, char party, int& voteTally) {

    party = toupper(party); //make parameter uppercase
    for (int i = 0; i < pollData.size(); i++) {
        pollData[i] = toupper(pollData[i]);
    }
    
    if (! isSyntacticallyCorrect(pollData)){    //if string isn't syntactically correct
        return 1;
    }
    if (! isalpha(party)) { //if party code isn't a letter
        return 2;
    }
    if (pollData.substr(0, 1) == "0" || pollData.substr(0, 2) == "00") {
        return 3;
    }
    for (int i = 2; i < pollData.length(); i++) {
        if (isdigit(pollData[i]) && isalpha(pollData[i+1]) && pollData[i] == 0) {
            return 3;
        }
    }
    
    for (int i = 0; i < pollData.length(); i++) {
        if (isdigit(pollData[i]) && isdigit(pollData[i+1])) {
            if (pollData[i+4] == party) {
                voteTally += stoi(pollData.substr(i, i+2));
            }
        }
        if (isdigit(pollData[i]) && isalpha(pollData[i+1])) {
            if (pollData[i+3] == party) {
                voteTally += stoi(pollData.substr(i, i+1));
            }
        }
    }
    
    return 0;
}
