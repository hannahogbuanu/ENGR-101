// <Your Name> 
// <Lab Section Number> 
// <Date Submitted>

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

#include "reviews.h"

using namespace std;

// TODO: add more helper functions if you want to 



// Reads in keywords and corresponding weights from an input stream and stores them into
// the 'keywords' and 'weights' vectors in the same order as they appear in the file.
// NOTE: They keywords in the file have already been preprocessed (e.g. to remove punctuation),
//       so you do not have to do that here.
// PARAMETERS:
//   input - An input stream from which keywords and weights are read. For this project, we
//           assume the input stream is a file input stream, where the file format is that
//           provided in the project specification.
//   keywords - An "output parameter", passed by reference, into which the keywords are stored.
//   weights - An "output parameter", passed by reference, into which the weights are stored.
void readKeywordWeights(istream &input, vector<string> &keywords, vector<double> &weights) {
    // TODO: Write an implementation for this function!
    // Fill in the passed in vector of strings and passed in vector of doubles from
    // the passed in filestream.
    string keyw;
    double weight;
    while (input >> keyw >> weight) {
        keywords.push_back(keyw);
        weights.push_back(weight);
    }
    
}

// Reads in a review from an input stream and stores each individual word from the review
// into the vector 'reviewWords', in the same order they appeared in the input.
// PARAMETERS:
//   input - An input stream from which the review is read. For this project, we assume the
//           input stream is a file input stream, with words separated by whitespace.and weights are read.
//   reviewWords - An "output parameter", passed by reference, into which the review words are stored.
void readReview(istream &input, vector<string> &reviewWords) {
    // TODO: Write an implementation for this function!
    // Fill passed in vector of strings with words in text file connected to passed
    // in filestream
    string reviewW;
    while (input >> reviewW) {
        reviewWords.push_back(reviewW);
    }
}

// Returns the weight of a given word by looking it up in the provided vectors.
// The keywords and their corresponding weights are provided as vector parameters.
// It is assumed that these are parallel vectors, so that weights[i] is the weight of keywords[i].
// If a word does not appear in the keywords vector, its weight is zero.
// PARAMETERS:
//   word - The word to be looked up
//   keywords - A vector containing all keywords.
//   weights - A vector containing weights corresponding to each keyword.
double wordWeight(const string &word, const vector<string> &keywords, const vector<double> &weights) {
    // TODO: Write an implementation for this function!
    // Check passed in word against each keyword to see if they match. If they match
    // function returns weight of the keyword. If no match, function returns 0.0
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (keywords.at(i) == word) {
            return weights.at(i);
        }
    }
    return 0.0;
    
}


// Computes and returns the overall score for a review. This is the sum of the weights of
// the individual words in the review. Note that a word may appear more than once in the review,
// and if this happens it's weight is added in multiple times as well. The keywords and their
// corresponding weights are provided as vector parameters. It is assumed that these are parallel
// vectors, so that weights[i] is the weight of keywords[i]. If a word does not appear in the
// keywords vector, its weight is zero.
// HINT: Make a copy of the reviewWords vector using a separate variable. Then, call the
//       preprocessReview() function on the copy. Having a preprocessed copy of the words
//       will allow you to compare against the keywords.
// PARAMETERS:
//   reviewWords - A vector containing the individual words in the review.
//   keywords - A vector containing all keywords.
//   weights - A vector containing weights corresponding to each keyword.
double reviewScore(const vector<string> &reviewWords, const vector<string> &keywords, const vector<double> &weights) {
    // TODO: Write an implementation for this function!
    // Copy passed in review to keep the original version to potentially work on later.
    vector<string> reviewWords2 = reviewWords;
    // call preprocessReview function to standardize the passed in text
    preprocessReview(reviewWords2);

    // initialize sum value
    double sum = 0.0;
    // iterate through each word in the prepocessed review
    // get the weight of each word and add it to running total sum  
    for (size_t i = 0; i < reviewWords2.size(); ++i) {
        sum += wordWeight(reviewWords2.at(i), keywords, weights);
    }
    return sum;
}










// -------------------- !!! *** DO NOT MODIFY ANY CODE BELOW THIS LINE *** !!! --------------------




// If you're curious, it's ok to look this code. But definitely don't change it!
// These are functions we intend for you to use in the rest of your code.

// *********************************************************************
//    The code in these functions is not part of the course content, 
//    and anything here that has not been taught in the course is 
//    not allowable for use outside of these functions.
// *********************************************************************




// Used as a helper function in preprocessReview.
static bool isNonAlphanumeric(char c) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.
    return !isalnum(c);
}

// Preprocesses the individual words in a review by removing punctuation,
// converting all letters to lowercase, and replacing numbers (e.g. 100)
// by "<number>".
void preprocessReview(vector<string> &reviewWords) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.

    for (size_t i = 0; i < reviewWords.size(); ++i) {
        // Create a reference to the word in the vector to use to change it.
        // A reference variable (just like a pass-by-reference parameter) will
        // refer to the original object, so our changes will show up in the vector.
        string &word = reviewWords.at(i);
        
        // Remove all non-alphanumeric characters (i.e. punctuation) from the word
        word.erase(remove_if(word.begin(), word.end(), isNonAlphanumeric), word.end());

        // Adjust all letters in the word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // If the "word" is entirely numeric, change it to "<number>"
        if (all_of(word.begin(), word.end(), ::isdigit)) {
            word = "<number>";
        }
    }
}

// Generates the filename for the hotel review file corresponding
// to the given integer. It is presumed there will be no more than
// 100 reviews, numbered 0-99. It is required that 0 <= i && i <= 99.
string makeReviewFilename(int n) {
    // THIS FUNCTION IS ALREADY IMPLEMENTED FOR YOU. DO NOT CHANGE IT.
    int tensPlace = n / 10;
    int onesPlace = n % 10;
    return "review" + to_string(tensPlace) + to_string(onesPlace) + ".txt";
}
