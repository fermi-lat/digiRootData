REM do rootcint for Event classes
cd ..\digiRootData
%ROOTSYS%\bin\rootcint -f EventCint.cxx -c AcdHeader.h AcdId.h AcdTile.h CalHeader.h CalLog.h ESAPID.h Event.h L1T.h LogId.h StripId.h SubSystemHeader.h Tagger.h TkrHeader.h TkrLayer.h EventLinkDef.h
