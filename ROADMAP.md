# Feature Roadmap #

Paperclip uses a feature-based release schedule. Every time a feature is added, a release is made.

This release methodology is used to prevent useful features being held back by development delays on big features, typical of 'major' releases. Sometimes a release might be a simple addition to the menu, such as "Select Line", and sometimes a larger, more involved feature such as printing support.

See [HISTORY.md](HISTORY.md) for a list of feature releases.

## Queued Features ##

Features to be added, but not yet assigned to a release version:  
(The order of this list is no guarantee of when a feature will be implemented)

* Cut / Copy / Paste, Sidebar Clipboard menu

* Undo, Redo

* Zoom (change font-size only);
  Zoom Sidebar support

* New File
* Open [text] file
* Save [text] file

* Save As
* Revert to saved

* Select All
* Select Word
* Select Line
* Select Paragraph
  (is this sufficiently different from Select Line?)

* Insert Symbol
* Insert Backtick character (Fn+Q?)
* Insert Pipe character (Fn+K?)
* Use shift+space for inserting underscore?
  (or other symbol, e.g. em-dash) via DSTEdit

* Show/hide Toolbar
* Show/hide Toolband
  (only useful when Toolband is sufficiently implemented)

* View Whitespace: spaces, tabs, line-endings (depends on SDK)

* Word-wrap, to screen
* Word-wrap, to column
* Show / hide scrollbars

* Go To: Line number
* Bookmarks
  Which shortcuts should we use for adding / removing and jumping to bookmarks? Ctrl+<n>, Ctrl+Shift+<n>

* Edit: Change case (lower / UPPER)
* Edit: Change case, Title (use my PHP version? Relies on regex)

* Edit: Delete Line
* Edit: Duplicate Line
* Edit: Move Line Up
* Edit: Move Line Down

* Find
  Use SDK / Word's dialog for a first version?
* Find Toolbar:
  - Place on bottom of editor
    (should it be part of AppUI or ViewEditor?)
  - Show & Hide
  - Close button
  - Trap Esc in AppUI to close
  - Input field
    (Use combo-box)
  - Next / prev buttons
  
* Replace
  Use SDK / Word's dialog initially
  - Extend Find toolband with replace field
  - Button for whole-word
  - Button for case-sensitive
  - Replace & Go button
  - Repalce all button
  - Button to switch to Find In Files?

* Sort Lines, A-Z, Z-A
  Should we include natural sort?
* Sort lines using specific column number (ala DSTEdit)
* Remove empty lines

* Infrared send+receive, Sidebar menu

* Preferences: Default font-size
* Preferences: Save global preferences to "/System/Data"(?) INI file
* Preferences:Save Toolbar visibility state

* Project: Set app to use default document name
* Project: New project (how do the built-in apps do this?)
* Project: Open project

* Project: Close file
  How will we handle having no file open at all?
  Default to a blank editor, or have a no-file UI state?

* Project: Save all open files
* Project: Close all open files

* Project: Add file to project (copy file from elsewhere into project folder)
* Project: Remove [current] file from project (delete file?)

* Project: Open file by name (filterable filepath list, like Sublime & VSCode)

* Project: Remember cursor position in each file

* File properties

* Help menu
* Help file - document only released features

* Tools: Word Count (how does Word do this?)
* Tools: Spell Check

* Print
* Print: Print preview
* Print: Page setup

## Feature Ideas ##

These are features that are currently being debated and might not make it into any release:

* Auto numbering / bulleting
* Bracket matching (e.g. `Ctrl+B` in DSTEdit)
* Select between brackets (`Shift+Ctrl+B` in DSTEdit)
* Auto-close `" ( [ < ... > ] ) "`
* Indent / unindent line (like VSCode)
* Auto-indent
* Wrap-indent (very difficult!)
* Convert UTF8 to Latin1 when loading files and convert back when saving
* Convert line-endings (LF / CRLF / CR?)
* Convert whitespace (Tabs <=> Spaces)
* Trim leading / trailing whitespace
* Prefix and unprefix lines: (via DSTEdit)
  E.g. toggling comment markers, dependant on file's language-type
* Gutter: Line-numbers
* Gutter: Bookmark indicator
* Wrap ruler (i.e. show a line at col 80)
* Dictionary / Thesaurus lookup
* Outline features (would require language-type & symbol support)
* Custom tab-stops, visible Ruler?
* Recogniser: Can this be done on ER3?
* Recogniser: Customise recognised file-types
* Spell Checker settings:
  - Ignore `CamelCase` words
  - Ignore words with numbers & symbols in the middle, e.g. `dotted.form`, `snake_case`, but *not* words that may begin and end with symbols, e.g. MarkDown's `**bold**`
  - Ignore content between backticks
  - Ignore between arbitrary bounds (multi-line), e.g. ```...``` (code blocks) -- language dependent
  - Ignore *except* between bounds, e.g. spell-check only comments in code! -- language dependent
  - The user-dictionary is buggy on Series 5 & 5MX, failing beyond a certain size, should we implement our own user dictionary?