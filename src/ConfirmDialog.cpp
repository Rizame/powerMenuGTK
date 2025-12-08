#include "ConfirmDialog.h"
#include <giomm/subprocess.h>
#include <giomm/subprocesslauncher.h>
#include <gtkmm.h>
#include <iostream>

ConfirmDialog::ConfirmDialog(Gtk::Window &parent, View viewMode)
    : m_buttonBox(Gtk::Orientation::VERTICAL), m_closeButton("Cancel", true),
      m_confirmButton("Confirm"), m_parent(&parent) {

  auto keyController = Gtk::EventControllerKey::create();
  keyController->signal_key_pressed().connect(
      sigc::mem_fun(*this, &ConfirmDialog::on_key_pressed), false);
  add_controller(keyController);

  set_modal(true);
  set_transient_for(parent);
  parent.set_sensitive(false);

  m_closeButton.signal_clicked().connect([this]() { this->close(); });

  m_confirmButton.signal_clicked().connect(
      [this, viewMode]() { this->execute_powerOption(viewMode); });

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

void ConfirmDialog::execute_powerOption(View viewMode) {
  Glib::ustring command;
  switch (viewMode) {
  case View::CONFIRM_SHUTDOWN:
    command = "poweroff";
    break;
  case View::CONFIRM_SUSPEND:
    command = "suspend";
    break;
  case View::CONFIRM_REBOOT:
    command = "reboot";
    break;
  case View::CONFIRM_HIBERNATE:
    command = "hibernate";
    break;
  default:
    std::cerr << "Unknown viewMode.." << std::endl;
  }

  try {
    auto launcher = Gio::SubprocessLauncher::create();
    auto powerActionSubprocess =
        launcher->spawn(std::vector<std::string>{"systemctl", command});

    Glib::signal_idle().connect_once([this]() {
      this->close();
      if (m_parent)
        m_parent->close();
    });

  } catch (Glib::Error &err) {
    std::cout << "Error happened while spawning a process: " << err.what()
              << std::endl;
    Glib::signal_idle().connect_once([this]() { this->close(); });
  }
}
