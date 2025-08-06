# MATLAB Commands, um C Code zu generieren
Die folgenden Befehle in das Command Window eingeben:
``` MATLAB
cfg = coder.config('lib');
cfg.TargetLang = 'C';
codegen -config cfg bildvorverarbeitung.m -args {zeros(1280,720,3,'uint8')} -report
```
