#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include "graphicdisplay.h"

using namespace std;

Xwindow::Xwindow(int width, int height): width{width}, height{height}{

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display,yes indeedly" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);

  // Set up colours.
    Colormap cmap = DefaultColormap(d, DefaultScreen(d));
    XColor xcolour;
    char color_vals[10][20] = {
        "white", "black",
        "#FFCCCC", // Soft Red
        "#CCFFCC", // Soft Green
        "#CCCCFF", // Soft Blue
        "#FFFFCC", // Soft Yellow
        "#FFEDCC", // Soft Orange
        "#ECC6EC", // Soft Purple
        "#CCCCCC", // Light Gray
        "#FFC0CB"  // Pink
    };

    for(int i = 0; i < 10; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

   XSetForeground(d,gc,colours[Black]);


  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);
  playerColors = {
        {"G", Red}, {"B", Green}, {"D", Blue},
        {"P", Yellow}, {"S", Orange}, {"$", Purple},
        {"L", Gray}, {"T", Pink}
    };

  usleep(100);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}


void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}


void Xwindow::loadBoxes(){
    for(int i = 0; i < static_cast<int>(names.size()); i++){
      boxes.emplace_back(names[i],i);
    }
}

void Xwindow::drawBox(int idx) {
    const int boxesPerSide = 11; // Assuming 11 boxes per side
    const int boxWidth = getWidth() / boxesPerSide;
    const int boxHeight = getHeight() / boxesPerSide;

    // Calculate position based on index, similar logic as in redrawBox but adjusted for drawBox
    int x, y;
    // Determine x, y position logic here as needed...
        if (idx < 11) { // Bottom row
            x = idx * boxWidth;
            y = 10 * boxHeight;
        } else if (idx < 20) { // Right column
            x = 10 * boxWidth;
            y = (10 - (idx - 10)) * boxHeight;
        } else if (idx < 31) { // Top row
            x = (10 - (idx - 20)) * boxWidth;
            y = 0;
        } else { // Left column
            x = 0;
            y = (idx - 30) * boxHeight;
        }
        std::string lastPlayer = boxes[idx].getLastPlayer();
        int color = (playerColors.find(lastPlayer) != playerColors.end()) ? playerColors[lastPlayer] : White;

        // Fill the rectangle with the determined color
        fillRectangle(x, y, boxWidth, boxHeight, color);

        // Draw the black border
        XSetForeground(d, gc, colours[Black]);
        XDrawRectangle(d, w, gc, x, y, boxWidth, boxHeight);

        // Draw the box name slightly above center
        drawString(x + 5, y + boxHeight / 2 - 10, boxes[idx].getName());

        // If there's an owner, display it
        if (boxes[idx].getOwner() != "none") {
            drawString(x + 5, y + boxHeight / 2 + 10, "Owner: " + boxes[idx].getOwner());
        }
        if (boxes[idx].getLevel() > 0) {
            drawString(x + 5, y + boxHeight / 2 + 30, "Level: " + std::to_string(boxes[idx].getLevel()));
        }
}


#include <iostream>

#include <iostream>

void Xwindow::drawBoard() {
    XSetForeground(d, gc, colours[White]);
    XFillRectangle(d, w, gc, 0, 0, width, height);
    XSetForeground(d, gc, colours[Black]);
    drawString(getWidth() / 2 - 30, getHeight() / 2, "WATOPOLY");

    int startX = getWidth() / 2 + 200;  // Start right of WATOPOLY
    int startY = getHeight() / 2 - 100;  // Start above the center
    for (const auto& [name, color] : playerColors) {
        XSetForeground(d, gc, colours[color]);
        XFillRectangle(d, w, gc, startX, startY, 20, 20);
        XSetForeground(d, gc, colours[Black]);
        drawString(startX + 30, startY + 15, name);
        startY += 30;
    }
    XFlush(d);
}







void Xwindow::waitForCloseEvent() {
    XEvent event;
    while (true) {
        XNextEvent(d, &event); // Wait for the next event

        if (event.type == KeyPress) { // Check if the event is a key press
            break; // Exit the loop and allow the program to close the window
        }
    }
}


void Xwindow::notify(Entity entity){
      std::visit([this](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::shared_ptr<Building>>) {
                int idx = arg->getIdx();
                boxes[idx].owner = arg->getOwner();
                boxes[idx].level = arg->getLevel();
                auto playerNames = arg->getCurrPlayerName();


                if (!playerNames.empty()) {
                    boxes[idx].currPlayer = playerNames;
                } else {
                    boxes[idx].currPlayer = {"none"};
                }

                drawBox(idx);
                XFlush(d);
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<Player>>){
                string pName = arg->getName();
                int pAsset = arg->getAsset();

                auto it = playerInfo.find(pName);
                if(it != playerInfo.end()){
                    it->second = pAsset;
                }else{
                    playerInfo[pName] = pAsset;
                }
                if(!playerInfo.empty()){
                    drawPlayerInfo();
                }
            
            }
        }, entity);
}



void Xwindow::drawPlayerInfo() {
    int startX = 200;
    int startY = 300;
    int stepY = 20;
    int totalPlayers = playerInfo.size();  // Assuming playerInfo is accessible and you count the players
    int windowWidth = 100;  // Example width, adjust according to your needs

    // Clear the area where player info is displayed
    clearArea(startX, startY - 10, windowWidth, totalPlayers * stepY + 10);

    // Draw player information as before
    for (const auto& [name, assets] : playerInfo) {
        std::string info = name + ": $" + std::to_string(assets);
        drawString(startX, startY, info);
        startY += stepY;
    }

    XFlush(d);
}



void Xwindow::clearArea(int x, int y, int width, int height) {
    // Assuming 'd' is the Display* and 'w' is the Window
    // The last parameter being True causes the X server to generate expose events.
    XClearArea(d, w, x, y, width, height, True);
    XFlush(d);
}

