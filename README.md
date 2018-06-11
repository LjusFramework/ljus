# Ljus (yoos)
[![Travis](https://api.travis-ci.com/LjusFramework/ljus.svg?branch=master)]()
[![Codacy grade](https://img.shields.io/codacy/grade/9cadf04aee3f4f608796e96cf3bc3e31.svg?style=flat-square)]()
[![Coveralls](https://img.shields.io/coveralls/ErikPartridge/ljus.svg?style=flat-square)]()
[![license](https://img.shields.io/github/license/ErikPartridge/ljus.svg?style=flat-square)]()
[![stability](https://img.shields.io/badge/stability-experimental-orange.svg?style=flat-square)]()

C++ web framework inspired by Laravel - in development - **do not use this in production**.

Ljus = light in Swedish (the thing that comes from the sun, not the adjective)

## Goals of the Project

To make the web blazing fast. It's a shame that web apps are rarely written with a C++ backend, and this framework tries to couple together useful libraries and some other great features to make C++ web development more accessible. 

The goal is also to bring in modern goodies into the framework! The algorithms and features that make you say cool! Part of the benefit of working with C++ is not only do we get the stability of system libraries, but we also get access to cutting edge reference specifications, usually written in C. Argon2 is therefore used for password hashing, ChaCha for Encryption: those using ljus should always be using standards as they are adopted and considered safe to use.

## Components (Updated as I go)

#### Hashing 

[Laravel version](https://laravel.com/docs/5.5/hashing)

[![stability](https://img.shields.io/badge/stability-stable-green.svg?style=flat-square)]()
[![production](https://img.shields.io/badge/production-not%20ready-red.svg?style=flat-square)]()

```c++
#include "ljus/hash/Hash.h"
```
A component to securely salt and hash most things (including passwords), using [Argon 2](https://github.com/P-H-C/phc-winner-argon2) the algorithm that won the password hashing competition (specifically, Ljus uses Argon2i). This is rapidly becoming the standard for password hashing, and is the default for LibSodium. However, Ljus uses libargon2 for implementation.


Ljus uses the reference specification as its dependency, and adds only a thin C++ layer to support strings and a function to check if the password needs rehashing. Therefore, this function should be theoretically fairly secure. However, it's still being left with do not use in production, so that it can be more widely tested.

By default, ljus uses a time cost of 3 (adjust this somewhat to your needs, 2 is the lower bar as of September 2017), parallelism of 2, and a memory cost of 1 MiB.

The api looks almost identical to Laravel's
```c++
std::string password = "passw0rd";
std::string hashed = Hash::make(password);
bool match = Hash::check(password, hashed); // true
bool needs_rehash = Hash::needs_rehash(hashed); //false
```

#### Encryption 

[Laravel version](https://laravel.com/docs/5.5/encryption)

[![stability](https://img.shields.io/badge/stability-stable-green.svg?style=flat-square)]()
[![production](https://img.shields.io/badge/production-not%20ready-red.svg?style=flat-square)]()


```c++
#include "ljus/encryption/Crypt.h"
```
A component to encrypt strings (and anything you can turn into a string) (NOT passwords), using [LibSodium's](https://libsodium.org/) implementation of the ChaCha20-Poly1305 algorithm.

This is in a fairly stable external state and has been extensively tested using [American Fuzzy Lop](https://lcamtuf.coredump.cx/afl/), however, is still not yet considered production ready.

The api looks slightly different from Laravel's, and the internals significantly so. Crypt exposes two methods:

```c++
std::string plain = "encrypt me";
std::string cipher_text = Crypt::encrypt(plain); //Base64 encoded
std::string decrypted = Crypt::decrypt(cipher_text);
bool plain.compare(decrypted) == 0; // true
```

#### Filesystem

[Laravel version](https://laravel.com/docs/5.5/filesystem)

[![stability](https://img.shields.io/badge/stability-active%20development-orange.svg?style=flat-square)]()
[![production](https://img.shields.io/badge/production-not%20ready-red.svg?style=flat-square)]()

```c++
#include "ljus/filesystem/Filesystem.h"
```

A component to manage files, mostly depends on the new C++ 17 filesystem library (the old boost filesystem). If you don't want to use the wrapper, the new C++ filesystem library is pretty darn good, but if you're coming from Laravel, this will be more familiar.

This portion of Ljus is platform dependent.

The API is identical to the Laravel one, except potentially for the hash function (still working on this one)
```c++
std::string contents = Filesystem::get(path);
Filesystem::put(path, contents);
Filesystem::exists(path); // true
```

## Dependencies
All dependencies are included in external

There are two system dependencies for Ljus, other than a relatively recent version of g++ or clang++ supporting c++17:

Recent versions of libuv libsodium:

```shell
$ add-apt-repository ppa:chris-lea/libsodium
$ apt install libsodium-dev libuv-dev
```

JSON processing is included from [nlohmann::json](https://github.com/nlohmann/json), included in external. It's (c) 2013-2017 Niels Lohmann, and licensed under the MIT license.

Password hashing is included as a git submodule from [the Argon2 Ref-Spec](https://github.com/P-H-C/phc-winner-argon2), which is in the public domain.

Web server things are included as a git submodule from [Simple Web Server](https://github.com/eidheim/Simple-Web-Server), which is under the MIT license.

Base64 supported is coupled in the project, and is a lightly modified version of [Base64](https://github.com/tkislan/base64), which is released under the MIT license.

The padding algorithms for encrypting using libsodium are primarily derived from [SodiumPP](https://github.com/rubendv/sodiumpp), although sodiumpp is not included in the project. SodiumPP is under the BSD 2 Clause.
