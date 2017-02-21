This lab attempted to prove the advantage of using a parallel implementation on a program that uses ray tracing. Since ray tracing is a very time intensive program and since different parts of the ima
ge can be worked on concurrently, the program qualifies as embarassingly parallel.

I started out the lab by making global variables for the number of threads and the color vector for each pixel in the grid. I then made for loops for creating and joining threads, and finally printing
 the image.

I made the ray trace function by sectioning off the relevant portion of code already in the main function. To parallelize the ray trace function, I passed in the thread number of each loop iteration. 
I would then split up the image into columns of equal height but varying width, using the thread number to determine the starting and ending point of each column.

I ran into a few problems with this implementation. The first of which was that when I would call the create function, I would use &t as the variable I passed. This failed since the value at &t would 
change in real time as the loop progressed which made different threads work on the same pixels. To remedy this, I made an int array in which to store the thread numbers.

The other error I ran into was that I had my ray trace function creating and freeing scenes. This caused a new scene to be made with every thread. When I would output the final image, all the scenes w
ould have trouble combining. I simply made the scene variable global and declared it in the main function to fix this.

===========
Performance
===========
The results of the program execution using 1, 2, 4, and 8 threads are shown below.

real 0m48.002s
user 0m48.009s
sys  0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real 0m24.923s
user 0m48.402s
sys  0m0.002s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real 0m16.545s
user 0m48.252s
sys  0m0.004s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real 0m10.573s
user 0m50.068s
sys  0m0.004s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
  done

The data shows that using 2 threads halves the time, using 4 threads reduces the time even more, and using 8 threads is the fastest. Thus, the program is effectively multithreaded and we have succeede
d in our parallel implementation. 
