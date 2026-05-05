% Hannah Ogbuanu 
% 011 
% 2.10.26

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 72a7eabf-94c8-4b11-8c2c-751f9693133d
%------------------------------------------------------

function [ rad ] = removeNoise( rad, n )
    %removeNoise Removes noise from a matrix of radiation values by
    %  applying an nxn mean filter three times.
    %       n: The size of the filter (e.g. if n=3, use a 3x3 filter)
    %     rad: a matrix of numbers representing the radiation
    %          measurements from the scanner.
    %          NOTE: A matrix obtained from a call to the scan_radiation()
    %          may be used as an input argument when calling this function,
    %          but you should NOT call scan_radiation() inside of this
    %          function!

    % Create filter matrix using passed in n value
    filterMatrix = zeros(n, n);
    filterMatrix(:, :) = 1/(n^2);

    % Use imfilter function to apply the mean filter to the radiation data
    % three times
    filteredImg = imfilter(rad, filterMatrix, 'replicate');
    filteredImg2 = imfilter(filteredImg, filterMatrix, 'replicate');
    filteredImg3 = imfilter(filteredImg2, filterMatrix, 'replicate');
    
    rad = filteredImg3;
    
end