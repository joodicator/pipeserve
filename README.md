# pipeserve
A wrapper that shares access to a program's `stdin` and `stdout` between a physical terminal and multiple other programs connected to a UNIX domain socket. It can be used to turn a simple console program into a local service.

## Usage
```
pipeserve SOCKET_NAME COMMAND [ARGS ...]
```
Creates a listening UNIX domain stream socket called `SOCKET_NAME`, runs `COMMAND` with a pair of pipes connected to to its `stdin` and `stdout` and inheriting `pipeserve`'s `stderr`, and makes the subprocess's `stdout` and `stdin` available to any client connecting to `SOCKET_NAME`: each line received from a client is written to the `stdin` pipe, and each line read from the `stdout` pipe is sent to all clients.

See comments at the beginning of [`pipeserve.c`](pipeserve.c) for a more exact specification of `pipeserve`'s behaviour.

## Requirements
* An operating system supporting UNIX domain sockets
* [GNU Make](https://www.gnu.org/software/make/)
* [GCC](https://gcc.gnu.org/) for C compilation

## Installation
1. Clone this repository, or download and extract an archive, into an empty directory.
2. Run `make` in the same directory.
3. Optionally, create a symbolic link somewhere on your system path to the compiled executable, `pipeserve`.
