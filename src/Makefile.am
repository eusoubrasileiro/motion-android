ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = \
	libmotion.la

libmotion_la_LIBADD = @LIBS@

libmotion_la_SOURCES = motion.c logger.c conf.c draw.c jpegutils.c video_loopback.c \
	video_v4l2.c video_common.c video_bktr.c netcam.c netcam_http.c netcam_ftp.c \
	netcam_jpeg.c netcam_wget.c netcam_rtsp.c track.c alg.c event.c picture.c \
	rotate.c translate.c ffmpeg.c util.c dbse.c webu_status.c \
	webu.c webu_html.c webu_stream.c webu_text.c mmalcam.c
