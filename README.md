Chip-8 Emulator 

Not completed all the way, but baseline for all functionality is written out.

Uses GoogleTest for the testing framework and SDL for the graphical display

If wanted for use, after cloning the repo into some local directory, you want to execute the following commands
in order to build the project:

cd chip8
cmake .
cmake --build .
make

You have now compiled the program! 

All of the test for the individual files in chip8/src/ should appear in chip8/

To run emulator, command is (buggy and honestly not working):

cd chip8
./chip8 roms/{romName}

Things I learned from this:
    - The idea of an emulator:
        It is really intersting to think that we can simulate hardware virtually. In this case we are simulating
        chip-8, and receiving a virtual version of a program that would have previously ran on the physical device,
        and running it on top of software. Very similar to a interpreter, but none the less still a very interesting concept.
    - the usefulness of data type sizes in c. Had I chosen uint_8 instead of a pointer to unsigned chars, my 
      implmentation could have been much more cleaner
    - SDL!
      - Pretty cool that there is a graphical library in c that also can interact with io on hardware. 
        Interesting to see how to use it in the program in order to get the visual to display at the same time
        that the program is running.
      - Also a pain in the butt because my linter does not like files that are non local 
    - Gained a better understanding of what memory allocation is and how to use it in different scenarios, 
      Also learbed when it is more useful to use a static list instead of one that is stored on the heap
      - Better undestanding of memory allocation for individual programs
      - Note: I was not freeing in this program yet so if youre looking for memleaks yes they are there...
    - How to dereference pointers:
      - Definetely saying explicitly what I want to do outloud helped me figure out where the dereference pointers come
        into play
    - Definition vs Declaratoin:
      - If you define a variable, its basically like creating a macro for the value that you assign to it, meaning that there 
        is now space in our heap that is designated to hold that one value forever
      - Delcaring a variable is basially like saying "hey this variable is going to be used throuhgout the program, and its value 
        can be defined diff in different files"
    - CMAKE
      - Might be the most beautiful tool i stumbled across for c in my entire life. Struggled with it a lot when initially dealing with
        varible scopes, as well as compilation, and finding external libraries such as googletest and SDL
    - GoogleTest
      - Might be the 2nd most beautiful tool I stumbled across for c. Testing framework, really easy to use and straight out the box with
        a little but of setup that can easily be automated.
    - Vim
      - Switched from atom to emacs (barely used it to be honest, setup failed everytime) to vim. So far I enjoy vim the most because not
        only is the installation a little bit more easier to set up than emacs, but it has a lot of powerful tools such as the different modes,
        and shortcuts available from built-in or plug-ins. 
    - This project also allowed me to realize how important consistency the lower level you get. For example, specific memory locations are 
      meant for certain aspects of programs in chip-8. I believe this is the same in cpus for their bootloader programs and etc (have to do more 
      research on that one).
    - New implementation of a stack (that might be failling rn but hey... mind your business lol)
      - Really cleaver to allocate a bunch of bits, and move a pointer that can either overwrite values or insert values into an empty space, and 
        if we run out of space in our allocated memory, we have a stack overflow, hence the name
