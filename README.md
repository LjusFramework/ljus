# Ljus (yoos)
[![Build Status](https://travis-ci.org/ErikPartridge/ljus.svg?branch=master)](https://travis-ci.org/ErikPartridge/ljus)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/9cadf04aee3f4f608796e96cf3bc3e31)](https://www.codacy.com/app/erikdevelopments/ljus?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=ErikPartridge/ljus&amp;utm_campaign=Badge_Grade)
[![Coverage Status](https://coveralls.io/repos/github/ErikPartridge/ljus/badge.svg?branch=master)](https://coveralls.io/github/ErikPartridge/ljus?branch=master)


C++ web framework inspired by Laravel - in development - **do not use this in production**.

Ljus = light in Swedish (the thing that comes from the sun, not the adjective)

## Goals of the Project

To make the web blazing fast. It's a shame that web apps are rarely written with a C++ backend, and this framework tries to couple together useful libraries and some other great features to make C++ web development more accessible. 

## Components (Updated as I go)

#### Hashing 

[Laravel version](https://laravel.com/docs/5.5/hashing)

```c++
#include ljus/hash/Hash.h
```
A component to securely salt and hash most things (including passwords), using [Argon 2](https://P-H-C/phc-winner-argon2) the algorithm that won the password hashing competition (specifically, Ljus uses Argon2i). This is rapidly becoming the standard for password hashing, and is the default for LibSodium. However, Ljus uses libargon2 for implementation.

By default, ljus uses a time cost of 4, parallelism of 2, and a memory cost of 1 MiB.

The api looks almost identical to Laravel's
```c++
std::string password = "passw0rd";
std::string hashed = Hash::make(password);
bool match = Hash::check(password, hashed); // true
bool needs_rehash = Hash::needs_rehash(hashed); //false
```

#### Encryption 

[Laravel version](https://laravel.com/docs/5.5/encryption)

```c++
#include ljus/encryption/Crypt.h
```
A component to encrypt strings (and anything you can turn into a string) (NOT passwords), using [NaCL's](https://nacl.cr.yp.to/) implementation of the XSalsa20Poly1305 algorithm.

The api looks slightly different from Laravel's, and the internals significantly so. Crypt exposes two methods:

```c++
std::string plain = "encrypt me";
std::string cipher_text = Crypt::encrypt(plain); //Base64 encoded
std::string decrypted = Crypt::decrypt(cipher_text);
bool plain.compare(decrypted) == 0; // true
```

#### Filesystem

[Laravel version](https://laravel.com/docs/5.5/filesystem)
```c++
#include ljus/filesystem/Filesystem.h
```

A component to manage files, mostly depends on the new C++ 17 filesystem library. If you don't want to use the wrapper, the new C++ filesystem library is pretty darn good, but if you're coming from Laravel, this will be more familiar.

The API is identical to the Laravel one, except that it's not a SHA-256 hash (Blake2B instead). 

```c++
std::string contents = Filesystem::get(path);
Filesystem::put(path, contents);
Filesystem::exists(path); // true
```

## Dependencies
All dependencies are included in includes/ under their respective licenses as gitsubmodules
