Learnings:
How system calls work and their practical implementation in programming:

1. read() and write():
   - These system calls are used for input/output operations.
   - Facilitate communication between the program and external sources (like standard input/output).
   what are standard fd's 
   0 for standard input that is keyboard
   1 for standard output that is display
   2 for standard errorr device

2. open():
   - The `open()` system call is used to open files and obtain a file descriptor.
   - It's essential for working with files and streams.

3. lseek():
   - The `lseek()` system call allows seeking to specific positions within a file.
   - It's useful for reading or writing at specific offsets.

4. dup():
   - `dup()` duplicates an existing file descriptor, creating a new reference to the same resource.
   - Useful for scenarios where multiple references to the same resource are needed.

5. fork():
   - The `fork()` system call creates a new process by duplicating the existing process.
   - The parent and child processes have separate memory spaces but share the same code and data.

6. Creating an Orphan Process:
   - An orphan process is created when a  parent process gets terminated and child process still lives.
   - The orphaned child continues executing even after the parent has exited.