#include "ConfirmDialog.h"
#include <gtkmm.h>
#include <iostream>

ConfirmDialog::ConfirmDialog(Gtk::Window &parent)
    : m_buttonBox(Gtk::Orientation::VERTICAL), m_closeButton("Cancel", true),
      m_confirmButton("Confirm"), m_parent(&parent) {

  auto keyController = Gtk::EventControllerKey::create();
  keyController->signal_key_pressed().connect(
      sigc::mem_fun(*this, &ConfirmDialog::on_key_pressed), false);
  add_controller(keyController);

  set_modal(true);
  set_transient_for(parent);
  parent.set_sensitive(false);

  m_buttonBox.append(m_confirmButton);
  m_buttonBox.append(m_closeButton);

  m_closeButton.add_css_class("power-button");
  m_confirmButton.add_css_class("power-button");

  set_child(m_buttonBox);
}
ConfirmDialog::~ConfirmDialog() {
  std::cout << "DESTRUCTOR CALLED\n";
  m_parent->set_sensitive(true);
}

bool ConfirmDialog::on_key_pressed(guint keyval, guint,
                                   Gdk::ModifierType state) {
  if (keyval == GDK_KEY_Escape) {
    close();
    return true;
  }
  return false;
}
