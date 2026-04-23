🔍 Inverted Index Search Engine (C Project)

📌 Overview
- Inverted Index is a data structure used to map words to their locations in documents.
- Widely used in search engines for fast full-text search.
- This project implements inverted indexing using hashing and linked data structures.
- Enables efficient searching of words across multiple files.

🎯 Objective
- Build a document retrieval system using inverted indexing.
- Implement fast search using hashing techniques.
- Understand indexing and querying mechanisms in search systems.

🧠 Concept
- Inverted index maps:
  - Word → List of documents containing the word
- Improves search efficiency by avoiding full file scanning.
- Uses hashing or sorted structures for faster access.
- Works as a Boolean index (checks presence of words).

📚 Key Concepts

Forward Index
- Maps:
  - Document → Words present in the document
- Extracts words from files.
- Stores words with corresponding file names.
- Avoids duplicate entries by updating existing word records.

Inverted Index
- Maps:
  - Word → List of documents
- Created by sorting or hashing the forward index.
- Enables faster lookup during search.

⚙️ Features

📥 Indexing (Database Creation)
- Accepts multiple input files.
- Parses each file into words.
- Stores:
  - Word
  - List of files containing the word
- Uses:
  - Hashing or sorted linked list
- Creates a database file for indexing.
- Updates index when files are added or removed.

🔍 Querying (Searching)
- Accepts search input (word or phrase).
- Parses query into tokens.
- Searches words in index.
- Retrieves:
  - List of matching documents
- Displays files with maximum matches.

⚡ Optimization
- Avoids re-reading files during search.
- Converts index file into memory structure (linked list/hash table).
- Improves search time complexity.

🧾 Requirements
- Language: C
- Platform: Command-line (Linux/Windows)
- Concepts used:
  - Hashing
  - Linked Lists
  - File handling
  - String parsing
  - Searching and sorting

🧪 Working Flow

Indexing Phase
- Input multiple files.
- Read and parse words.
- Insert words into hash table / linked list.
- Store index into database file.

Querying Phase
- Read search query.
- Parse into words.
- Load index into memory.
- Search words efficiently.
- Retrieve and display matching files.

📊 Advantages
- Fast search using indexing.
- Efficient handling of large datasets.
- Reduces time complexity compared to linear search.
- Scalable for multiple files.

⚠️ Limitations
- Does not rank results (Boolean index only).
- No frequency-based relevance scoring.
- Limited phrase/proximity search.

🚀 Applications
- Search engines
- Document retrieval systems
- Text indexing tools
- Log/file search utilities
