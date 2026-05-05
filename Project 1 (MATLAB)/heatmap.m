% Hannah Ogbuanu
% 011
% 2.10.26

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 72a7eabf-94c8-4b11-8c2c-751f9693133d
%------------------------------------------------------

function [ img ] = heatmap( img, rad )
    %heatmap Generates a heatmap image by using values from rad to set
    %  values in the hue channel for img. Hue values vary smoothly
    %  depending on the corresponding radiation level.
    %     img: a 3-dimensional matrix of numbers representing an image in
    %          RGB (red-green-blue) format, which forms the background
    %          to which the heatmap colors are applied.
    %     rad: a matrix of numbers representing the radiation
    %          measurements, between 0 and 100 millisieverts.
    %          It is has the same width and height as the img parameter.

    % Convert image to HSV
    imgHSV = rgb2hsv(img);

    % Pull out channels seperately and set saturation to 1 for all 
    % elements
    hue = imgHSV(:,:,1);
    sat = imgHSV(:, :, 2);
    sat(:) = 1;

    % Convert radiation levels in the rad matrix to the appropriate hue
    % value and set the hue channel to that
    hue(:) = 0.7 - 0.7 .* rad ./ 100.0;
    
    % Overlay changes to hue channel and saturation channel back on the
    % original image
    imgHSV(:, :, 1) = hue;
    imgHSV(:, :, 2) = sat;
    
    % Convert image to RGB
    imgRGB = hsv2rgb(imgHSV);
    img = imgRGB;

 
end

