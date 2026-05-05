// <Your Name> 
// <Lab Section Number> 
// <Date Submitted>

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------



// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

// This #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

// Set weight limit for truthful reviews and deceptive reviews
const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){

    // Open a file input stream for the text file if it cannot be opened print error
    // message and return 1 to exit main function.
    ifstream input("keywordWeights.txt");
    if (!input.is_open()){
        cout << "Error: keywordWeights.txt could not be opened." << endl;
        return 1;

    }
    // initialize truth, deceptive, and uncategorized, tally variables to sum up 
    // the amount of each type of review.
    int truthx = 0;
    int deceptivey = 0;
    int uncz = 0;

    // Read keywords and weights into parallel vectors
    vector<string> Keywords;
    vector<double> Weights;
    readKeywordWeights(input, Keywords, Weights);

    // initialize previousfinalsum values to later compare to find highest and lowest scores
    double previousfinalsumH = 0.0;
    double previousfinalsumL = 0.0;
    int highestscore = 0;
    int lowestscore = 0;

    // write out heading of report summary to a file named report.txt
    ofstream output("report.txt");
    output << "review score category" << endl;
    
    // go through each hotel review 
    for (int i = 0; i < 100; ++i) {
        // create filename for each file and open a filestream to the file
        string nameFile = makeReviewFilename(i);
        ifstream inPut(nameFile);
        if (!inPut.is_open()){
            break;
        }
        // call readReview to read each word of the review into a vector of string variables
        vector<string> ReviewWords;
        readReview(inPut, ReviewWords);
        // initialize review category variable
        string reviewCat;
        // call review score function and save the value to a final sum value
        double finalsum = reviewScore(ReviewWords, Keywords, Weights);
        
        if (i == 0) {
            previousfinalsumH = finalsum;
            previousfinalsumL = finalsum;
        }
        // Determine the review's category 
        if ( finalsum > SCORE_LIMIT_TRUTHFUL) {
           reviewCat = "truthful";
           ++truthx;
        }
        else if (finalsum < SCORE_LIMIT_DECEPTIVE) {
            reviewCat = "deceptive";
            ++deceptivey;
        }
        else {
            reviewCat = "uncategorized";
            ++uncz;
        }
        // Track the review with the highest score and the review with the lowest score        
        if (finalsum > previousfinalsumH) {
            previousfinalsumH = finalsum;
            highestscore = i;
        }
        if (finalsum < previousfinalsumL) {
            previousfinalsumL = finalsum;
            lowestscore = i;
            
        }
        // send to output a line of information for each report
        output << i << " " << finalsum << " " << reviewCat << endl;
        
       
        
    }
    
    output << " " << endl;
    output << "Number of reviews: " << truthx + deceptivey + uncz << endl;
    output << "Number of truthful reviews: " << truthx << endl;
    output << "Number of deceptive reviews: " << deceptivey << endl;
    output << "Number of uncategorized reviews: " << uncz << endl;
    output << " " << endl;
    output << "Review with highest score: " << highestscore << endl;
    output << "Review with lowest score: " << lowestscore << endl;

    cout << "Program complete.  Check report.txt file for summary." << endl;
    // TODO: implement the main program


}



