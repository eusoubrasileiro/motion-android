/*   This file is part of Motion.
 *
 *   Motion is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   Motion is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Motion.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 *  logger.h
 *    Headers associated with functions in the logger.c module.
 *    Copyright 2005, William M. Brack
 *    Copyright 2008 by Angel Carpintero  (motiondevelop@gmail.com)
 */

#ifndef _INCLUDE_LOGGER_H_
#define _INCLUDE_LOGGER_H_

#include "motion.h"
#include <syslog.h>
#include <android/log.h>

/* Logging mode */
#define LOGMODE_NONE            0   /* No logging             */
#define LOGMODE_FILE            1   /* Log messages to file   */
#define LOGMODE_SYSLOG          2   /* Log messages to syslog */

#define NO_ERRNO                0   /* Flag to avoid how message associated to errno */
#define SHOW_ERRNO              1   /* Flag to show message associated to errno */

/* Log levels */
#define LOG_ALL                 9
#define EMG                     LOG_EMERG     /* syslog 0 motion 1 */
#define ALR                     LOG_ALERT     /* syslog 1 motion 2 */
#define CRT                     LOG_CRIT      /* syslog 2 motion 3 */
#define ERR                     LOG_ERR       /* syslog 3 motion 4 */
#define WRN                     LOG_WARNING   /* syslog 4 motion 5 */
#define NTC                     LOG_NOTICE    /* syslog 5 motion 6 */
#define INF                     LOG_INFO      /* syslog 6 motion 7 */
#define DBG                     LOG_DEBUG     /* syslog 7 motion 8 */
#define ALL                     LOG_ALL       /* syslog 8 motion 9 */
#define LEVEL_DEFAULT           NTC           /* syslog 5 motion 6 default */
#define SHOW_LEVEL_VALUE(x)     (x+1)

/* Log types */
#define TYPE_CORE               1             /* Core logs         */
#define TYPE_STREAM             2             /* Stream logs       */
#define TYPE_ENCODER            3             /* Encoder logs      */
#define TYPE_NETCAM             4             /* Netcam logs       */
#define TYPE_DB                 5             /* Database logs     */
#define TYPE_EVENTS             6             /* Events logs       */
#define TYPE_TRACK              7             /* Track logs        */
#define TYPE_VIDEO              8             /* V4L1/2 Bktr logs  */
#define TYPE_ALL                9             /* All type logs     */
#define TYPE_DEFAULT            TYPE_ALL      /* Default type      */
#define TYPE_DEFAULT_STR        "ALL"         /* Default name logs */

#define MOTION_LOG(x, y, z, format, args...)  motion_log(x, y, z, 1, format, __FUNCTION__, ##args)

int get_log_type(const char* type);
const char* get_log_type_str(unsigned int type);
void set_log_type(unsigned int type);
const char* get_log_level_str(unsigned int level);
void set_log_level(unsigned int level);
void set_log_mode(int mode);
FILE * set_logfile(const char *logfile_name);
void motion_log(int level, unsigned int type, int errno_flag,int fncname, const char *fmt, ...);

/** Defines tag used for Android logging. */
#define LIB_NAME "motion-mobile"

/** Verbose Android logging macro. */
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LIB_NAME, __VA_ARGS__)

/** Debug Android logging macro. */
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LIB_NAME, __VA_ARGS__)

/** Info Android logging macro. */
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LIB_NAME, __VA_ARGS__)

/** Error Android logging macro. */
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LIB_NAME, __VA_ARGS__)
/*__android_log_print(ANDROID_LOG_INFO, "MyTag", "The value is %d", some_variable);*/

#endif
