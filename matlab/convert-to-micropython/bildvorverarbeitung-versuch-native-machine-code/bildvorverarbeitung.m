function output = bildvorverarbeitung(img)
%#codegen

grayImage = rgb2gray(img);

[centers, radii] = imfindcircles(grayImage, [15, 50], 'Sensitivity', 0.9)
output = [centers,radii];
end
