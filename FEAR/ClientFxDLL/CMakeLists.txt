project( FEAR_ClientFX )

set(SOURCES
  BaseCreateFX.cpp
  BaseFx.cpp
  BaseSpriteFX.cpp
  CameraShakeFX.cpp
  clientfx.cpp
  ClientFXVertexDeclMgr.cpp
  CreateFX.cpp
  CreateRayFX.cpp
  DebrisSystemFX.cpp
  DebrisSystemProps.cpp
  ../Shared/DebugNew.cpp
  DecalFX.cpp
  dynalightfx.cpp
  FlareSpriteFX.cpp
  LensFlareFX.cpp
  lightningfx.cpp
  LightningProps.cpp
  ltbmodelfx.cpp
  ../../sdk/inc/ltmemhook.cpp
  ../../sdk/inc/ltmodule.cpp
  ../../sdk/inc/ltobjref.cpp
  MemoryPageMgr.cpp
  OverlayFX.cpp
  ParticleSimulation.cpp
  ParticleSystemFX.cpp
  ParticleSystemGroup.cpp
  ParticleSystemProps.cpp
  ../../sdk/inc/performancemonitorhook.cpp
  PolyTrailFX.cpp
  PolyTrailProps.cpp
  RumbleFX.cpp
  Soundfx.cpp
  spritefx.cpp
  stdafx.cpp
  TracerFX.cpp
  VideoControllerFX.cpp
)

include_directories(
  ../../sdk/inc
  ../../libs/platform
  ../../libs/stdlith
  ../shared
)

add_definitions(
  -DMEMTRACK_CLIENTFX
  -D_DEBUG
)
if(WIN32)
add_definitions(
  -DWIN32
  -D_WINDOWS
)
else(WIN32)
add_definitions(
  -D_LINUX
  -D__LINUX
)
endif(WIN32)

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} shared_assert )

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive --std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)
