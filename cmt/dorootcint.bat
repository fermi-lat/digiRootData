REM do rootcint for Digi ROOT classes

REM Save the current directory, so we can return when finished
cd > dirstor.txt
copy %DIGIROOTDATAROOT%\cmt\cd.cmd+dirstor.txt %DIGIROOTDATAROOT%\changeDir.bat
del dirstor.txt

cd %DIGIROOTDATAROOT%\digiRootData
REM Remove old cint files
del EventCint.cxx
del EventCint.h

%ROOT_PATH%\bin\rootcint -f EventCint.cxx -c ACDTile.h CalHit.h ESAPID.h Event.h L1T.h LogID.h StripID.h Tagger.h TileID.h TkrLayer.h EventLinkDef.h

REM Return to the original directory
call %DIGIROOTDATAROOT%\changeDir.bat
del %DIGIROOTDATAROOT%\changeDir.bat
