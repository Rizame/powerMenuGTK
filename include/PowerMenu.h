#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class PowerMenu : public Gtk::Window {
public:
  PowerMenu();
  virtual ~PowerMenu();

protected:
  Gtk::Box *main_container;
  enum class View {
    MAIN_MENU,
    CONFIRM_SHUTDOWN,
    CONFIRM_REBOOT,
    CONFIRM_SUSPEND,
    CONFIRM_HIBERNATE
  };
  std::array<const char *, 4> white_icons = {
      "/home/risame/study/cpp/powerMenuGTK/images/w_poweroff.png",
      "/home/risame/study/cpp/powerMenuGTK/images/w_reboot.png",
      "/home/risame/study/cpp/powerMenuGTK/images/w_suspend.png",
      "/home/risame/study/cpp/powerMenuGTK/images/w_hibernate.png",
  };
  std::array<const char *, 4> dark_icons = {
      "/home/risame/study/cpp/powerMenuGTK/images/poweroff.png",
      "/home/risame/study/cpp/powerMenuGTK/images/reboot.png",
      "/home/risame/study/cpp/powerMenuGTK/images/suspend.png",
      "/home/risame/study/cpp/powerMenuGTK/images/hibernate.png",
  };
  std::array<View, 4> powerActions = {
      View::CONFIRM_SHUTDOWN, View::CONFIRM_REBOOT, View::CONFIRM_SUSPEND,
      View::CONFIRM_HIBERNATE};

  View current_view;
  void on_button_clicked();
};
