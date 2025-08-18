# python initialisieren

Mit pyenv python 3.11.11 installieren:

```bash
pyenv install 3.11.11
pyenv local 3.11.11
```

Dann eine Virtuelle Python umgebung erstellen (geht aber auch ohne):

```bash
python -m venv venv
source ./venv/bin/activate
```

Anschließend die Abhängigkeiten installieren

```bash
pip install --upgrade pip
pip install tensorflow numpy pillow
# oder alternativ
pip install -r python-requirements.txt
```

Mit STRG + Shift + P `Python: Interpreter auswählen` den Interpreter von dem Python im venv Ordner auswählen.

# .tflite Datei erstellen

1. Aus Matlab lässt sich mit `exportNetworkToTensorFlow(net,"tf_model")` (siehe [die offizielle Hilfe](https://de.mathworks.com/help/deeplearning/ref/exportnetworktotensorflow.html)) ein Tensorflow Modell exportieren
2. Diesen Ordner `tf_model` in diesen Ordner legen
3. 100 Bilder von den 200\*200 Pixel großen Trainingsbildern in den Ordner `Quantisierungsbilder` legen
4. Das Script mit `python convert-tensorflow-to-tflite.py` ausführen
5. Die Datei `sign-classifier.tflite` auf die SD-Karte des OpenMV Board laden
6. Die Datei `test-tflite.py` in der OpenMV IDE öffnen und ausprobieren

Die sign-classifier.tflite lässt sich mit http://netron.app in der Struktur überprüfen
