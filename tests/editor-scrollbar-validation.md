# The editor's scrollbar, and the preview above the first block (#291)

Validated on Windows on 2026-10-29. Reported by go4399: in edit mode the
editor's scrollbar went under the tab bar when dragged up, while the
preview's was fine. The report also pointed out an unsigned wrap-around in
`syncPreviewToEditor`, with a patch.

## Cause

- The editor's scrollbar was drawn, hit and dragged along the window's
  whole height. #287 put the document's and the side panels' bars on a
  track below the tab strip, but the editor's bar kept its own arithmetic:
  at the top, all but about 8 px of its thumb sat under the tab strip.
- `syncPreviewToEditor` took the editor's top line's byte offset minus the
  first block's as a `size_t`. While the editor's top line lies above the
  first block (a heading's `# ` on line 1, or front matter), that wrapped
  to a huge number, the interpolation clamped to 1, and the preview jumped
  to the second block.
- The way back, `editorFollowPreview` (the preview's own scrollbar drags
  the editor too, #280), mapped any point above the first block to that
  block's line. With front matter, dragging the preview to its top left the
  editor on the heading, and the next sync pulled the page down again.

## Change

- `editorScrollbarV` (beside the document's bars in `sidepanels.cpp`)
  gives the editor's bar a track from below the tab strip to the window's
  foot. Drawing (wrapped and unwrapped, now one helper), track clicks and
  drags read it, so the thumb starts under the strip, stays under the
  pointer and ends at the window's foot. Presses on the bar count from
  below the strip.
- Above the first block, the sync moves the page from its top to that
  block, by the share of the source above it, and the reverse mapping does
  the same, so the panes meet at their tops. This takes in the reporter's
  patch (the wrap), and moves the page through front matter instead of
  holding it at the first block.

## Fixtures and automated checks

`fixtures/editor-scrollbar-291.md` opens with twelve lines of front
matter, then 30 sections with headings, bold, italics, links, nested and
task lists, tables, code blocks and quotes: 335 lines, several screens in
both panes.

`split_scrollbars` now also runs on that fixture (Paper and Midnight, 1050
and 650 px, wrapped and not):

- at the top the editor's thumb starts below the tab strip and its track
  ends at the window's foot; the thumb moves with the pointer; dragged to
  the end it ends at the window's foot, and dragged back up it stops below
  the strip; a click on the track centres the thumb there;
- through the front matter, a third of a line at a time, the preview stays
  between the page's top and the first block and moves on as the editor
  does; a pixel down from the top keeps the page at its top;
- dragging the preview's bar back to the top puts both panes at their
  tops, front matter or not.

With the old track 32 checks fail, with the old sync 16, and with the old
way back 8. The full suite passes, 50 of 50.

## Checked in the built app

- Before the change (Release build of 3.9.4 plus the morning's merges,
  `fixtures/scrollbar-tracks-287.md`, Midnight, 1200 by 700): at the top
  only about 8 px of the editor's thumb showed below the tab strip, where
  the preview's thumb started right under it. Dragging the editor's thumb
  by 1 px (mouse messages posted to the window) scrolled the editor by
  about 14 px, its first line still showing, and the preview jumped past
  the heading to the first paragraph.
- The fixed build could not be seen in a window: by the time it was built,
  the Remote Desktop session was locked, so Windows composed no windows to
  capture. The checks above drive the same mouse handlers with window
  messages.

Captures are in `out/check-1029/sb291/` and `out/check-1029/wrap291/`
(ignored).

## Limitations

- See above: the fixed scrollbar is checked by the tests, not by eye.
- Unwrapped long lines still have no horizontal bar in the editor (Shift+
  wheel pans them, as before).
