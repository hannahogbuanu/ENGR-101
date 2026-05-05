% Hannah Ogbuanu
% 011
% 2.10.26

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 72a7eabf-94c8-4b11-8c2c-751f9693133d
%------------------------------------------------------

function [ img ] = zones( img, rad )
    %zones Generates an image colored according to radiation threat 
    %  zones. Values from rad are used to determine the zone, and the hue
    %  value in img is set accordingly.
    %     img: a 3-dimensional matrix of numbers representing an image in
    %          RGB (red-green-blue) format, which forms the background for
    %          to which the heatmap colors are applied.
    %     rad: a matrix of numbers representing the radiation
    %          measurements, between 0 and 100 millisieverts.
    %          It is has the same width and height as the img parameter.

    % Convert image to HSV
    imgHSV = rgb2hsv(img);

    % Pull out image channels and set saturation to 1 for all elements
    hue = imgHSV(:,:,1);
    sat = imgHSV(:, :, 2);
    sat = 1;

    % Set values to each radiation range based on given table
    radLvl1 = rad >= 0 & rad < 20;
    radLvl2 = rad >= 20 & rad < 50;
    radLvl3 = rad >= 50 & rad < 70; 
    radLvl4 = rad >= 70 & rad < 90;
    radLvl5 = rad >= 90;

    % Set values to separate hue variables based on given table
    hue1 = 0.6;
    hue2 = 0.4;
    hue3 = 0.2;
    hue4 = 0.1;
    hue5 = 0;

    % Overlay colors on the image of the settlement area using the
    % appropriate hue level depending on the radiation range
    hue(radLvl1) = hue1;
    hue(radLvl2) = hue2;
    hue(radLvl3) = hue3;
    hue(radLvl4) = hue4;
    hue(radLvl5) = hue5;

    imgHSV(:, :, 1) = hue;
    imgHSV(:, :, 2) = sat;
 
    % Convert image back to RGB
    imgRGB = hsv2rgb(imgHSV);
    img = imgRGB;


end

