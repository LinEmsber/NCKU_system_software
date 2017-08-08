# Compute Pi

## Introduction
Use discrete integral method to compute Pi.

Authored by Lee Chao Yuan `<charles620016@gmail.com>`

![](https://raw.githubusercontent.com/charles620016/embedded-fall2015/master/hw1-computePi/screenshot/integral.png)

## Goal
1. Use discrete integral method to compute Pi.
2. Understand how to programming language to calculate integral.
3. Understand the concept of openMP and how to use it.
4. Use SIMD instructions to achieve the optimization.

## Baseline verison

```c
double computePi_v1(size_t N)
{
    double pi = 0.0;
    double dt = 1.0 / N;                // dt = (b-a)/N, b = 1, a = 0
    for (size_t i = 0; i < N; i++) {
        double x = (double) i / N;      // x = ti = a+(b-a)*i/N = i/N
        pi += dt / (1.0 + x * x);       // integrate 1/(1+x^2), i = 0....N
    }
    return pi * 4.0;
}
```

## Reference

* [開發紀錄與效能分析](https://charles620016.hackpad.com/Charles-Week-1-kBMD0GhbC7d)
* [Leibniz formula for π](https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80)
