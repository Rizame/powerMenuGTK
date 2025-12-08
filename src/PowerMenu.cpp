#include "PowerMenu.h"
#include "ConfirmDialog.h"
#include <gtkmm/cssprovider.h>
#include <gtkmm/image.h>
#include <iostream>

PowerMenu::PowerMenu()
    : main_container{Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL,
                                                 10)},
      current_view{View::MAIN_MENU} {

  set_modal();
  fullscreen();
  set_decorated(false);

  auto css = Gtk::CssProvider::create();
  try {
    css->load_from_path("/usr/local/share/powerGtk/styles.css");
    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), css,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  } catch (const Glib::Error &e) {
    std::cerr << "Css error: " << e.what() << std::endl;
  }

  for (int i = 0; i < 4; i++) {
    auto icon = Gtk::make_managed<Gtk::Image>(white_icons[i]);
    icon->set_pixel_size(128);

    auto btn = Gtk::make_managed<Gtk::Button>();
    btn->set_hexpand(true);
    btn->set_vexpand(true);
    btn->set_child(*icon);
    btn->set_margin(10);
    btn->add_css_class("power-button");
    btn->signal_clicked().connect(sigc::bind(
        sigc::mem_fun(*this, &PowerMenu::on_button_clicked), powerActions[i]));

    main_container->append(*btn);
  }

  main_container->set_halign(Gtk::Align::CENTER);
  main_container->set_valign(Gtk::Align::CENTER);

  set_child(*main_container);
}

PowerMenu::~PowerMenu() {}

void PowerMenu::on_button_clicked(View viewMode) {
  auto popup = Gtk::make_managed<ConfirmDialog>(*this, viewMode);
  popup->set_modal(true);
  popup->set_transient_for(*this);
  popup->show();
}
