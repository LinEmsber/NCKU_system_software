# Raytracing

---

## original:

	> make clean && make PROFILE=1 && ./raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -pg
	# Rendering scene
	Done!
	Execution time of raytracing() : 6.009028 sec


### Result of gprof:
	Flat profile:

	Each sample counts as 0.01 seconds.
	  %   cumulative   self              self     total
	 time   seconds   seconds    calls   s/call   s/call  name
	 23.30      0.61     0.61 69646433     0.00     0.00  dot_product
	 19.86      1.13     0.52 56956357     0.00     0.00  subtract_vector
	  9.74      1.39     0.26 31410180     0.00     0.00  multiply_vector
	  8.02      1.60     0.21 17836094     0.00     0.00  add_vector
	  8.02      1.81     0.21 13861875     0.00     0.00  rayRectangularIntersection
	  6.87      1.99     0.18 17821809     0.00     0.00  cross_product
	  6.87      2.17     0.18 10598450     0.00     0.00  normalize
	  5.73      2.32     0.15 13861875     0.00     0.00  raySphereIntersection
	  3.06      2.40     0.08  4620625     0.00     0.00  ray_hit_object
	  1.91      2.45     0.05        1     0.05     2.61  raytracing
	  1.53      2.49     0.04  2110576     0.00     0.00  compute_specular_diffuse
	  1.53      2.53     0.04  1048576     0.00     0.00  ray_color
	  0.95      2.55     0.03  4221152     0.00     0.00  multiply_vectors
	  0.76      2.57     0.02  1241598     0.00     0.00  refraction
	  0.38      2.58     0.01  3838091     0.00     0.00  length
	  0.38      2.59     0.01  2520791     0.00     0.00  idx_stack_top
	  0.38      2.60     0.01  1241598     0.00     0.00  protect_color_overflow
	  0.38      2.61     0.01        1     0.01     0.01  delete_sphere_list
	  0.19      2.62     0.01  2558386     0.00     0.00  idx_stack_empty
	  0.19      2.62     0.01  1204003     0.00     0.00  idx_stack_push
	  0.00      2.62     0.00  2110576     0.00     0.00  localColor
	  0.00      2.62     0.00  1241598     0.00     0.00  reflection
	  0.00      2.62     0.00  1048576     0.00     0.00  idx_stack_init
	  0.00      2.62     0.00  1048576     0.00     0.00  rayConstruction
	  0.00      2.62     0.00   113297     0.00     0.00  fresnel
	  0.00      2.62     0.00    37595     0.00     0.00  idx_stack_pop
	  0.00      2.62     0.00        3     0.00     0.00  append_rectangular
	  0.00      2.62     0.00        3     0.00     0.00  append_sphere
	  0.00      2.62     0.00        2     0.00     0.00  append_light
	  0.00      2.62     0.00        1     0.00     0.00  calculateBasisVectors
	  0.00      2.62     0.00        1     0.00     0.00  delete_light_list
	  0.00      2.62     0.00        1     0.00     0.00  delete_rectangular_list
	  0.00      2.62     0.00        1     0.00     0.00  diff_in_second
	  0.00      2.62     0.00        1     0.00     0.00  write_to_ppm


---
## Inline Function

Add __attribute__((always_inline)) to functions of files: math-toolkit.h and idx_stack.h

### Before:
	> make clean && make PROFILE=1 && ./raytracing && ll raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -pg
	# Rendering scene
	Done!
	Execution time of raytracing() : 5.976539 sec
	-rwxrwxr-x 1 jl jl 41624 Jul 20 22:58 raytracing*



### After:
	> make clean && make PROFILE=1 && ./raytracing && ll raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -pg
	# Rendering scene
	Done!
	Execution time of raytracing() : 3.388548 sec
	-rwxrwxr-x 1 jl jl 61752 Jul 20 22:59 raytracing*


---

## Loop unrolling

### Search for loop:
	> grep -rn "for" .
	./math-toolkit.h:28:    for (int i = 0; i < 3; i++)
	./math-toolkit.h:35:    for (int i = 0; i < 3; i++)
	./math-toolkit.h:42:    for (int i = 0; i < 3; i++)
	./math-toolkit.h:49:    for (int i = 0; i < 3; i++)
	./math-toolkit.h:65:    for (int i = 0; i < 3; i++)
	./raytracing.c:263:    for (rectangular_node rec = rectangulars; rec; rec = rec->next) {
	./raytracing.c:274:    for (sphere_node sphere = spheres; sphere; sphere = sphere->next) {
	./raytracing.c:340:    for (int i = 0; i < 3; i++)
	./raytracing.c:382:    for (light_node light = lights; light; light = light->next) {
	./raytracing.c:470:    for (int j = 0; j < height; j++) {
	./raytracing.c:471:        for (int i = 0; i < width; i++) {
	./raytracing.c:474:            for (int s = 0; s < SAMPLES; s++) {
	./objects.c:16:            for (tmp = *list; tmp->next; tmp = tmp->next) ; \
	./objects.c:38:    for (int i = 0; i < 4; i++) {


We use the technique of loop unrolling to reduce the branch of for loops.
We first do some effort on those for loops which are only three or four loops.

### Example:

```c
// for (int i = 0; i < 3; i++)
//     out[i] = a[i] + b[i];
out[0] = a[0] + b[0];
out[1] = a[1] + b[1];
out[2] = a[2] + b[2];
```

	> make clean && make PROFILE=1 && ./raytracing && ll raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -pg
	# Rendering scene
	Done!
	Execution time of raytracing() : 2.691450 sec
	-rwxrwxr-x 1 jl jl 60024 Jul 20 23:07 raytracing*

Not only reduce the execution time, but also reduce the size of the program.


---

## MACRO

Re-write the function into MACRO,
and delete the two not used functions: scalar_triple_product() and scalar_triple().

	> make clean && make PROFILE=1 && ./raytracing && ll raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -pg
	# Rendering scene
	Done!
	Execution time of raytracing() : 1.983881 sec
	-rwxrwxr-x 1 jl jl 49856 Jul 20 23:13 raytracing*


Not only extremely reduce the execution time, but also extremely reduce the size of the program.

---

## Gprof

Use gprof to compare the result between modified program and the original program.


	Flat profile:

	Each sample counts as 0.01 seconds.
	  %   cumulative   self              self     total
	 time   seconds   seconds    calls   s/call   s/call  name
	 37.95      0.44     0.44 13861875     0.00     0.00  rayRectangularIntersection
	 14.66      0.61     0.17 13861875     0.00     0.00  raySphereIntersection
	 13.80      0.77     0.16  2110576     0.00     0.00  compute_specular_diffuse
	 12.07      0.91     0.14  1048576     0.00     0.00  ray_color
	  9.49      1.02     0.11  4620625     0.00     0.00  ray_hit_object
	  6.04      1.09     0.07  2110576     0.00     0.00  localColor
	  3.45      1.13     0.04  1048576     0.00     0.00  rayConstruction
	  1.72      1.15     0.02        1     0.02     1.16  raytracing
	  0.86      1.16     0.01  1241598     0.00     0.00  reflection
	  0.00      1.16     0.00  1241598     0.00     0.00  protect_color_overflow
	  0.00      1.16     0.00  1241598     0.00     0.00  refraction
	  0.00      1.16     0.00   113297     0.00     0.00  fresnel
	  0.00      1.16     0.00        3     0.00     0.00  append_rectangular
	  0.00      1.16     0.00        3     0.00     0.00  append_sphere
	  0.00      1.16     0.00        2     0.00     0.00  append_light
	  0.00      1.16     0.00        1     0.00     0.00  calculateBasisVectors
	  0.00      1.16     0.00        1     0.00     0.00  delete_light_list
	  0.00      1.16     0.00        1     0.00     0.00  delete_rectangular_list
	  0.00      1.16     0.00        1     0.00     0.00  delete_sphere_list
	  0.00      1.16     0.00        1     0.00     0.00  diff_in_second
	  0.00      1.16     0.00        1     0.00     0.00  write_to_ppm


---

## openMP

	> make clean && make PROFILE=1 && ./raytracing && ll raytracing
	rm -f raytracing objects.o raytracing.o main.o use-models.h \
		out.ppm gmon.out
	cc -std=gnu99 -Wall -O0 -g -fopenmp -pg -c -o objects.o objects.c
	cc -std=gnu99 -Wall -O0 -g -fopenmp -pg -c -o raytracing.o raytracing.c
	cc -std=gnu99 -Wall -O0 -g -fopenmp -pg -c -o main.o main.c
	cc -o raytracing objects.o raytracing.o main.o -lm -lgomp -pg
	# Rendering scene
	Done!

```c
#pragma omp parallel for num_threads(64) private(stk), private(d),private(object_color)
for (int j = 0; j < height; j++) {
```


## References:
[6.39 An Inline Function is As Fast As a Macro](https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Inline.html)
[How to use lock in openMP?](https://stackoverflow.com/questions/2396430/how-to-use-lock-in-openmp)
