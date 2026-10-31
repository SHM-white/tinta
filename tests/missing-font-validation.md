# A theme's missing faces (#264)

Validated on Windows on 2026-10-29. Reported by a86022: a square root
typed or pasted into the editor showed as an A with a tilde. Their custom
theme and Midnight name Cascadia Code, which their Windows 10 does not have
(it is not in `C:\Windows\Fonts`); Paper, in Consolas, was right.

## Cause

- With a face the PC lacks, DirectWrite takes every character from the
  document's fallback list. The list's last entry sends anything that is
  not CJK to Segoe UI Emoji first, so the editor and the code blocks were
  drawn in Segoe UI Emoji, in no fixed pitch.
- Segoe UI Emoji's character map gives a few signs another character's
  glyph. On this machine (Windows 11, build 26200): the square root takes
  the glyph of Ã, infinity that of °, the integral º, not-equal the soft
  hyphen (nothing shows), the bullet operator ·, the ligature fl ß, and the
  breve and dot above ù and ú. The reporter's Windows 10 copy of the font
  got the square root wrong and infinity right.
- Reproduced with a theme naming a face that exists nowhere: the editor and
  the code blocks drew √ as Ã and ∞ as °, exactly as with a theme that asks
  for Segoe UI Emoji itself.

## Change

- A face the PC lacks gives way to an installed one when a theme is
  applied, at startup and for printing: for code the nearest of Cascadia
  Mono, Cascadia Code and Consolas (Courier New last), for text Segoe UI
  (Arial last). A missing heading face leaves the headings to the body's.
  The theme itself, `themes.ini` and the theme editor keep the faces it
  names; the theme chooser's previews and the theme editor's specimen show
  the faces it draws with. Diagrams, maths and exports read the same faces.
- The document fallback list sends the spacing modifier letters, the
  mathematical operators and the Latin ligatures to Segoe UI, then Segoe UI
  Symbol, then Cambria Math, ahead of the emoji faces, so a face without
  one of those signs no longer gets Segoe UI Emoji's glyph for it. Emoji
  still come from Segoe UI Emoji.
- Applying a theme compares the faces the formats were made from with the
  faces the new theme draws with, so applying a theme with a missing face
  again keeps its formats.

## Fixtures and automated checks

`fixtures/missing-font-symbols-264.md` has the signs in a heading, prose,
bold, italics, a link, inline code, a quote, nested and task lists, an
ordered list, a table, a text and a C code block, and emoji;
`fixtures/missing-font-themes.ini` is a theme whose text, heading and code
faces exist nowhere.

`inline_code_theme` (`theme_tests`) applies that theme and checks:

- the theme keeps the faces it names, while the applied theme has the
  nearest installed code face, Segoe UI for text and no heading face;
- code, bold code and the editor take the code face, body and headings
  Segoe UI; the editor keeps a fixed pitch (ten i as wide as ten M, and the
  editor's measured character width); plain text in the editor is all in
  the code face, and the signs draw without the emoji face;
- the fixture laid out at 1050 and 520 px draws no run from the emoji face
  but the emoji line's;
- applying the theme again keeps its formats; the theme chooser previews
  the installed faces; a theme whose faces are installed keeps them;
- for a face without them, √ ∞ ∫ ≠ ∙, the breve, the dot above and fl come
  from Segoe UI, ∛ from Segoe UI Symbol, and an emoji from Segoe UI Emoji.

Without the faces giving way, 10 checks fail; without the fallback entry,
8 (one for each sign).
The full suite passes, 50 of 50.

## Checked in the built app

- The Release build printed the fixture (`--printpages`, an isolated
  portable copy with the theme above): every sign in prose, lists, the
  table, inline code and both code blocks reads as itself, and the code
  blocks are in Cascadia Mono with their columns lined up. The same build
  without the change drew the code blocks in a proportional face, with
  "Ã ° º - ·" for "√ ∞ ∫ ≠ ∙" and "// a - b" for "// a ≠ b": the report.
- Before the change, the editor with a missing code face (`:` posted to the
  window) showed Ã for √ and ° for ∞ in a proportional face, in the same
  places as with Segoe UI Emoji as the code face; with Cascadia Code
  installed it was right.
- The fixed editor could not be captured: by then the Remote Desktop
  session was locked, so Windows composed no windows to capture. The
  checks above cover its format and glyphs.

Captures are in `out/check-1029/` (ignored).

## Limitations

- The stand-ins are fixed lists: a missing serif face gives way to Segoe UI.
- A face installed while Tinta runs is seen after a restart.
- Windows 10 itself was not at hand. Its missing face was simulated with a
  name that exists nowhere, which DirectWrite treats the same way.
- Only Segoe UI Emoji's character map was surveyed for wrong glyphs.
