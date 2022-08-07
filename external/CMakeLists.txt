cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(dokun_ui_external)

# todo: compile all external library source files into static libraries to speed up compile time
# Edit: oops, I forgot that static libraries can't link to static libraries :O
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

option(DOKUN_USE_LUA51 "Build dokun-ui with Lua 5.1.5" OFF)
option(DOKUN_USE_LUA52 "Build dokun-ui with Lua 5.2.4" OFF)
option(DOKUN_USE_LUA53 "Build dokun-ui with Lua 5.3.6" OFF)
option(DOKUN_USE_LUA54 "Build dokun-ui with Lua 5.4.x" OFF)
# todo: update to Lua 5.4.4
set(lua_target "lua")
set(lua51_srcs lua/lua-5.1.5/src/lua.c lua/lua-5.1.5/src/luac.c lua/lua-5.1.5/src/lapi.c lua/lua-5.1.5/src/lcode.c lua/lua-5.1.5/src/ldebug.c lua/lua-5.1.5/src/ldo.c lua/lua-5.1.5/src/ldump.c lua/lua-5.1.5/src/lfunc.c lua/lua-5.1.5/src/lgc.c lua/lua-5.1.5/src/llex.c lua/lua-5.1.5/src/lmem.c lua/lua-5.1.5/src/lobject.c lua/lua-5.1.5/src/lopcodes.c lua/lua-5.1.5/src/lparser.c lua/lua-5.1.5/src/lstate.c lua/lua-5.1.5/src/lstring.c lua/lua-5.1.5/src/ltable.c lua/lua-5.1.5/src/ltm.c lua/lua-5.1.5/src/lundump.c lua/lua-5.1.5/src/lvm.c lua/lua-5.1.5/src/lzio.c lua/lua-5.1.5/src/lauxlib.c lua/lua-5.1.5/src/lbaselib.c lua/lua-5.1.5/src/ldblib.c lua/lua-5.1.5/src/liolib.c lua/lua-5.1.5/src/lmathlib.c lua/lua-5.1.5/src/loslib.c lua/lua-5.1.5/src/lstrlib.c lua/lua-5.1.5/src/ltablib.c lua/lua-5.1.5/src/loadlib.c lua/lua-5.1.5/src/linit.c)
set(lua52_srcs lua/lua-5.2.4/src/lua.c lua/lua-5.2.4/src/luac.c lua/lua-5.2.4/src/lapi.c lua/lua-5.2.4/src/lcode.c lua/lua-5.2.4/src/lctype.c lua/lua-5.2.4/src/ldebug.c lua/lua-5.2.4/src/ldo.c lua/lua-5.2.4/src/ldump.c lua/lua-5.2.4/src/lfunc.c lua/lua-5.2.4/src/lgc.c lua/lua-5.2.4/src/llex.c lua/lua-5.2.4/src/lmem.c lua/lua-5.2.4/src/lobject.c lua/lua-5.2.4/src/lopcodes.c lua/lua-5.2.4/src/lparser.c lua/lua-5.2.4/src/lstate.c lua/lua-5.2.4/src/lstring.c lua/lua-5.2.4/src/ltable.c lua/lua-5.2.4/src/ltm.c lua/lua-5.2.4/src/lundump.c lua/lua-5.2.4/src/lvm.c lua/lua-5.2.4/src/lzio.c lua/lua-5.2.4/src/lauxlib.c lua/lua-5.2.4/src/lbaselib.c lua/lua-5.2.4/src/lbitlib.c lua/lua-5.2.4/src/lcorolib.c lua/lua-5.2.4/src/ldblib.c lua/lua-5.2.4/src/liolib.c lua/lua-5.2.4/src/lmathlib.c lua/lua-5.2.4/src/loslib.c lua/lua-5.2.4/src/lstrlib.c lua/lua-5.2.4/src/ltablib.c lua/lua-5.2.4/src/loadlib.c lua/lua-5.2.4/src/linit.c) # 5.2 added lctype.c, lbitlib.c, and lcorolib.c
set(lua53_srcs lua/lua-5.3.6/src/lua.c lua/lua-5.3.6/src/luac.c lua/lua-5.3.6/src/lapi.c lua/lua-5.3.6/src/lcode.c lua/lua-5.3.6/src/lctype.c lua/lua-5.3.6/src/ldebug.c lua/lua-5.3.6/src/ldo.c lua/lua-5.3.6/src/ldump.c lua/lua-5.3.6/src/lfunc.c lua/lua-5.3.6/src/lgc.c lua/lua-5.3.6/src/llex.c lua/lua-5.3.6/src/lmem.c lua/lua-5.3.6/src/lobject.c lua/lua-5.3.6/src/lopcodes.c lua/lua-5.3.6/src/lparser.c lua/lua-5.3.6/src/lstate.c lua/lua-5.3.6/src/lstring.c lua/lua-5.3.6/src/ltable.c lua/lua-5.3.6/src/ltm.c lua/lua-5.3.6/src/lundump.c lua/lua-5.3.6/src/lvm.c lua/lua-5.3.6/src/lzio.c lua/lua-5.3.6/src/lauxlib.c lua/lua-5.3.6/src/lbaselib.c lua/lua-5.3.6/src/lbitlib.c lua/lua-5.3.6/src/lcorolib.c lua/lua-5.3.6/src/ldblib.c lua/lua-5.3.6/src/liolib.c lua/lua-5.3.6/src/lmathlib.c lua/lua-5.3.6/src/loslib.c lua/lua-5.3.6/src/lstrlib.c lua/lua-5.3.6/src/ltablib.c lua/lua-5.3.6/src/lutf8lib.c lua/lua-5.3.6/src/loadlib.c lua/lua-5.3.6/src/linit.c) # 5.3 added lutf8lib
set(lua54_srcs lua/lua-5.4.1/src/lua.c lua/lua-5.4.1/src/luac.c lua/lua-5.4.1/src/lapi.c lua/lua-5.4.1/src/lcode.c lua/lua-5.4.1/src/lctype.c lua/lua-5.4.1/src/ldebug.c lua/lua-5.4.1/src/ldo.c lua/lua-5.4.1/src/ldump.c lua/lua-5.4.1/src/lfunc.c lua/lua-5.4.1/src/lgc.c lua/lua-5.4.1/src/llex.c lua/lua-5.4.1/src/lmem.c lua/lua-5.4.1/src/lobject.c lua/lua-5.4.1/src/lopcodes.c lua/lua-5.4.1/src/lparser.c lua/lua-5.4.1/src/lstate.c lua/lua-5.4.1/src/lstring.c lua/lua-5.4.1/src/ltable.c lua/lua-5.4.1/src/ltm.c lua/lua-5.4.1/src/lundump.c lua/lua-5.4.1/src/lvm.c lua/lua-5.4.1/src/lzio.c lua/lua-5.4.1/src/lauxlib.c lua/lua-5.4.1/src/lbaselib.c lua/lua-5.4.1/src/lcorolib.c lua/lua-5.4.1/src/ldblib.c lua/lua-5.4.1/src/liolib.c lua/lua-5.4.1/src/lmathlib.c lua/lua-5.4.1/src/loadlib.c lua/lua-5.4.1/src/loslib.c lua/lua-5.4.1/src/lstrlib.c lua/lua-5.4.1/src/ltablib.c lua/lua-5.4.1/src/lutf8lib.c lua/lua-5.4.1/src/linit.c) # lbitlib.c removed in 5.4
if(DOKUN_USE_LUA51)
    set(lua_srcs ${lua51_srcs})
elseif(DOKUN_USE_LUA52)
    set(lua_srcs ${lua52_srcs})
elseif(DOKUN_USE_LUA53)
    set(lua_srcs ${lua53_srcs})
    add_definitions(-DLUA_LIBRARY) # required if using lua 5.3
elseif(DOKUN_USE_LUA54)
    set(lua_srcs ${lua54_srcs})
else() #if(NOT lua_srcs)
    message(STATUS "Lua version not specified. Using Lua 5.4 by default")
	set(DOKUN_USE_LUA54 ON)
	set(lua_srcs ${lua54_srcs})
endif()
# Build library (static)
add_library(${lua_target} STATIC ${lua_srcs})
# Include directories
if(DOKUN_USE_LUA51)
    target_include_directories(${lua_target} PUBLIC lua/lua-5.1.5/src/)
elseif(DOKUN_USE_LUA52)
    target_include_directories(${lua_target} PUBLIC lua/lua-5.2.4/src/)
elseif(DOKUN_USE_LUA53)
    target_include_directories(${lua_target} PUBLIC lua/lua-5.3.6/src/)
elseif(DOKUN_USE_LUA54)
    target_include_directories(${lua_target} PUBLIC lua/lua-5.4.1/src/)
endif()
# Compiler definitions
if(DOKUN_USE_LUA51)
    target_compile_definitions(${lua_target} PUBLIC DOKUN_LUA51) # this version of Lua is different from later versions. Functions have different names
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_definitions(${lua_target} PUBLIC LUA_USE_POSIX)
endif()

set(glew_target "glew")
set(glew_srcs glew/src/glew.c)
add_library(${glew_target} STATIC ${glew_srcs})
target_include_directories(${glew_target} PUBLIC glew/include/)

set(zlib_target "zlib")
set(zlib_srcs zlib/adler32.c zlib/crc32.c zlib/deflate.c zlib/inflate.c zlib/compress.c zlib/gzclose.c zlib/gzlib.c zlib/gzread.c zlib/gzwrite.c zlib/infback.c zlib/inffast.c zlib/inftrees.c zlib/trees.c zlib/uncompr.c zlib/zutil.c)
add_library(${zlib_target} STATIC ${zlib_srcs})
target_include_directories(${zlib_target} PUBLIC zlib/)
set_target_properties(${zlib_target} PROPERTIES OUTPUT_NAME "z")

set(png_target "png")
set(png_srcs png/png.c png/pngerror.c png/pngget.c png/pngmem.c png/pngpread.c png/pngread.c png/pngrio.c png/pngrtran.c png/pngrutil.c png/pngset.c png/pngtrans png/pngwio.c png/pngwrite.c png/pngwtran.c png/pngwutil.c)
add_library(${png_target} STATIC ${png_srcs})
target_include_directories(${png_target} PUBLIC png/)

set(jpeg_target "jpeg")
set(jpeg_srcs jpeg/jaricom.c jpeg/jcapimin.c jpeg/jcapistd.c jpeg/jcarith.c jpeg/jccoefct.c jpeg/jccolor.c jpeg/jcdctmgr.c jpeg/jchuff.c jpeg/jcinit.c jpeg/jcmainct.c jpeg/jcmarker.c jpeg/jcmaster.c jpeg/jcomapi.c jpeg/jcparam.c jpeg/jcprepct.c jpeg/jcsample.c jpeg/jctrans.c jpeg/jdapimin.c jpeg/jdapistd.c jpeg/jdarith.c jpeg/jdatadst.c jpeg/jdatasrc.c jpeg/jdcoefct.c jpeg/jdcolor.c jpeg/jddctmgr.c jpeg/jdhuff.c jpeg/jdinput.c jpeg/jdmainct.c jpeg/jdmarker.c jpeg/jdmaster.c jpeg/jdmerge.c jpeg/jdpostct.c jpeg/jdsample.c jpeg/jdtrans.c jpeg/jerror.c jpeg/jfdctflt.c jpeg/jfdctfst.c jpeg/jfdctint.c jpeg/jidctflt.c jpeg/jidctfst.c jpeg/jidctint.c jpeg/jmemansi.c #[[jpeg/jmemdos.c]] #[[jpeg/jmemmac.c]] jpeg/jmemmgr.c #[[jpeg/jmemname.c]] #[[jpeg/jmemnobs.c]] #[[jpeg/jpegtran.c]] jpeg/jquant1.c jpeg/jquant2.c jpeg/jutils.c)
add_library(${jpeg_target} STATIC ${jpeg_srcs})
target_include_directories(${jpeg_target} PUBLIC jpeg/)# jpeg/jpeg-6b/)

set(gif_target "gif")
set(gif_srcs gif/lib/dgif_lib.c gif/lib/egif_lib.c gif/lib/gifalloc.c gif/lib/gif_err.c gif/lib/gif_font.c gif/lib/gif_hash.c gif/lib/openbsd-reallocarray.c gif/lib/quantize.c)
add_library(${gif_target} STATIC ${gif_srcs})
target_include_directories(${gif_target} PUBLIC gif/lib/)

set(tiff_target "tiff")
set(tiff_srcs #[[tiff/libtiff/mkg3states.c]] tiff/libtiff/tif_aux.c tiff/libtiff/tif_close.c tiff/libtiff/tif_codec.c tiff/libtiff/tif_color.c tiff/libtiff/tif_compress.c tiff/libtiff/tif_dir.c tiff/libtiff/tif_dirinfo.c tiff/libtiff/tif_dirread.c tiff/libtiff/tif_dirwrite.c tiff/libtiff/tif_dumpmode.c tiff/libtiff/tif_error.c tiff/libtiff/tif_extension.c tiff/libtiff/tif_fax3.c tiff/libtiff/tif_fax3sm.c tiff/libtiff/tif_flush.c tiff/libtiff/tif_getimage.c tiff/libtiff/tif_jbig.c tiff/libtiff/tif_jpeg_12.c tiff/libtiff/tif_jpeg.c tiff/libtiff/tif_luv.c tiff/libtiff/tif_lzma.c tiff/libtiff/tif_lzw.c tiff/libtiff/tif_next.c tiff/libtiff/tif_ojpeg.c tiff/libtiff/tif_open.c tiff/libtiff/tif_packbits.c tiff/libtiff/tif_pixarlog.c tiff/libtiff/tif_predict.c tiff/libtiff/tif_print.c tiff/libtiff/tif_read.c tiff/libtiff/tif_stream.cxx tiff/libtiff/tif_strip.c tiff/libtiff/tif_swab.c tiff/libtiff/tif_thunder.c tiff/libtiff/tif_tile.c #[[tiff/libtiff/tif_unix.c]] tiff/libtiff/tif_version.c tiff/libtiff/tif_warning.c #[[tiff/libtiff/tif_win32.c]] tiff/libtiff/tif_write.c tiff/libtiff/tif_zip.c)
add_library(${tiff_target} STATIC ${tiff_srcs})
target_include_directories(${tiff_target} PUBLIC tiff/libtiff/)

set(ogg_target "ogg")
set(ogg_include_dir ogg/include/)
set(ogg_srcs ogg/src/bitwise.c ogg/src/framing.c)
add_library(${ogg_target} STATIC ${ogg_srcs})
target_include_directories(${ogg_target} PUBLIC ${ogg_include_dir})

set(vorbis_target "vorbis")
set(vorbis_srcs vorbis/lib/analysis.c #[[vorbis/lib/barkmel.c]] vorbis/lib/bitrate.c vorbis/lib/block.c vorbis/lib/codebook.c vorbis/lib/envelope.c vorbis/lib/floor0.c vorbis/lib/floor1.c vorbis/lib/info.c vorbis/lib/lookup.c vorbis/lib/lpc.c vorbis/lib/lsp.c vorbis/lib/mapping0.c vorbis/lib/mdct.c vorbis/lib/psy.c #[[vorbis/lib/psytune.c]] vorbis/lib/registry.c vorbis/lib/res0.c vorbis/lib/sharedbook.c vorbis/lib/smallft.c vorbis/lib/synthesis.c #[[vorbis/lib/tone.c]] vorbis/lib/vorbisenc.c vorbis/lib/vorbisfile.c vorbis/lib/window.c)
add_library(${vorbis_target} STATIC ${vorbis_srcs})
target_include_directories(${vorbis_target} PUBLIC ${ogg_include_dir} vorbis/include/ vorbis/lib/)

set(flac_target "flac")
set(flac_srcs flac/src/libFLAC/bitmath.c flac/src/libFLAC/bitreader.c flac/src/libFLAC/bitwriter.c flac/src/libFLAC/cpu.c flac/src/libFLAC/crc.c flac/src/libFLAC/fixed.c flac/src/libFLAC/fixed_intrin_sse2.c flac/src/libFLAC/fixed_intrin_ssse3.c flac/src/libFLAC/float.c flac/src/libFLAC/format.c flac/src/libFLAC/lpc.c flac/src/libFLAC/lpc_intrin_avx2.c flac/src/libFLAC/lpc_intrin_sse2.c flac/src/libFLAC/lpc_intrin_sse41.c flac/src/libFLAC/lpc_intrin_sse.c #[[lpc_intrin_vsx.c]] flac/src/libFLAC/md5.c flac/src/libFLAC/memory.c flac/src/libFLAC/metadata_iterators.c flac/src/libFLAC/metadata_object.c flac/src/libFLAC/ogg_decoder_aspect.c flac/src/libFLAC/ogg_encoder_aspect.c flac/src/libFLAC/ogg_helper.c flac/src/libFLAC/ogg_mapping.c flac/src/libFLAC/stream_decoder.c flac/src/libFLAC/stream_encoder.c flac/src/libFLAC/stream_encoder_framing.c flac/src/libFLAC/stream_encoder_intrin_avx2.c flac/src/libFLAC/stream_encoder_intrin_sse2.c flac/src/libFLAC/stream_encoder_intrin_ssse3.c flac/src/libFLAC/window.c flac/src/libFLAC/windows_unicode_filenames.c)
if(NOT WIN32)
    list(REMOVE_ITEM flac_srcs "flac/src/libFLAC/windows_unicode_filenames.c")
endif()
add_library(${flac_target} STATIC ${flac_srcs})
target_include_directories(${flac_target} PUBLIC ${ogg_include_dir} flac/include/ flac/src/libFLAC/include/)
target_compile_definitions(${flac_target} PUBLIC FLAC__HAS_OGG=1 HAVE_LROUND=1 FLAC__NO_DLL=1)

set(theora_target "theora")
set(theora_srcs theora/lib/analyze.c theora/lib/apiwrapper.c theora/lib/bitpack.c theora/lib/cpu.c theora/lib/decapiwrapper.c theora/lib/decinfo.c theora/lib/decode.c theora/lib/dequant.c theora/lib/encapiwrapper.c theora/lib/encfrag.c theora/lib/encinfo.c theora/lib/encode.c #[[theora/lib/encoder_disabled.c]] theora/lib/enquant.c theora/lib/fdct.c theora/lib/fragment.c theora/lib/huffdec.c theora/lib/huffenc.c theora/lib/idct.c theora/lib/info.c theora/lib/internal.c theora/lib/mathops.c theora/lib/mcenc.c theora/lib/quant.c theora/lib/rate.c theora/lib/state.c theora/lib/tokenize.c)
add_library(${theora_target} STATIC ${theora_srcs})
target_include_directories(${theora_target} PUBLIC ${ogg_include_dir} theora/include)

set(freetype2_target "freetype")
set(freetype2_srcs freetype/src/autofit/autofit.c freetype/src/base/ftbase.c freetype/src/base/ftbbox.c freetype/src/base/ftbdf.c freetype/src/base/ftbitmap.c freetype/src/base/ftcid.c freetype/src/base/ftfstype.c freetype/src/base/ftgasp.c freetype/src/base/ftglyph.c freetype/src/base/ftgxval.c freetype/src/base/ftinit.c freetype/src/base/ftmm.c freetype/src/base/ftotval.c freetype/src/base/ftpatent.c freetype/src/base/ftpfr.c freetype/src/base/ftstroke.c freetype/src/base/ftsynth.c freetype/src/base/ftsystem.c freetype/src/base/fttype1.c freetype/src/base/ftwinfnt.c freetype/src/bdf/bdf.c freetype/src/bzip2/ftbzip2.c freetype/src/cache/ftcache.c freetype/src/cff/cff.c freetype/src/cid/type1cid.c freetype/src/gzip/ftgzip.c freetype/src/lzw/ftlzw.c freetype/src/pcf/pcf.c freetype/src/pfr/pfr.c freetype/src/psaux/psaux.c freetype/src/pshinter/pshinter.c freetype/src/psnames/psnames.c freetype/src/raster/raster.c freetype/src/sfnt/sfnt.c freetype/src/smooth/smooth.c freetype/src/truetype/truetype.c freetype/src/type1/type1.c freetype/src/type42/type42.c freetype/src/winfonts/winfnt.c 
# 2.11.0
freetype/src/dlg/dlg.c freetype/src/dlg/dlgwrap.c #[[freetype/src/sdf/ftbsdf.c]] #[[freetype/src/sdf/ftsdf.c]] freetype/src/sdf/ftsdfcommon.c #[[freetype/src/sdf/ftsdfrend.c]] freetype/src/sdf/sdf.c
)
add_library(${freetype2_target} STATIC ${freetype2_srcs})
target_include_directories(${freetype2_target} PUBLIC freetype/include)
target_compile_definitions(${freetype2_target} PUBLIC FT2_BUILD_LIBRARY)

#[[
set(_target "")
set(_srcs )
add_library(${} STATIC ${_srcs})
target_include_directories(${} PUBLIC )
#set_target_properties(${} PROPERTIES PREFIX "")
]]
