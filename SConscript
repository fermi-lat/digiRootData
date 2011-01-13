# -*- python -*-
# $Header$
# Authors: H. Kelly <heather@slac.stanford.edu>, David Chamont <chamont@poly.in2p3.fr>
# Version: digiRootData-11-14-01

Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()
locInc = listFiles(['digiRootData/*'], recursive=True)

libEnv.Tool('digiRootDataLib', depsOnly = 1)
digiRootDataRootcint = libEnv.Rootcint('digiRootData/digiRootData_rootcint',
                                       ['digiRootData/AcdDigi.h',
                                        'digiRootData/CalDiagnosticData.h',
                                        'digiRootData/CalDigi.h',
                                        'digiRootData/CalXtalReadout.h',
                                        'digiRootData/DigiEvent.h',
                                        'digiRootData/GlastAxis.h',
                                        'digiRootData/L1T.h',
                                        'digiRootData/GemTime.h',
                                        'digiRootData/TimeTone.h',
                                        'digiRootData/LsfTime.h',
                                        'digiRootData/RunInfo.h',
                                        'digiRootData/DatagramInfo.h',
                                        'digiRootData/GemScalers.h',
                                        'digiRootData/Configuration.h',
                                        'digiRootData/LsfKeys.h',
                                        'digiRootData/MetaEvent.h',
                                        'digiRootData/Ccsds.h',
                                        'digiRootData/TkrDiagnosticData.h',
                                        'digiRootData/TkrDigi.h',
                                        'digiRootData/Gem.h',
                                        'digiRootData/ErrorData.h',
                                        'digiRootData/Tem.h',
                                        'digiRootData/FilterStatus.h',
                                        'digiRootData/ObfFilterStatus.h',
                                        'digiRootData/AdfDigi.h',
                                        'digiRootData/EventSummaryData.h', 
                                        'digiRootData/LinkDef.h'], 
                                       localIncludes=locInc,
                                       includes = [''])

libEnv['rootcint_node'] = digiRootDataRootcint
                                       
digiRootData = libEnv.SharedLibrary('digiRootData', listFiles(['src/*.cxx']) + ['digiRootData/digiRootData_rootcint.cxx'])

progEnv.Tool('digiRootDataLib')
test_digiRootData = progEnv.Program('test_digiRootData',
                                    ['src/test/testDigiClasses.cxx'])
progEnv.Tool('addLibrary', library = baseEnv['ldfLibs'])
progEnv.Tool('lsfDataLib')
progEnv.Tool('facilitiesLib')
ReadFilterStats = progEnv.Program('ReadFilterStats',
                                  ['apps/ReadFilterStats.cxx',
                                   'apps/XGetopt.cxx'])

progEnv.Tool('registerTargets', package = 'digiRootData',
             rootcintSharedCxts = [[digiRootData, libEnv]], 
             testAppCxts = [[test_digiRootData, progEnv]],
             binaryCxts=[[ReadFilterStats, progEnv]],
             includes = listFiles(['digiRootData/*.h']))




