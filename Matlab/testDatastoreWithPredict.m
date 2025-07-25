function results = testDatastoreWithPredict(net, imds, inputSize)
    % Erwartet ein trainiertes dlnetwork 'net', ein imageDatastore 'imds',
    % sowie die gewünschte Eingabegröße (z.B. [48 48 3]).
    
    numImages = numel(imds.Files);
    results = strings(numImages, 1);

    classes = categories(imds.Labels);

    for i = 1:numImages
        % Bild lesen
        img = readimage(imds, i);
        filename = imds.Files{i};
        trueLabel = imds.Labels(i);

        % Resize auf Eingabegröße (falls nötig)
        if ~isequal(size(img,1), inputSize(1)) || ~isequal(size(img,2), inputSize(2))
            img = imresize(img, inputSize(1:2));
        end

        % Typkonvertierung (falls nötig)
        img = single(img);

        % In dlarray konvertieren ("SSC" → height, width, channels)
        dlImg = dlarray(img, 'SSC');

        % Vorhersage
        scores = predict(net, dlImg);
        [prob, idx] = max(extractdata(scores));
        predictedClass = classes{idx};

        % Formatierte Ausgabe
        results(i) = sprintf("Datei %s --- Klasse %s (%.2f%%) --- Label: %s", ...
            filename, predictedClass, prob*100, string(trueLabel));
    end
end
