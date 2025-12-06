#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class ConfirmDialog : public Gtk::Window {
public:
  ConfirmDialog(Gtk::Window &parent);
  virtual ~ConfirmDialog();

protected:
  bool on_key_pressed(guint keyval, guint, Gdk::ModifierType state);
  Gtk::Box m_buttonBox;
  Gtk::Button m_closeButton;
  Gtk::Button m_confirmButton;

  Gtk::Window *m_parent;
};
