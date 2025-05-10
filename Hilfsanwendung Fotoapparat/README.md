# Hilfsanwendung Fotoapparat
## Anleitung
1. Den Ordner `website` auf die SD-Karte des OpenMV Cam Boards legen.
2. Hotspot am Smartphone starten
3. WLAN namen und Passwort in das Script `photograph_ui.py` in die Variablen SSID und KEY eintragen
4. Das script `photograph_ui.py` aus der OpenMV IDE ausführen.
5. Im Serial Terminal die erste IP Adresse merken/kopieren, die nach dem erfolgreichen Verbinden des Boards mit dem Hotspot gedruckt wird
Die Ausgabe sieht ungefähr so aus:
`WiFi Connected  ('192.168.27.114', '255.255.255.0', '192.168.27.77', '192.168.27.77')`
6. Den PC ebenfalls mit dem Smartphone Hotspot verbinden
7. Browser öffnen
8. Adresse `http://{hier-ip-von-Schritt-5-einfügen}:8080 aufrufen
9. Nun sollte nach kurzer Ladezeit der Stream und ein Knopf zu sehen sein

## CPU Takt
480 MHz
