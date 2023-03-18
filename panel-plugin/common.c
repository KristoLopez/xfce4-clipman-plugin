/*
 *  Copyright (c) 2020 Simon Steinbeiß <simon@xfce.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <gtk/gtk.h>

#include <libxfce4ui/libxfce4ui.h>

#include <common.h>

void
clipman_common_show_info_dialog (void)
{
  xfce_dialog_show_info (NULL,
                         _("Could not start the Clipboard Manager Daemon because it is already running."),
                         _("The Xfce Clipboard Manager is already running."));
}

void
clipman_common_show_warning_dialog (void)
{
  xfce_dialog_show_warning (NULL,
                            _("You can launch it with 'xfce4-clipman'."),
                            "%s",
                            _("The Clipboard Manager Daemon is not running."));
}

gchar *
clipman_common_shorten_preview (const gchar *text)
{
  const gint preview_length = 48;
  gchar *tmp1, *tmp2;
  const gchar *offset;

  /* Strip white spaces for preview */
  tmp2 = tmp1 = g_strdup (text);

  g_strchug (tmp2);

  tmp2 = g_strstr_len (tmp2, preview_length, "  ");
  while (tmp2)
    {
      g_strchug (++tmp2);
      /* We've already parsed `tmp2 - tmp1` chars */
      tmp2 = g_strstr_len (tmp2, preview_length - (tmp2 - tmp1), "  ");
    }

  /* Shorten preview */
  if (g_utf8_strlen (tmp1, -1) > preview_length)
    {
      offset = g_utf8_offset_to_pointer (tmp1, preview_length);
      tmp2 = g_strndup (tmp1, offset - tmp1);
      g_free (tmp1);
      g_strchomp (tmp2);

      tmp1 = g_strconcat (tmp2, "...", NULL);
      g_free (tmp2);
    }
  else
    g_strchomp (tmp1);

  /* Cleanup special characters from preview */
  g_strdelimit (tmp1, "\n\r\t", ' ');

  return tmp1;
}
