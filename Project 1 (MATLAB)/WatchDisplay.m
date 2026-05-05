% Hannah Ogbuanu
% 011
% 2.10.26

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 72a7eabf-94c8-4b11-8c2c-751f9693133d
%------------------------------------------------------


%% Driver program for smartwatch display

% Clear any existing data
clear
close all

% Read in dome image
domeImg = imread("dome_area.jpg");

% Get GPS data from user
[rowN, colN, time] = GPS_data();

% Get display settings
zoomOfs = display_settings();

% Get radiation data from the scanner
radData = scan_radiation(time);

% Remove noise in the radiation data
filteredRad = removeNoise(radData, 15);

% Use heatmap and zones functions to create heatmap and zones images
heatmapImg = heatmap(domeImg, filteredRad);
zonesImg = zones(domeImg, filteredRad);

% Crop heatmap and zones images, using the cropImg function, to create
% the local version of the heatmap and zones images
cropZones = cropImg(zonesImg, rowN, colN, zoomOfs);
cropHeat  = cropImg(heatmapImg, rowN, colN, zoomOfs);

% Save the local version of these images to a graphics file
imwrite(cropHeat, 'heatmap_local.png')
imwrite(cropZones, 'zones_local.png')


%% Crop Image function

function [img] = cropImg(img, row_n, col_n, offset)
    rows = [row_n - offset, row_n + offset];
    cols = [col_n - offset, col_n + offset];
    img = img(rows(1):rows(2), cols(1):cols(2), :);
end

