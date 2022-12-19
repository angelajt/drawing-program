/*
 * adts.hpp
 *
 *  Created on: Dec 14, 2022
 *      Author: angela
 */

#ifndef FINAL_PROJECT_ANGELAJT_SRC_ADTS_HPP_
#define FINAL_PROJECT_ANGELAJT_SRC_ADTS_HPP_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

using namespace ftxui;
using namespace std;

unordered_map<string, Color> stringToColor = {
	{"Black", Color::Black},
	{"Blue", Color::Blue},
	{"BlueLight", Color::BlueLight},
	{"Cyan", Color::Cyan},
	{"CyanLight", Color::CyanLight},
	{"GrayDark", Color::GrayDark},
	{"GrayLight", Color::GrayLight},
	{"Green", Color::Green},
	{"GreenLight", Color::GreenLight},
	{"Magenta", Color::Magenta},
	{"MagentaLight", Color::MagentaLight},
	{"Red", Color::Red},
	{"RedLight", Color::RedLight},
	{"White", Color::White},
	{"Yellow", Color::Yellow},
	{"YellowLight", Color::YellowLight},
};



#endif /* FINAL_PROJECT_ANGELAJT_SRC_ADTS_HPP_ */
