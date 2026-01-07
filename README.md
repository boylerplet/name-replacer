# Story Name Anonymizer

A C++ utility for anonymizing character names in text files to protect privacy.

## Overview

This program replaces real names in story or autobiography text files with generic placeholders like `[Character 1]`, `[Character 2]`, etc. This is useful when you want to share personal writing while maintaining the privacy of individuals mentioned in the text.

## Features

- Reads character names from a separate file
- Replaces all occurrences of names with numbered placeholders
- Handles possessive forms (e.g., "John's" becomes "[Character 1]'s")
- Supports partial matching for first names (e.g., if "John Doe" is listed, both "John Doe" and "John" will be replaced)
- Preserves the original story structure and formatting

## Usage

The program takes three arguments:
1. Character names file (one name per line)
2. Input story file
3. Output anonymized file

## Example

**characters.txt:**
```
John Doe
Jane Smith
```

**Input story:**
```
John met Jane at the park. Later, John's friend arrived.
```

**Output:**
```
[Character 1] met [Character 2] at the park. Later, [Character 1]'s friend arrived.
```

## Use Cases

- Sharing personal autobiographies while protecting privacy
- Anonymizing sensitive documents for review
- Creating privacy-safe versions of personal narratives
