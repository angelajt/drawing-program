
#include <string>
#include <cstdlib>

#include "LinkedStack.hpp"
#include "SortedList.hpp"
#include "adts.hpp"

/*******************************************************************************
 * Function prototype
*******************************************************************************/

RadioboxOption makeToColor();
void getFiles(vector<string>&);
void narrow(vector<string>&, string);
int search(vector<string>&, string);

/*******************************************************************************
 * Starting point
*******************************************************************************/

int main() {
    // create the linked stack to store squares
    LinkedStack* squareList = new LinkedStack;

    // create the redo buffer to store ~undone~ squares
    LinkedStack* redoBuffer = new LinkedStack;

    // create the sorted list to store filenames
    SortedList* fileList = new SortedList;

    // unsorted vector of filenames
    vector<string> names;

    // populate the vector of filenames by reading from the directory
    getFiles(names);

    // populate the sorted list with the vector of filenames, sorting the
    // vector in the process.
	fileList->populate(names);

	vector<string> allNames = names;

    // color selection entries
    int colorSelection = 0;

    vector<string> colorNames = {
        "Black", "Blue", "BlueLight",
		"Cyan", "CyanLight", "GrayDark",
        "GrayLight", "Green", "GreenLight",
		"Magenta", "MagentaLight", "Red",
        "RedLight", "White", "Yellow",
		"YellowLight",
    };

    vector<Color> vc = {
        Color::Black, Color::Blue, Color::BlueLight,
		Color::Cyan, Color::CyanLight, Color::GrayDark,
		Color::GrayLight, Color::Green, Color::GreenLight,
		Color::Magenta, Color::MagentaLight, Color::Red,
        Color::RedLight, Color::White, Color::Yellow,
		Color::YellowLight,
    };

    // use the full screen for the program
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    // input variables, components, and renderer
    string pt1x, pt1y, pt2x, pt2y;
	string errorMsg;
    Component inputPt1x = Input(&pt1x, "0");
    Component inputPt1y = Input(&pt1y, "0");
    Component inputPt2x = Input(&pt2x, "0");
    Component inputPt2y = Input(&pt2y, "0");
    Component inputRenderer = Renderer(
        Container::Vertical({inputPt1x, inputPt1y, inputPt2x, inputPt2y}),
        [&] {
            return vbox({
            	hbox(text("Point 1 x: ") | bold, inputPt1x->Render()),
            	hbox(text("Point 1 y: ") | bold, inputPt1y->Render()),
				hbox(text(" ")),
                hbox(text("Point 2 x: ") | bold, inputPt2x->Render()),
                hbox(text("Point 2 y: ") | bold, inputPt2y->Render()),
            });
        }
    );

    // string to store user-selected filename
    string fn;

    // user input field for filename
    Component filename = Input(&fn, "enter filename");
	Component fileSelection = Renderer(

		Container::Vertical({filename}),
		[&] {
			names = allNames;

			if (!fn.empty()) {
				narrow(names, fn);
			}
			return hbox(text("Filename: ") | bold, filename->Render());
		}

	);

    // filename selection menu
    int selected = 0;
    auto fileMenu = Menu(&names, &selected);

    // filled/empty shape toggle
    int toggle_selected = 0;
    vector<string> toggle_entries = {
    		"Filled",
			"Empty",
    };

    Component toggle = Toggle(&toggle_entries, &toggle_selected);

    // canvas size
    const int CANVAS_SIZE = 225;

    // arbitrary limit for # of squares drawn
    const int SQUARE_LIMIT = 80;

    // display the squares on the canvas
    Component squareCanvasRenderer = Renderer([&] {

    	// create the canvas
		Canvas c = Canvas(CANVAS_SIZE, CANVAS_SIZE);
		Square q;

		// O(n*m) where m depends on the lines drawn per shape.
		for (int i = 0; i < squareList->getLength(); i++) {
			// rotate the stack to get each element
			squareList->rotate(Stack<Square>::LEFT);
			q = squareList->peek();

			// drawing a square
			// top, right, bottom, left
			if (toggle_selected == 0) {
				// filled
				// (draw a bunch of vertical lines to simulate a filled-in square)
				int width = abs(q.pnts[2].x - q.pnts[0].x);
				// check if x values are swapped or not
				// (if right x values > left x values)
				if (q.pnts[2].x > q.pnts[0].x) {
					for (int j = 0; j <= width; j++) {
						c.DrawBlockLine(
							q.pnts[0].x + j, q.pnts[0].y,
							q.pnts[3].x + j, q.pnts[3].y,
							q.qColor
						);
					}
				} else {
					for (int j = 0; j <= width; j++) {
						c.DrawBlockLine(
							q.pnts[1].x + j, q.pnts[1].y,
							q.pnts[2].x + j, q.pnts[2].y,
							q.qColor
						);
					}
				}
			} else {
				// empty
				for (int j = 0; j < 4; j++) {
					c.DrawBlockLine(
						q.pnts[j].x, q.pnts[j].y,
						q.pnts[(j + 1) % 4].x, q.pnts[(j + 1) % 4].y,
						q.qColor
					);
				}
			}
		}

		return canvas(move(c));
    });

    // a callback function for redo, using pop
    function<void()> redoCallback = [&] {

    	// clear error message
    	errorMsg.clear();

    	// get a temporary square from the top of the redo buffer
    	Square tmp;
    	try {
    		tmp = redoBuffer->peek();
    	} catch (string&) {
    		errorMsg = "nothing to redo";
    		return;
    	}

    	// try to pop the square from the redo buffer
    	try {
    		redoBuffer->pop();
    	} catch (string& e) {
    		errorMsg = e;
    		return;
    	}

    	// since the pop was successful, add the square to the main stack
    	try {
    		squareList->push(tmp);
    	} catch (string& e) {
    		errorMsg = e;
    		return;
    	}
    };

    // a callback function for push
    function<void()> pushCallback = [&] {

    	// clear redo buffer
    	redoBuffer->clear();

    	// clear the error message
        errorMsg.clear();

        // check to see if user has provided point coordinates
        bool pt1Entered = (!pt1x.empty() && !pt1y.empty());
    	bool pt2Entered = (!pt2x.empty() && !pt2y.empty());

        if (pt1Entered && pt2Entered) {

        	// enforce the very useful arbitrary square limit
			if (squareList->getLength() >= SQUARE_LIMIT) {
				errorMsg = "Too many squares";
				return;
			}

			// convert user input point coordinate strings to integers
			int int1x, int2x, int1y, int2y;
			try {
				int1x = stoi(pt1x);
				int1y = stoi(pt1y);
				int2x = stoi(pt2x);
				int2y = stoi(pt2y);
			} catch (...) {
				errorMsg = "enter points as valid integers";
				return;
			}

			// convert point coordinate integers to points,
			// get user selected color,
			// create a square,
			// and push the square to the stack.
			try {
				Square::Point pt1 = Square::Point(int1x, int1y);
				Square::Point pt2 = Square::Point(int2x, int2y);

				squareList->push(Square(vc[colorSelection], pt1, pt2));
			}
			catch (string& e) {
				errorMsg = e;
				return;
			}
		} else {
			errorMsg = "Please enter all points";
			return;
		}
    };

    // a callback function for clearing the stack (empties the canvas)
    function<void()> clearCallback = [&] {
    	// clear the error message
    	errorMsg.clear();

        squareList->clear();
    };

    // a callback function for save
    function<void()> saveCallback = [&] {

    	// clear the error message
    	errorMsg.clear();

    	// if empty stack, nothing to save
    	if (squareList->isEmpty()) {
    		errorMsg = "nothing to save";
    		return;
    	}

    	// if user did not type a filename in the field, use the file selected
    	// in the menu.
    	if (fn.empty()) {
    		fn = fileList->getElement(selected);
    	}

    	// i actually don't think this would pose a problem since getFiles() is
    	// only concerned with the last part of the filename but i don't want
    	// to test it the hard way.
    	if (fn.find(".draw") != string::npos) {
    		errorMsg = "invalid filename, cannot include \".draw\"";
    		return;
    	}

    	// save the stack to the file
    	try {
    		squareList->save("../drawings/" + fn + ".draw");
    	} catch (string& err) {
    		errorMsg = err;
    		return;
    	}

    	// if filename isn't already in the menu, add it to the menu
    	if (!fileList->find(fn)) {
    		fileList->insert(fn);
    		allNames = fileList->toVector();
    	}

    	// clear the filename input field
    	fn.clear();
    };

    // a callback function for load
    function<void()> loadCallback = [&] {

    	// clear the redo buffer
    	redoBuffer->clear();

    	// clear the error message
		errorMsg.clear();

		if (names.size() == 0) {
			errorMsg = "file doesn't exist";
			return;
		}

    	// use the file selected in the menu.
		string target = names.at(selected);
		int actualPos = search(allNames, target);
		fn = fileList->getElement(actualPos);

		// if the file isn't in the menu, it doesn't exist.
		if (!fileList->find(fn)) {
			errorMsg = "file doesn't exist";
			return;
		}

		// load the contents of the file into the stack
    	try {
    		squareList->load("../drawings/" + fn + ".draw");
    	} catch (string& err) {
    		errorMsg = err;
    	}

    	// clear the filename string
    	fn.clear();
    };

    // a callback function for pop
    function<void()> popCallback = [&] {

    	// clear the error message
        errorMsg.clear();

        if (squareList->getLength() == 0) {
        	return;
        }

        // set a temporary variable to store the undone square
        Square tmp;
        try {
        	tmp = squareList->peek();
        } catch (string& e) {
        	errorMsg = e;
        	return;
        }

        try {
        	squareList->pop();
        }
        catch (string& e) {
            errorMsg = e;
            return;
        }

        // since the undo was successful, add the undone square to the redo
        // buffer
        try {
        	redoBuffer->push(tmp);
        } catch (string& e) {
        	errorMsg = e;
        }
    };

    // a container for the actions to perform on the stack
    Component actionsContainer = Container::Vertical({

    	// title of color selection box
        Renderer([&] {
            return hbox({
                text("Color Selection\n"),
            }) | hcenter;
        }),

        // radiobox for all of the colors
        Radiobox(&colorNames, &colorSelection, makeToColor()) | border,

		// horizontal separator
		Renderer([] { return separator(); }),

		// toggle for filled or empty shapes
    	toggle | center,

		// horizontal separator
		Renderer([] { return separator(); }),

		// title for actions box
        Renderer([&] {
            return hbox({
                text("Actions"),
            }) | hcenter;
        }),

		// buttons
        Container::Horizontal({
            Button("Draw", pushCallback),
            Button("Undo", popCallback),
			Button("Redo", redoCallback),
            Button("Clear", clearCallback),
        }),
        Container::Horizontal({
        	Button("Save", saveCallback),
        	Button("Load", loadCallback),
        	Button("Quit", screen.ExitLoopClosure()),
        }),
    });

    // an outer container for actions, point coordinate input, & error message
    Component canvasModifiers = Container::Horizontal({

    	// inner actions container
    	actionsContainer,

		// inner container for point coordinate input and error message
        Container::Vertical({

    		// point coordinate input
            inputRenderer,

			// error message
            Renderer([&] {
                return hbox({
                    text("Program message: ") | bold,
                    text(errorMsg) | color(Color::Red1),
                });
            }),
        }),
    });

    // an outer outer container for everything that isn't the canvas
    Component rightPanel = Container::Vertical({

    	// container of canvas controls
    	canvasModifiers,

		// horizontal separator
		Renderer([] { return separator(); }),

		// user input filename renderer
		fileSelection,

		// horizontal separator
		Renderer([] { return separator(); }),

		// filename selection menu
		fileMenu,
    });

    // compose all the layouts together into one
    Component mainLayout = Container::Horizontal({

    	// canvas
        squareCanvasRenderer,

		// vertical separator
        Renderer([] { return separator(); }),

		// right panel
		rightPanel,
    }) | border;

    // start running the TUI
    screen.Loop(mainLayout);

    // release the memory for the list
    delete squareList;
    delete redoBuffer;
    delete fileList;

    // terminate
    return 0;
}

/*
 * stylize radiobox entries for color selection
 */
RadioboxOption makeToColor() {
    RadioboxOption option;
    option.transform = [](const EntryState& state) {

    	// color strings with their respective Color types
        Element e = text(state.label) | color(stringToColor[state.label]);

        // decorative bullets
        Element prefix = text(state.focused ? " ► " : " ○ ");
        if (state.focused) {
            e |= inverted;
        }
        if (state.active) {
            e |= bold;
        }

        return hbox({prefix, e});
    };
    return option;
}

// get all of the files with the .draw extension in the ../drawings directory
// and populate a vector of strings with the filenames (sans extension)
void getFiles(vector<string>& names) {
	DIR *dr;
	struct dirent *en;

	// open directory
	dr = opendir("../drawings");
	if (dr) {
		// go through directory
		while ((en = readdir(dr)) != NULL) {
			// get name of each file
			string file = string(en->d_name);

			// if the file extension is .draw, add filename without extension
			// to the vector
			if(file.substr(file.find_last_of(".") + 1) == "draw") {
				string name = file.substr(0, file.find_last_of("."));
				names.push_back(name);
			}
		}
		// close directory
		closedir(dr);
	}
}

// narrow down a vector by only populating it with strings that have substrings
// that match the target string.
// used in the incremental search.
//
// asymptotic analysis: O(n)
void narrow(vector<string>& names, string target) {
	vector<string> tmp;
	for (int i = 0; i < names.size(); i++) {
		string curr = names.at(i);
		size_t found = curr.find(target);
		if (found != string::npos) {
			tmp.push_back(curr);
		}
	}
	names = tmp;
}

// return the position of a target string in the vector of strings.
// return -1 if position isn't found.
// used in the incremental search.
//
// asymptotic analysis: O(n)
int search(vector<string>& names, string target) {
	for (int i = 0; i < names.size(); i++) {
		if (names.at(i) == target) {
			return i;
		}
	}

	return -1;
}
