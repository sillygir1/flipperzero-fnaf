#include "../fnaf.h"
#include "menu.h"
#include "office.h"

void draw_menu(Canvas* canvas, Fnaf* fnaf) {
    if (fnaf->progress > 6) fnaf->progress = 0;

    canvas_set_bitmap_mode(canvas, 1);
    canvas_draw_str(canvas, 15, 16, "New Game");
    uint8_t y = 32;
    if (fnaf->progress > 0) {
        char text[19];
        snprintf(text, 19, "Continue Night %u", fnaf->progress + 1);
        canvas_draw_str(canvas, 15, 32, text);
        y = 48;
    }
    canvas_draw_str(canvas, 16, y, "Exit");
    canvas_set_font(canvas, FontPrimary);

    switch (fnaf->menu_cursor) {
    case 0:
        canvas_draw_line(canvas, 14, 19, 59, 19);
        break;
    case 1:
        if (fnaf->progress > 0) { canvas_draw_line(canvas, 14, 35, 83, 35); } else
            canvas_draw_line(canvas, 15, 35, 32, 35);
        break;
    case 2:
        canvas_draw_line(canvas, 15, 51, 32, 51);
        break;
    }
}

static void new_game(Fnaf* fnaf) {
    FURI_LOG_D(TAG, "new_game");
    fnaf->progress = 0;
    night_start(fnaf);
}

static void continue_game(Fnaf* fnaf) {
    FURI_LOG_D(TAG, "continue_game");
    night_start(fnaf);
}

bool menu_input(Fnaf* fnaf) {
    if (fnaf->event.type == InputTypePress) {
        switch (fnaf->event.key) {
        case InputKeyLeft:
            break;
        case InputKeyRight:

            // REMOVE FOR RELEASE
            fnaf->progress += 1;
            // REMOVE FOR RELEASE

            if (fnaf->progress > 6) fnaf->progress = 0;
            break;
        case InputKeyUp:
            fnaf->menu_cursor -= 1;
            break;
        case InputKeyDown:
            fnaf->menu_cursor += 1;
            break;
        case InputKeyOk:
            switch (fnaf->menu_cursor) {
            case 0:
                new_game(fnaf);
                break;
            case 1:
                if (fnaf->progress == 0) { return false; } else continue_game(fnaf);
                break;
            case 2:
                return false;
                break;
            }
            break;
        case InputKeyBack:
            return false;
        default:
            break;
        }
        if (fnaf->menu_cursor > 2) {
            fnaf->menu_cursor = 0;
        } else if (fnaf->menu_cursor < 0) {
            fnaf->menu_cursor = 2;
            if (fnaf->progress == 0) fnaf->menu_cursor = 1;
        }
        if (fnaf->menu_cursor > 1 && fnaf->progress == 0) fnaf->menu_cursor = 0;
    }
    return true;
}
