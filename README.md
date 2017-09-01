# Ljus (yoos)
C++ web framework inspired by Laravel - in development - **do not use this in production**.

Ljus = light in Swedish

## Goals of the Project


## Components (Updated as I go)

#### Hashing (Laravel version)[https://laravel.com/docs/5.5/hashing]

```c++
#include ljus/hash/Hash.h
```
A component to securely salt and hash most things (including passwords), using (Argon 2)[https://P-H-C/phc-winner-argon2] the algorithm that won the password hashing competition (specifically, Ljus uses Argon2i). This is rapidly becoming the standard for password hashing, and is the default for LibSodium. However, Ljus uses libargon2 for implementation. 

The api looks almost identical to Laravel's
```c++
std::string password = "passw0rd";
std::string hashed = Hash::make(password);
bool match = Hash::check(password, hashed); // true
bool needs_rehash = Hash::needs_rehash(hashed); //false
```

## Dependencies
All dependencies are included in includes/ under their respective licenses as gitsubmodules
