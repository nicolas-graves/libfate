# libfate

A simple collection of tiny libraries to patch system functions deterministically using the LD_PRELOAD trick.

## What is libfate?

libfate provides deterministic replacements for common non-deterministic system functions that can break reproducible builds. Instead of relying on complex build systems or apps or extensive patching, libfate uses the LD_PRELOAD trick to intercept system calls and return fixed, predictable values.

The library currently provides deterministic variants of:

- **Random number generation**: `getrandom()` and `/dev/urandom` reading
- **Time functions**: `clock_gettime()`
- **System information**: `sysinfo()`

The project is tiny, is **maintained** (I will happily merge PRs) but is not under active development in the sense that I don't have time to dedicate for a complete library) in the sense of having a complete list of libraries.  If I need a new function, I will add it ; but you can expect big gaps in development.

## Use-case

I originally used the openSUSE dettrace approach to make Emacs reproducible in Guix.  But when Guix switched to GCC@14, dettrace stopped working as expected.  dettrace is a complex piece of software, my need was much less heavy: I don't need to systematically patch all sources of nondeterminism, just the ones that make a process/binary unreproducible in a container/chroot.

## Usage

Each library in the collection intercepts specific system calls:

- `libfate-random.so`: Replaces random number generation with a simple LCG (Linear Congruential Generator)
- `libfate-sysinfo.so`: Returns a fixed description of system information
- `libfate-time.so`: Returns a fixed timestamp (2024-01-01 00:00:00 UTC) for time queries

Each library is self-contained and can be used independently or combined as needed.

Usage is straightforward:
```bash
LD_PRELOAD=./libfate-random.so:./libfate-sysinfo.so your-program
```

## Comparison with alternatives

| Approach             | Complexity  | Maintenance | Coverage     |
|----------------------|-------------|-------------|--------------|
| Build system patches | High        | High        | Partial      |
| Source modifications | Medium      | High        | Complete     |
| dettrace             | Medium-High | High        | Good         |
| **libfate**          | **Low**     | **Low**     | **Targeted** |

libfate fills the gap for lightweight, build-time determinism without the complexity of extensive patching.

## Testing

The package includes test programs that verify the deterministic behavior:
```bash
make check
```

This confirms that multiple runs with the same LD_PRELOAD configuration produce identical outputs.
