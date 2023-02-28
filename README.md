This project will be a toy browser built using C and as few dependencies as possible.

### Resources
As I go throughout this project I will be using many resources and I will try to post them all here in this readme.
- This [set of articles](https://limpet.net/mbrubeck/2014/08/08/toy-layout-engine-1.html) is what I will be looking through while creating the HTML renderer.

Some choices will seem odd. For example I am using POSIX functions for reading, writing, etc because I learned about it in a class and I wanted to get familiar with it. There might be other choices which probably wouldn't be the most optimal but which I make for my learning and experience. 

### TODO:
- HTML parser
  - [x] ~~Create a function which can parse through an extremely basic HTML file.~~
  - [ ] Add support for text and inline tags.
  - [ ] Add support for class, style, and other attributes

- Utilities
  - [ ] Create a hashtable module to convert strings in tag form to enum form in constant time. 
  - [ ] Make a "utils" folder with all the misc. modules I create. 
