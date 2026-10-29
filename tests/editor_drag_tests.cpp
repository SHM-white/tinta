// #289: the editor's selection drags to another place to move it, or with
// Ctrl to copy it, as one undo step; a click on it still places the caret,
// and Shift+click, double-click and dragging off it select as before
#include "d2d_init.h"
#include "editor.h"
#include "input.h"
#include "render.h"
#include "settings.h"
#include "utils.h"

#include "keystroke.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

namespace {
int failures = 0;
void check(bool ok, const std::string& message) {
    if (!ok) { if (failures < 60) std::cerr << "FAIL editor drag: " << message << '\n'; ++failures; }
}

void paint(App& app) {
    ensureLayoutComplete(app);
    app.renderTarget->BeginDraw();
    renderEditor(app, editorPaneWidth(app));
    check(SUCCEEDED(app.renderTarget->EndDraw()), "the editor paints");
}

// The main window puts a dragged selection back when it loses the mouse
// (main_d2d.cpp). The test window does the same, so a release that let go
// of the mouse before landing the text fails here too.
App* windowApp = nullptr;
WNDPROC staticProc = nullptr;
LRESULT CALLBACK testWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CAPTURECHANGED && windowApp && (HWND)lParam != hwnd)
        editorTextDragCancel(*windowApp, hwnd);
    return CallWindowProcW(staticProc, hwnd, msg, wParam, lParam);
}

float lineHeight(const App& app) { return app.editorTextFormat->GetFontSize() * 1.5f; }

// The caret boundary before pos, halfway down its row: where a drop lands
D2D1_POINT_2F atBoundary(App& app, size_t pos) {
    const size_t saved = app.editorCursorPos;
    D2D1_POINT_2F point{};
    app.editorCursorPos = pos;
    editorCaretPoint(app, point);
    app.editorCursorPos = saved;
    return {point.x, point.y + lineHeight(app) * 0.5f};
}
// The middle of the character at pos: where a press lands on it
D2D1_POINT_2F onCharacter(App& app, size_t pos) {
    const D2D1_POINT_2F left = atBoundary(app, pos), right = atBoundary(app, pos + 1);
    const float x = right.y == left.y ? right.x : left.x + app.editorCharWidth;
    return {(left.x + x) * 0.5f, left.y};
}

void select(App& app, size_t from, size_t to) {
    app.editorExtraCarets.clear();
    app.editorSelStart = from;
    app.editorSelEnd = to;
    app.editorCursorPos = to;
    app.editorHasSelection = from != to;
}
std::wstring selected(const App& app) {
    if (!app.editorHasSelection) return L"";
    const size_t from = std::min(app.editorSelStart, app.editorSelEnd);
    const size_t to = std::max(app.editorSelStart, app.editorSelEnd);
    return app.editorText.substr(from, to - from);
}

LPARAM at(D2D1_POINT_2F p) { return MAKELPARAM((int)std::lround(p.x), (int)std::lround(p.y)); }
void moveTo(App& app, D2D1_POINT_2F p) { handleMouseMove(app, app.hwnd, at(p)); }
void release(App& app, D2D1_POINT_2F p) { handleMouseUp(app, app.hwnd, 0, at(p)); }
void press(App& app, D2D1_POINT_2F p) {
    app.lastClickTime = {};  // a click of its own, not the second of a double-click
    moveTo(app, p);
    handleMouseDown(app, app.hwnd, MK_LBUTTON, at(p));
}
// Press on the selection, move past the drag distance, go to the drop point
void startDrag(App& app, D2D1_POINT_2F from, D2D1_POINT_2F to) {
    press(app, from);
    moveTo(app, {from.x + 12.0f, from.y + 3.0f});
    moveTo(app, to);
}
void dragTo(App& app, D2D1_POINT_2F from, D2D1_POINT_2F to, KeyMods dropMods = {}) {
    startDrag(app, from, to);
    withKeysHeld(dropMods, [&] { release(app, to); });
}

void scenario(App& app, const char* path, int width, bool wrap) {
    const std::string where = " (" + std::to_string(width) + (wrap ? ", wrap)" : ")");
    app.width = width;
    check(openDocumentInViewer(app, toWide(path)), "the fixture opens" + where);
    enterEditMode(app);
    app.editorShowPreview = true;
    app.editorWordWrap = wrap;
    rebuildLineStarts(app);
    paint(app);
    const std::wstring original = app.editorText;
    auto reset = [&] {
        app.editorTextDrag = {};
        app.editorText = original;
        app.editorDirty = false;  // as saved: leaving edit mode asks nothing
        app.undoStack.clear();
        app.redoStack.clear();
        app.editorScrollY = 0.0f;
        rebuildLineStarts(app);
        app.clearEditorLineLayoutCache();
        app.editorRowMetricsWidth = -1.0f;
        select(app, 0, 0);
        paint(app);
    };
    const size_t sentence = original.find(L"The quick brown fox jumps over the lazy dog.");
    check(sentence != std::wstring::npos, "the fixture has its sentence" + where);
    if (sentence == std::wstring::npos) return;
    const size_t quick = sentence + 4, fox = sentence + 16, lazy = sentence + 35,
                 dog = sentence + 40;

    // A click on the selection puts the caret there, as before; so does a
    // press that moves less than the drag distance
    select(app, quick, quick + 11);  // "quick brown"
    const D2D1_POINT_2F onBrown = onCharacter(app, quick + 8);
    press(app, onBrown);
    check(app.editorTextDrag.armed && !app.editorTextDrag.active && selected(app) == L"quick brown",
          "a press on the selection waits, keeping it" + where);
    check(GetCapture() == app.hwnd, "the press holds the mouse" + where);
    release(app, onBrown);
    check(app.editorText == original && !app.editorHasSelection && !app.editorTextDrag.armed &&
              (app.editorCursorPos == quick + 8 || app.editorCursorPos == quick + 9),
          "a click on the selection puts the caret there" + where);
    select(app, quick, quick + 11);
    press(app, onBrown);
    moveTo(app, {onBrown.x + 1.0f, onBrown.y});
    release(app, {onBrown.x + 1.0f, onBrown.y});
    check(app.editorText == original && !app.editorHasSelection,
          "a press that moves less than the drag distance is a click" + where);

    // A drag moves the text; it stays selected; one Ctrl+Z puts it back
    select(app, quick, quick + 6);  // "quick "
    dragTo(app, onCharacter(app, quick + 2), atBoundary(app, lazy));
    const std::wstring moved = L"The brown fox jumps over the quick lazy dog.";
    check(app.editorText.compare(sentence, moved.size(), moved) == 0 &&
              app.editorText.size() == original.size(),
          "dragging the selection moves it" + where);
    check(selected(app) == L"quick " && app.editorCursorPos == std::max(app.editorSelStart, app.editorSelEnd),
          "the moved text stays selected" + where);
    check(app.editorDirty && !app.editorTextDrag.armed, "the move is an edit, and the drag is over" + where);
    keystroke(app, 'Z', {true, false, false});
    check(app.editorText == original, "one Ctrl+Z puts the text back" + where);
    keystroke(app, 'Y', {true, false, false});
    check(app.editorText.compare(sentence, moved.size(), moved) == 0, "and Ctrl+Y moves it again" + where);
    reset();

    // With Ctrl held as it drops, a copy lands and the original stays
    select(app, fox, fox + 4);  // "fox "
    dragTo(app, onCharacter(app, fox + 1), atBoundary(app, dog), {true, false, false});
    const std::wstring copied = L"The quick brown fox jumps over the lazy fox dog.";
    check(app.editorText.compare(sentence, copied.size(), copied) == 0,
          "Ctrl as the text drops leaves a copy" + where);
    check(selected(app) == L"fox " && std::min(app.editorSelStart, app.editorSelEnd) == dog,
          "the copy is selected where it landed" + where);
    keystroke(app, 'Z', {true, false, false});
    check(app.editorText == original, "one Ctrl+Z takes the copy away" + where);
    reset();

    // With the search bar open, whose hover takes the pointer otherwise, a
    // drag still reaches the editor
    app.showSearch = true;
    select(app, quick, quick + 6);
    dragTo(app, onCharacter(app, quick + 2), atBoundary(app, lazy));
    app.showSearch = false;
    check(app.editorText.compare(sentence, moved.size(), moved) == 0,
          "a drag moves the text with the search bar open" + where);
    reset();

    // Onto the selection, or a move to its own edge, nothing changes
    select(app, quick, quick + 11);
    dragTo(app, onCharacter(app, quick + 1), atBoundary(app, quick + 8));
    check(app.editorText == original && selected(app) == L"quick brown" && app.undoStack.empty(),
          "a drop onto the selection changes nothing" + where);
    select(app, quick, quick + 11);
    dragTo(app, onCharacter(app, quick + 1), atBoundary(app, quick + 11));
    check(app.editorText == original && selected(app) == L"quick brown" && app.undoStack.empty(),
          "a move to the selection's own end changes nothing" + where);

    // The drop caret follows the pointer; Esc puts the drag back, and the
    // editor stays open
    select(app, quick, quick + 6);
    startDrag(app, onCharacter(app, quick + 2), atBoundary(app, lazy));
    check(app.editorTextDrag.active && app.editorTextDrag.dropPos == lazy,
          "the drop caret follows the pointer" + where);
    paint(app);  // the drop caret draws
    keystroke(app, VK_ESCAPE);
    check(!app.editorTextDrag.armed && app.editMode && app.editorText == original &&
              selected(app) == L"quick " && GetCapture() != app.hwnd,
          "Esc puts the drag back and leaves the editor open" + where);
    release(app, atBoundary(app, lazy));
    check(app.editorText == original, "the release after Esc drops nothing" + where);

    // Over the preview there is nowhere to drop; a lost capture ends a drag
    select(app, quick, quick + 6);
    dragTo(app, onCharacter(app, quick + 2), {documentViewportX(app) + 60.0f, atBoundary(app, lazy).y});
    check(app.editorText == original && selected(app) == L"quick ",
          "a drop over the preview changes nothing" + where);
    select(app, quick, quick + 6);
    startDrag(app, onCharacter(app, quick + 2), atBoundary(app, lazy));
    ReleaseCapture();  // another window takes the mouse
    check(!app.editorTextDrag.armed && app.editorText == original && selected(app) == L"quick ",
          "a lost capture puts the drag back" + where);
    release(app, atBoundary(app, lazy));

    // Shift+click, double-click and dragging off the selection work as
    // before
    select(app, quick, quick + 6);
    withKeysHeld({false, true, false}, [&] { press(app, onCharacter(app, quick + 2)); });
    check(!app.editorTextDrag.armed && app.editorSelecting && app.editorSelStart == quick,
          "Shift+click on the selection moves its end, as before" + where);
    release(app, onCharacter(app, quick + 2));
    select(app, quick, quick + 15);  // "quick brown fox"
    press(app, onBrown);
    release(app, onBrown);
    handleMouseDown(app, app.hwnd, MK_LBUTTON, at(onBrown));  // the second click
    release(app, onBrown);
    check(selected(app) == L"brown" && app.editorText == original,
          "a double-click on the selection selects the word, as before" + where);
    select(app, quick, quick + 5);
    press(app, onCharacter(app, lazy));
    moveTo(app, atBoundary(app, dog + 3));
    release(app, atBoundary(app, dog + 3));
    check(!app.editorTextDrag.armed && selected(app).find(L"azy dog") != std::wstring::npos &&
              app.editorText == original,
          "a drag that starts off the selection selects, as before" + where);

    // Several carets, or a finger, do not drag (#251, #286)
    select(app, quick, quick + 6);
    App::EditorCaret extra;
    extra.pos = extra.anchor = dog;
    app.editorExtraCarets.push_back(extra);
    press(app, onCharacter(app, quick + 2));
    check(!app.editorTextDrag.armed && app.editorSelecting, "with several carets a press does not drag" + where);
    release(app, onCharacter(app, quick + 2));
    select(app, quick, quick + 6);
    app.touch.active = true;
    press(app, onCharacter(app, quick + 2));
    app.touch.active = false;
    check(!app.editorTextDrag.armed, "a finger's press does not drag" + where);
    release(app, onCharacter(app, quick + 2));
    check(app.editorText == original, "and neither edits the text" + where);

    // A whole list line moves above the others
    const size_t first = original.find(L"- first item"), third = original.find(L"- third item");
    const size_t thirdEnd = original.find(L'\n', third) + 1;
    select(app, third, thirdEnd);
    dragTo(app, onCharacter(app, third + 3), atBoundary(app, first));
    const size_t a = app.editorText.find(L"- third item"), b = app.editorText.find(L"- first item"),
                 c = app.editorText.find(L"- second item");
    check(a < b && b < c && app.editorText.size() == original.size(),
          "a list line moves above the others" + where);
    keystroke(app, 'Z', {true, false, false});
    check(app.editorText == original, "and back in one step" + where);
    reset();

    // Past the bottom edge the editor scrolls, so the text can go off screen
    select(app, quick, quick + 6);
    const D2D1_POINT_2F from = onCharacter(app, quick + 2);
    startDrag(app, from, {from.x, (float)app.height - 4.0f});
    check(app.editorTextDrag.scrollVel > 0.0f, "past the bottom edge the drag scrolls down" + where);
    const float maxScroll = std::max(0.0f, app.editorContentHeight - (float)app.height);
    for (int tick = 0; tick < 2000 && app.editorScrollY < maxScroll; ++tick)
        editorTextDragScroll(app, app.hwnd);  // what TIMER_EDITOR_DRAG_SCROLL calls
    check(maxScroll > (float)app.height * 0.5f && app.editorScrollY >= maxScroll - 0.5f,
          "the editor scrolls on while the pointer stays there" + where);
    const size_t end = original.find(L"The end of the document.");
    const D2D1_POINT_2F target = atBoundary(app, end);
    check(target.y > chromeTopHeight(app) && target.y < (float)app.height, "the far end is on screen" + where);
    moveTo(app, target);
    release(app, target);
    check(app.editorText.find(L"quick The end of the document.") != std::wstring::npos &&
              app.editorText.find(L"The brown fox") != std::wstring::npos,
          "the text lands off the first screen" + where);
    reset();
    exitEditMode(app);
}
}  // namespace

int runEditorDragTests(const char* path) {
    auto state = std::make_unique<App>();
    App& app = *state;
    app.hwnd = CreateWindowExW(0, L"STATIC", L"Editor drag tests", WS_POPUP, 0, 0, 1050, 900,
                               nullptr, nullptr, nullptr, nullptr);
    if (!app.hwnd || !initD2D(app) || !createRenderTarget(app)) return 2;
    windowApp = &app;
    staticProc = reinterpret_cast<WNDPROC>(
        SetWindowLongPtrW(app.hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(testWindowProc)));
    app.width = 1050;
    app.height = 900;
    updateTextFormats(app);
    Settings settings;
    settings.keyProfile = "windows";
    applyKeymap(app, settings);
    applyTheme(app, 0);
    // Unwrapped, the narrow pane cuts the fixture's sentence off before its
    // end, where nothing can be pressed or dropped: that case runs wide
    for (int width : {1050, 700}) {
        for (bool wrap : {false, true}) {
            if (wrap || width == 1050) scenario(app, path, width, wrap);
        }
    }
    windowApp = nullptr;
    DestroyWindow(app.hwnd);
    app.hwnd = nullptr;
    state.reset();
    CoUninitialize();
    std::cout << "Editor drag: " << failures << " failures\n";
    return failures ? 1 : 0;
}
