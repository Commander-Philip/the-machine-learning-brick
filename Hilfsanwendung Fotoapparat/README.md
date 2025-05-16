# Hilfsanwendung Fotoapparat
## Anleitung
1. Den Ordner `website` auf die SD-Karte des OpenMV Cam Boards legen.
2. Alle Einzeldateien aus dem Ordner "Hilfsanwendung Fotoapparat/src" auf die SD-Karte des OpenMV Cam Boards legen. Direkt auf die SD-Karte, nicht in einen Unterordner!
3. Hotspot am Smartphone starten (separater WLAN-Router wäre natürlich besser.
4. WLAN namen und Passwort in das Script `config.py` in die Variablen SSID und WIFI_PASSWORD eintragen
5. Das script `main.py` in der OpenMV IDE ausführen.
6. Im Serial Terminal erscheint nach dem Verbinden mit dem WLAN die IP Konfiguration. Davon die erste IP Adresse merken/kopieren.
Die Ausgabe sieht ungefähr so aus:
`WiFi Connected  ('192.168.27.114', '255.255.255.0', '192.168.27.77', '192.168.27.77')`
7. Solange die `main.py` ebenfalls auf der SD-Karte liegt, kann das Board wieder vom PC getrennt werden und mit einer Powerbank oder dem Akku versorgt werden. Wir haben nur die IP Adresse gebraucht.
8. Den PC ebenfalls mit dem Smartphone Hotspot verbinden
9. Browser öffnen
10. Adresse `http://{hier-ip-von-Schritt-6-einfügen}:8080 aufrufen
11. Nun sollte nach kurzer Ladezeit der Stream und ein Button zu sehen sein
12. Wenn man nun den Button betätigt, wird das Board ein Bild aufnehmen und auf der SD Karte im Ordner pictures speichern
        Nicht 100% Zuverlässig. Wenn man den Knopf zu schnell drückt, werden ein paar Fotos scheitern. Die Website gibt aber rückmeldung darüber.
13. Nach dem Fotografieren das Board wieder mit dem PC verbinden und als Datenträger einbinden
14. Ordner `/pictures` öffnen
15. Bilder anschauen, kopieren und verarbeiten

## CPU Takt
480 MHz
