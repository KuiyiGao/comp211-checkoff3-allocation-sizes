# Allocation size checks

COMP211 Checkoff 3 — Integer Overflows and Memory Safety.

```sh
make
./demo
make test
make sanitize
```

The demo compares 32-bit unsigned wrap with checks performed before multiplication. `checked_bytes` rejects empty requests, arithmetic overflow, and sizes above the supplied budget.

`268435457 × 16` wraps to `16` in the 32-bit example. On a 64-bit `size_t`, the same request is representable but exceeds the demo's 1,024-byte budget. Only 128 bytes are actually allocated.

Tests cover 12 boundary cases.

[Slides](https://github.com/KuiyiGao/comp211-checkoff3-allocation-sizes/blob/main/slides/Checkoff3.pptx)

[References](resources.md)
