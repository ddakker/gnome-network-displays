#include <errno.h>
#include <glib/gstdio.h>
#include "wfd-settings.h"

/* Stored in a key file so the app, daemon and stream processes share it
 * without installing a GSettings schema. */
#define SETTINGS_GROUP "wfd"

static gchar *
settings_path (void)
{
  return g_build_filename (g_get_user_config_dir (), "gnome-network-displays", "settings.ini", NULL);
}

guint
wfd_settings_get (const gchar *key)
{
  g_autoptr(GKeyFile) key_file = g_key_file_new ();
  g_autofree gchar *path = settings_path ();
  gint value;

  if (!g_key_file_load_from_file (key_file, path, G_KEY_FILE_NONE, NULL))
    return 0;

  value = g_key_file_get_integer (key_file, SETTINGS_GROUP, key, NULL);
  return value > 0 ? (guint) value : 0;
}

void
wfd_settings_set (const gchar *key, guint value)
{
  g_autoptr(GKeyFile) key_file = g_key_file_new ();
  g_autoptr(GError) error = NULL;
  g_autofree gchar *path = settings_path ();
  g_autofree gchar *dir = g_path_get_dirname (path);

  g_key_file_load_from_file (key_file, path, G_KEY_FILE_KEEP_COMMENTS, NULL);

  if (value > 0)
    g_key_file_set_integer (key_file, SETTINGS_GROUP, key, (gint) value);
  else
    g_key_file_remove_key (key_file, SETTINGS_GROUP, key, NULL);

  if (g_mkdir_with_parents (dir, 0700) != 0 ||
      !g_key_file_save_to_file (key_file, path, &error))
    g_warning ("WfdSettings: Failed to save %s: %s", path, error ? error->message : g_strerror (errno));
}
