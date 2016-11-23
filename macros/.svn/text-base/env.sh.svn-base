######################################
#
# Clean all G4 envs
unset  CLHEP_BASE_DIR
unset  CLHEP_INCLUDE_DIR
unset  CLHEP_LIB
unset  CLHEP_LIB_DIR

unset  G4ANALYSIS_USE
unset  G4DEBUG
unset  G4INCLUDE
unset  G4INSTALL

unset  G4LEDATA
unset  G4LEVELGAMMADATA
unset  G4NEUTRONHPDATA
unset  G4RADIOACTIVEDATA

unset  G4LIB
unset  G4LIB_BUILD_G3TOG4
unset  G4LIB_BUILD_SHARED
unset  G4LIB_BUILD_STATIC
unset  G4LIB_BUILD_ZLIB
unset  G4LIB_USE_G3TOG4
unset  G4LIB_USE_GRANULAR
unset  G4LIB_USE_ZLIB

unset  G4SYSTEM

unset  G4UI_BUILD_WIN32_SESSION
unset  G4UI_BUILD_XAW_SESSION
unset  G4UI_BUILD_XM_SESSION
unset  G4UI_USE_TCSH
unset  G4UI_USE_WIN32
unset  G4UI_USE_XAW
unset  G4UI_USE_XM

unset  G4VIS_BUILD_DAWN_DRIVER
unset  G4VIS_BUILD_OIWIN32_DRIVER
unset  G4VIS_BUILD_OIX_DRIVER
unset  G4VIS_BUILD_OPENGLWIN32_DRIVER
unset  G4VIS_BUILD_OPENGLXM_DRIVER
unset  G4VIS_BUILD_OPENGLX_DRIVER
unset  G4VIS_BUILD_RAYTRACERX_DRIVER
unset  G4VIS_BUILD_VRML_DRIVER

unset  G4VIS_USE_DAWN
unset  G4VIS_USE_OIWIN32
unset  G4VIS_USE_OIX
unset  G4VIS_USE_OPENGLWIN32
unset  G4VIS_USE_OPENGLX
unset  G4VIS_USE_OPENGLXM
unset  G4VIS_USE_RAYTRACERX
unset  G4VIS_USE_VRML


#
# g4system.U
#
#+
G4SYSTEM="Linux-g++"
export G4SYSTEM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4SYSTEM=$G4SYSTEM"
fi

#
# g4dirs.U
#
#+
if [ X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ] ; then
G4INSTALL="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/src/geant4"
else
G4INSTALL="/site/local/ups/prd/geant4/v4_9_0/Linux/geant"
fi
export G4INSTALL
if [ X$g4non_display = X ] ; then
echo "On this machine the G4INSTALL=$G4INSTALL"
fi

#+
if [ Xy != Xn ] ; then 
if [ X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ] ; then
G4INCLUDE="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include/geant4"
else
G4INCLUDE="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include/"
fi
export G4INCLUDE
if [ X$g4non_display = X ] ; then
echo "On this machine the G4INCLUDE=$G4INCLUDE"
fi
#else
#G4BASE="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/include/geant4/source"
#export G4BASE
#if [ X$g4non_display = X ] ; then
#echo "On this machine the G4BASE=$G4BASE"
#fi
fi

#+
if [ X/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib != X ] ; then 
if [ X/site/local/ups/prd/geant4/v4_9_0/Linux/geant != X/site/local/ups/prd/geant4/v4_9_0/Linux/geant ] ; then
G4LIB="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib/geant4"
else
G4LIB="/site/local/ups/prd/geant4/v4_9_0/Linux/geant/lib"
fi
export G4LIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB=$G4LIB"
fi
fi

#+
if [ X/site/local/ups/prd/geant4data/v4_8_2/NULL/PhotonEvaporation2.0 != X ] ; then 
G4LEVELGAMMADATA="/site/local/ups/prd/geant4data/v4_8_2/NULL/PhotonEvaporation2.0"
export G4LEVELGAMMADATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LEVELGAMMADATA=$G4LEVELGAMMADATA"
fi
fi

#+
if [ X/site/local/ups/prd/geant4data/v4_8_2/NULL/RadioactiveDecay3.2 != X ] ; then 
G4RADIOACTIVEDATA="/site/local/ups/prd/geant4data/v4_8_2/NULL/RadioactiveDecay3.2"
export G4RADIOACTIVEDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA"
fi
fi

#+
if [ X/site/local/ups/prd/geant4data/v4_8_2/NULL/G4EMLOW4.3 != X ] ; then 
G4LEDATA="/site/local/ups/prd/geant4data/v4_8_2/NULL/G4EMLOW4.3"
export G4LEDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LEDATA=$G4LEDATA"
fi
fi

#+
if [ X/site/local/ups/prd/geant4data/v4_8_2/NULL/G4NDL3.11 != X ] ; then 
G4NEUTRONHPDATA="/site/local/ups/prd/geant4data/v4_8_2/NULL/G4NDL3.11"
export G4NEUTRONHPDATA
if [ X$g4non_display = X ] ; then
echo "On this machine the G4NEUTRONHPDATA=$G4NEUTRONHPDATA"
fi
fi

#+
#if [ X != X ] ; then 
#G4ELASTICDATA=""
#export G4ELASTICDATA
#if [ X$g4non_display = X ] ; then
#echo "On this machine the G4ELASTICDATA=$G4ELASTICDATA"
#fi
#fi

#
# g4clhep.U
#
if [ X/site/local/ups/prd/clhep/v2_0_3_1/Linux != X ] ; then 
CLHEP_BASE_DIR="/site/local/ups/prd/clhep/v2_0_3_1/Linux"
export CLHEP_BASE_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_BASE_DIR=$CLHEP_BASE_DIR"
fi
fi

#+
if [ X/site/local/ups/prd/clhep/v2_0_3_1/Linux/include != X ] ; then 
CLHEP_INCLUDE_DIR="/site/local/ups/prd/clhep/v2_0_3_1/Linux/include"
export CLHEP_INCLUDE_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_INCLUDE_DIR=$CLHEP_INCLUDE_DIR"
fi
fi

#+
if [ X/site/local/ups/prd/clhep/v2_0_3_1/Linux/lib != X ] ; then 
CLHEP_LIB_DIR="/site/local/ups/prd/clhep/v2_0_3_1/Linux/lib"
export CLHEP_LIB_DIR
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_LIB_DIR=$CLHEP_LIB_DIR"
fi
fi

#+
if [ XCLHEP != X ] ; then 
CLHEP_LIB="CLHEP"
export CLHEP_LIB
if [ X$g4non_display = X ] ; then
echo "On this machine the CLHEP_LIB=$CLHEP_LIB"
fi
fi

#+
#
# g4debug
#
if [ Xn = Xy ] ; then 
G4DEBUG=1
export G4DEBUG
if [ X$g4non_display = X ] ; then
echo "On this machine the G4DEBUG=$G4DEBUG"
fi
fi

#
# g4analysis
#
#+
if [ Xn = Xy ] ; then
G4ANALYSIS_USE=1
export G4ANALYSIS_USE
if [ X$g4non_display = X ] ; then
echo "On this machine the G4ANALYSIS_USE=$G4ANALYSIS_USE"
fi
fi 

#
# g4ui
#
#+
if [ Xn = Xy ] ; then
G4UI_BUILD_XAW_SESSION=1
export G4UI_BUILD_XAW_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_XAW_SESSION=$G4UI_BUILD_XAW_SESSION"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_USE_XAW=1
export G4UI_USE_XAW
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_XAW=$G4UI_USE_XAW"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_BUILD_XM_SESSION=1
export G4UI_BUILD_XM_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_XM_SESSION=$G4UI_BUILD_XM_SESSION"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_USE_XM=1
export G4UI_USE_XM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_XM=$G4UI_USE_XM"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_BUILD_WIN32_SESSION=1
export G4UI_BUILD_WIN32_SESSION
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_BUILD_WIN32_SESSION=$G4UI_BUILD_WIN32_SESSION"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4UI_USE_WIN32=1
export G4UI_USE_WIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_WIN32=$G4UI_USE_WIN32"
fi
fi 

#
# g4vis
#
#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_DAWN_DRIVER=1
export G4VIS_BUILD_DAWN_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_DAWN_DRIVER=$G4VIS_BUILD_DAWN_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_OPENGLX_DRIVER=1
export G4VIS_BUILD_OPENGLX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLX_DRIVER=$G4VIS_BUILD_OPENGLX_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OPENGLXM_DRIVER=1
export G4VIS_BUILD_OPENGLXM_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLXM_DRIVER=$G4VIS_BUILD_OPENGLXM_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OPENGLWIN32_DRIVER=1
export G4VIS_BUILD_OPENGLWIN32_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OPENGLWIN32_DRIVER=$G4VIS_BUILD_OPENGLWIN32_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OIX_DRIVER=1
export G4VIS_BUILD_OIX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OIX_DRIVER=$G4VIS_BUILD_OIX_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_RAYTRACERX_DRIVER=1
export G4VIS_BUILD_RAYTRACERX_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_RAYTRACERX_DRIVER=$G4VIS_BUILD_RAYTRACERX_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_BUILD_OIWIN32_DRIVER=1
export G4VIS_BUILD_OIWIN32_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_OIWIN32_DRIVER=$G4VIS_BUILD_OIWIN32_DRIVER"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_BUILD_VRML_DRIVER=1
export G4VIS_BUILD_VRML_DRIVER
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_BUILD_VRML_DRIVER=$G4VIS_BUILD_VRML_DRIVER"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_DAWN=1
export G4VIS_USE_DAWN
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_DAWN=$G4VIS_USE_DAWN"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_OPENGLX=1
export G4VIS_USE_OPENGLX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLX=$G4VIS_USE_OPENGLX"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OPENGLXM=1
export G4VIS_USE_OPENGLXM
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLXM=$G4VIS_USE_OPENGLXM"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OPENGLWIN32=1
export G4VIS_USE_OPENGLWIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OPENGLWIN32=$G4VIS_USE_OPENGLWIN32"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OIX=1
export G4VIS_USE_OIX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OIX=$G4VIS_USE_OIX"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_RAYTRACERX=1
export G4VIS_USE_RAYTRACERX
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_RAYTRACERX=$G4VIS_USE_RAYTRACERX"
fi
fi 

#+
if [ Xn = Xy ] ; then
G4VIS_USE_OIWIN32=1
export G4VIS_USE_OIWIN32
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_OIWIN32=$G4VIS_USE_OIWIN32"
fi
fi 

#+
if [ Xy = Xy ] ; then
G4VIS_USE_VRML=1
export G4VIS_USE_VRML
if [ X$g4non_display = X ] ; then
echo "On this machine the G4VIS_USE_VRML=$G4VIS_USE_VRML"
fi
fi 

#+
if [ X != X ] ; then
OGLHOME=""
export OGLHOME
if [ X$g4non_display = X ] ; then
echo "On this machine the OGLHOME=$OGLHOME"
fi
fi 

#+
if [ X != X ] ; then
OIVHOME=""
export OIVHOME
if [ X$g4non_display = X ] ; then
echo "On this machine the OIVHOME=$OIVHOME"
fi
fi 

#+
if [ Xn != X ] ; then
XMFLAGS=""
export XMFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMFLAGS=$XMFLAGS"
fi
fi 

#+
if [ Xn != X ] ; then
XMLIBS=""
export XMLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMLIBS=$XMLIBS"
fi
fi 

#+
if [ Xn != X ] ; then
XMFLAGS=""
export XMFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMFLAGS=$XMFLAGS"
fi
fi 

#+
if [ X != X ] ; then
XMLIBS=""
export XMLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XMLIBS=$XMLIBS"
fi
fi 

#+
if [ Xn != X ] ; then
XAWFLAGS=""
export XAWFLAGS
if [ X$g4non_display = X ] ; then
echo "On this machine the XAWFLAGS=$XAWFLAGS"
fi
fi 

#+
if [ Xn != X ] ; then
XAWLIBS=""
export XAWLIBS
if [ X$g4non_display = X ] ; then
echo "On this machine the XAWLIBS=$XAWLIBS"
fi
fi 

#
# Use G3TOG4 module
#
#+
if [ Xn = Xy ] ; then
G4LIB_BUILD_G3TOG4=1
export G4LIB_BUILD_G3TOG4
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_G3TOG4=$G4LIB_BUILD_G3TOG4"
fi
fi 

if [ Xn = Xy ] ; then
G4LIB_USE_G3TOG4=1
export G4LIB_USE_G3TOG4
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_G3TOG4=$G4LIB_USE_G3TOG4"
fi
fi 

#
# Use ZLIB module
#
#+
if [ Xy = Xy ] ; then
G4LIB_BUILD_ZLIB=1
export G4LIB_BUILD_ZLIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_ZLIB=$G4LIB_BUILD_ZLIB"
fi
fi 

if [ Xy = Xy ] ; then
G4LIB_USE_ZLIB=1
export G4LIB_USE_ZLIB
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_ZLIB=$G4LIB_USE_ZLIB"
fi
fi 


#+
#
# g4shared
#
if [ Xy = Xy ] ; then
G4LIB_BUILD_SHARED=1
export G4LIB_BUILD_SHARED
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_SHARED=$G4LIB_BUILD_SHARED"
fi
fi 

if [ Xy = Xy ] ; then
G4LIB_BUILD_STATIC=1
export G4LIB_BUILD_STATIC
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_BUILD_STATIC=$G4LIB_BUILD_STATIC"
fi
fi 

#+
#
# g4granular
#
if [ Xy = Xy ] ; then
G4LIB_USE_GRANULAR=1
export G4LIB_USE_GRANULAR
if [ X$g4non_display = X ] ; then
echo "On this machine the G4LIB_USE_GRANULAR=$G4LIB_USE_GRANULAR"
fi
fi 

# Check for Windows!
if test "X$G4SYSTEM" != "XWIN32-VC" -a "X$G4SYSTEM" != "XWIN32-VC7"; then
#+
#
# UI_USE_TCSH for Unix
#
G4UI_USE_TCSH=1
export G4UI_USE_TCSH
if [ X$g4non_display = X ] ; then
echo "On this machine the G4UI_USE_TCSH=$G4UI_USE_TCSH"
fi 
fi

#####################################################################



#+
#
# G4WORKDIR
#
if [ $G4WORKDIR ] ; then

if [ X\$g4non_display = X ] ; then
echo "In your environment you have the G4WORKDIR=$G4WORKDIR"
fi

else

# Check for Windows!
if test "X$G4SYSTEM" = "XWIN32-VC" -o "X$G4SYSTEM" = "XWIN32-VC7"; then

if [ X\$g4non_display = X ] ; then
echo "G4WORKDIR will be set to c:/geant4 (in "native" Windows syntax)"
fi

G4WORKDIR="c:/geant4"
export G4WORKDIR

else # if Unix

if [ X\$g4non_display = X ] ; then
echo "G4WORKDIR will be set to HOME/geant4=$HOME/geant4"
fi

G4WORKDIR=$HOME/geant4
export G4WORKDIR

fi # if platforms

fi




#
# Shared libraries
#
if [ $G4LIB_BUILD_SHARED ] ; then
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

if [ $LD_LIBRARY_PATH ] ; then
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
export LD_LIBRARY_PATH
else
LD_LIBRARY_PATH=${G4LIB}/${G4SYSTEM}
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
export LD_LIBRARY_PATH
fi
fi

#
# Shared libraries for Mac
#
if test "X$G4SYSTEM" = "XDarwin-g++" ; then

if [ $G4LIB_BUILD_SHARED ] ; then
if [ $DYLD_LIBRARY_PATH ] ; then
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
export DYLD_LIBRARY_PATH
else
DYLD_LIBRARY_PATH=${G4LIB}/${G4SYSTEM}
DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${CLHEP_BASE_DIR}/lib
export DYLD_LIBRARY_PATH
fi
fi

fi

#
# For BIN
#
PATH=${PATH}:${G4WORKDIR}/bin/${G4SYSTEM}
export PATH

