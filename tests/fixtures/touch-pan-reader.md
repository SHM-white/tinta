# Touch panning — mixed Markdown fixture

Swipe slowly and rapidly within this reading surface, including directly
across the link below. **Lifting the finger must stop movement immediately.**
The page must *never* fly to the bottom. Tap the link separately to check
that ordinary touch clicks are still handled.

[Jump to the last section](#last-section)

## LaTeX formula

A block formula must remain readable after touch scrolling:

$$
\hat{\beta}=(X^\top X)^{-1}X^\top y,\qquad
\operatorname{Var}(\hat{\beta})=\sigma^2(X^\top X)^{-1}.
$$

Inline math: $\mathbb E[X]=\mu$ and $\sum_i p_i=1$.

## Diagram, code, and table

```mermaid
flowchart LR
    A[Tap] --> B[Drag]
    B --> C[Release stops immediately]
```

| Test | Expected |
| --- | --- |
| Slow vertical drag | Tracks finger |
| Fast flick | No kinetic scrolling |
| Tap link | Opens normally |
| Mouse wheel | Unchanged |

> Touch only the page; native dialogs and editor mode keep existing behavior.

```cpp
float scrollY = tinta_touch::applyPan(scrollY, dy, contentHeight, height);
```

## Long-page scrolling

- Paragraph 1: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 2: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 3: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 4: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 5: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 6: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 7: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 8: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 9: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 10: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 11: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 12: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 13: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 14: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 15: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 16: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 17: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 18: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 19: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 20: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 21: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 22: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 23: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 24: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 25: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 26: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 27: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 28: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 29: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 30: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 31: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 32: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 33: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 34: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 35: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 36: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 37: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 38: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 39: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 40: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 41: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 42: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 43: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 44: Scroll through several screen heights while checking headings, links, text selection and formula layout.
- Paragraph 45: Scroll through several screen heights while checking headings, links, text selection and formula layout.

## Last section

This target should be reachable by ordinary panning, mouse wheel or link tap.
