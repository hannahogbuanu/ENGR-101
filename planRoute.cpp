// Hannah Ogbuanu 
// 011
// 4.21.26

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// 35b24e49-2842-4603-8ba7-0f656200c2d1
//------------------------------------------------------

// Add your code here!`
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <fstream>
#include <cmath>

//#include "route.h"

using namespace std;
//READ IN DATA

// Created a planet struct to store planet data
struct Planet {
    int Row;
    int Column;
    char Symbol;
    int ID;
    bool visited;
    
};

// Created a struct to store names and ID's of planets 
struct PlanetName {
    int ID;
    string Name;
};

// Created a struct to save/ignore planet data that was out of range
struct Ignore {
    int Row;
    int Column;
    char Symbol;
    int ID;
};

// Created to help print out my planets struct to make sure all data was being properly saved
void printPlanet(const Planet &planets, ostream &output){
        output << planets.Row;
        output << " " << planets.Column;
        output << " " << planets.Symbol;
        output << " " << planets.ID;
};

// Created to help print out my name data to make sure all names were being properly saved
void printName(const PlanetName &names, ostream &output){
        output << names.ID;
        output << " " << names.Name;
};

// Function that loads in planetary data from locations file to Planet Struct and returns a vector of starter data
vector<int> loadData(vector<Planet> &planets, istream &input) {
    int driverRow;
    int driverCol;
    int StartRow;
    int StartCol;
    int EndRow;
    int EndCol;
    
    input >> driverRow >> driverCol >> StartRow >> StartCol >> EndRow >> EndCol;
    vector<int> startData{driverRow, driverCol, StartRow, StartCol, EndRow, EndCol};

    Planet planet;
    Ignore ignored;
    vector<Ignore> ignores;
        
    while (input >> planet.Row >> planet.Column >> planet.Symbol >> planet.ID) {
        if (planet.Row >= driverRow + 1 || planet.Column >= driverCol + 1 || planet.Row < 1 || planet.Column < 1 ) {
            ignores.push_back(ignored);
            cout << planet.ID << " out of range - ignoring" << endl;
        }
        else {
            planets.push_back(planet);
        }
            
            
    }   
    return startData;
};

// Created as a way to store data from names file as parallel vectors 
void loadNameData(vector<int> &ID, vector<string> &Name, istream &nameinput) {
    
    int id;
    string names;
    
    
    while (nameinput >> id >> names) {
            ID.push_back(id);
            Name.push_back(names);
        }
};

// Places each symbol in it's correct place in the driver's grid
void matrixSymbol(vector< vector<char> > &matrix, vector<Planet> planets){
    for (int i = 0; i < planets.size(); ++i) {
        matrix.at(planets.at(i).Row - 1).at(planets.at(i).Column -1) = planets.at(i).Symbol;

    }
    
};

// Calculates and returns the distance from current planet to each planet passed in
double CalcDistance(int &currentx, int &currenty, int planetR, int planetC) {
   
    double distance = sqrt(((currentx - planetR) * (currentx - planetR)) + ((currenty - planetC) * (currenty - planetC)) );
 
    return distance;

}


int main(){

    // asks user for filenames, saves them to variables and creates input stream
    cout << "Enter Locations Filename: ";
    string locationFile;
    cin >> locationFile;
    cout << "Enter Names Filename: ";
    string nameFile;
    cin >> nameFile;

    ifstream input(locationFile);
    ifstream nameinput(nameFile);

    // prints error message if file is not opened
    if (!input.is_open() || !nameinput.is_open() ) {
        cout << "Input file could not be opened" << endl;
        return 1;
    }
    
    // Defines vector of structs so they can be called later
    vector<Planet> planets;
    Planet planet;

    vector<PlanetName> names;
    PlanetName name;

    Ignore ignored;
    vector<Ignore> ignores;

    // calls loadData function and loads in data from location file
    vector<int> starterData = loadData(planets, input);
    
    // Outputs vector of starter data from the load Data function into separate variables
    int driverRow = starterData[0];
    int driverCol = starterData[1] ;
    int StartRow = starterData[2];
    int StartCol = starterData[3];
    int EndRow = starterData[4];
    int EndCol = starterData[5];
   
    // Defines parrallel vectors of ID and Name created for reading in data from the names file
    vector<int> ID;
    vector<string> Name;

    // calls loadNameData, reads in names file data, and saves all data to previously defined parallel vectors.
    loadNameData(ID, Name, nameinput);
    
    // for loop for data corruption, finds XX pairs and underscores and corrects them
    for (int i = 0; i < Name.size(); ++i) {
        
        int index = Name.at(i).find("XX");
        while (index != string::npos){
            Name.at(i).erase(index, 2);
            index = Name.at(i).find("XX");

        }

        
        int sindex = Name.at(i).find("_");
        while (sindex != string::npos) {
            Name.at(i).replace(sindex, 1, " ");
            sindex = Name.at(i).find("_");
        }
    
  
        
        
    }
    
    // creates matrix of periods for driver grid
    vector<char> mat(driverCol, '.');
    vector< vector<char> > matrix(driverRow, mat);

    // places each symbol in it's correct position in the matrix including the start and end symbols
    matrixSymbol(matrix, planets);
    matrix.at(StartRow - 1).at(StartCol - 1) = 'S';
    matrix.at(EndRow - 1).at(EndCol - 1) = 'E';

    // Sets the value of visited variable in Planet struct of every planet to false
    for (size_t i = 0; i < planets.size(); ++i) {
        planets.at(i).visited = false;
    }


    // Opens output stream to journey.txt file
    ofstream output("journey.txt");

    // Outputs the driver grid to the journey.txt file
    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix.at(row).size(); ++col) {
            output << matrix.at(row).at(col);
        }
        output << endl;
    }
    
    
    // Set initial current x and current y
    int currentx = StartRow;
    int currenty = StartCol;
   
    // define row, column, and pname variables
    int row = 0;
    int col = 0;
    string Pname;
   
    // Set initial lowestID
    int lowestID = planets.at(0).ID;

    // Output first line to journey.txt file
    output << "Start at " << StartRow << " " << StartCol << endl;

    // for loop to output sentence with closest planet name, row, and column, set new current x and y, and reset index value and lowest value
    for (size_t x = 0; x < planets.size(); ++x) {
    int index = 0;
    double lowest = 1000000000000000;
        // for loop to calculate the distance of every planet that has not yet been visited from current planet and find the ID of the closest one
        for (size_t j = 0; j < planets.size(); ++j) {
            if (planets.at(j).visited == false) {

        
                double distance = CalcDistance(currentx, currenty, planets.at(j).Row, planets.at(j).Column);
                
                if (distance < lowest || (distance == lowest && planets.at(j).ID < lowestID)){
                    lowest = distance;
                    
                    index = j;
                    lowestID = planets.at(j).ID;
                    
                }
            }
        }
       
        // for loop to save name of closest planet to a variable
        for (size_t i = 0; i < Name.size(); ++i) {
            if(ID.at(i) == lowestID) {
                Pname = Name.at(i);
                
               
            }
        }   
            // Sets row and column values to row and column of closest planet
            row = planets.at(index).Row;
            col = planets.at(index).Column;

            // Sets closest planet to visited
            planets.at(index).visited = true;
    
        

        
        output << "Go to " << Pname << " at " << row << " " << col << endl;
        currentx = row;
        currenty = col;
       
        
        
    } 
    
    // Output final line to journey.txt
    output << "End at " << EndRow << " " << EndCol << endl;
            
}


    


    
    
  
    
    
    

      
    
    


    

    

    

   

    
    



    

   

