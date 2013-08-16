/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007-2013 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __GS_PLUGIN_LOADER_H
#define __GS_PLUGIN_LOADER_H

#include <glib-object.h>

#include "gs-app.h"
#include "gs-plugin.h"

G_BEGIN_DECLS

#define GS_TYPE_PLUGIN_LOADER		(gs_plugin_loader_get_type ())
#define GS_PLUGIN_LOADER(o)		(G_TYPE_CHECK_INSTANCE_CAST ((o), GS_TYPE_PLUGIN_LOADER, GsPluginLoader))
#define GS_PLUGIN_LOADER_CLASS(k)	(G_TYPE_CHECK_CLASS_CAST((k), GS_TYPE_PLUGIN_LOADER, GsPluginLoaderClass))
#define GS_IS_PLUGIN_LOADER(o)	 	(G_TYPE_CHECK_INSTANCE_TYPE ((o), GS_TYPE_PLUGIN_LOADER))
#define GS_IS_PLUGIN_LOADER_CLASS(k)	(G_TYPE_CHECK_CLASS_TYPE ((k), GS_TYPE_PLUGIN_LOADER))
#define GS_PLUGIN_LOADER_GET_CLASS(o)	(G_TYPE_INSTANCE_GET_CLASS ((o), GS_TYPE_PLUGIN_LOADER, GsPluginLoaderClass))
#define GS_PLUGIN_LOADER_ERROR		(gs_plugin_loader_error_quark ())

typedef struct GsPluginLoaderPrivate GsPluginLoaderPrivate;

typedef struct
{
	 GObject		 parent;
	 GsPluginLoaderPrivate	*priv;
} GsPluginLoader;

typedef struct
{
	GObjectClass		 parent_class;
	void			(*status_changed)	(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GsPluginStatus	 status);
} GsPluginLoaderClass;

typedef enum
{
	GS_PLUGIN_LOADER_ERROR_FAILED,
	GS_PLUGIN_LOADER_ERROR_LAST
} GsPluginLoaderError;

GQuark		 gs_plugin_loader_error_quark		(void);
GType		 gs_plugin_loader_get_type		(void);

GsPluginLoader	*gs_plugin_loader_new			(void);
void		 gs_plugin_loader_get_installed_async	(GsPluginLoader	*plugin_loader,
							 GCancellable	*cancellable,
							 GAsyncReadyCallback callback,
							 gpointer	 user_data);
GList		*gs_plugin_loader_get_installed_finish	(GsPluginLoader	*plugin_loader,
							 GAsyncResult	*res,
							 GError		**error);
void		 gs_plugin_loader_get_updates_async	(GsPluginLoader	*plugin_loader,
							 GCancellable	*cancellable,
							 GAsyncReadyCallback callback,
							 gpointer	 user_data);
GList		*gs_plugin_loader_get_updates_finish	(GsPluginLoader	*plugin_loader,
							 GAsyncResult	*res,
							 GError		**error);
void		 gs_plugin_loader_get_popular_async	(GsPluginLoader	*plugin_loader,
							 GCancellable	*cancellable,
							 GAsyncReadyCallback callback,
							 gpointer	 user_data);
GList		*gs_plugin_loader_get_popular_finish	(GsPluginLoader	*plugin_loader,
							 GAsyncResult	*res,
							 GError		**error);
void		 gs_plugin_loader_get_featured_async	(GsPluginLoader	*plugin_loader,
							 GCancellable	*cancellable,
							 GAsyncReadyCallback callback,
							 gpointer	 user_data);
GList		*gs_plugin_loader_get_featured_finish	(GsPluginLoader	*plugin_loader,
							 GAsyncResult	*res,
							 GError		**error);
GList		*gs_plugin_loader_search		(GsPluginLoader	*plugin_loader,
							 const gchar	*value,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_loader_setup			(GsPluginLoader	*plugin_loader,
							 GError		**error);
gboolean	 gs_plugin_loader_set_enabled		(GsPluginLoader	*plugin_loader,
							 const gchar	*plugin_name,
							 gboolean	 enabled);
void		 gs_plugin_loader_set_location		(GsPluginLoader	*plugin_loader,
							 const gchar	*location);
gboolean	 gs_plugin_loader_app_refine		(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_loader_app_install		(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_loader_app_update		(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_loader_app_remove		(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GCancellable	*cancellable,
							 GError		**error);
gboolean	 gs_plugin_loader_app_set_rating	(GsPluginLoader	*plugin_loader,
							 GsApp		*app,
							 GCancellable	*cancellable,
							 GError		**error);

G_END_DECLS

#endif /* __GS_PLUGIN_LOADER_H */
