---
title: Editor scrollbar and preview sync
issue: 291
tags: [editor, scrollbar, preview, sync]
owners: [go4399]
created: 2026-10-29
notes: >
  Twelve lines of front matter put the first block well below the
  editor's first line, where the preview sync used to wrap and send
  the page to the second block.
draft: false
---

# Editor scrollbar (#291)

Press `:` for the editor beside its preview. At the top, the editor's
scrollbar thumb sits just **below the tab strip**, like the preview's;
dragged to the bottom it ends at the window's foot, and dragged back up
it stops under the strip again. Scrolling the editor through the front
matter above moves the page *smoothly* from its top to this heading.

## Section 1: bed 1

Bed 1 gets **2 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/1). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 1 | 2 l | dry |
| 2 | 3 l | rain |

## Section 2: bed 2

Bed 2 gets **4 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/2). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=2):
    return 2 * 2  # litres
```

## Section 3: bed 3

Bed 3 gets **6 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/3). Keep the path
beside it clear for the wheelbarrow.

> Bed 3: check the **soil** before sowing.

## Section 4: bed 4

Bed 4 gets **8 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/4). Keep the path
beside it clear for the wheelbarrow.

- Sow row 4a
- Sow row 4b
  - thin to 10 cm
- [x] Mulch row 4c

## Section 5: bed 5

Bed 5 gets **10 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/5). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 5 | 10 l | dry |
| 6 | 11 l | rain |

## Section 6: bed 6

Bed 6 gets **12 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/6). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=6):
    return 6 * 2  # litres
```

## Section 7: bed 7

Bed 7 gets **14 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/7). Keep the path
beside it clear for the wheelbarrow.

> Bed 7: check the **soil** before sowing.

## Section 8: bed 8

Bed 8 gets **16 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/8). Keep the path
beside it clear for the wheelbarrow.

- Sow row 8a
- Sow row 8b
  - thin to 10 cm
- [x] Mulch row 8c

## Section 9: bed 9

Bed 9 gets **18 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/9). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 9 | 18 l | dry |
| 10 | 19 l | rain |

## Section 10: bed 10

Bed 10 gets **20 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/10). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=10):
    return 10 * 2  # litres
```

## Section 11: bed 11

Bed 11 gets **22 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/11). Keep the path
beside it clear for the wheelbarrow.

> Bed 11: check the **soil** before sowing.

## Section 12: bed 12

Bed 12 gets **24 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/12). Keep the path
beside it clear for the wheelbarrow.

- Sow row 12a
- Sow row 12b
  - thin to 10 cm
- [x] Mulch row 12c

## Section 13: bed 13

Bed 13 gets **26 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/13). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 13 | 26 l | dry |
| 14 | 27 l | rain |

## Section 14: bed 14

Bed 14 gets **28 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/14). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=14):
    return 14 * 2  # litres
```

## Section 15: bed 15

Bed 15 gets **30 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/15). Keep the path
beside it clear for the wheelbarrow.

> Bed 15: check the **soil** before sowing.

## Section 16: bed 16

Bed 16 gets **32 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/16). Keep the path
beside it clear for the wheelbarrow.

- Sow row 16a
- Sow row 16b
  - thin to 10 cm
- [x] Mulch row 16c

## Section 17: bed 17

Bed 17 gets **34 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/17). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 17 | 34 l | dry |
| 18 | 35 l | rain |

## Section 18: bed 18

Bed 18 gets **36 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/18). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=18):
    return 18 * 2  # litres
```

## Section 19: bed 19

Bed 19 gets **38 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/19). Keep the path
beside it clear for the wheelbarrow.

> Bed 19: check the **soil** before sowing.

## Section 20: bed 20

Bed 20 gets **40 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/20). Keep the path
beside it clear for the wheelbarrow.

- Sow row 20a
- Sow row 20b
  - thin to 10 cm
- [x] Mulch row 20c

## Section 21: bed 21

Bed 21 gets **42 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/21). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 21 | 42 l | dry |
| 22 | 43 l | rain |

## Section 22: bed 22

Bed 22 gets **44 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/22). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=22):
    return 22 * 2  # litres
```

## Section 23: bed 23

Bed 23 gets **46 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/23). Keep the path
beside it clear for the wheelbarrow.

> Bed 23: check the **soil** before sowing.

## Section 24: bed 24

Bed 24 gets **48 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/24). Keep the path
beside it clear for the wheelbarrow.

- Sow row 24a
- Sow row 24b
  - thin to 10 cm
- [x] Mulch row 24c

## Section 25: bed 25

Bed 25 gets **50 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/25). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 25 | 50 l | dry |
| 26 | 51 l | rain |

## Section 26: bed 26

Bed 26 gets **52 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/26). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=26):
    return 26 * 2  # litres
```

## Section 27: bed 27

Bed 27 gets **54 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/27). Keep the path
beside it clear for the wheelbarrow.

> Bed 27: check the **soil** before sowing.

## Section 28: bed 28

Bed 28 gets **56 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/28). Keep the path
beside it clear for the wheelbarrow.

- Sow row 28a
- Sow row 28b
  - thin to 10 cm
- [x] Mulch row 28c

## Section 29: bed 29

Bed 29 gets **58 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/29). Keep the path
beside it clear for the wheelbarrow.

| Week | Water | Notes |
|------|-------|-------|
| 29 | 58 l | dry |
| 30 | 59 l | rain |

## Section 30: bed 30

Bed 30 gets **60 litres** a day, *more in July*, and its notes
live at [the garden log](https://example.com/beds/30). Keep the path
beside it clear for the wheelbarrow.

```python
def water(bed=30):
    return 30 * 2  # litres
```

## The end

Dragged to the bottom, the thumb ends at the window's foot and the
page shows this line.
