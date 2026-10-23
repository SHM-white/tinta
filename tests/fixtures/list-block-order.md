# Mixed blocks in lists

Surrounding **bold**, *emphasis*, [link](https://example.com), and `code`.

7. Before table paragraph with **bold** and a [cell link](https://example.com).

   | Header left | Header right |
   | :--- | ---: |
   | Cell alpha | Cell beta |
   | Cell gamma | Cell delta |

   After table paragraph.

   ### Item heading

   After heading paragraph.

   ---

   After rule paragraph.

   > Quoted paragraph with *emphasis*.

   ```text
   fenced sample
   ```

   - Nested first
     - Nested deeper
   - Nested last

   Final item paragraph.

8. Next numbered item.

## Ordinary lists

- Ordinary item with enough continuation words to wrap at a narrow viewport while keeping all continuation lines aligned with the text instead of the bullet marker.
- Parent item
  - Child item
- Last bullet

- [ ] Pending task
- [x] Completed task

## HTML and heading-first lists

<ul><li>Unordered HTML alpha<li>Unordered HTML beta</ul>
<p>After the omitted HTML end tags.</p>

<ol><li><b>Ordered HTML alpha<li><i>Ordered HTML beta</ol>
<p>After the ordered HTML list.</p>

<ul><li>Outer alpha<ul><li>Inner alpha<li>Inner beta</ul><li>Outer beta</ul>
<p>After the nested HTML lists.</p>

<ul><li><h3>HTML heading first</h3><p>HTML heading body.</p><li>HTML following item</ul>

7. ### Ordered heading first with enough words to wrap at a narrow width while keeping the number on the first text baseline
8. Paragraph-first ordered control.
9. # Ordered level one heading
10. ###### Ordered level six heading

Following the ordered headings.

- ### Unordered heading first with enough words to wrap at a narrow width while keeping the bullet on the first text baseline
- Paragraph-first unordered control.
- # Unordered level one heading
- ###### Unordered level six heading

Following the unordered headings.

> Surrounding quote.

```text
surrounding code
```

Final surrounding paragraph.
