project( Game_ClientFX )

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
  ../../Engine/sdk/inc/ltmemhook.cpp
  ../../Engine/sdk/inc/ltmodule.cpp
  ../../Engine/sdk/inc/ltobjref.cpp
  MemoryPageMgr.cpp
  OverlayFX.cpp
  ParticleSimulation.cpp
  ParticleSystemFX.cpp
  ParticleSystemGroup.cpp
  ParticleSystemProps.cpp
  ../../Engine/sdk/inc/performancemonitorhook.cpp
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
  ../../Engine/sdk/inc
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
)
endif(WIN32)

add_library( ${project} SHARED ${SOURCES} )

target_link_libraries( ${project} shared_assert )
