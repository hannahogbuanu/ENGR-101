% <Your Name> 
% <Lab Section Number> 
% <Date Submitted>

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 4d56ac82-3232-4493-bb2f-f76ce9e60751
%------------------------------------------------------

%evalyate the design constraints for a given location. 
%plotting functions shouldnt be in analyze wind farm
%return values should be 1's or zeros
%cr1,4+5 = average wind speed at location within min-max range
%cr2,6 = average wave height at location < max value
%cr3,7 = local buoy measurement of wave height < max value at least XX%
%of the time. (frequency)
%cr4,8 = all potential wave height < deck height
%cr5 = std of buoy wave height measurements < 5% of the 
%average wave height

function [ c1, c2, c3, c4, c5 ] = analyzeWindFarm(filenameWind, filenameWave, ...
    filenameBuoy, windSpeedMin, windSpeedMax,waveHeightMax, waveHeightRisk, deckHeight)
% Function to complete Task 1. Evaluates the 5 constraints on the location of a
% wind farm.
%
%   parameters: 
%          filenameWind: a string that names the file containing the 
%                        global-model-based average wind speed 
%                        (i.e. 'windSpeedTestCase.csv')
%          filenameWave: a string that names the file containing the 
%                        global-model-based average global wave heights 
%                        (i.e. 'waveHeightTestCase.csv')
%          filenameBuoy: a string that names the file containing the time 
%                        series of wave heights measured by the buoy          
%                        (i.e. 'buoyTestCase.csv')
%          windSpeedMin: for constraint 1 -- minimum wind speed (m/s)
%          windSpeedMax: for constraint 1 -- maximum wind speed (m/s)
%         waveHeightMax: for constraints 2 & 3 -- maximum wave height (m)
%        waveHeightRisk: for constraint 3 -- maximum wave height risk (%)
%            deckHeight: for constraint 4 -- height of the deck that supports 
%                        the turbine base (m)
%
%   return values:
%                    c1: boolean values corresponding to whether the wind 
%                        farm location passes constraint #1
%                    c2: boolean values corresponding to whether the wind 
%                        farm location passes constraint #2
%                    c3: boolean values corresponding to whether the wind 
%                        farm location passes constraint #3
%                    c4: boolean values corresponding to whether the wind 
%                        farm location passes constraint #4
%                    c5: boolean values corresponding to whether the wind 
%                        farm location passes constraint #5

%% YOUR CODE HERE

% Load and import all data files
windSpeed = readmatrix(filenameWind);
waveHeight = readmatrix(filenameWave);
buoyData = readtable(filenameBuoy,"VariableNamingRule","preserve");

% Save buoy location latitude and longitude variables
indexPair = buoyData{1, 2:3};
lat = indexPair(1);
lon = indexPair(2);

% Find the global-model-based average wind speed corresponding to the
% buoy location
WindSpeedI = windSpeed(lat, lon);

% Constraint 1
c1 = WindSpeedI >= windSpeedMin & WindSpeedI <= windSpeedMax ;

% Find the global-model-based average wave height corresponding to the
% buoy location
waveHeightI = waveHeight(lat, lon); 

% Constraint 2
c2 = waveHeightI < waveHeightMax;

% Get wave heights data from buoy table
waveHData = buoyData{4:end, "Lat (index)"};

% Calculate constraint 3
chosenW = waveHData < waveHeightMax;
NumWave = sum(chosenW(:));
division = NumWave ./ numel(waveHData);
c3 = division > (waveHeightRisk / 100);

% Find all rogue wave heights
rogueWaveH = 2 .* mean(waveHData);

% Calculate constraing 4
measured = rogueWaveH < deckHeight;
c4 = any(measured == 1);

% Calculate standard deviation of buoy-measured wave heights
waveHData = buoyData{4:end, "Lat (index)"};
c5 = std(waveHData) < 0.05 * waveHeightI;

end

