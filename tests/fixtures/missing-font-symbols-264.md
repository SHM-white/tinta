# Signs with a missing code font (#264)

Open this file with the theme in `missing-font-themes.ini`, whose faces are
installed nowhere, and press `:` for the editor. Every sign reads as itself
in the editor and on the page: √ ∞ ∫ ≠ ∙ ≤ ≥ ± × ÷ ∑ ∂ ∆ π Ω, the
breve ˘ and dot above ˙, the ligatures ﬁ and ﬂ.

## In prose and emphasis

The **square root of two, √2**, is about 1.414; *a loop that runs ∞
times* never ends, and [a link about ∫ f(x) dx](https://example.com/integral)
stays a link. Inline code keeps a fixed pitch: `if (a ≠ b) x = √y;`.

> A quote: 0 ≤ p ≤ 1, and x ∙ y ≠ y ∙ x for matrices.

## In lists and a table

- Squares: √4 = 2, √9 = 3
- Limits: 1/x → 0 as x → ∞
  - Nested: ∫ x dx = x²/2
- [x] Checked: ≠ is not =

1. Ordered: a ≠ b
2. Ligatures: ﬂow and ﬁle

| Sign | Name | Code point |
|------|------|------------|
| √ | square root | U+221A |
| ∞ | infinity | U+221E |
| ∫ | integral | U+222B |
| ≠ | not equal | U+2260 |
| ∙ | bullet operator | U+2219 |

## In code

```text
√ ∞ ∫ ≠ ∙  the columns line up
abcdefghij
0123456789
```

```c
double r = sqrt(x);   // √x
if (a != b) { }       // a ≠ b
```

Emoji still come in colour: 😀 ✅ 🎉
