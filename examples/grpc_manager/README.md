
## Setup Required Packages

ubuntu 16.04 LTS and using bash.

Go-lang newer version install and setup Go devenv (for gobgp)
```
$ sudo add-apt-repository ppa:longsleep/golang-backports
$ sudo apt update
$ sudo apt install golang-go
$ export GOPATH=~/go
$ mkdir -p $GOPATH
$ export PATH=$PATH:$GOPATH/bin:
```

gRPC install
```
$ sudo apt install build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev
$ git clone https://github.com/grpc/grpc && cd grpc
$ git submodule update --init
$ make && sudo make install
$ cd grpc/third_party/protobuf
$ sudo make install
```

GoBGP suite insall
```
$ go get github.com/osrg/gobgp/gobgpd
$ go get github.com/osrg/gobgp/gobgp
```

openconffigd install
```
$ go get github.com/coreswitch/openconfigd/openconfigd
$ go get github.com/coreswitch/openconfigd/cli_command
$ cd $GOPATH/src/github.com/coreswitch/openconfigd/cli
$ ./configure
$ make
$ sudo make install
$ cd $GOPATH/src/github.com/coreswitch/openconfigd/bash_completion.d
$ sudo cp cli /etc/bash_completion.d/
```


