#pragma once

#include <glib.h>

G_BEGIN_DECLS

/* Keys in the [wfd] group; 0 always means the default */
#define WFD_SETTINGS_BITRATE_KBIT "bitrate-kbit"
#define WFD_SETTINGS_ENCODER      "encoder"      /* 1 = software only */
#define WFD_SETTINGS_MAX_FPS      "max-fps"      /* 60 = 60 fps if supported */
#define WFD_SETTINGS_H264_PROFILE "h264-profile" /* 1 = baseline */

#define WFD_SETTINGS_ENCODER_SOFTWARE      1
#define WFD_SETTINGS_H264_PROFILE_BASELINE 1

guint wfd_settings_get (const gchar *key);
void  wfd_settings_set (const gchar *key,
                        guint        value);

G_END_DECLS
