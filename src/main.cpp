#include <gtkmm.h>
#include <stdlib.h>
#include <iostream>

#include "Eigen/Dense"

Gtk::Window* mainWindow            = nullptr; // gui window
Gtk::Entry*  motorNumber_entry     = nullptr; // motor index
Gtk::Entry*  inputPosition_entry   = nullptr; // input positions
Gtk::Entry*  commandPosition_entry = nullptr; // current commanded positions

// Eigen::Matrix<double,1,5> jointPos

// Glib::ustring getText(int entryNo){
//     Glib::ustring gstring;
//     if (entryNo == 0) {
//         gstring = motorNumber_entry->get_text();
//     }
// }

// bool setText(int entryNo, std::string text) {
//     // Glib::ustring
// }

static void on_button_clicked_home() {
	std::cout << "Home Motor!"<<"\n";
}

static void on_button_clicked_jogDown() {
	std::cout << "Jog Down Motor "<<"\n";
}

static void on_button_clicked_jogUp() {
	std::cout << "Jog Up Motor "<<"\n";
}

static void on_button_clicked_goToZero() {
	std::cout << "Go To Zero Position Motor "<<"\n";
}

static void on_button_clicked_setMotorNumber() {
	std::cout << "Set motor number "<<"\n";
}

static bool update_display() {
    Glib::ustring commandPosNumber;
    std::stringstream ss;
    ss << 100; // here we would tie into subscribed positions
    ss >> commandPosNumber;
    commandPosition_entry->set_text(commandPosNumber);
	return true;
}

static void on_button_clicked_setPosition() {
    Glib::ustring positionString = inputPosition_entry->get_text();
    Glib::ustring motorNumString = motorNumber_entry->get_text();
	std::stringstream ss, ss2;
	int position, motorNum;
	ss << positionString.raw();
	ss >> position;
    ss2 << motorNumString.raw();
    ss2 >> motorNum;
	std::cout << "Moving motor " << motorNum << " to position " << position << "\n";
}

std::string gladFilename = "/home/smoose/coding/gtkmm_ex/src/main.glade";

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("max.gtkmm.examples.base");

    // find glade source file
    auto refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file(gladFilename);
    refBuilder->get_widget("mainWindow", mainWindow);

    // Connect the text inputs to appropriate callbacks
	refBuilder->get_widget("motorNumber", motorNumber_entry);
	motorNumber_entry->signal_activate().connect(sigc::ptr_fun(on_button_clicked_setMotorNumber));
	
	refBuilder->get_widget("inputPosition", inputPosition_entry);
	inputPosition_entry->signal_activate().connect(sigc::ptr_fun(on_button_clicked_setPosition));

	// Map all the buttons to the appropriate callbacks
	Gtk::Button* home = nullptr;
	refBuilder->get_widget("home", home);
	home->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_home));

	Gtk::Button* jogDown = nullptr;
	refBuilder->get_widget("jogDown", jogDown);
	jogDown->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_jogDown));

	Gtk::Button* jogUp = nullptr;
	refBuilder->get_widget("jogUp", jogUp);
	jogUp->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_jogUp));

	Gtk::Button* goToZero = nullptr;
	refBuilder->get_widget("goToZero", goToZero);
	goToZero->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_goToZero));
	
	Gtk::Button* setMotorNumber = nullptr;
	refBuilder->get_widget("setMotorNumber", setMotorNumber);
	setMotorNumber->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_setMotorNumber));
	
	Gtk::Button* goToInput = nullptr;
	refBuilder->get_widget("goToInput", goToInput);
	goToInput->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_setPosition));
	
	// Update command position label using callback fn
	refBuilder->get_widget("commandPosition", commandPosition_entry);
	Glib::signal_timeout().connect(sigc::ptr_fun(update_display), 100);

    // run app
    app->run(*mainWindow);

    delete mainWindow;
    return 0;
}