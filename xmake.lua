-- project("testfolly")
-- 设置 C++ 标准为 C++17
set_languages("c++17")
add_includedirs("include")

add_rules("mode.debug", "mode.release")

package("libaio")
    set_homepage("https://gitlab.kernel.org/pub/scm/libs/libaio/libaio.git")
    set_description("Linux-native asynchronous I/O access library")
    set_license("LGPL-2.1-or-later")

    set_urls("https://deb.debian.org/debian/pool/main/liba/libaio/libaio_$(version).orig.tar.gz",
             "https://mirrors.aliyun.com/debian/pool/main/liba/libaio/libaio_$(version).orig.tar.gz")
    add_versions("0.3.113", "2c44d1c5fd0d43752287c9ae1eb9c023f04ef848ea8d4aafa46e9aedb678200b")

    add_configs("shared", {description = "Build shared library.", default = true, type = "boolean", readonly = true})

    on_install("linux", function (package)
        io.replace("Makefile", "prefix=/usr", "prefix=" .. package:installdir())
        import("package.tools.make").make(package, {})
        import("package.tools.make").make(package, {"install"})
    end)

    on_test(function (package)
        assert(package:has_cfuncs("io_setup", {includes = "libaio.h"}))
    end)
package_end()

add_requires("folly 2024.10.07")

target("testfolly")
    set_kind("binary")
    add_files("src/clh_example.cpp")
    add_packages("folly")
    before_build(function (target)
        target:add("defines", "DROGON_USE_MYSQL=OFF")
    end)
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

