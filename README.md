♻️ Garbage Collection Simulator

A custom garbage collection system in C that simulates how managed languages handle memory. The project includes a fixed memory pool, reference counting, and compaction to efficiently allocate, track, and reclaim objects.

✨ Features

Custom Memory Pool – Fixed-size memory buffer with dynamic allocation and freeing.

Reference Counting – Objects track active references and are automatically reclaimed when counts reach zero.

Garbage Collection & Compaction – Defragments memory by moving live objects to free contiguous space.

Safe Object Access – Object<T> wrapper provides automatic reference management with operator overloads.

Debugging Tools – dumpPool() prints the pool state, including addresses, sizes, and reference info.

Test Drivers – Multiple programs (main.c, main0.c … main5.c) validate allocation, retrieval, reference management, and compaction.

📂 Project Structure
/src
  ├── main.c … main5.c     # Test drivers for different features
  ├── Object.h             # Object<T> wrapper class
  ├── ObjectManager.c      # Core garbage collection system
  ├── ObjectManager.h      # Public API
  ├── Makefile             # Build automation

⚙️ Build & Run

Compile with Makefile

make


Run a test (example with main.c):

./main


Output shows:

Successful/failed allocations

Reference add/drop events

Pool statistics (used space, free space, object IDs, and addresses)

🎯 Highlights

Demonstrates low-level memory management concepts.

Implements reference counting and compaction for safe, efficient memory usage.

Shows how to build a custom garbage collector in C with reusable components.
