set(ARTEFACTS_DIR ${CMAKE_CURRENT_LIST_DIR}/../artefacts)
if (THIRDPARTY_PLATFORM_OVERRIDE)
	set(PACKAGE_PLATFORM ${THIRDPARTY_PLATFORM_OVERRIDE})
	set(PACKAGE_PLATFORM_DEBUG ${THIRDPARTY_PLATFORM_OVERRIDE})
elseif (UNIX)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(PACKAGE_PLATFORM "lnx64_s_gcc_rel_stdcpp")
		set(PACKAGE_PLATFORM_DEBUG "lnx64_s_gcc_rel_stdcpp")
	else ()
		set(PACKAGE_PLATFORM "lnx32_s_gcc_rel_stdcpp")
		set(PACKAGE_PLATFORM_DEBUG "lnx32_s_gcc_rel_stdcpp")
	endif ()
elseif (MSVC)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(PACKAGE_PLATFORM "win64_s_vc_rel_mt")
		set(PACKAGE_PLATFORM_DEBUG "win64_s_vc_rel_mtd")
	else ()
		set(PACKAGE_PLATFORM "win32_s_vc_rel_mt")
		set(PACKAGE_PLATFORM_DEBUG "win32_s_vc_rel_mtd")
	endif ()
endif ()
