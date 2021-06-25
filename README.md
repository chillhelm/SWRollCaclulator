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

# SW Roll Calculator

### What is this?
This is a small utility to compute the probability of certain outcomes for trait rolls in the Pen&Paper RPG Savage Worlds.

## License
This is published under GPL 3.0 License. See the accompanying gpl-3.0.txt for details.
This project also uses Qt library (see qt.io) for it's User Interface.

## Usage
Launch the SWRollCalculator application (if you compiled the program yourself, you will probably find it in the qtInterface folder).
You can add rolls using the button on the top right and then configure them as you see fit in the list on the top left.
Once you have configured your roll(s), click the [Plot] button in the top right.
The plot will show the probabilities for different outcomes of your roll, numbering from left to right according to the list at the top.
By default, the program will display probabilities of getting EXACTLY [N] Successes and Raises. You can change this behaviour in the
options Menu ([Menu]->[Options]).

You can save the plot as PNG file or export the probabilities as a CSV (Comma Seperated Values) File using the corresponding buttons on the top right.

## Feedback
Any feedback is welcome ever to reddit.com/u/chillhelm or on github.com/chillhelm/SWRollCalculator

## Building
This program requires Qt 5.12 and CMake 3.4. It may work with newer versions of Qt and CMake as well, I just haven't tested it.

Get the code from github.com/chillhelm/SWRollCalculator

> git checkout https://github.com/chillhelm/SWRollCalculator.git

Create a build directory and cd there.

> mkdir SWRollCalculator_build && cd SWRollCalculator_build

Run cmake, passing the path to your Qt installation as QT_DIR parameter

> cmake -DQt5_DIR=/home/wilhelm/qt5-build/qtbase/lib/cmake/Qt5/Qt5Config.cmake ../SWRollCalculator_build

Run make to compile it all

> make

The main program is found in qtInterface/SWRollCalculator
