% Hannah Ogbuanu
% 011
% 2.10.26

%------------------------------------------------------
% AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
% test_cases: true
% feedback('all')
% 72a7eabf-94c8-4b11-8c2c-751f9693133d
%------------------------------------------------------

function [ hasTumor ] = detectTumor( brain )
    %detectTumor Returns whether or not a tumor was found in the image.
    %     brain: a matrix of numbers representing a grayscale image of a 
    %            brain scan. Bright areas may be tumors and need to
    %            be flagged for further testing.
    %            To get test data for this function, you may call the
    %            provided scan_brain() function and pass the value it
    %            returns into this function. However, DO NOT call
    %            scan_brain() in the code for this function itself.

    % Set threshold value for white pixels of tumor
    threshold = 0.7;

    % Remove noise from brain scan image
    filteredBrain = removeNoise(brain, 15);

    % Logically index possible tumor areas by filtering out darker values
    locationTumor = filteredBrain >= threshold;

    % Return a logical value of 1 for true or 0 for false if a tumor was
    % detected
    hasTumor = any(locationTumor(:)) == 1;

end

