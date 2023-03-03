This project will be a toy browser built using C and as few dependencies as possible.

### Resources

As I go throughout this project I will be using many resources and I will try to post them all here in this readme.

- This [set of articles](https://limpet.net/mbrubeck/2014/08/08/toy-layout-engine-1.html) is what I will be looking through while creating the HTML renderer.
- Youtube [video](https://www.youtube.com/watch?v=7ZdKlyXV2vw) where the guy makes a parser in C++. This is where I found a [specification] (https://html.spec.whatwg.org/multipage/parsing.html#markup-declaration-open-state) for building an HTML parser which I will use now.

### TODO:

#### HTML parser

- Build a simple parser with basic support for things.
  - [ ] Create a tokenizer.
  - [ ] Create a parser which will take the tokens and build the DOM.

Utilities

- [ ] Create a hashtable module to convert strings in tag form to enum form in constant time.
