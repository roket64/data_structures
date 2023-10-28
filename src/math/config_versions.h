#ifndef CONFIG_VERSIONS_H
#define CONFIG_VERSIONS_H

#if defined(__clang__) && defined(__apple_build_version__)
#define APPLE_CLANG_VERSION \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__clang__)
#define CLANG_VERSION \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

#if (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)
#define GCC_VERSION \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if defined(__clang__) && ((defined(__GNUG__) || defined(__GNUC__)))
#define CLANG_VERSION \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

#if defined(__INTEL_COMPILER)
#define ICC_VERSION __INTEL_COMPILER
#endif

#if defined(_MSC_VER)
#define MSVC_VERSION _MSC_VER
#endif

#endif  // config_versions.h