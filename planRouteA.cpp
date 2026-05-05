// <Your Name> 
// <Lab Section Number> 
// <Date Submitted>

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
struct Planet {
    int Row;
    int Column;
    char Symbol;
    int ID;
    bool visited;
    
};
struct PlanetName {
    int ID;
    string Name;
};
struct Ignore {
    int Row;
    int Column;
    char Symbol;
    int ID;
};
void printPlanet(const Planet &planets, ostream &output){
        output << planets.Row;
        output << " " << planets.Column;
        output << " " << planets.Symbol;
        output << " " << planets.ID;
};
void printName(const PlanetName &names, ostream &output){
        output << names.ID;
        output << " " << names.Name;
};
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
            cout << planet.ID << " out of range - ignoring." << endl;
        }
        else {
            planets.push_back(planet);
        }
            
            
    }   
    return startData;
};

void loadNameData(vector<int> &ID, vector<string> &Name, istream &nameinput) {
    
    int id;
    string names;
    
    
    while (nameinput >> id >> names) {
            ID.push_back(id);
            Name.push_back(names);
        }
};

void matrixSymbol(vector< vector<char> > &matrix, vector<Planet> planets){
    for (int i = 0; i < planets.size(); ++i) {
        matrix.at(planets.at(i).Row - 1).at(planets.at(i).Column -1) = planets.at(i).Symbol;

    }
    
};
int CalcDistance(int &currentx, int &currenty, vector<Planet> planets) {
    vector<double> distances;
    vector<int> planetIDs;
    Ignore ignored;
    vector<Ignore> ignores;
    for (size_t i = 0; i < planets.size(); ++i){ 
        if (planets.at(i).visited == false) {
            double distance = sqrt(((currentx - planets.at(i).Row) * (currentx - planets.at(i).Row)) + ((currenty - planets.at(i).Column) * (currenty - planets.at(i).Column)) );
            distances.push_back(distance);
            planetIDs.push_back(planets.at(i).ID);

        }
        else {
            ignore = planets.at(i);
                
        }

    }
    for (size_t i = 0; i < planets.size(); ++i) {
        double lowest = 1000000000000000000000000;
        int index = 0;
        int lowestID = 100000;
        for (size_t i = 0; i < distances.size(); ++i) {
            if (distances.at(i) < lowest || distances.at(i) == lowest && planetIDs.at(i) < planetIDs.at(index)){
                lowest = distances.at(i);
                index = i;
                lowestID = planetIDs.at(i);
                //distances.erase(distances.begin() + i);

            } else{
                ++i;    
            }
        } 
        return planetIDs.at(index);
    }
    //double lowest = distances.at(0);
    
    
    

}


int main(){

    
    cout << "Enter Locations Filename: ";
    string locationFile;
    cin >> locationFile;
    cout << "Enter Names Filename: ";
    string nameFile;
    cin >> nameFile;

    ifstream input(locationFile);
    ifstream nameinput(nameFile);
    if (!input.is_open() || !nameinput.is_open() ) {
        cout << "Input file could not be opened" << endl;
        return 1;
    }
    
    vector<Planet> planets;
    Planet planet;

    vector<PlanetName> names;
    PlanetName name;

    Ignore ignored;
    vector<Ignore> ignores;

    vector<int> starterData = loadData(planets, input);
    
    int driverRow = starterData[0];
    int driverCol = starterData[1] ;
    int StartRow = starterData[2];
    int StartCol = starterData[3];
    int EndRow = starterData[4];
    int EndCol = starterData[5];
    vector<int> ID;
    vector<string> Name;
    loadNameData(ID, Name, nameinput);
    //vector<string> nameC;
    for (int i = 0; i < Name.size(); ++i) {
        //string PlanetNamed = names.at(i).Name;
        //vector<string> named;
        //string named = Name.at(i);
        int index = Name.at(i).find("XX");
        while (index != string::npos){
            Name.at(i).erase(index, 2);
            index = Name.at(i).find("XX");

        }

        //while (index != Name.at(i).npos){
            //Name.at(i) = Name.at(i).erase(index, 2);
        //}
        
        int sindex = Name.at(i).find("_");
        while (sindex != string::npos) {
            Name.at(i).replace(sindex, 1, " ");
            sindex = Name.at(i).find("_");
        }
    
        //named.at(i)
        //create new vector
        
        
    }
    
    vector<char> mat(driverCol, '.');
    vector< vector<char> > matrix(driverRow, mat);

    matrixSymbol(matrix, planets);
    matrix.at(StartRow - 1).at(StartCol - 1) = 'S';
    matrix.at(EndRow - 1).at(EndCol - 1) = 'E';

    for (size_t i = 0; i < planets.size(); ++i) {
        planets.at(i).visited = false;
    }


    ofstream output("journey.txt");
    for (size_t row = 0; row < matrix.size(); ++row) {
        for (size_t col = 0; col < matrix.at(row).size(); ++col) {
            output << matrix.at(row).at(col);
        }
        output << endl;
    }
    
    
    
    int currentx = StartRow;
    int currenty = StartCol;
    int lowestID = planets.at(0).ID;
    int row = 0;
    int col = 0;
    string Pname;

    output << "Start at " << StartRow << " " << StartCol << endl;
    for (size_t j = 0; j < planets.size(); ++j) {
        lowestID = CalcDistance(currentx, currenty, planets);
        for (size_t i = 0; i < planets.size(); ++i) {
            if (planets.at(i).ID == lowestID) {
                row = planets.at(i).Row;
                col = planets.at(i).Column;
                planets.at(i).visited = true;
            }

        }
        for (size_t i = 0; i < planets.size(); ++i) {
            if (ID.at(i) == lowestID) {
                Pname = Name.at(i);
            }
        }
        output << "Go to " << Pname << " at " << row << " " << col << endl;
        currentx = row;
        currenty = col;

    }
    output << "End at " << EndRow << " " << EndCol << endl;

    
    
  
    
    
    

      
    
    


    

    //row and column of current location. and inputs it into the distance equation
    //and then inputs each potential planets row and column. Saves each of these distances
    //And determine which one is the shortest
    //if two planets have the same distance select planet with lower planetID.
    //mark the planet at the next location as visited.
    //planets.at(i) = visited.
    //continue selecting. for loop i < planets.size.
    //update current row/colum to the next location row/column

    
    

    //helper functions put symbols into matrix(cector of vectors) at their column and row.
    //and fill with periods first. 
    //make route using NNA.
    //then print sentences.

    
}
   

    
    


//printName(name, cout);
    //cout << endl;

    //printPlanet(planet, cout);
    //cout << endl;


   
    //if (planets.at(i).Row > driverRow) {
                //planets.erase(planets.begin() + i);
            //}
            //++i;
            //else if ()
    
    //printPlanet(planeta1, cout);
    //cout << endl;
    

   

