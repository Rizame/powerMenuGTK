#pragma once

#include <PowerActions.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class ConfirmDialog : public Gtk::Window {
public:
  ConfirmDialog(Gtk::Window &parent, View viewMode);
  virtual ~ConfirmDialog();

protected:
  void execute_powerOption(View viewMode);
  bool on_key_pressed(guint keyval, guint, Gdk::ModifierType state);
  Gtk::Box m_buttonBox;
  Gtk::Button m_closeButton;
  Gtk::Button m_confirmButton;

  Gtk::Window *m_parent;
};
