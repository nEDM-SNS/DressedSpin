######################################
#
# Clean all G4 envs
unsetenv  CLHEP_BASE_DIR
unsetenv  CLHEP_INCLUDE_DIR
unsetenv  CLHEP_LIB
unsetenv  CLHEP_LIB_DIR

unsetenv  G4ANALYSIS_USE
unsetenv  G4DEBUG
unsetenv  G4INCLUDE
unsetenv  G4INSTALL

unsetenv  G4LEDATA
unsetenv  G4LEVELGAMMADATA
unsetenv  G4NEUTRONHPDATA
unsetenv  G4RADIOACTIVEDATA

unsetenv  G4LIB
unsetenv  G4LIB_BUILD_G3TOG4
unsetenv  G4LIB_BUILD_SHARED
unsetenv  G4LIB_BUILD_STATIC
unsetenv  G4LIB_BUILD_ZLIB
unsetenv  G4LIB_USE_G3TOG4
unsetenv  G4LIB_USE_GRANULAR
unsetenv  G4LIB_USE_ZLIB

unsetenv  G4SYSTEM

unsetenv  G4UI_BUILD_WIN32_SESSION
unsetenv  G4UI_BUILD_XAW_SESSION
unsetenv  G4UI_BUILD_XM_SESSION
unsetenv  G4UI_USE_TCSH
unsetenv  G4UI_USE_WIN32
unsetenv  G4UI_USE_XAW
unsetenv  G4UI_USE_XM

unsetenv  G4VIS_BUILD_DAWN_DRIVER
unsetenv  G4VIS_BUILD_OIWIN32_DRIVER
unsetenv  G4VIS_BUILD_OIX_DRIVER
unsetenv  G4VIS_BUILD_OPENGLWIN32_DRIVER
unsetenv  G4VIS_BUILD_OPENGLXM_DRIVER
unsetenv  G4VIS_BUILD_OPENGLX_DRIVER
unsetenv  G4VIS_BUILD_RAYTRACERX_DRIVER
unsetenv  G4VIS_BUILD_VRML_DRIVER

unsetenv  G4VIS_USE_DAWN
unsetenv  G4VIS_USE_OIWIN32
unsetenv  G4VIS_USE_OIX
unsetenv  G4VIS_USE_OPENGLWIN32
unsetenv  G4VIS_USE_OPENGLX
unsetenv  G4VIS_USE_OPENGLXM
unsetenv  G4VIS_USE_RAYTRACERX
unsetenv  G4VIS_USE_VRML

######################################
#
# g4system.U
#
#+
setenv G4SYSTEM "Linux-g++"
echo "On this machine the G4SYSTEM=$G4SYSTEM"

#
# g4dirs.U
#
#+
if ( X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ) then
setenv G4INSTALL "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/src/geant4"
echo "On this machine the G4INSTALL=$G4INSTALL"
else
setenv G4INSTALL "/site/local/ups/prd/geant4/v4_9_0/Linux/geant"
echo "On this machine the G4INSTALL=$G4INSTALL"
endif

#+
if ( Xy != Xn ) then
if ( X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ) then
setenv G4INCLUDE "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include/geant4"
else
setenv G4INCLUDE "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include"
endif
echo "On this machine the G4INCLUDE=$G4INCLUDE"
#else
#setenv G4BASE "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include/geant4/source"
#echo "On this machine the G4BASE=$G4BASE"
endif

#+
if ( X/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib != X ) then
if ( X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ) then
setenv G4LIB "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib/geant4"
else
setenv G4LIB "/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib"
endif
echo "On this machine the G4LIB=$G4LIB"
endif

#+
if ( X/site/local/ups/prd/geant4data/v4_8_2/NULL/PhotonEvaporation2.0 != X ) then
setenv G4LEVELGAMMADATA "/site/local/ups/prd/geant4data/v4_8_2/NULL/PhotonEvaporation2.0"
echo "On this machine the G4LEVELGAMMADATA=$G4LEVELGAMMADATA"
endif

#+
if ( X/site/local/ups/prd/geant4data/v4_8_2/NULL/RadioactiveDecay3.2 != X ) then
setenv G4RADIOACTIVEDATA "/site/local/ups/prd/geant4data/v4_8_2/NULL/RadioactiveDecay3.2"
echo "On this machine the G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA"
endif

#+
if ( X/site/local/ups/prd/geant4data/v4_8_2/NULL/G4EMLOW4.3 != X ) then
setenv G4LEDATA "/site/local/ups/prd/geant4data/v4_8_2/NULL/G4EMLOW4.3"
echo "On this machine the G4LEDATA=$G4LEDATA"
endif

#+
if ( X/site/local/ups/prd/geant4data/v4_8_2/NULL/G4NDL3.11 != X ) then
setenv G4NEUTRONHPDATA "/site/local/ups/prd/geant4data/v4_8_2/NULL/G4NDL3.11"
echo "On this machine the G4NEUTRONHPDATA=$G4NEUTRONHPDATA"
endif

#+
#if ( X != X ) then
#setenv G4ELASTICDATA ""
#echo "On this machine the G4ELASTICDATA=$G4ELASTICDATA"
#endif

#
# g4clhep.U
#
if ( X/site/local/ups/prd/clhep/v2_0_3_1/Linux != X ) then
setenv CLHEP_BASE_DIR "/site/local/ups/prd/clhep/v2_0_3_1/Linux"
echo "On this machine the CLHEP_BASE_DIR=$CLHEP_BASE_DIR"
endif

#+
if ( X/site/local/ups/prd/clhep/v2_0_3_1/Linux/include != X ) then
setenv CLHEP_INCLUDE_DIR "/site/local/ups/prd/clhep/v2_0_3_1/Linux/include"
echo "On this machine the CLHEP_INCLUDE_DIR=$CLHEP_INCLUDE_DIR"
endif

#+
if ( X/site/local/ups/prd/clhep/v2_0_3_1/Linux/lib != X ) then
setenv CLHEP_LIB_DIR "/site/local/ups/prd/clhep/v2_0_3_1/Linux/lib"
echo "On this machine the CLHEP_LIB_DIR=$CLHEP_LIB_DIR"
endif

#+
if ( XCLHEP != X ) then
setenv CLHEP_LIB "CLHEP"
echo "On this machine the CLHEP_LIB=$CLHEP_LIB"
endif

#+
#
# g4debug
#
if ( Xn == Xy ) then
setenv G4DEBUG 1
echo "On this machine the G4DEBUG=$G4DEBUG"
endif

#
# g4analysis
#
#+
if ( Xn == Xy ) then
setenv G4ANALYSIS_USE 1
echo "On this machine the G4ANALYSIS_USE=$G4ANALYSIS_USE"
endif

#
# g4ui
#
#+
if ( Xn == Xy ) then
setenv G4UI_BUILD_XAW_SESSION 1
echo "On this machine the G4UI_BUILD_XAW_SESSION=$G4UI_BUILD_XAW_SESSION"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_USE_XAW 1
echo "On this machine the G4UI_USE_XAW=$G4UI_USE_XAW"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_BUILD_XM_SESSION 1
echo "On this machine the G4UI_BUILD_XM_SESSION=$G4UI_BUILD_XM_SESSION"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_USE_XM 1
echo "On this machine the G4UI_USE_XM=$G4UI_USE_XM"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_BUILD_WIN32_SESSION 1
echo "On this machine the G4UI_BUILD_WIN32_SESSION=$G4UI_BUILD_WIN32_SESSION"
endif

#+
if ( Xn == Xy ) then
setenv G4UI_USE_WIN32 1
echo "On this machine the G4UI_USE_WIN32=$G4UI_USE_WIN32"
endif

#
# g4vis
#
#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_DAWN_DRIVER 1
echo "On this machine the G4VIS_BUILD_DAWN_DRIVER=$G4VIS_BUILD_DAWN_DRIVER"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_BUILD_OPENGLX_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLX_DRIVER=$G4VIS_BUILD_OPENGLX_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLXM_DRIVER=$G4VIS_BUILD_OPENGLXM_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OPENGLWIN32_DRIVER 1
echo "On this machine the G4VIS_BUILD_OPENGLWIN32_DRIVER=$G4VIS_BUILD_OPENGLWIN32_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OIX_DRIVER 1
echo "On this machine the G4VIS_BUILD_OIX_DRIVER=$G4VIS_BUILD_OIX_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_RAYTRACERX_DRIVER 1
echo "On this machine the G4VIS_BUILD_RAYTRACERX_DRIVER=$G4VIS_BUILD_RAYTRACERX_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_BUILD_OIWIN32_DRIVER 1
echo "On this machine the G4VIS_BUILD_OIWIN32_DRIVER=$G4VIS_BUILD_OIWIN32_DRIVER"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_BUILD_VRML_DRIVER 1
echo "On this machine the G4VIS_BUILD_VRML_DRIVER=$G4VIS_BUILD_VRML_DRIVER"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_DAWN 1
echo "On this machine the G4VIS_USE_DAWN=$G4VIS_USE_DAWN"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_USE_OPENGLX 1
echo "On this machine the G4VIS_USE_OPENGLX=$G4VIS_USE_OPENGLX"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OPENGLXM 1
echo "On this machine the G4VIS_USE_OPENGLXM=$G4VIS_USE_OPENGLXM"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OPENGLWIN32 1
echo "On this machine the G4VIS_USE_OPENGLWIN32=$G4VIS_USE_OPENGLWIN32"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OIX 1
echo "On this machine the G4VIS_USE_OIX=$G4VIS_USE_OIX"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_RAYTRACERX 1
echo "On this machine the G4VIS_USE_RAYTRACERX=$G4VIS_USE_RAYTRACERX"
endif

#+
if ( Xn == Xy ) then
setenv G4VIS_USE_OIWIN32 1
echo "On this machine the G4VIS_USE_OIWIN32=$G4VIS_USE_OIWIN32"
endif

#+
if ( Xy == Xy ) then
setenv G4VIS_USE_VRML 1
echo "On this machine the G4VIS_USE_VRML=$G4VIS_USE_VRML"
endif

#+
if ( X != X )  then
setenv OGLHOME ""
echo "On this machine the OGLHOME=$OGLHOME"
endif 

#+
if ( X != X )  then
setenv OIVHOME ""
echo "On this machine the OIVHOME=$OIVHOME"
endif 

#+
if ( Xn != X )  then
setenv XMFLAGS ""
echo "On this machine the XMFLAGS=$XMFLAGS"
endif 

#+
if ( Xn != X )  then
setenv XMLIBS ""
echo "On this machine the XMLIBS=$XMLIBS"
endif 

#+
if ( Xn != X )  then
setenv XMFLAGS ""
echo "On this machine the XMFLAGS=$XMFLAGS"
endif 

#+
if ( Xn != X )  then
setenv XMLIBS ""
echo "On this machine the XMLIBS=$XMLIBS"
endif 

#+
if ( Xn != X )  then
setenv XAWFLAGS ""
echo "On this machine the XAWFLAGS=$XAWFLAGS"
endif 

#+
if ( Xn != X )  then
setenv XAWLIBS ""
echo "On this machine the XAWLIBS=$XAWLIBS"
endif 

#
# Use G3TOG4 module
#
#+
if ( Xn == Xy )  then
setenv G4LIB_BUILD_G3TOG4 1
echo "On this machine the G4LIB_BUILD_G3TOG4=$G4LIB_BUILD_G3TOG4"
endif 

if ( Xn == Xy )  then
setenv G4LIB_USE_G3TOG4 1
echo "On this machine the G4LIB_USE_G3TOG4=$G4LIB_USE_G3TOG4"
endif 


#
# Use ZLIB module
#
#+
if ( Xy == Xy )  then
setenv G4LIB_BUILD_ZLIB 1
echo "On this machine the G4LIB_BUILD_ZLIB=$G4LIB_BUILD_ZLIB"
endif 

if ( X == Xy )  then
setenv G4LIB_USE_ZLIB 1
echo "On this machine the G4LIB_USE_ZLIB=$G4LIB_USE_ZLIB"
endif 

#+
#
# g4shared
#
if ( Xy == Xy ) then
setenv G4LIB_BUILD_SHARED 1
echo "On this machine the G4LIB_BUILD_SHARED=$G4LIB_BUILD_SHARED"
endif

if ( Xy == Xy ) then
setenv G4LIB_BUILD_STATIC 1
echo "On this machine the G4LIB_BUILD_STATIC=$G4LIB_BUILD_STATIC"
endif

#+
#
# g4granular
#
if ( Xy == Xy ) then
setenv G4LIB_USE_GRANULAR 1
echo "On this machine the G4LIB_USE_GRANULAR=$G4LIB_USE_GRANULAR"
endif

# Check for Windows!
if ( "X$G4SYSTEM" != "XWIN32-VC" && "X$G4SYSTEM" != "XWIN32-VC7" ) then
setenv G4UI_USE_TCSH 1
echo "On this machine the G4UI_USE_TCSH=$G4UI_USE_TCSH"
endif

#####################################################################



#+
#
# G4WORKDIR
#
if ( ${?G4WORKDIR} ) then
echo "In your environment you have the G4WORKDIR=$G4WORKDIR"
else
# Check for Windows!
if ( "X$G4SYSTEM" == "XWIN32-VC" || "X$G4SYSTEM" == "XWIN32-VC7" ) then

echo "G4WORKDIR will be set to c:/geant4 (in "native" Windows syntax)."
setenv G4WORKDIR "c:/geant4"

else # if Unix

echo "G4WORKDIR will be set to HOME/geant4=$HOME/geant4"
setenv G4WORKDIR $HOME/geant4

endif
endif

#
# Shared libraries
#
if ( ${?G4LIB_BUILD_SHARED} ) then

#
# Warning about LD_LIBRARY_PATH
#
echo ''
echo 'LD_LIBRARY_PATH is set to include CLHEP and Geant4 libraries. '
echo ''
echo 'NOTE : verify that the correct path for the CLHEP library'
echo '- $CLHEP_BASE_DIR/lib - is included in the $LD_LIBRARY_PATH'
echo 'variable in your environment, and no other outdated installations'
echo 'of CLHEP are by chance referenced through $LD_LIBRARY_PATH and'
echo 'present in your system !'
echo ''

if ( ${?LD_LIBRARY_PATH} )  then
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
else
setenv LD_LIBRARY_PATH ${G4LIB}/${G4SYSTEM}
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
endif
endif

#
# Shared libraries for Mac
#
if ( "X$G4SYSTEM" == "XDarwin-g++" ) then

if ( ${?G4LIB_BUILD_SHARED} ) then
if ( ${?DYLD_LIBRARY_PATH} )  then
setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
else
setenv DYLD_LIBRARY_PATH ${G4LIB}/${G4SYSTEM}
setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
endif
endif

endif

#
# For BIN
#
setenv PATH ${PATH}:${G4WORKDIR}/bin/${G4SYSTEM}

