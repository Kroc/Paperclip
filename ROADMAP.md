# Feature Roadmap #

Paperclip uses a feature-based release schedule. Every time a feature is added, a release is made.

This release methodology is used to prevent useful features being held back by devlopment delays on big features, typical of 'major' releases. Sometimes a release might be a simple addition to the menu, such as "Select Line", and sometimes a larger, more involved feature such as printing support.

See [HISTORY.md] for a list of feature releases.

## Queued Features ##

Features to be added, but not yet assigned to a release version:

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
  (is this sufficently different from Select Line?)

* Insert Symbol
* Insert Backtick character (Fn+Q?)
* Insert Pipe character (Fn+K?)

* Show/hide Toolbar
* Show/hide Toolband
  (only useful when Toolband is sufficiently implemented

* Go To: Line number
* GO To: ...?

* Edit: Delete Line
* Edit: Duplicate Line
* Edit: Move Line Up
* Edit: Move Line Down
* Sort Lines, A-Z, Z-A
  Should we include natural sort?

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

* Word Count (how does Word do this?)
* Spell Check

* Print
* Print: Print preview
* Print: Page setup

* Recogniser: Can this be done on ER3?

## Feature Ideas ##

These are features that are currently being debated and might not make it into any release:

* Bracket matching (e.g. Ctrl+B in DSTEdit)
* Auto-close " ( [ ...
* Indent / unindent line (like VSCode)
* Auto-indent
* Wrap-indent (very difficult!)
* Convert UTF8 to Latin1 when loading files and convert back when saving
* Convert line-endings (LF / CRLF / CR?)
* Convert whitespace (Tabs <=> Spaces)
* Trim leading / trailing whitespace
* Gutter: Line-numbers
* Gutter: Bookmark indicator
* Wrap ruler (i.e. show a line at col 80)
* Dictionary / Thesarus lookup
* Outline features (would require language-type & symbol support)