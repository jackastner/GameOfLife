#include <gtk/gtk.h>
#include "game_of_life.h"
#include "gol_gtk_app.h"

cairo_surface_t *surface = NULL;

void clear_surface(){
    cairo_t *cr= cairo_create(surface);

    cairo_set_source_rgb(cr,1,1,1);
    cairo_paint(cr);

    cairo_destroy(cr);
}

gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data){
    if(surface){
        cairo_surface_destroy(surface);
    }
    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
                                                CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width(widget),
                                                gtk_widget_get_allocated_height(widget));

    clear_surface();

    return TRUE;
}

gboolean draw_cb(GtkWidget *widget, cairo_t *cr,gpointer data){
    cairo_set_source_surface(cr,surface,0,0);
    cairo_paint(cr);

    return FALSE;
}

void close_window(){
    if(surface){
        cairo_surface_destroy(surface);
    }

    gtk_main_quit();
}

void activate(GtkApplication* app, gpointer user_data){
  GtkWidget *window,*drawing_area;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), "Game Of Life");
  gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
  g_signal_connect(window,"destroy",G_CALLBACK(close_window),NULL);

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area,200,200);
  gtk_container_add(GTK_CONTAINER(window),drawing_area);

  g_signal_connect(drawing_area,"configure-event",G_CALLBACK(configure_event_cb),NULL);

  gtk_widget_show_all(window);
}

int main(int argc,char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.github.jackastner.gameoflife", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}

