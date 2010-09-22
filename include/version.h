#ifndef SAM_VERSION_H
#define SAM_VERSION_H

#ifdef  __cplusplus
extern "C" {
#endif

#define SAM_NAME "SAM-FS"
#define SAM_MAJORV "4.6"
#define SAM_MINORV "0"
#define SAM_FIXV "73"
#define SAM_VERSION SAM_MAJORV "." SAM_FIXV
#define SAM_BUILD_INFO SAM_VERSION ", knuckleball-mn 2008-12-13 03:40:45"
#define SAM_BUILD_UNAME "SunOS knuckleball-mn 5.10 Generic_137138-09 i86pc i386 i86pc"
/* the sam_license_file is relative to the SAMPATH */
#define  SAM_LICENSE_FILE    "LICENSE." SAM_MAJORV

#ifdef  __cplusplus
}
#endif

#endif /* SAM_VERSION_H */
