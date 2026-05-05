% <Your Name>  
% <Lab Section Number> 
% <Date Submitted>

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 4d56ac82-3232-4493-bb2f-f76ce9e60751
%------------------------------------------------------


function [  ] = makePlots( filenameWind, filenameWave, filenameBuoy, ...
    windSpeedMin, windSpeedMax, waveHeightMax )

%   Function to complete Task 2. Creates a figure with multiple plots that 
%   summarizes the environmental conditions for a wind farm.  Saves figure as 
%   a .png file.
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
%         waveHeightMax: for constraint 2 -- maximum wave height (m)
%
%   return values: none
%
%   notes:
%       Feel free to use different variable names than these if it makes 
%       your code more readable to you.  These are internal to your 
%       function, so it doesn't matter what you call them.

    %% Load the data
    
    % Get lat/lon data
    lat = csvread('lat.csv');
    lon = csvread('lon.csv');
    
    
    % Read in the rest of the data you need...
    buoyData = readtable(filenameBuoy,"VariableNamingRule","preserve");
    waveHData = buoyData{4:end, "Lat (index)"};
    windSpeed = readmatrix(filenameWind);
    waveHeight = readmatrix(filenameWave);
    lat = readmatrix('lat.csv');
    lon = readmatrix('lon.csv');
    
    %% Plot 1
    
    % Set first graph in plot 1 using the subplot function
    subplot(3,2,1);
    
    % Use meshgrid function on latitude and longitude vectors
    [X, Y] = meshgrid(lon, lat);
    
    % Plot contourf graph of the average wind speed vs. latitude and longitude
    contourf(X, Y, windSpeed, 'LineStyle','none');
    
    % Set colormap to parula and add a colorbar to the figure
    colormap('parula');
    c = colorbar;
    
    % Set all other details of the graph to match image in the specs
    title('Average Wind Speed (m/s) Across Planet');
    xlabel('longitude (deg)');
    ylabel('latitude (deg)');
    
    %% Plot 2
    
    % Set second graph in plot 2 using the subplot function
    subplot(3,2,2);
    
    % Use meshgrid function on latitude and longitude vectors
    [A, B] = meshgrid(lon, lat);
    
    % Plot contourf graph of the average wave height vs. latitude and 
    % longitude
    contourf(A, B, waveHeight, 'LineStyle','none');
    
    % Set colormap to parula and add a colorbar to the figure
    colormap('parula');
    c = colorbar;
    
    % Set all other details of the graph to match image in the specs
    title('Average Wave Height (m) Across Planet');
    xlabel('longitude (deg)');
    ylabel('latitude (deg)');
    
    %% Plot 3
    
    % Set third graph in plot 3 using the subplot function
    subplot(3,2,3);
    
    % Use meshgrid function on latitude and longitude vectors
    [M, N] = meshgrid(lon, lat);
    
    % Set constraint 1 and constraint 2
    chosen = (windSpeed >= windSpeedMin & windSpeed <= windSpeedMax) & (waveHeight < waveHeightMax);
    
    % Plot contourf map of all potential wind farm locations based on
    % constraints 1 & 2 vs. latitude and longitude
    contourf(M, N, chosen, 'LineStyle', 'none');
    
    % Apply gray colormap in reverse
    ax = gca;
    colormap(ax, flipud(gray));
    
    % Use scatter function to plot the buoy location to match specs image
    hold on;
    
    indexPair = buoyData{1, 2:3};
    lat1 = indexPair(1);
    lon1 = indexPair(2);
    RealLat = lat(lat1);
    RealLon = lon(lon1);
    
    
    p = scatter(RealLon, RealLat, 200, "red", 'Marker','square');
    p.LineWidth = 3;
    
    
    title('Potential Wind Farm Locations');
    xlabel('longitude (deg)');
    ylabel('latitude (deg)');
    
    hold off;
    
    %% Plot 4
    
    % Set fourth graph in plot 4 using the subplot function
    subplot(3, 2, 4);
    
    % Plot histogram of buoy measured wave heights to match specs image
    histogram(waveHData);
    xlabel('wave height (m)');
    ylabel('number of occurrences');
    title('Wave Heights at Buoy Location');
    grid on
    
    %% Plot 5
    
    indexPair = buoyData{1, 2:3};
    lat = indexPair(1);
    lon = indexPair(2);
    waveHeightI = waveHeight(lat, lon);
    
    % Set fifth graph in plot 5 using the subplot function
    subplot(3,1,3);
    
    % Pull both wave height and time series data out of buoy Table
    waveHData = buoyData{4:end, "Lat (index)"};
    TimeHData = buoyData{4:end, 'Year'};
    
    % Plot the buoy measured wave heights vs. time using the data from the 
    % buoy
    plot(TimeHData, waveHData);
    
    hold on;
    
    % Plot the average wave height vs. time using the time data from the
    % buoy's measurements
    [T W] = meshgrid(TimeHData, waveHeightI);
    plot(T, W)
    
    % Add all features of graph to match image in project specs
    legend('Buoy-measured', 'Global average');
    xlabel('time (hours)');
    ylabel('wave height (m)');
    title('Wave Height Comparison: Global to Local');
    
    grid on
    
    % Save figure
    print('environmentalSummary.png', '-dpng');

end

