#!/usr/bin/env bash
git submodule init
git submodule update

git clone https://github.com/jeremywohl/nacl includes/nacl
cd includes/nacl
sudo ./do
sudo ln -s /usr/lib/nacl/libnacl.a /usr/lib/libnacl.a