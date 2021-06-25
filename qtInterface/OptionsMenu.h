/*
Copyright 2021 Wilhelm Neubert
This file is part of SW Roll Calculator.

SW Roll Calculator is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SW Roll Calculator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SW Roll Calculator.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__

#include <QWidget>
class OptionsMenu;
#include "MainQtWindow.h"

class OptionsMenu: public QWidget {
    private:
        void raiseNumberChanged(int val);
        void probDisplayModeComboBoxChanged(int newIndex);

        MainQtWindow& optionsTarget;
    public:
        OptionsMenu(MainQtWindow& optionsTarget_, QWidget* parent_=nullptr);
        ~OptionsMenu(void);
};

#endif
