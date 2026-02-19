# Async Signal Logger

A lightweight, thread-safe C logging library designed to be controlled dynamically at runtime via POSIX signals. 

It allows you to toggle logging on/off, change the verbosity level, and asynchronously dump internal states to separate files without interrupting the main application logic.

## Features
* **Thread-Safe Logging:** Uses mutexes to prevent log file corruption when multiple threads write simultaneously.
* **Signal Control:** Control the logger remotely using `kill` or `sigqueue` commands.
* **Background Processing:** State dumps triggered by signals are processed in a dedicated background thread using semaphores, keeping signal handlers minimal and safe.
* **Log Levels:** Supports standard log levels (`MIN`, `STANDARD`, `MAX`).

## Getting Started

### Prerequisites
* A Linux/POSIX-compliant environment.
* GCC or any standard C compiler.

### Compilation
Because this library uses POSIX threads and POSIX real-time extensions, you need to compile it with the `-pthread` flag.

```bash
gcc main.c logger.c -o logger_app -pthread
