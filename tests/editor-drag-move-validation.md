# Dragging selected text in the editor (#289)

Validated on Windows on 2026-10-29. Requested by nokia5118: in edit mode,
pressing on a selection and dragging started a new selection; the text
could only be moved by cutting and pasting.

## Behaviour

- A press on the selected text arms a drag and keeps the selection. Past
  the system's drag distance (`SM_CXDRAG`, `SM_CYDRAG`) the drag starts: the
  pointer is an arrow and a steady caret in the accent colour marks where
  the text will land.
- Letting go moves the text there; with Ctrl held as it lets go, a copy
  lands and the original stays. Either way it is one undo step, and the
  text stays selected where it landed, the caret at its end.
- A release before the drag distance is a click: the caret goes where it
  pressed, as before. Shift+click, double-click (word), triple-click
  (line) and dragging from outside the selection select as before.
- Dropping onto the selection, or moving it to its own edge, changes
  nothing. Over the preview there is nowhere to drop, so letting go there
  changes nothing either.
- Past the editor's top or bottom edge the editor scrolls, faster the
  further out (a 24 px band, as the viewer's selection drag does it).
- Esc, the mouse going to another window (`WM_CAPTURECHANGED`) or a
  cancelled mode (`WM_CANCELMODE`) put the drag back as it was. Esc does
  not leave edit mode while a drag is under way, and other keys wait for
  the release.
- With several carets (#251) a press on the selection selects as before,
  and a finger's press never drags: its slide extends the selection
  (#286).
- The help overlay lists "Drag / Ctrl+Drag: Move / copy the selection" in
  every shipped language, and the README's shortcut table has the row.

Not done (the request's "nice to have"): a copy cursor with a plus badge,
a ghost of the dragged text, and touch dragging.

## Fixtures and automated checks

`fixtures/editor-drag-move-289.md` has a sentence to rearrange, a list, a
table, a quote, a code block, bold, italics and links, and sixty lines
further down for the edge scrolling.

`editor_drag_move` (`input_tests --editor-drag-tests`) drives the window's
mouse and key handlers at 1050 px unwrapped and wrapped, and at 700 px
wrapped (unwrapped, a pane that narrow cuts the sentence off before its
end):

- a press on the selection waits and holds the mouse; a click there, or a
  press that moves less than the drag distance, puts the caret there;
- a drag moves "quick " before "lazy", keeps it selected, counts as an
  edit; one Ctrl+Z restores the text and Ctrl+Y moves it again;
- with Ctrl held as it drops, "fox " is copied before "dog" and the copy
  selected; one Ctrl+Z takes it away;
- with the search bar open, whose hover takes the pointer otherwise, a drag
  still moves the text;
- a drop onto the selection, or a move to its own end, changes nothing and
  leaves the undo stack empty;
- the drop caret follows the pointer; Esc puts the drag back and leaves
  the editor open, and the release after it drops nothing;
- a drop over the preview changes nothing; another window taking the mouse
  puts the drag back;
- Shift+click, a double-click and a drag from outside the selection select
  as before; with several carets, or from a finger, a press does not drag;
- a whole list line moves above the others and comes back in one step;
- past the bottom edge the editor scrolls to its end while the pointer
  stays there, and the text lands on the last screen.

The test window passes `WM_CAPTURECHANGED` to the drag the way the main
window does. That caught a real fault: the window's release handler lets
go of the mouse before routing the release, so the first version dropped
nothing in the app. The release now lands the text first, as the other
drags' releases do.

Taking parts out: without arming on a press 60 checks fail, without the
one undo step 6, without the Esc handling 24, without routing moves to the
drag ahead of the hover handlers 3, and with the release after letting go
of the mouse 30.

The full suite passes, 51 of 51.

## Checked in the built app

The Release build ran from an isolated portable copy on a copy of the
fixture, in Paper at 1200 by 800, driven by mouse and key messages posted
to its window, and checked through the saved file (Ctrl+S after each
step):

- a triple-click selected "- third item"; dragged to the start of
  "- first item", the line moved there (third, first, second);
- with Ctrl held as it was let go, a copy of the line landed before the
  table and the original stayed;
- one Ctrl+Z took the copy back and a second the move, which left the file
  byte for byte as before;
- a click on a selected line put the caret there (a typed Q landed inside
  the line, not over the selection).

The drop caret and the pointer were not seen: the Remote Desktop session
was locked, so Windows composed no windows to capture. The first run in
the app found the release fault above; the coordinates in the later runs
were first a column off (estimated from an earlier capture), which only
moved where the text landed.

Evidence is in `out/check-1029/drag289/` (ignored).

## Limitations

- See above: the drop caret was checked by the tests, not by eye.
- Unwrapped, nothing scrolls sideways while dragging; text past the pane's
  right edge is not a drop target until the pane is scrolled there.
- Only the primary caret's selection drags; with several carets a press
  selects as before.
