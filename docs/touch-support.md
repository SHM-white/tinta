# Native Windows touch panning (experimental)

This fork adds **single-finger vertical drag-to-scroll** to the normal Markdown
reading page using the operating system's `WM_GESTURE` recognizer. It does
not add Electron, WebView or any runtime dependencies. Formula, Mermaid, and
Markdown rendering are untouched.

## Behavior

- Finger moves up/down: scroll follows displacement, clipped to document edges.
- System inertia is disabled; flicking and lifting a finger must stop scrolling.
- Individual gesture updates are capped at 240 screen pixels, preventing
  unexpectedly large input samples from jumping far into the document.
- The synthetic mouse-release after a recognized pan is ignored to avoid
  unintentionally activating a link or selecting text; regular taps remain clicks.
- Mouse wheel, keyboard scrolling and Ctrl+wheel remain unchanged.
- Document panning is intentionally disabled in editor mode, overlays, and
  floating Contents/File Browser controls. Pinch zoom is not implemented.

## Validation

Pure scroll-boundary regression tests: `ctest -R touch_pan_bounds`.
Windows CI runs the complete CMake/CTest suite and uploads a portable EXE on
PRs. Manual review is necessary on an actual touchscreen; a CI job cannot
validate Windows touch gesture delivery or synthetic mouse event ordering.

On a physical Windows touchscreen test:
1. Tap a Markdown link without moving; it should open.
2. Swipe upward across a link; it must scroll **without** opening the link.
3. Drag slowly and fast in both directions; after finger-up there must be no
   inertia and no end-of-document jump.
4. Verify very long/short documents, window resize, 125–200% display scale,
   mouse-wheel, Ctrl+wheel, keyboard scrolling, and text selection.
5. Open `tests/fixtures/touch-pan-reader.md` and inspect LaTeX, Mermaid, code,
   a table and heading navigation while scrolling.
6. Touch Contents and folder-browser panels: their controls should not pan the
   page behind them.

Notes: touch is currently only supported on the normal reading surface;
no claim is made that multi-touch/pinch or stylus panning is supported.
