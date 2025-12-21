# Pipex study notes & to-do list

##
print functions check for forbidden command":
- `nm -g ./pipex | grep U`

## 19/12/25

is working but
according to pipex tester:
- [ ] not giving the right exit codes
- [ ] does not output command not found
- [ ] does not handle outfile's open error
- [ ] does not handles execve errors    

## 04/12/25

### functions needed:

**access()**:

```C
int access(const char *pathname, int mode);
```
- checks whether the file `pathname` can be accessed
- `mode` specifies which permissions we wanna check the file under (bitwise masks, can be 1 or more separated by `|` OR):
    ```C
    if (access("readfile", R_OK) == 0)
        printf("readfile is accessible in reading mode\n");
    if (access("writefile", W_OK) == 0)
        printf("writefile is accessible in writing mode\n");
    if (access("executefile", X_OK) == 0)
        printf("executefile is accessible in execution mode\n");
    if (access("rwfile", R_OK|W_OK) == 0)
        printf("rwfile is accessible in writing and reading mode\n");
    ```
- on success (all requested permissions granted), 0 is returned. On error (at least one bit in mode asked for a permission that is denied, or some other error occurred), -1 is returned, and `errno` is set appropriately

**dup2()**:

```C
int dup2(int oldfd, int newfd);
```
- makes `newfd` the copy of `oldfd`, making `newfd` able to access the same file as `oldfd` and **closing** `newfd` first if necessary
- if `oldfd` is not a valid file descriptor, then the call fails, and `newfd` is not closed
- if `oldfd` is a valid file descriptor, and `newfd` has the same value as `oldfd`, then `dup2()` does nothing, and returns `newfd`
- on error, `dup2()` returns `-1`

**pipe()**:

```C
int pipe(int pipefd[2]);
```
- `pipe()` creates a pipe, a unidirectional data channel that can be used for interprocess communication
- The array `pipefd` is used to return two file descriptors referring to the ends of the pipe:
    * `pipefd[0]` refers to the read end of the pipe
    * `pipefd[1]` refers to the write end of the pipe
- data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe
- on success, `0` is returned. On error, `-1` is returned, and `errno` is set appropriately

**fork()**

```C
pid_t fork(void);
```
- `fork()` creates a new process by duplicating the calling process. The new process is referred to as the `child` process. The calling process is referred to as the `parent` process.

**waitpid()**:

```C
pid_t waitpit(pid_t pid, int *status, int options);
```
- The `waitpid()` system call suspends execution of the calling process until **a child** specified by `pid` argument has **changed state**.
- By default, `waitpid()` waits only for terminated children.

**wait()**
```C
pid_t wait(int *status);
```
- The wait() system call suspends execution of the calling process until **one of its children terminates**.

**wait() vs waitpid()**:
- the first waits for any child of the process/thread to terminate to suspend the execution of the process/thread;
- the second waits for a specific child's `pid` to change state to suspend the execution of the parent process/thread;

**execve()**
```C
int execve(const char *filename, char *const argv[], char *const envp[]);
```
- `execve()` executes the program pointed to by `filename`
- example:
```C
int main(int ac, char **av, char **envp)
{
    (void) ac;
    const char *filename = "/usr/bin/grep";
    char *const argv[] = {"/usr/bin/grep", "a", NULL};
    
    execve(filename, argv, envp);
}
```
- on success, `execve()` does not return, on error `-1` is returned, and `errno` is set to indicate the error
- `envp` is an array of pointers to strings, conventionally of the form **key=value**, which are passed as the environment of the new program. The `envp` array must be terminated by a null pointer.

**unlink**:
```C
int unlink(const char *pathname);
```
